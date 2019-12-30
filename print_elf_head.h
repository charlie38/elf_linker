#ifndef __PRINT_ELF_HEAD_H__
#define __PRINT_ELF_HEAD_H__

#include "elf.h"


/*Fonction permettant d'afficher l'ent�te d'un fichier en format ELF :
M�me affichage que la commande : readelf -h fichier.o */

void print_elf_head(Elf32_Ehdr elf) ;

#endif
