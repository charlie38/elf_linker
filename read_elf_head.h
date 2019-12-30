#ifndef __READ_ELF_HEAD_H__
#define __READ_ELF_HEAD_H__

#include "elf.h"

/*Fonction permettant de lire dans le fichier f toutes les informations
concernant l'entête du fichier*/

Elf32_Ehdr read_header(FILE *f) ;

#endif