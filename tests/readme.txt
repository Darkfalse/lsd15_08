* introduction des tests
  ----------------------

Il suffit de placer les 2 ou 3 fichiers du tests dans le bon r�pertoire, en faisant attention qu'ils portent tous les 3 le m�me nom et que leurs extensions v�rifient les contraintes donn�es plus bas.

Essayez de toujours indiquer au d�but du fichier un commentaire donnant l'auteur du fichier test et l'�l�ment de sp�cification test�, ca simplifie la recherche des probl�mes par apr�s :)

** s�ries L* : 
  - fichier source : extension .input
  - fichier de r�sultat : extension .output

** s�ries P* : 
  - fichier source : extension .input
  - fichier code : extension .code
  - fichier de r�sultat : extension .output


Par exemple : le programme vide.
** s�rie L0 : 
  - vide.input contient le code source LSD du programme vide
  - vide.output contient "OK" + saut de ligne

** s�rie P0 : 
  - vide.code contient le code source LSD du programme vide
  - vide.input contient l'input requis lors de l'ex�cution du code compil� (ici rien, donc fichier vide)
  - vide.output contient le r�sultat attendu de l'ex�cution du code compile (donc ici rien non plus)
