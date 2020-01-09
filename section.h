#ifndef __SECTION_H__
#define __SECTION_H__
#define SIZE_MAX_ 5000
#define SIZE_MAX__ 100

#include "elf.h"

/** Structures permetant de reecrire les sections dans le
 * fichier resultat 
 * Cela a été nécessaire pour mémoriser certaines données**/

typedef struct
{
	Elf32_Shdr header ;
	int taille ; // Necessaire pour creer petit a petit le contenu (char par char)
	char content[SIZE_MAX_] ;
} 
section ;

typedef struct
{
	section T[SIZE_MAX__] ;
	int nb ;
}
tab_section ;

/**Fonction permettant de créer une section_header**/
int create_section_header(Elf32_Shdr tab[], tab_section sections) ;

/**Fonction creant une section**/
void creer_section(section *S, Elf32_Shdr header) ;

/**Fonction permettant d'ajouter un caractère dans la section**/
void ajouter_char_section(section *S, char c) ;

/**Fonction permettant d'ajouter une chaîne directement dans la section**/
void ajouter_str_section(section *S, char *s) ;

/**Fonction permettant de créer la table des sections**/
void creer_tab_section(tab_section *T) ;

/**Fonction permettant d'ajouter une section à la table**/
void ajouter_tab_section(tab_section *T, section S) ;

/**Fonction permettant d'afficher une section**/
void afficher_une_section(section S) ;

/**Fonction permettant d'afficher l'ensemble des sections**/
void afficher_sections(tab_section tab) ;

/**Fonction permettant l'écriture d'une section dans un fichier**/
void ecrire_section(FILE *f, section S) ;

/**Fonction permettant de concaténer 2 sections**/
void concat(section* A, section B) ;

/**Fonction permettant de lire une section**/
section lire_section(FILE* f, Elf32_Shdr header) ;

/**Fonction permettant de modifier l'offset d'une section**/
void modifier_section_offset(section *S, int new_offset) ;

/**Fonction permettant de modifier la taille d'une section**/
void modifier_section_taille(section *S, int new_taille) ;

/**Fonction permettant d'inserer la table des sections**/
void inserer_tab_section(tab_section *T, section S, int index) ;

/**Fonction pour avoir toutes les en-têtes de sections**/
void get_all_headers(tab_section T, Elf32_Shdr sections[]) ;

/**Fonction pour ajouter la table des symboles dans les sections**/
section symtab_to_section(Elf32_Sym symtab[], int nbsymb, int name, int flags, int offset) ;

/**Fonction pour ajouter une strtab dans les sections**/
section strtab_to_section(char* strtab, int size, int name, int flags, int offset) ;

#endif
