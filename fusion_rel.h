#ifndef _FUSION_REL_H_
#define _FUSION_REL_H_

#include <elf.h>
#include <stdio.h>
#include <stdbool.h>

#include "section.h"

#define SIZE_MAX___ 50

/** Structure pour memoriser les indices des sections deja lues dans le 2e fichier **/
typedef struct 
{
    int size ;
    int elements[SIZE_MAX___] ;
}
memorize_read ;

/** Constructeur **/
void create_memorize_read(memorize_read *m) ;

/** Fonction d'ajout **/
void add_memorize_read(memorize_read *m, int element) ;

/** Retourne vrai si 'element' appartient à 'm' **/
bool is_in_memorize_read(memorize_read m, int element) ;

/** -- **/

/** Fusionne les sections 'ler' et 'lera' des deux fichiers elf contenus dans f1 et f2,
    et definis par les parametres **/
void fusion_rel(tab_section *tab, char strtab[], Elf32_Sym symtab[], int symtab2_size, 
            FILE *f1, Elf32_Ehdr header1, Elf32_Shdr sections1[], char strtab1[],
            FILE *f2, Elf32_Ehdr header2, Elf32_Shdr sections2[], char strtab2[]) ; 

/** Lit la section 'rel' ou 'rela' dans f, definie par les parametres **/
section read_rel_section(bool is_rela, FILE *f, Elf32_Shdr sectionHeader, 
		Elf32_Sym symtab[], char old_strtab[], char new_strtab[], int symtab2_size) ;

/** Retourne l'offset 'du 'rel' a la position de courante de f **/
Elf32_Addr read_rel_offset(FILE *f, bool is_rela, char *section_name) ;

/** Retourne l'info 'du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Word read_rel_info(FILE *f, char old_strtab[], char new_strtab[]) ;

/** Retourne l'addend du 'rela' a la position de courante de f */ 
Elf32_Sword read_rel_addend(FILE *f) ;

/** Modifie l'addend du 'rela' en ajoutant l'offset de la table de symboles si besoin **/
void modif_rel_addend(FILE *f, Elf32_Sword *addend, Elf32_Word rel_info, int symtab2_size) ;

/** Retourne le nouvel index associe au string donne **/
Elf32_Word find_new_sym_index(int old_index, char old_strtab[], char new_strtab[]) ;

/** Insere la section juste apres sa section 'PROGBITS' associee (si elle existe) **/
void insert_tab_section(bool is_rela, tab_section *tab, section section, char *strtab) ;

/** Retourne vrai si le fichier correspond au second **/
bool is_f2(FILE *f) ;

/** Retourne le nom de la section progbits potentiellement rattache a section_name **/
void get_progbits_name(bool is_rela, int len, char *section_name, char *progbits_name) ;

/** Retourne vrai si il existe une section progbits associee a section_name **/
bool is_progbits_associated(bool is_rela, char *progbits_name, char *section_name) ;

#endif
