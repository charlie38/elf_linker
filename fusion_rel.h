#ifndef _FUSION_REL_H_
#define _FUSION_REL_H_

#include <elf.h>
#include <stdio.h>
#include <stdbool.h>

#include "section.h"

#define SIZE_MAX_ 50000

/** Structure pour memoriser les indices des sections deja lues dans le 2e fichier **/
typedef struct 
{
    int size ;
    int elements[] ;
}
memorize_read ;

void create_memorize_read(memorize_read *m) ;

void add_memorize_read(memorize_read *m, int element) ;

bool is_in_memorize_read(memorize_read m, int element) ;

/** Fusionne les sections 'ler' et 'lera' des deux fichiers elf contenus dans f1 et f2,
    et definis par les parametres **/
void fusion_rel(tab_section *tab, char strtab[], Elf32_Sym symtab[], int newOffSet,
            FILE *f1, Elf32_Ehdr header1, Elf32_Shdr sections1[], char strtab1[],
            FILE *f2, Elf32_Ehdr header2, Elf32_Shdr sections2[], char strtab2[]) ; 

/** Lit la section 'rel' ou 'rela' dans f, definie par les parametres **/
section read_rel_section(bool is_rela, FILE *f, int num_sec, Elf32_Shdr sections[], 
                            Elf32_Sym symtab[], char old_strtab[], char new_strtab[], int offSet) ;

/** Retourne l'offset 'du 'rel' a la position de courante de f **/
Elf32_Addr read_rel_offset(FILE *f) ;

/** Retourne l'info 'du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Word read_rel_info(FILE *f, char old_strtab[], char new_strtab[]) ;

/** Retourne l'addend du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Sword read_rel_addend(FILE *f, Elf32_Word rel_info) ;

/** Retourne le nouvel index associe au string donne **/
Elf32_Word find_new_sym_index(int old_index, char old_strtab[], char new_strtab[]) ;

/** Cherche le string associe a l'index donne **/
void get_sym_from_index(char *sym, int index, char strtab[]) ;

#endif