#ifndef __READ_ELF_SYMT_H__
#define __READ_ELF_SYMT_H__

#include "elf.h"

/*Fonction permettant de renvoyer le numéro de la section : table des strings*/
int index_strtab(Elf32_Shdr section_tab[]) ;

/*Fonction permettant de renvoyer le numéro de la section : table des symboles*/
int index_symtab(Elf32_Shdr section_tab[]);

/*Fonction permettant de lire la table des symboles*/
void read_symtab(FILE *f, Elf32_Sym symtab[],Elf32_Shdr section_tab[],uint32_t offset,uint32_t nb_symb);

#endif
