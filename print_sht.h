#ifndef __PRINT_SHT_H__
#define __PRINT_SHT_H__

void afficher_table_sections(Elf32_Shdr TS[], int taille,char strtab[]);

void  afficher_name(char strtab[],int i);

void afficher_section(FILE* f, Elf32_Shdr TS[], int s,char strtab[]);

#endif