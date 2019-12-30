#ifndef __PRINT_ELF_SECT_H__
#define __PRINT_ELF_SECT_H__

/*Fonction permettant d'afficher l'ent�te de chaques sections (SHT)*/
void afficher_sht(Elf32_Shdr section_tab[], int taille,char strtab[]);

/*Fonction permettant d'afficher le contenu en hexad�cimal d'une section
La section sera � pr�ciser dans la fonction*/
void afficher_section_hexa(FILE* f, Elf32_Shdr section_tab[], int num_sect,char strtab[]);

#endif