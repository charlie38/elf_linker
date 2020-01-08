#ifndef WRITE_ELF_SECT_HEAD_H
#define WRITE_ELF_SECT_HEAD_H

void write_section_header(FILE *f, Elf32_Shdr section_tab[],uint32_t offset,uint32_t nb_sect);


#endif
