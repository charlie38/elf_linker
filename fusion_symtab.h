#ifndef __FUSION_SYMTAB_H__
#define __FUSION_SYMTAB_H__

#include "elf.h"

#define NMAX 50000

int fusion_symtab(FILE *A,FILE *B,Elf32_Sym symtabA[],Elf32_Sym symtabB[],int nb_symbA,int nb_symbB);

#endif