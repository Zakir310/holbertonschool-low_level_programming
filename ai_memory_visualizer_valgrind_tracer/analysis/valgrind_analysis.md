# Analyse Valgrind

Trois petits programmes (`programs/`) avec des erreurs de mémoire volontaires :
`leak_example.c`, `invalid_access_example.c`, `uninit_example.c`.

Commande utilisée pour chacun :

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./programme
```

Rappel (voir `memory_maps.md`) : une variable locale est sur la **pile** et
**meurt** à la fin de la fonction. Un bloc de `malloc` est sur le **tas** et
vit jusqu'au `free`.

---

## 1. `leak_example.c` — fuites de mémoire

Le programme affiche seulement `fin de main` : rien ne se voit à l'écran.

```
in use at exit: 32 bytes in 2 blocks
16 bytes in 1 blocks are definitely lost ... lose_at_return (leak_example.c:10)
16 bytes in 1 blocks are definitely lost ... overwrite_pointer (leak_example.c:20)
ERROR SUMMARY: 2 errors from 2 contexts
```

| Ligne | Avertissement | Type | Bloc concerné | Ce qui s'est passé |
|---|---|---|---|---|
| 10 | `definitely lost` | **fuite par propriété perdue** | bloc de 16 octets créé dans `lose_at_return` | `p` est sur la pile : il **meurt au `return`**. Le bloc du tas reste, mais plus aucun pointeur ne mène à lui. Impossible de faire `free`. |
| 20 | `definitely lost` | **fuite par écrasement du pointeur** | premier bloc de 16 octets de `overwrite_pointer` | À la ligne 23, `a = malloc(...)` remplace la seule adresse du premier bloc. Il devient inaccessible. Le 2ᵉ bloc est bien libéré ligne 24. |

**Vérification des chiffres** : 2 blocs perdus × 16 octets = 32 octets, et Valgrind
annonce `32 bytes in 2 blocks`. `4 allocs, 2 frees` : 3 `malloc` du programme
+ le tampon de `printf`. Seul `free(a)` (ligne 24) et ce tampon sont libérés.

---

## 2. `invalid_access_example.c` — accès invalides

Le programme ne plante pas et affiche `a[0] apres free : 10`. Il a pourtant 3 erreurs.

Le bloc de `a` fait 12 octets : seuls `a[0]`, `a[1]`, `a[2]` sont autorisés.

| Ligne | Avertissement | Type | Bloc concerné | Ce qui s'est passé |
|---|---|---|---|---|
| 13 | `Invalid write of size 4` … `0 bytes after a block of size 12` | **dépassement de tampon** (écriture hors limites) | bloc de `a` (créé ligne 6) | `a[3]` commence à l'octet 12, **juste après la fin** du bloc. On écrit dans de la mémoire qui n'est pas à `a`. |
| 16 | `Invalid read of size 4` … `inside a block of size 12 free'd` | **use-after-free** (lecture après libération) | bloc de `a`, libéré ligne 15 | `free(a)` a terminé la vie du bloc, mais `a` contient toujours l'ancienne adresse (pointeur pendant). On lit un bloc qui n'existe plus. |
| 19 | `Invalid free() / delete / delete[] / realloc()` | **double free** | bloc de `b` (créé ligne 7) | `free(b)` est fait ligne 18, puis **une deuxième fois** ligne 19 sur le même bloc. |

**Pourquoi 2 « piles d'appels » par avertissement** : la première montre où l'erreur
a lieu, la seconde montre ce qui a rendu l'adresse invalide (le `free` ou le `malloc`).

**Indice dans le résumé** : `3 allocs, 4 frees` → il y a **un `free` de trop**. C'est
le signe du double free.

**Le programme « marche » quand même** : la ligne 16 affiche `10`, l'ancienne
valeur. Le bloc libéré n'est pas effacé, donc rien ne plante. Seul Valgrind le voit.
C'est le même cas que le pointeur `h2` après `free(h1)` dans `memory_maps.md`.

---

## 3. `uninit_example.c` — mémoire non initialisée

Le programme affiche `x positif` : la valeur de `x` est du hasard (ici positive).

```
line 9  : Conditional jump ... uninitialised value(s)  — created by a stack allocation
line 12 : Conditional jump ... uninitialised value(s)  — created by a heap allocation (line 7)
```

| Ligne | Avertissement | Type | Variable concernée | Ce qui s'est passé |
|---|---|---|---|---|
| 9 | `Conditional jump depends on uninitialised value(s)` | **décision sur une valeur non initialisée** | `x` (pile, ligne 6) | `x` n'a jamais reçu de valeur. `if (x > 0)` décide à partir d'un contenu aléatoire. |
| 12 | `Conditional jump depends on uninitialised value(s)` | **décision sur une valeur non initialisée** | `*p` (bloc du tas, ligne 7) | `malloc` ne met rien dans le bloc. `if (*p == 5)` lit un contenu aléatoire. |

**À savoir** : Valgrind ne se plaint pas quand on déclare `int x;` ni quand on
fait `malloc`. Il se plaint quand la valeur **sert à décider** (un `if`).

---

## 4. Explications de l'IA vérifiées

> Avant d'exécuter, une IA a été interrogée **à partir du code seul**, sans la
> sortie de Valgrind. Voici ses erreurs.

### Erreur 1 — l'erreur serait à la déclaration `int x;` (faux)

- **Ce que l'IA a dit** : Valgrind signale `x` à la ligne où il est déclaré (ligne 6).
- **Ce que Valgrind montre** : l'erreur est à la **ligne 9**, le `if (x > 0)`.
  La déclaration n'apparaît qu'en indice d'origine (`created by a stack allocation`,
  ligne 5, début de `main`).
- **Pourquoi c'est faux** : déclarer une variable sans valeur n'est pas une erreur.
  L'erreur est de **se servir** de cette valeur.
- **Correction** : l'avertissement est placé sur la ligne qui **utilise** la
  valeur, pas sur la ligne qui la déclare.

### Erreur 2 — `a[3]` serait « 4 octets après » le bloc (faux)

- **Ce que l'IA a dit** : l'écriture `a[3]` est à `4 bytes after a block of size 12`.
- **Ce que Valgrind montre** : `0 bytes after a block of size 12`.
- **Pourquoi c'est faux** : le bloc occupe les octets 0 à 11. `a[3]` commence à
  l'octet 12, donc **0 octet après la fin**. Le « 4 » est la taille d'un `int`, pas
  la distance à la fin du bloc.
- **Correction** : la distance se compte depuis la **fin du bloc**. `a[4]` aurait été
  à `4 bytes after`.

---

## 5. À retenir

| Message de Valgrind | Cause en mémoire |
|---|---|
| `definitely lost` | le dernier pointeur vers le bloc a disparu (fin de fonction, écrasement) |
| `Invalid write/read … after a block` | indice hors des limites d'un bloc vivant |
| `Invalid read/write … free'd` | use-after-free : pointeur pendant |
| `Invalid free()` | double free |
| `Conditional jump … uninitialised` | une décision dépend d'une valeur jamais écrite |
