#ifndef __PRINT_ELF_SYMT_H__
#define __PRINT_ELF_SYMT_H__

#include "elf.h"

/*Fonction permettant d'afficher la table des symboles*/
void afficher_symb_tab(Elf32_Sym symtab[],int nb_symb,char strsymtab[]);


#endif
