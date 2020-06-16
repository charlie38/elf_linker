# Utilisations des make et des executables

## PARTIE 1

`$ make read` : même fonctionnalité que readelf

`$ ./read [nom_fichier.o] [-option]`<br>
`[nom_fichier.o]` : fichier au format ELF à lire et à afficher <br>
`[-option]` : -a (all) -h (en-tête)  -S (sections) -x (section en hexa)  -s (symboles) -r (REL)
     
## PARTIE 2

`$ make merge_bis` <br>
`$ ./merge_bis [nom_fichier1.o] [nom_fichier2.o]`<br>
Fait la fusion des sections et affiche la nouvelle table des symboles suite à la fusion du fichier 1 et du fichier 2

`$ make merge`<br>
`$ ./merge [nom_fichier1.o] [nom_fichier2.o] [nom_fichier_dest.o]`<br>
Fait la fusion entre le fichier 1 et le fichier 2 et écrit le fichier résultat dans le fichier destination 
