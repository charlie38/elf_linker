#ifndef __PRINT_ELF_REL_H__
#define __PRINT_ELF_REL_H__

#include "elf.h"

/*Fonction permettant d'afficher toutes les relocations pour chaque sections
Même affichage que la fonction : readelf -r fichier.o*/
void afficher_rel(FILE *f,Elf32_Ehdr head,Elf32_Shdr section_tab[],char strtab[],Elf32_Sym symtab[]);

#endif