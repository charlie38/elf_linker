#ifndef FUSION_PROGBITS_H
#define FUSION_PROGBITS_H

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
void fusion_progbits(FILE* A, FILE* B, tab_section* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTab[]) ;

/** Retourne vrai si cette section a ete concatenee **/
bool is_progbits_concat(char *section_name) ;

/** Retourne la taille de la section concatenee **/ 
int get_progbits_concat_size(char *section_name) ;

void create_progbits_concat() ;

void add_progbits_concat(char *name, int size) ;

#endif
