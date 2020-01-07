#ifndef SECTION_H
#define SECTION_H
#define SIZE_MAX_ 50000

#include "elf.h"

/** Structures permetant de reecrire les sections dans le
 * fichier resultat **/

typedef struct
{
	Elf32_Shdr header ;
	int offset ;
	int taille ;
	char content[SIZE_MAX_] ;
} 
section ;

typedef struct
{
	section T[SIZE_MAX_] ;
	int nb ;
}
tab_section ;

int create_section_header(Elf32_Shdr tab[],tab_section sections) ;

void creer_section(section *S, int offSet);

void ajouter_char_section(section *S, char c);

void ajouter_str_section(section *S, char *s) ;

void creer_tab_section(tab_section *T, int offSet);

void ajouter_tab_section(tab_section *T, section S);

void afficher_une_section(section S);

void afficher_sections(tab_section tab);

void concat(section* A, section B);

#endif
