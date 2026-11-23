# Memory maps — Tâche 0

Programmes analysés (dans `programs/`) : `stack_example.c`, `aliasing_example.c`,
`heap_example.c`. Compilés avec `make` (`-Wall -Wextra -Werror -pedantic`) et
lancés normalement, sans Valgrind. Les adresses sont celles d'une vraie
exécution ; elles changent à chaque lancement (ASLR), seules les relations entre
elles comptent.

| | **Pile (stack)** | **Tas (heap)** |
|---|---|---|
| Contient | variables locales, paramètres | blocs obtenus avec `malloc` / `realloc` |
| Adresses vues | `0x7ff…` | `0x55…` / `0x56…` |
| Disparaît | quand la fonction se termine | au `free` |

---

## 1. `stack_example.c` — appels, retours, récursivité

Sortie réelle :

```
[add]  &a=0x7ffd7618840c &b=0x7ffd76188408 &sum=0x7ffd76188414
[fact] entree n=3 &n=0x7ffd761883fc
[fact] entree n=2 &n=0x7ffd761883bc
[fact] entree n=1 &n=0x7ffd7618837c
[main] &x=0x7ffd76188438 &y=0x7ffd7618843c &f=0x7ffd76188440
[main] ancienne adresse de sum = 0x7ffd76188414
```

| Étape | Pile | Tas |
|---|---|---|
| 1. début de `main` | `x=5` ; `y`, `f` pas encore affectés | vide |
| 2. appel `add(5, 3)` | + cadre de `add` : `a=5`, `b=3`, `sum=8` (`sum` à `…8414`) | vide |
| 3. retour de `add` | cadre de `add` **détruit** ; `y=8` (valeur copiée) | vide |
| 4. appel `fact(3)` | + cadre : `n=3` (`…83fc`), `result` | vide |
| 5. `fact(2)` puis `fact(1)` | + 2 cadres : `n=2` (`…83bc`), `n=1` (`…837c`) | vide |
| 6. retours de `fact` | cadres détruits dans l'ordre 1, 2, 3 ; `f=6` | vide |
| 7. fin de `main` | tout détruit | — |

- **Récursivité** : chaque appel a son **propre** `n` et son propre `result`.
  Les `n` sont à `0x40` (64 octets) d'écart, de plus en plus bas. Au plus
  profond, **3 cadres `fact` existent en même temps**.
- **Alias** : aucun. `y = add(...)` copie la **valeur** 8, `y` n'est pas lié à `sum`.
- **Tas** : le programme n'appelle jamais `malloc`. (Valgrind note 1 bloc de
  4096 octets : c'est le tampon de `printf`, alloué par la bibliothèque.)

**Durées de vie**

| Variable | Naît | Meurt |
|---|---|---|
| `x`, `y`, `f` | début de `main` | fin de `main` |
| `a`, `b`, `sum` | appel de `add` | retour de `add` |
| `n`, `result` (un par appel) | appel de `fact` | retour de ce `fact` |

---

## 2. `aliasing_example.c` — plusieurs pointeurs vers le même objet

Sortie réelle :

```
[main] &x=0x7ffcb62c4228 &y=0x7ffcb62c422c
[main] p=0x7ffcb62c4228 q=0x7ffcb62c4228
[main] x=11 *p=11 (meme variable)
[add_one] p=0x7ffcb62c4228 (copie de l'adresse recue)
[main] x=12
[main] p=0x7ffcb62c422c (maintenant y) q=0x7ffcb62c4228 (toujours x)
[main] h1=0x55c713a772a0 h2=0x55c713a772a0 *h2=7
[main] apres free : h1=(nil), h2 contenait 0x55c713a772a0 (pendant)
```

