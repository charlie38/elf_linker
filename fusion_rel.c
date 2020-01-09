#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "string.h"
#include "elf.h"

#include "elf_linker-1.0/util.h"
#include "util_bis.h"
#include "fusion_rel.h"
#include "fusion_progbits.h"
#include "section.h"

#define STRING_SIZE_MAX 10000

FILE *F2 ;

void fusion_rel(tab_section *tab, char strtab[], Elf32_Sym symtab[], int symtab2_size,
            FILE *f1, Elf32_Ehdr header1, Elf32_Shdr sections1[], char strtab1[],
            FILE *f2, Elf32_Ehdr header2, Elf32_Shdr sections2[], char strtab2[])
{
	// Memorise pour la fonction 'is_f2()'
	F2 = f2 ;
    int num_sec, num_sec_bis ;
    int section_type, section_type_bis ;
    memorize_read memorize_read ;
    section section, section_bis ;
    // Pour sauvegarder les sections lues dans f2
    create_memorize_read(&memorize_read) ;
    // On parcourt toutes les sections de f1
    for (num_sec = 0 ; num_sec < header1.e_shnum ; num_sec ++)
    {
        section_type = sections1[num_sec].sh_type ;
        // On lit les sections de relocation
        if (section_type == SHT_REL || section_type == SHT_RELA) 
        {
            section = read_rel_section(section_type == SHT_RELA, f1, sections1[num_sec],
					symtab, strtab1, strtab, symtab2_size) ;
            // On regarde si il en existe une de meme nom dans le deuxieme fichier     
            for (num_sec_bis = 0 ; num_sec_bis < header2.e_shnum ; num_sec_bis ++)
            {
                section_type_bis = sections2[num_sec_bis].sh_type ;
                // Si oui la lit
                if (section_type_bis == SHT_REL || section_type_bis == SHT_RELA) 
                {
					section_bis = read_rel_section(section_type_bis == SHT_RELA, f2, 
							sections2[num_sec_bis], symtab, strtab2, strtab, symtab2_size) ;          
                    // On la concatene
                    concat(&section, section_bis) ; 
                    // On memorise l'indice pour ne pas relire cette section
                    add_memorize_read(&memorize_read, num_sec_bis) ;
                    // Seulement une seule possible donc on sort
                    break ;
                }
            }
            // On sauvegarde
            insert_tab_section(section_type == SHT_RELA, tab, section, strtab) ;   
        }
    }
    // On finit en parcourant toutes les sections de f2
    for (num_sec = 0 ; num_sec < header2.e_shnum ; num_sec ++)
    {
        section_type = sections2[num_sec].sh_type ;
        // On lit les sections de relocation qui n'ont pas deja ete lues
        if ((section_type == SHT_REL || section_type == SHT_RELA)
            && ! is_in_memorize_read(memorize_read, num_sec)) 
        {
            section = read_rel_section(section_type == SHT_RELA, f2, sections2[num_sec],
					symtab, strtab2, strtab, symtab2_size) ;
            // On sauvegarde
            insert_tab_section(section_type == SHT_RELA, tab, section, strtab) ;   
        }
    }
}

/** Lit la section 'rel' ou 'rela' dans f, definie par les parametres **/
section read_rel_section(bool is_rela, FILE *f, Elf32_Shdr sectionHeader, 
		Elf32_Sym symtab[], char old_strtab[], char new_strtab[], int symtab2_size)
{
    int entry ;
    section section ;
	char tmp[20] ;
    // On creer la stucture pour accueillir la section
    creer_section(&section, sectionHeader) ; //sections1[num_sec].sh_offset) ;
    // On parcourt la section
    for (entry = 0 ; entry < sectionHeader.sh_size ; entry += 8)
    {
         // On se positionne
        fseek(f, sectionHeader.sh_offset + entry, SEEK_SET) ;
        // On recupere le 'rel'
        Elf32_Addr rel_offset = read_rel_offset(f, is_rela, 
				get_name(new_strtab, sectionHeader.sh_name)) ;
        Elf32_Word rel_info = read_rel_info(f, old_strtab, new_strtab) ;
        // Et on ecrit
		sprintf(tmp, "%d", rel_offset) ;
        ajouter_str_section(&section, tmp) ; 
		sprintf(tmp, "%d", rel_info) ;
        ajouter_str_section(&section, tmp) ; 
        // Et son addend si c'est un 'rela'
        if (is_rela) 
        {
            Elf32_Sword rel_addend = read_rel_addend(f) ;
			// Que l'on modifie si c'est un type 'SECTION'
			if (ELF32_ST_TYPE(symtab[ELF32_R_SYM(reverse_4(rel_info))].st_info) == STT_SECTION)
			{
				modif_rel_addend(f, &rel_addend, rel_info, symtab2_size) ;
			}
			// On ecrit
			sprintf(tmp, "%d", rel_addend) ;
            ajouter_str_section(&section, tmp) ; 
        }
        
    }

    return section ;
}

/** Retourne l'offset 'du 'rel' a la position de courante de f,
    en effectuant des modifications **/
