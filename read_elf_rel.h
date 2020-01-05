#ifndef __READ_ELF_REL_H__
#define __READ_ELF_REL_H__

#include "elf.h"

/*Fonction permettant de lire une entree repositionnable:
section_offset : Est l'offset du debut du fichier a la section (de type REL) correspondante*/
Elf32_Rel read_rel_entry(FILE *f,uint32_t section_offset);



/*Fonction permettant de lire une entree repositionnable avec l'addend :
section_offset : Est l'offset du debut du fichier a la section (de type RELA) correspondante*/
Elf32_Rela read_rela_entry(FILE *f,uint32_t section_offset);


#endif