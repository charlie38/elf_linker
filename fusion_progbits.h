#ifndef __FUSION_PROGBITS_H__
#define __FUSION_PROGBITS_H__

#include <stdbool.h> 
#include "section.h"

#define NB_PROGBITS_MAX 50
#define SIZE_NAME_MAX 50

/** Pour memoriser les sections concatenees **/
typedef struct
{
	char name[SIZE_NAME_MAX] ;
	int size ;
}
concat_progbits ;

typedef struct 
{
	int nb ;
	concat_progbits sections[NB_PROGBITS_MAX] ;
}
memorize_concat_progbits ;

/** Fusionne les sections progbits **/ 
void fusion_progbits(int *nb_shstr, char *shstrtab, FILE* A, FILE* B, 
		tab_section* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTabA[],char strTabB[],
		char shstrtabA[], char shstrtabB[], Elf32_Sym symtabB[],int nbsymB) ;

/** Retourne vrai si cette section a ete concatenee **/
bool is_progbits_concat(char *section_name) ;

/** Retourne la taille de la section concatenee **/ 
int get_progbits_concat_size(char *section_name) ;

/** Permet la concaténation de deux sections progbits **/
void create_progbits_concat() ;

/**Permet d'ajouter la concaténation a la table des sections finales**/
void add_progbits_concat(char *name, int size) ;

#endif
