#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>

#include "elf_linker-1.0/util.h"
#include "util_bis.h"
#include "print_elf_sect.h"
#include "print_elf_head.h"
#include "print_elf_symt.h"
#include "print_elf_rel.h"
#include "read_elf_sect.h"
#include "read_elf_head.h"
#include "read_elf_symt.h"
#include "read_elf_rel.h"
#include "section.h"
#include "fusion_progbits.h"
#include "fusion_symtab.h"
#include "fusion_rel.h"
#include "write_elf_head.h"
#include "write_elf_section_header.h"

#define ERROR_NB_FILES 2001 
#define ERROR_READ_FILE_1 2002 
#define ERROR_READ_FILE_2 2003
#define ERROR_WRITE_FILE 2004

#define SECTION_TAB_SIZE 30 
#define SYM_TAB_SIZE 30 
#define STR_TAB_SIZE 512 

void get_header(FILE *f, Elf32_Ehdr *header)
{
	*header = read_header(f) ;
}

void get_sections(FILE *f, Elf32_Ehdr header, Elf32_Shdr *sections)
{
    read_section(f, sections, header.e_shoff, header.e_shnum) ;
}

void get_symtab(FILE *f, Elf32_Shdr sections[], int index, Elf32_Sym *symtab)
{
    read_symtab(f, symtab, sections, sections[index].sh_offset, 
			sections[index].sh_size / sizeof(Elf32_Sym)) ;
}

void get_shstrtab(FILE *f, Elf32_Ehdr header, Elf32_Shdr sections[], char *strtab)
{
    read_string_table(f, header, sections, strtab, header.e_shstrndx) ;
}

void get_strtab(FILE *f, Elf32_Ehdr header, Elf32_Shdr sections[], char *strtab)
{
    read_string_table(f, header, sections, strtab, header.e_shstrndx + 2) ;
}

void create_new_header(Elf32_Ehdr *header, Elf32_Ehdr header1, Elf32_Ehdr header2,
		tab_section tab_section)
{
	header->e_shoff = tab_section.T[tab_section.nb - 1].header.sh_offset 
		+ tab_section.T[tab_section.nb - 1].header.sh_size + 1 ;
    header->e_flags = header1.e_flags || header2.e_flags;
    header->e_shnum = tab_section.nb + 4 ;
    header->e_shstrndx = tab_section.nb ;
}

