#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "fusion_progbits.h"
#include "elf.h"
#include "util_bis.h"
#include "section.h"

#define MAX_PROGBITS 10000

memorize_concat_progbits memorize_progbits[MAX_PROGBITS] ;

// Fusion et enregistrement
void fusion_progbits(FILE* A, FILE* B, tab_section* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTab[])
{
	int i, j, cond, decalage;
	section a,b;
	create_progbits_concat() ;
	//cond=1 => ShdrA[i] deja ajoutee a tab
	cond=0;
	decalage = 0 ;
	int presents[nbsectB]; // ( presents[i]!=-1 => ShdrB[i] a ete concatenee a la section ShdrA[presents[i]] )
	//Initialisation de presents
	for(j=0;j<nbsectB;j++) presents[j]=-1;
	//Parcours toutes les sections du fichier A
	for(i=0;i<nbsectA;i++)
	{
		//Si section est de type PROGBITS
		if (ShdrA[i].sh_type==SHT_PROGBITS)
		{
			//Parcours toutes les sections du fichier B
			for(j=0; j<nbsectB; j++)
			{
				//Si les deux sections ont le meme nom
				if( !strcmp(get_name(strTab, ShdrA[i].sh_name), get_name(strTab, ShdrB[i].sh_name)) )
				{
					//Lecture et enregistrement des deux sections
					a = lire_section(A, ShdrA[i]) ;
					b = lire_section(B, ShdrB[i]) ;
					//Concatenation des deux sections
					concat(&a,b);
					a.header.sh_offset+=decalage;
					//Mise a jour du decalage d'offset des sections suivantes
					decalage+=b.header.sh_size;
					//On l'ajoute au tableau final des sections progbits
					ajouter_tab_section(tab, a) ;
					//Condition = vrai
					cond=1;
					presents[j]=i;
					// On memorise la concatenation
					add_progbits_concat(get_name(strTab, ShdrB[i].sh_name), b.header.sh_size) ;
				}
			}
		}

		//Si on n'a pas ajoute la section courante, on l'ajoute
		if(cond==0 && ShdrA[i].sh_type != SHT_SYMTAB && ShdrA[i].sh_type != SHT_STRTAB 
				&& ShdrA[i].sh_type != SHT_REL)
		{
			a = lire_section(A, ShdrA[i]) ;
			a.header.sh_offset += decalage ;
			tab->T[tab->nb]=a;
			tab->nb++;
		}

	}

	//Tous ceux qui ne sont pas presents dans tab, sont ajoutes a la fin
	for(j=0;j<nbsectB;j++)
	{

		//Si la section j de ShdrB n'est pas presente et est de type progbits
		if(presents[j]==-1 && ShdrB[i].sh_type != SHT_SYMTAB 
				&& ShdrB[i].sh_type != SHT_STRTAB && ShdrB[i].sh_type != SHT_REL 
				&& ShdrB[i].sh_type != SHT_NULL)
		{
			b = lire_section(B, ShdrB[j]) ;
			tab->T[tab->nb]=b;
			tab->nb++;
		}
	}
}

bool is_progbits_concat(char *section_name)
{
	int i ;

	for (i = 0 ; i < memorize_progbits->nb ; i ++)
	{
		if (! strcmp(memorize_progbits->sections[i].name, section_name))
		{
			return true ;
		}
	}

	return false ;
}

int get_progbits_concat_size(char *section_name)
{
	int i ;

	for (i = 0 ; i < memorize_progbits->nb ; i ++)
	{
		if (! strcmp(memorize_progbits->sections[i].name, section_name))
		{
			return memorize_progbits->sections[i].size ;
		}
	}

	return 0 ;
}

void create_progbits_concat()
{
	memorize_progbits->nb = 0 ;
}

void add_progbits_concat(char *name, int size)
{
	strcpy(memorize_progbits->sections[memorize_progbits->nb].name, name) ;
	memorize_progbits->sections[memorize_progbits->nb].size = size ;
	memorize_progbits->nb ++ ;
}