Elf32_Addr read_rel_offset(FILE *f, bool is_rela, char *section_name)
{ 
    Elf32_Addr offset ;
    // On lit la variable
    fread(&offset, sizeof(Elf32_Addr), 1, f) ;
    // On change le boutisme
    offset = reverse_4(offset) ;
    // On rechange le boutisme
    offset = reverse_4(offset) ;
	// On recupere le potentiel nom de section progbits associee
	int len = strlen(section_name) ;
	char progbits_name[len] ;
	get_progbits_name(is_rela, len, section_name, progbits_name) ;
	// Si la reimplementation appartient a une section progbit concatenee en fin de section 
	if (is_f2(f) && is_progbits_concat(progbits_name))
	{
		// On additionne la taille de la section concatene avant celle la
		offset += get_progbits_concat_size(progbits_name) ;
	}

    return offset ;
}

/** Retourne l'info 'du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Word read_rel_info(FILE *f, char old_strtab[], char new_strtab[])
{
    Elf32_Word info ;
    // On lit la variable
    fread(&info, sizeof(Elf32_Word), 1, f) ;
    // On change le boutisme
    info = reverse_4(info) ;
    // On change le numero de symbole (index)
    Elf32_Word old_sym_index = ELF32_R_SYM(info) ;
    Elf32_Word new_sym_index = find_new_sym_index(old_sym_index, old_strtab, new_strtab) ;
    info &= 256 ;
    info |= new_sym_index << 8 ;
    // On rechange le boutisme
    info = reverse_4(info) ;

    return info ;
}

/** Retourne l'addend du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Sword read_rel_addend(FILE *f)
{
    Elf32_Sword addend ;
    // On lit la variable
    fread(&addend, sizeof(Elf32_Sword), 1, f) ;

    return addend ;
}

void modif_rel_addend(FILE *f, Elf32_Sword *addend, Elf32_Word rel_info, int symtab2_size)
{
    // On change le boutisme
    *addend = reverse_4(*addend) ;
	// Lorsque le 'rel' provient du second fichier
	if (is_f2(f))
	{
		// On rajoute l'offset de la concatenation des tables de symboles
		switch (ELF32_R_TYPE(reverse_4(rel_info)))        
		{
			case R_ARM_ABS32 : 
				*addend = *addend + symtab2_size ; 
				break;
			case R_ARM_CALL : 
			case R_ARM_JUMP24 : 
				*addend = *addend + symtab2_size / 4 ; 
		}
	}
    // On rechange le boutisme
    *addend = reverse_4(*addend) ;
}

/** Retourne le nouvel index associe au string donne **/
Elf32_Word find_new_sym_index(int old_index, char old_strtab[], char new_strtab[])
{
    char *sym ;
    int i = 0, j, last_i ;
    int sym_size ;
    // On recupere le string
    sym = get_name(old_strtab, old_index) ;
    sym_size = strlen(sym) ;
    // Puis on cherche dans la nouvelle table jusqu'a retrouver le nouvel indice de depart
    while (i < strlen(new_strtab))
    {
        last_i = i ;

        for (j = 0 ; j < sym_size && sym[j] == new_strtab[i] ; j ++)
        {
            if (j == sym_size - 1)
            {
                return last_i ;
            }

            i ++ ;
        }

		i = last_i + 1 ;
    }

    return 0 ;
}

/** Struct **/

void create_memorize_read(memorize_read *m)
{
    m->size = 0 ;
}

void add_memorize_read(memorize_read *m, int element)
{
    m->elements[m->size] = element ;
    m->size ++ ;
}

bool is_in_memorize_read(memorize_read m, int element)
{
    int i ;

    for (i = 0 ; i < m.size ; i ++)
    {
        if (m.elements[i] == element)
        {
            return true ;
        }
    } 

    return false ;
}

void insert_tab_section(bool is_rela, tab_section *tab, section section, char *strtab)
{
	int i, j ;
	// On parcourt toutes les sections
	for (i = 0 ; i < tab->nb ; i ++)
	{
		// Pour trouver celle de type 'PROGBITS' associee
		if (is_progbits_associated(is_rela,
					get_name(strtab, tab->T[i].header.sh_name), 
					get_name(strtab, section.header.sh_name)))
		{
			// Puis on insere juste apres celle la notre section
			inserer_tab_section(tab, section, i + 1) ;
			// Et on augmente l'offset de toutes les sections suivantes avec la taille
			// de cette section
			for (j = i + 2 ; j < tab->nb ; j ++)
			{
				modifier_section_offset(&(tab->T[j]), tab->T[j].header.sh_offset 
						+ section.header.sh_size) ;
			}
			// Une seule section a ajouter donc on sort
			return ;
		}
	}
	// Aucune section de type 'PROGBITS' associee ; on ajoute a la fin
	ajouter_tab_section(tab, section) ;
}

bool is_f2(FILE *f)
{
	return f == F2 ;
}

void get_progbits_name(bool is_rela, int len, char *section_name, char *progbits_name)
{
	int i ;

	for (i = 0 ; i <= len ; i ++)
	{
		progbits_name[i] = section_name[i + 4 + ((is_rela) ? 1 : 0)] ;
	}
}

bool is_progbits_associated(bool is_rela, char *progbits_name, char *section_name)
{
	int len = strlen(section_name) ;
	char name[len] ;

	get_progbits_name(is_rela, len, section_name, progbits_name) ;

	return ! strcmp(progbits_name, name) ;
}
