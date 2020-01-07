#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "elf_linker-1.0/util.h"
#include "util_bis.h"
#include "string.h"

#include "read_elf_sect.h"
#include "read_elf_head.h"
#include "read_elf_symt.h"
#include "read_elf_rel.h"
#include "print_elf_head.h"
#include "print_elf_sect.h"
#include "print_elf_symt.h"
#include "print_elf_rel.h"


#define ERROR_NB_FILES 2001 
#define ERROR_READ_FILE_1 2002 
#define ERROR_READ_FILE_2 2003

int main(int argc,char *argv[])
{
    //Gestion erreurs nombre arguments
    if (argc < 3)
	{
        fprintf(stderr, "ERREUR : utilisation \"./prog nom_fichier nom_fichier\"\n") ; 
        return ERROR_NB_FILES ;
    }
    //Ouverture fichiers
    FILE *f1, *f2 ;
    f1 = fopen(argv[1], "r") ;
    f2 = fopen(argv[2], "r") ;
    //Gestion erreurs sur les fichiers en lecture
    if (! f1) 
	{
        fprintf(stderr, "ERREUR : premier fichier non accessible en lecture\n") ; 
        return ERROR_READ_FILE_1 ;
    }
    //Gestion erreurs sur les fichiers en lecture
    if (! f2) 
	{
        fprintf(stderr, "ERREUR : second fichier non accessible en lecture\n") ; 
        return ERROR_READ_FILE_2 ;
    }
	// On fusionne les sections de type 'PROGBITS'
	fus_all_progbits(f1, f2, tab_sections, shdr1, nb_sect1, shdr2, nb_sect2, strTab) ;
	// On fusionne les tables de symboles
	fusion_symtab(symtab1, symtab2, nb_sym1, nb_sym2, strtab1, strtab2) ;
	// On fusionne les tables de reimplantation 
	fusion_rel(tab_sections, strtab, symtab, f1, header1, sections1, strtab1, 
			f2, header2, sections2, strtab2) ;
	// Libere la memoire
	fclose(f1) ;
	fclose(f2) ;

    return 0 ;
}
