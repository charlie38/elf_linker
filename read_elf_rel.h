#ifndef __READ_ELF_REL_H__
#define __READ_ELF_REL_H__

#include "elf.h"

/*Fonction permettant de lire une entr�e repositionnable:
section_offset : Est l'offset du d�but du fichier � la section (de type REL) correspondante*/
Elf32_Rel read_rel_entry(FILE *f,uint32_t section_offset);


#endif