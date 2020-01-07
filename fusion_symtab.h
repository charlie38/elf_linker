#ifndef __FUSION_SYMTAB_H__
#define __FUSION_SYMTAB_H__

#include "elf.h"

#define NMAX 50000

/*Fonction permettant la fusion de la table des symboles et de la strtab ( noms des symboles )*/
int fusion_symtab(Elf32_Sym symtabA[],Elf32_Sym symtabB[],int nb_symbA,int nb_symbB,char strtabA[],char strtabB[]);

#endif