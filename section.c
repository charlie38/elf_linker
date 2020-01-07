#include <stdio.h>
#include <stdlib.h>
#include "elf.h"
#include "section.h" 

int create_section_header(Elf32_Shdr tab[],tab_section sections)
{
	int i ;

	for(i = 0 ; i < sections.nb ; i ++)
	{
		tab[i]=sections.T[i].header ;
	}

	return sections.nb ;
}

void creer_section(section *S, Elf32_Shdr header)
{
	S->taille = 0 ;
	S->header = header ;
}

void ajouter_char_section(section *S, char c)
{
	S->content[S->taille] = c ;
	S->taille ++ ;
}

void ajouter_str_section(section *S, char *s)
{
	int i = 0 ;

	while (s[i] != '\0')
	{
		S->content[S->taille] = s[i] ;
		S->taille ++ ;
		i ++ ; 
	}
}

void creer_tab_section(tab_section *T, int offSet)
{
	T->nb = 0 ;
}

void ajouter_tab_section(tab_section *T, section S)
{
	T->T[T->nb] = S ;
	T->nb ++ ;
}

void afficher_une_section(section S)
{
	int i ;

	for(i = 0 ; i <  S.taille ; i ++)
	{
		if(i != 0 && i % 8 == 0) printf("\n") ;
		printf("%2.2x", S.content[i]) ;
	}
}

void afficher_sections(tab_section tab)
{
	int i ;
	for (i = 0 ; i < tab.nb ; i ++) afficher_une_section(tab.T[i]); printf("\n") ;
}

void concat(section* A, section B)
{
	int i ;

	for(i = 0 ; i < B.taille ; i ++)
	{
		A->content[A->taille] = B.content[i] ;
	}

	A->taille += B.taille ;
}

section read_section(FILE* f, Elf32_Shdr header)
{
	fseek(f, header.sh_offset, SEEK_SET) ;
	int i ;
	section S ;

	for(i = 0 ; i < header.sh_size ; i++)
	{
		fread(&S.content[i], sizeof(char), 1, f) ;
	}

	S.header = header ;
	S.taille = header.sh_size ;

	return S ;
}

void modifier_section_offset(section *S, int new_offset)
{
	S->header.sh_offset = new_offset ;
}

void modifier_section_taille(section *S, int new_taille)
{
	S->header.sh_size = new_taille ;
}

void inserer_tab_section(tab_section *T, section S, int index)
{
	int i ;

	for (i = T->nb - 1 ; i > index ; i --)
	{
		T->T[i + 1] = T->T[i] ;
	}

	T->T[index] = S ;
	T->nb ++ ;
}
