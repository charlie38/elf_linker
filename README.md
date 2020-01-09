Utilisations des make et des executables : 

PARTIE 1 : make read : Même fonctionnalité que readelf
./read [fichier.o] [-option]
Où : [fichier.o] : est le fichier au format ELF (ici .o) à lire et à afficher
     [-option] : -a (all) -h (en-tête)  -S (sections) -x (section en hexa)  -s (symboles) -r (REL)
     
PARTIE 2 :
      make merge_bis
./merge_bis [fichier1.o] [fichier2.o]
Fait la fusion des sections et affichage de la nouvelle table des symboles suite à la fusion du fichier 1 et du fichier 2

      make merge
./merge [fichier1.o] [fichier2.o] [fichierdest.o]
Fait la fusion entre le fichier1.o et le fichier2.o et écrit dans le fichiedest.o le fichier resultat
