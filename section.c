#include <stdio.h>
#include <stdlib.h>
#include "elf.h"
#include "section.h" 

void creer_section(section *S, int offSet)
{
	S->taille = 0 ;
	S->offset = offSet ;
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

void afficher_une_section(section S){
  int i;
  for(i=0; i< S.taille; i++){
    if(i!=0 && i%8==0) printf("\n");
    printf("%2.2x",S.content[i]);
  }
}

void afficher_sections(tab_section tab){
  int i;
  for (i = 0 ; i < tab.nb ; i++){ afficher_une_section(tab.T[i]); printf("\n"); }
}

void concat(section* A, section B){
  int i;
  for(i=0; i<B.taille; i++){
    A->content[A->taille]=B.content[i];
    A->taille++;
  }
}