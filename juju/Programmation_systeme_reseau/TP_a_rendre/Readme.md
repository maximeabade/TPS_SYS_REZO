# Devoir à rendre 

# Rappel du problème

Une manière de déterminer les nombres premiers dans un intervalle est de découper l’espace derecherche en plusieurs sous-intervalles et d’affecter la recherche dans chaque intervalle à unprocessus créé par le père. 

Ainsi si on découpe l’intervalle [1, N ] en p sous-intervalles, le processuspère lance p fils et le fils k recherche l’intervalle [kN/p + 1, (k + 1)N/p], k = 0, ..., p−1. Cette technique permet, si on dispose d’une machine équipée de p processeurs, de paralléliser larecherche (et d’essayer de retourner le résultat p fois plus vite). 

Elle a cependant l’inconvénientd’affecter des espaces de recherche dont les temps d’exploration sont inégaux. Ainsi le processus 0 terminera la recherche sur [1, N/p] bien avant le processus p − 1. 

Il (et donc un des processeurs dela machine) sera donc oisif jusqu’à la fin du programme. La charge de travail entre les processus (et donc les processeurs) est inégalement repartie.Une solution pour repartir la charge de travail, consiste a utiliser un ”pool” de p processustravailleurs à qui un processus maitre affecte successivement des travaux de recherche de nombrespremiers dans de petits intervalles (taille T << N/p). 
Quand un travailleur fini sa recherche, le maitre lui affecte la recherche dans un intervalle encoreinexploré. 

On désire mettre en place cette solution avec un programme en langage C. On pourraéventuellement demander à l’utilisateur la taille N et le nombre de processus p.

# Description de la solution

Pour répondre au problème, j'ai suivi les consignes données dans le sujet.

Le maitre doit être le processus père; les p travailleurs des fils créés par le père. Pour dialoguer avec les fils, le père utilise un tube différent pour chaque fils. Pour dialoguer avec le père, les fils
utilisent un tube commun.

Le dialogue sera défini comme le suivant :
- le père passe à un fils les bornes de l’intervalle de recherche par le tube associé au fils.
- le père passe deux entiers de valeur 0 pour indiquer au fils que ces travaux sont terminés et qu’il
peut se terminer.
- le fils renvoie au père les nombres premiers trouvés et 0 pour indiquer qu’il a terminé
l’exploration de l’intervalle.
- pour s’identifier auprès du père, un fils précède chaque nombre envoyé par son numéro.

Les particularités de ma solutions sont :
- L'utilisation d'un tableau pour stocker les tubes de chaque fils
- Les informations transmises par les tubes sont sous forme de paires. En effet, il faut soit envoyer les deux bornes d'un intervalle ou, un id de processus suivi d'un nombre ou alors la paire [0,0]. J'ai donc développé les fonctions `write_pair_to_pipe` et `read_pair_from_buf` qui permettent de faire la conversion entre deux entiers et une chaine de caractère.


# Compilation et exécution

Pour compiler le programme, il faut entrer cette commende dans un terminal ouvert à la racine du projet :
```
gcc -Wall -Wextra -o myprogram prog.c
```
Pour exécuter le programme, il faut entrer la commande suivante :
```
./myprogram
```

# Utilisation 

Lorsque vous exécuter le programme, il y aura deux interractions avec l'utilisateur.

Premièrement il faudra saisir la borne supérieur de l'intervalle de recherche : N. (N > 1)

Ensuite il faudra saisir le nombre de processus fils qui exécuteront la taĉhe : p. (p >= 1 et p <= N / T_DIV)