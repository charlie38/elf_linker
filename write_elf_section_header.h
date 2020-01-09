#ifndef __WRITE_ELF_SECT_HEAD_H__
#define __WRITE_ELF_SECT_HEAD_H__

/**Fonction permettant d'écrire l'entête des section**/
void write_section_header(FILE *f, Elf32_Shdr section_tab[],uint32_t offset,uint32_t nb_sect);


#endif
