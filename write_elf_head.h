#ifndef __WRITE_ELF_HEAD_H__
#define __WRITE_ELF_HEAD_H__

/**Fonction permettant d'ecrire une en-tête dans un fichier au format ELF**/
void write_header(FILE *f, Elf32_Ehdr elf);


#endif
