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

void creer_tab_section(tab_section *T)
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

	for (i = 0 ; i < tab.nb ; i ++) 
	{
		afficher_une_section(tab.T[i]); 
		printf("\n") ;
	}
}

void ecrire_section(FILE *f, section S)
{
	int i ;

	for (i = 0 ; i < S.taille ; i ++)
	{
		fprintf(f, "%c", S.content[i]) ;
	}
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

section lire_section(FILE* f, Elf32_Shdr header)
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

void lire_mot(section* S, int word)
{
    S->content[S->header.sh_size]=(char) word>>24;
    S->header.sh_size++;
    S->content[S->header.sh_size]=(char) word>>16;
    S->header.sh_size++;
    S->content[S->header.sh_size]=(char) word>>8;
    S->header.sh_size++;
    S->content[S->header.sh_size]=(char) word;
    S->header.sh_size++;
}

void lire_symbole(section* S, Elf32_Sym Sym)
{
    //Ajouter st_name, st_value et st_size a la section
    lire_mot(S, Sym.st_name);
    lire_mot(S, Sym.st_value);
    lire_mot(S, Sym.st_size);
    //Ajouter st_info a la section
    S->content[S->header.sh_size]= (char) Sym.st_info;
    S->header.sh_size++;
    //Ajouter st_other a la section
    S->content[S->header.sh_size]=(char) Sym.st_other;
    S->header.sh_size++;
    //Ajouter st_shndx a la section
    S->content[S->header.sh_size]=(char) Sym.st_shndx>>8;
    S->header.sh_size++;
    S->content[S->header.sh_size]=(char) Sym.st_shndx;
    S->header.sh_size++;

}

section symtab_to_section(Elf32_Sym symtab[], int nbsymb, int name, int flags, int offset)
{
    section S ;
    int i ;
    //Remplir le header de la section
    S.header.sh_name = name;
    S.header.sh_type = SHT_SYMTAB;
    S.header.sh_flags = flags;
    S.header.sh_offset = offset ;
    S.header.sh_size = 0; //taille initialisee a 0
    S.header.sh_addr = 0;
    S.header.sh_link = SHT_SYMTAB;
    S.header.sh_info = SHT_SYMTAB;
    S.header.sh_addralign = 0;
    S.header.sh_entsize = sizeof(Elf32_Sym);
    //Remplir la section avec les symboles
    for(i = 0 ; i < nbsymb ; i ++)
	{
        lire_symbole(&S, symtab[i]) ;
    }

    S.taille = S.header.sh_size ;

    return S ;

}

section strtab_to_section(char* strtab, int size, int name, int flags, int offset)
{
    section S ;
    int i ;
    //Remplir le header de la section
    S.header.sh_name = name;
    S.header.sh_type = SHT_STRTAB;
    S.header.sh_flags = flags;
    S.header.sh_offset = offset;
    S.header.sh_size = sizeof(char)*size; //taille initialisee a 0
    S.header.sh_addr = 0;
    S.header.sh_link = SHN_UNDEF;
    S.header.sh_info = SHN_UNDEF;
    S.header.sh_addralign = 0;
    S.header.sh_entsize = 0;
    //Remplir la section
    for(i = 0 ; i < size ; i ++)
	{
        S.content[S.taille]=strtab[i] ;
        S.taille ++ ;
    }

    return S ;
}

void get_all_headers(tab_section T, Elf32_Shdr sections[])
{
	int i ;

	for (i = 0 ; i < T.nb ; i ++)
	{
		sections[i] = T.T[i].header ;
	}
}
