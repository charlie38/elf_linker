#ifndef __UTIL_BIS_H__
#define __UTIL_BIS_H__

#include "elf.h"

/*Fonction renvoyant le maximum entre a et b*/
int maxi(int a,int b);

/*Fonction recevant un entier n et affiche n fois un espace ( " " ) */
void espaces(int n);

/*Fonction permettant d'afficher un nom dans une table ( pour notre format ELF )
Renvoie un entier pour la taille du mot affiche et donc peut aider pour les espaces */
int afficher_nom(char strtab[],int i);

/*Fonction permettant de recuperer le nom associe au symbole*/
char *get_name(char strtab[],int i);

/*Fonction permettant de concaténer 2 chaînes de caractères , sans enlever le '\0'*/
int strcat2(char *dest,char *src,int taille);

#endif