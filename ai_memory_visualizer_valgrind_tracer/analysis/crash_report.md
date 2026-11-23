# Rapport de crash — crash_example.c

## Programme analysé

    1  #include <stdio.h>
    2  #include <string.h>
    3
    4  typedef struct student
    5  {
    6      char name[16];
    7      int grade;
    8  } student_t;
    9
   10  /* find_student : cherche un eleve par son nom.
   11     Retourne son adresse, ou NULL s'il n'existe pas. */
   17  student_t *find_student(student_t *list, int n, const char *name)
   18  {
   19      int i;
   20
   21      for (i = 0; i < n; i++)
   22      {
   23          if (strcmp(list[i].name, name) == 0)
   24              return (&list[i]);
   25      }
   26      return (NULL);
   27  }
   28
   29  int main(void)
   30  {
   31      student_t list[2] = {{"Ana", 15}, {"Leo", 12}};
   32      student_t *s = find_student(list, 2, "Zoe");
   33
   34      printf("note : %d\n", s->grade);
   35      return (0);
   36  }

## 1. Description du crash

Le programme s'arrête à la ligne 34, `printf("note : %d\n", s->grade);`, avant
d'avoir affiché quoi que ce soit. Le système d'exploitation le tue avec le signal
SIGSEGV (code de retour 139).

Ce qui s'est vraiment passé : le processeur a essayé de **lire 4 octets à l'adresse
`0x10`**. Cette adresse n'appartient à aucune zone mémoire du programme, donc le
système a refusé l'accès.

Preuves relevées pendant l'analyse :
- Valgrind : `Invalid read of size 4`, puis `Address 0x10 is not stack'd, malloc'd or (recently) free'd`.
- gdb : `s = 0x0` et `&s->grade = 0x10`.
- Valgrind : `0 allocs, 0 frees`, donc le programme n'utilise aucun `malloc`.

## 2. Analyse de la cause racine

Voici la chaîne complète, étape par étape, du code jusqu'à l'accès invalide :

1. **Ligne 31** : le tableau `list` contient deux élèves, `"Ana"` et `"Leo"`.
2. **Ligne 32** : le programme cherche `"Zoe"` avec `find_student`. `"Zoe"` n'est pas dans le tableau.
3. **Lignes 21 à 25** : la boucle compare `"Zoe"` avec `"Ana"`, puis avec `"Leo"`.
   Aucune comparaison ne donne 0, donc la fonction ne retourne jamais `&list[i]`.
4. **Ligne 26** : la boucle est finie, donc la fonction exécute `return (NULL)`. C'est
   son comportement normal quand l'élève est introuvable. La variable `s` de `main`
   reçoit alors la valeur **0**.
5. **Ligne 34** : `s->grade` veut dire « va à l'adresse de `s`, puis avance jusqu'au
   champ `grade` ». Dans la structure, `name` occupe 16 octets (ligne 6), donc
   `grade` commence 16 octets plus loin : `0 + 16 = 0x10`.
6. Le processeur lit 4 octets (la taille d'un `int`) à l'adresse `0x10`. Les toutes
   premières adresses de la mémoire ne sont jamais données à un programme. Le
   système détecte l'accès interdit et envoie SIGSEGV.

**Cause racine** : le programme ne vérifie pas que `find_student` a trouvé quelqu'un
avant d'utiliser son résultat. `s` vaut `NULL`, mais le code s'en sert comme s'il
pointait sur un vrai élève.

## 3. Pourquoi l'accès à la mémoire est invalide

- L'adresse `0x10` ne désigne rien de vivant : ce n'est ni une variable de la pile,
  ni un bloc du tas.
- **Pile ou tas ?**
  - La **pile** contient le pointeur qui pose problème : `s` et `list` sont des
    variables locales de `main`.
  - Le **tas** n'est pas concerné : le programme ne fait aucun `malloc`.
  - L'adresse lue, `0x10`, n'est ni dans la pile, ni dans le tas.
- **Catégorie de comportement indéfini** : **déréférencement d'un pointeur nul**
  (NULL pointer dereference). En C, utiliser un pointeur `NULL` avec `*` ou `->` est
  un comportement indéfini. Sous Linux, cela se termine presque toujours par un
  SIGSEGV, mais le langage C ne le garantit pas.

## 4. Critique des suggestions d'une IA

Une IA a été interrogée à partir du code seul, sans exécuter le programme.

| Suggestion de l'IA | Verdict | Pourquoi |
|---|---|---|
| « Le crash vient d'un accès à l'adresse 0x0. » | À moitié juste | Le pointeur `s` vaut bien 0, mais l'adresse lue est `0x10`. Le programme lit le champ `grade`, qui est 16 octets après le début de la structure : `0 + 16 = 0x10`. |
| « Il faut initialiser la liste avec `calloc` ou `memset`. » | Incorrect | `list` est déjà initialisée à la ligne 31. Le problème n'est pas son contenu : `find_student` retourne `NULL` et `s` est utilisé sans vérification. |
| « C'est un stack overflow ou un dépassement de buffer dans `strcmp`. » | Incorrect | La pile utilisée est minuscule, et `0x10` est très loin de la pile. `strcmp` lit des chaînes qui se terminent bien par `\0`. Le crash a lieu après la fin de `find_student`, donc pas dans `strcmp`. |

## 5. Correctif suggéré (optionnel, non appliqué)

Vérifier le résultat de `find_student` avant de l'utiliser :

    if (s == NULL)
    {
        printf("eleve introuvable\n");
        return (1);
    }
    printf("note : %d\n", s->grade);

Ce correctif est une **suggestion**. Le code n'a pas été modifié pour ce rapport.