int main(int argc, char *argv[])
{
    // Declaration des variables
    FILE *f1, *f2, *f3 ;
    Elf32_Ehdr header, header1, header2 ;
    Elf32_Shdr sections[SECTION_TAB_SIZE], sections1[SECTION_TAB_SIZE], 
			   sections2[SECTION_TAB_SIZE] ;
    Elf32_Sym symtab[SYM_TAB_SIZE], symtab1[SYM_TAB_SIZE], symtab2[SYM_TAB_SIZE] ;
	char strtab[STR_TAB_SIZE], strtab1[STR_TAB_SIZE], strtab2[STR_TAB_SIZE],
			shstrtab[STR_TAB_SIZE], shstrtab1[STR_TAB_SIZE], shstrtab2[STR_TAB_SIZE] ;
	tab_section tab_section ;
	int i, taille, name, flags, offset, nb_shstr, nb_sym ;
    // Gestion erreurs nombre arguments
    if (argc < 4)
	{
        fprintf(stderr, "ERREUR : utilisation \"./prog nom_src1 nom_src2 nom_dest\"\n") ; 
        return ERROR_NB_FILES ;
    }
    // Ouverture fichiers
    f1 = fopen(argv[1], "r") ;
    f2 = fopen(argv[2], "r") ;
    f3 = fopen(argv[3], "w") ;
    // Gestion erreurs sur les fichiers en lecture
    if (! f1) 
	{
        fprintf(stderr, "ERREUR : premier fichier non accessible en lecture\n") ; 
        return ERROR_READ_FILE_1 ;
    }
    // Gestion erreurs sur les fichiers en lecture
    if (! f2) 
	{
        fprintf(stderr, "ERREUR : second fichier non accessible en lecture\n") ; 
        return ERROR_READ_FILE_2 ;
    }
    // Gestion erreurs sur le fichier en ecriture
    if (! f3) 
	{
        fprintf(stderr, "ERREUR : troisieme fichier non accessible en ecriture\n") ; 
        return ERROR_WRITE_FILE ;
    }
	// Initialisation
	creer_tab_section(&tab_section) ;
	get_header(f1, &header1) ;
	get_header(f2, &header2) ;
	get_sections(f1, header1, sections1) ;
	get_sections(f2, header2, sections2) ;
	get_symtab(f1, sections1, index_symtab(sections1), symtab1) ;
	get_symtab(f2, sections2, index_symtab(sections2), symtab2) ;
	get_strtab(f1, header1, sections1, strtab1) ;
	get_strtab(f2, header2, sections2, strtab2) ;
	get_shstrtab(f1, header1, sections1, shstrtab1) ;
	get_shstrtab(f2, header2, sections2, shstrtab2) ;
	// On fusionne les sections de type 'PROGBITS'
	fusion_progbits(&nb_shstr, shstrtab, f1, f2, &tab_section, sections1, header1.e_shnum, 
			sections2, header2.e_shnum, strtab1, strtab2, shstrtab1, shstrtab2, symtab2,  
			sizeof(sections2) / sizeof(Elf32_Sym)) ;
	// On fusionne les tables de symboles
	fusion_symtab(strtab, &nb_sym, symtab, symtab1, symtab2, index_symtab(sections1), 
			index_symtab(sections2), strtab1, strtab2) ;
	// On fusionne les tables de reimplantation 
	fusion_rel(&tab_section, strtab, symtab, nb_sym, f1, header1, sections1, strtab1, 
			f2, header2, sections2, strtab2) ;
	// On creer le nouveau header
	header = header1 ;
	create_new_header(&header, header1, header2, tab_section) ;
	// On transforme la table des sh-strings en section
	taille = nb_shstr ; 
	name = tab_section.nb ;
	flags = sections1[index_strtab(sections1)].sh_flags
		+ sections2[index_strtab(sections2)].sh_flags ; 
	offset = tab_section.T[tab_section.nb - 1].header.sh_offset 
		+ tab_section.T[tab_section.nb - 1].header.sh_size ; 
	ajouter_tab_section(&tab_section, 
			strtab_to_section(shstrtab, taille, name, flags, offset)) ;
	// On transforme la table de symboles en section
	taille = nb_sym ; 
	name = tab_section.nb ;
	flags = sections1[index_symtab(sections1)].sh_flags 
		+ sections2[index_symtab(sections2)].sh_flags ; 
	offset = tab_section.T[tab_section.nb - 1].header.sh_offset 
		+ tab_section.T[tab_section.nb - 1].header.sh_size ; 
	ajouter_tab_section(&tab_section, 
			symtab_to_section(symtab, taille, name, flags, offset)) ;
	// On transforme la table des strings en section
	taille = sizeof(strtab) / sizeof(char) ;
	name = tab_section.nb ;
	flags = sections1[index_strtab(sections1) + 2].sh_flags
		+ sections2[index_strtab(sections2) + 2].sh_flags ; 
	offset = tab_section.T[tab_section.nb - 1].header.sh_offset 
		+ tab_section.T[tab_section.nb - 1].header.sh_size ; 
	ajouter_tab_section(&tab_section, 
			strtab_to_section(strtab, taille, name, flags, offset)) ;
	// Modification du header
	header.e_shoff = tab_section.T[tab_section.nb - 1].header.sh_offset 
		+ tab_section.T[tab_section.nb - 1].header.sh_size ;
	header.e_shnum = tab_section.nb ;
	// Ecriture du header
	write_header(f3, header) ;
	// Ecriture des sections
	for (i = 0 ; i < tab_section.nb ; i ++)
	{
		ecrire_section(f3, tab_section.T[i]) ;
	}
	// Et de la table des section headers
	offset = tab_section.T[tab_section.nb - 1].header.sh_offset 
		+ tab_section.T[tab_section.nb - 1].header.sh_size ; 
	get_all_headers(tab_section, sections) ; 	
	write_section_header(f3, sections, offset, header.e_shnum) ;
	// Libere la memoire
	fclose(f1) ;
	fclose(f2) ;
	fclose(f3) ;
	// On affiche les informations
	print_elf_head(header) ;
	printf("\n") ;
	afficher_symb_tab(symtab, nb_sym, strtab)	;

    return 0 ;
}
