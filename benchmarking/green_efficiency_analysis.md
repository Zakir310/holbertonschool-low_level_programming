# Analyse de l'efficacité énergétique

## Méthodologie de mesure

J'ai utilisé trois programmes : `baseline_loop.c`, `comparison_algorithms.c` et `instrumentation_lab.c`. Je les ai compilés avec `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`. Pour mesurer le temps, j'ai utilisé la fonction `clock()`. Elle donne le temps utilisé par le processeur. Je fais la différence entre deux appels à `clock()`, puis je divise par `CLOCKS_PER_SEC` pour avoir des secondes. J'ai lancé chaque programme trois fois de suite, sur la même machine. Ensuite, j'ai calculé la moyenne des trois temps. Toutes les sorties sont enregistrées dans les fichiers `-metrics.md`.

## Différences de performances observées

Pour `baseline_loop`, la boucle de 100 millions de tours a pris en moyenne [B_MOY] secondes. Les trois temps étaient proches, mais pas identiques.

Pour `comparison_algorithms`, l'algorithme naïf a pris en moyenne [A_MOY] secondes. L'algorithme single-pass a pris en moyenne [S_MOY] secondes. Le naïf est donc environ [RATIO] fois plus lent. La raison est simple : le naïf a deux boucles l'une dans l'autre. Il fait environ 1,25 milliard de vérifications. Le single-pass n'a qu'une seule boucle. Il fait seulement 50 000 vérifications.

Pour `instrumentation_lab`, j'ai obtenu TOTAL = [T] secondes, BUILD_DATA = [BD] secondes, PROCESS = [P] secondes et REDUCE = [R] secondes. Le TOTAL est bien plus grand ou égal à chaque phase.

## Relation entre l'autonomie et la consommation d'énergie

Un processeur consomme de l'énergie tant qu'il travaille. On peut dire que l'énergie est à peu près égale à la puissance multipliée par le temps. Donc, sur la même machine, un programme qui dure plus longtemps consomme plus d'énergie. Dans mes mesures, le naïf fait travailler le processeur environ [RATIO] fois plus longtemps que le single-pass, pour la même tâche : compter les nombres pairs du même tableau. Sur un ordinateur portable ou un téléphone, cela veut dire que la batterie se vide plus vite. L'autonomie de l'appareil est donc plus faible.

## Limites de l'expérience

Je n'ai pas mesuré l'énergie directement. J'ai seulement mesuré le temps, et j'en ai déduit l'énergie. De plus, `clock()` n'est pas très précis pour les temps très courts, comme ceux du single-pass. J'ai aussi fait seulement trois exécutions, sur une seule machine. D'autres programmes tournaient peut-être en même temps, ce qui peut expliquer les petites différences entre les runs.

## À retenir en ingénierie pratique

Le choix de l'algorithme est très important. Avec les mêmes données et la même machine, le naïf est [RATIO] fois plus lent. Il faut toujours mesurer avant d'optimiser, pour savoir quelle partie du programme prend le plus de temps. Il faut aussi mesurer plusieurs fois et faire une moyenne, car un seul résultat n'est pas fiable. Enfin, un code plus rapide consomme moins d'énergie. Écrire du code efficace, c'est donc aussi écrire du code plus écologique.
