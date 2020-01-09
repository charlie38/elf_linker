
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
void fusion_progbits(int *nb_shstr, char *shstrtab, FILE* A, FILE* B, tab_section* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTabA[],char strTabB[],
		char shstrtabA[], char shstrtabB[], Elf32_Sym symtabB[],int nbsymB)
{
	int i, j,k, cond, decalage;
	section a,b;
	create_progbits_concat() ;
	//cond=1 => ShdrA[i] deja ajoutee a tab
	cond=0;
	decalage = 0 ;
	int presents[nbsectB]; // ( presents[i]!=-1 => ShdrB[i] a ete concatenee a la section ShdrA[presents[i]] )
	int shstrtab_size = 0 ;
	*nb_shstr = 0 ;
	//Initialisation de presents
	for(j=0;j<nbsectB;j++) presents[j]=-1;
	//Parcours toutes les sections du fichier A
	for(i=0;i<nbsectA;i++)
	{
		// On ajoute au shstrtab
		strcat2(shstrtab, get_name(shstrtabA, ShdrA[i].sh_name), shstrtab_size) ;
		shstrtab_size += strlen(get_name(shstrtabA, ShdrA[i].sh_name)) + 1 ;
		*nb_shstr = *nb_shstr + 1 ;
		//Si section est de type PROGBITS
		if (ShdrA[i].sh_type==SHT_PROGBITS)
		{
			//Parcours toutes les sections du fichier B
			for(j=0; j<nbsectB; j++)
			{
				//Si les deux sections ont le meme nom
				if( !strcmp(get_name(strTabA, ShdrA[i].sh_name), get_name(strTabB, ShdrB[j].sh_name)) )
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
					add_progbits_concat(get_name(strTabB, ShdrB[j].sh_name), b.header.sh_size) ;
                        for(k=0;k<nbsymB;k++){
                            if((symtabB[k].st_shndx == i-1))
                            symtabB[k].st_shndx = i-1;
                        }
				}
			}
		}

		//Si on n'a pas ajoute la section courante, on l'ajoute
		if(cond==0 && ShdrA[i].sh_type != SHT_SYMTAB && ShdrA[i].sh_type != SHT_STRTAB 
				&& ShdrA[i].sh_type != SHT_REL)
		{
			a = lire_section(A, ShdrA[i]) ;
			a.header.sh_offset += decalage ;
			ajouter_tab_section(tab, a) ;
		}

	}

	//Tous ceux qui ne sont pas presents dans tab, sont ajoutes a la fin
	for(j=0;j<nbsectB;j++)
	{

		//Si la section j de ShdrB n'est pas presente et est de type progbits
		if(presents[j]==-1 && ShdrB[j].sh_type != SHT_SYMTAB 
				&& ShdrB[j].sh_type != SHT_STRTAB && ShdrB[j].sh_type != SHT_REL 
				&& ShdrB[j].sh_type != SHT_NULL)
		{
			b = lire_section(B, ShdrB[j]) ;
			ajouter_tab_section(tab, b) ;
			// On ajoute au shstrtab
			strcat2(shstrtab, get_name(shstrtabB, ShdrB[i].sh_name), strlen(shstrtab)) ;
			shstrtab_size += strlen(get_name(shstrtabB, ShdrB[i].sh_name)) + 1 ;
			*nb_shstr = *nb_shstr + 1 ;
		}
	}

    for(i=0;i<nbsectA;i++){
        if(presents[i]!=-1){
            for(j=0;j<nbsymB;j++){
                //Si les deux sections ont le même nom et que le nom du symbole de B existe
                if( !strcmp(get_name(strTabA, ShdrA[i].sh_name), get_name(strTabB, ShdrB[i].sh_name)) 
						&& symtabB[j].st_name != 0 ){
                    symtabB[j].st_value = ShdrA[i].sh_size + symtabB[j].st_value;
                }
            }
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
