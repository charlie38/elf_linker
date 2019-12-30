#ifndef __READ_SEC_ELF__H__
#define __READ_SEC_ELF__H__

#include <stdint.h>
#include "elf.h"

/*Fonction permettant de lire dans le fichier au format ELF , l'entete de la table des sections */
void read_section(FILE *f, Elf32_Shdr *section_tab,uint32_t offset,uint32_t nb_sect) ;

/*Fonction permettant de remplir une strtab ( soit les noms des sections , soit les noms des symboles )*/
void read_string_table(FILE *f,Elf32_Ehdr head,Elf32_Shdr section_tab[],char strtab[],int j);


#endif