* introduction des tests
  ----------------------

Il suffit de placer les 2 ou 3 fichiers du tests dans le bon répertoire, en faisant attention qu'ils portent tous les 3 le même nom et que leurs extensions vérifient les contraintes données plus bas.

Essayez de toujours indiquer au début du fichier un commentaire donnant l'auteur du fichier test et l'élément de spécification testé, ca simplifie la recherche des problèmes par après :)

** séries L* : 
  - fichier source : extension .input
  - fichier de résultat : extension .output

** séries P* : 
  - fichier source : extension .input
  - fichier code : extension .code
  - fichier de résultat : extension .output


Par exemple : le programme vide.
** série L0 : 
  - vide.input contient le code source LSD du programme vide
  - vide.output contient "OK" + saut de ligne

** série P0 : 
  - vide.code contient le code source LSD du programme vide
  - vide.input contient l'input requis lors de l'exécution du code compilé (ici rien, donc fichier vide)
  - vide.output contient le résultat attendu de l'exécution du code compile (donc ici rien non plus)
