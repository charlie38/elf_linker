#ifndef __READ_SEC_ELF__H__
#define __READ_SEC_ELF__H__

#include <stdint.h>
#include "elf.h"

void read_section(FILE *f, Elf32_Shdr *section_tab,uint32_t offset,uint32_t size_h,uint32_t nb_sect) ;

#endif