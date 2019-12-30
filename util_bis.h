#ifndef __UTIL_BIS_H__
#define __UTIL_BIS_H__


/*Fonction recevant un entier n et affiche n fois un espace ( " " ) */
void espaces(int n);

/*Fonction permettant d'afficher un nom dans une table ( pour notre format ELF )
Renvoie un entier pour la tailel du mot affiché et donc peut aider pour les espaces */
int afficher_nom(char strtab[],int i);


#endif