| Étape | Pile (`main`) | Tas |
|---|---|---|
| 1. déclarations | `x=10`, `y=20` | — |
| 2. `p = &x; q = p;` | `p=…4228`, `q=…4228` → **p, q et `&x`** : même adresse | — |
| 3. `*q = 11` | `x=11` (donc `*p` vaut 11 aussi) | — |
| 4. `add_one(&x)` | cadre de `add_one` : son `p=…4228` (copie de l'adresse) ; `*p = *p + 1` → `x=12` ; cadre détruit au retour | — |
| 5. `p = &y` | `p=…422c` ; **`q` reste `…4228`** (sur `x`) | — |
| 6. `h1 = malloc(4)`, `h2 = h1` | `h1=…72a0`, `h2=…72a0` | bloc `…72a0` |
| 7. `*h1 = 7` | — | bloc = 7 (`*h2` vaut 7) |
| 8. `free(h1); h1 = NULL;` | `h1=NULL`, **`h2=…72a0` inchangé** | bloc **libéré** |

**Ensembles d'alias**
- Sur la pile : `{ &x, p (jusqu'à l'étape 5), q }`. Après l'étape 5, `p` quitte
  le groupe et pointe sur `y` ; `q` reste sur `x`.
- Sur le tas : `{ h1, h2 }` (même bloc) jusqu'au `free`.
- Dans `add_one`, le paramètre `p` est une **copie** de l'adresse de `x`, donc
  un alias de `x` pendant l'appel seulement.

**Après l'étape 8** : le bloc n'existe plus, mais `h2` contient encore son
adresse (pointeur **pendant**). `h2` ne doit plus être lu ni écrit.

**Durées de vie**
- `x`, `y`, `p`, `q`, `h1`, `h2` : toute la durée de `main`.
- paramètre `p` de `add_one` : le temps de l'appel.
- bloc de 4 octets : de `malloc` à `free(h1)`.

---

## 3. `heap_example.c` — propriété d'un bloc et `realloc`

Sortie réelle :

```
[make_copy] &copy=0x7ffd26444e90 copy=0x561f6be862a0
[main] &name=0x7ffd26444eb8 name=0x561f6be862a0 ("abc")
[main] realloc : avant=0x561f6be862a0 apres=0x561f6be872d0 (deplace)
[main] contenu garde : "abc"
```

| Étape | Pile | Tas |
|---|---|---|
| 1. appel `make_copy("abc")` | cadre : `s`, `copy` (`…4e90`) | — |
| 2. `malloc(4)` + `strcpy` | `copy=…862a0` | bloc A `…862a0` = `"abc"` |
| 3. 1er `printf` | — | + bloc de 4096 octets (tampon de `stdout`), juste après A |
| 4. retour dans `main` | cadre de `make_copy` **détruit** (`copy` meurt) ; `name=…862a0` | A **toujours vivant** |
| 5. `realloc(name, 100)` | `name=…872d0` | A libéré ; bloc B `…872d0` contient `"abc"` |
| 6. `free(name)` | `name=NULL` | B libéré |

- **Propriété** : `make_copy` crée le bloc, mais c'est **`main` qui en devient
  propriétaire** et qui doit le libérer. La variable `copy` ne suffit pas à
  garder le bloc en vie : c'est seulement sa valeur (l'adresse) qui est copiée.
- **Pourquoi `realloc` déplace** : le tampon de `stdout` (étape 3, vérifié
  avec gdb) occupe l'espace juste derrière A. A ne peut pas grandir sur place,
  donc `realloc` prend un nouvel espace après ce tampon, copie `"abc"` et libère A.
- **Alias** : `name` et l'ancienne adresse `avant` ne sont plus alias après
  l'étape 5. C'est pour cela que `avant` est gardé comme **nombre** (`unsigned
  long`) et non comme pointeur.

**Durées de vie** : `copy` = durée de `make_copy` ; `name` = durée de `main` ;
bloc A = de `malloc` à `realloc` ; bloc B = de `realloc` à `free(name)`.

---

## 4. Erreurs de l'IA

> La première carte a été faite par une IA **en lisant seulement le code, avant
> l'exécution**. Puis vérifiée avec les sorties, gdb et le compilateur.

### Erreur 1 — la mémoire d'un cadre détruit « ne sert plus » (faux)

- **Ce que l'IA a dit** : après le retour de `add()`, `sum` est détruite et son
  adresse n'est plus utilisée ; les appels suivants « seront ailleurs ».
- **Pourquoi c'est faux** : `sum` est bien détruite (sa durée de vie est finie),
  mais **sa place sur la pile est réutilisée**. Avec gdb : `sum` est à
  `…7334` ; pendant `fact(3)`, `rsp=…7310` et `rbp=…7340`. L'ancienne adresse
  de `sum` se trouve donc **à l'intérieur du cadre de `fact(3)`** (entre `rsp`
  et `rbp`), à `0x18` octets au-dessus de `n`. C'est ce que montre la sortie :
  `ancienne adresse de sum = …8414` alors que `&n` de `fact(3)` vaut `…83fc`.
- **Correction** : « détruite » veut dire que la variable n'existe plus pour le
  programme, pas que la mémoire est protégée. Ce même emplacement sert ensuite
  à un autre appel. Lire l'ancienne adresse de `sum` donnerait une valeur
  d'un autre cadre, d'où l'intérêt de ne jamais garder un pointeur vers une
  variable locale après le `return`.

### Erreur 2 — `h1 = NULL` rend aussi `h2` sûr (faux)

- **Ce que l'IA a dit** : après `free(h1); h1 = NULL;`, `h2` est NULL (ou
  invalide « proprement »).
- **Pourquoi c'est faux** : `h1` et `h2` sont deux **variables différentes**.
  `h1 = NULL` ne change que `h1`. La sortie montre `h2 contenait
  0x55c713a772a0`, l'adresse du bloc libéré.
- **Correction** : `h2` est un pointeur **pendant**. Il faut aussi le mettre à
  `NULL`, ou ne plus s'en servir.

### Approximation 3 — `realloc` (résultat juste, raison absente)

- L'IA a prévu que `realloc` déplace le bloc : exact. Elle n'a pas vu **pourquoi** :
  elle ignorait le tampon de `stdout` de 4096 octets alloué par `printf` juste
  derrière le bloc. Test fait : en désactivant ce tampon (`setvbuf(stdout, NULL,
  _IONBF, 0)`), `realloc` garde la **même adresse**. Ajouté dans la carte
  (étape 3 de la section 3).

### Aussi corrigé en route (compilateur)

En écrivant les programmes, la première version de `aliasing_example.c` lisait
`h2` après `free`. gcc l'a refusé :
`error: pointer 'h2' used after 'free' [-Werror=use-after-free]`.
Correction : copier l'adresse dans un nombre (`h2_avant`) avant le `free`.
