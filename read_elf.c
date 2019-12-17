#include <stdio.h>

#include "elf.h"


Elf32_Ehdr read_header(FILE *f)
{

    Elf32_Ehdr elf;

    fseek(f,0,SEEK_SET);

    fread(&elf.e_ident[EI_MAG0], 1, 1, f) ; 
    fread(&elf.e_ident[EI_MAG1], 1, 1, f) ; 
    fread(&elf.e_ident[EI_MAG2], 1, 1, f) ; 
    fread(&elf.e_ident[EI_MAG3], 1, 1, f) ; 
    fread(&elf.e_ident[EI_CLASS], 1, 1, f) ; 
    fread(&elf.e_ident[EI_DATA], 1, 1, f) ; 
    fread(&elf.e_ident[EI_VERSION], 1, 1, f) ; 
    fread(&elf.e_ident[EI_OSABI], 1, 1, f) ; 
    fread(&elf.e_ident[EI_ABIVERSION], 1, 1, f) ; 
    fread(&elf.e_ident[EI_PAD], 1, 1, f) ;
    fread(&elf.e_ident[10], 1, 1, f) ; 
    fread(&elf.e_ident[11], 1, 1, f) ; 
    fread(&elf.e_ident[12], 1, 1, f) ; 
    fread(&elf.e_ident[13], 1, 1, f) ;
    fread(&elf.e_ident[14], 1, 1, f) ;
    fread(&elf.e_ident[15], 1, 1, f) ; 
    fread(&elf.e_ident[16], 1, 1, f) ; 
    fread(&elf.e_type, 2, 1, f) ; 
    fread(&elf.e_machine, 2, 1, f) ; 
    fread(&elf.e_version, 4, 1, f) ; 
    fread(&elf.e_entry, 4, 1, f) ; 
    fread(&elf.e_phoff, 4, 1, f) ; 
    fread(&elf.e_shoff, 4, 1, f) ; 
    fread(&elf.e_flags, 4, 1, f) ; 
    fread(&elf.e_ehsize, 2, 1, f) ; 
    fread(&elf.e_phentsize, 2, 1, f) ; 
    fread(&elf.e_phnum, 2, 1, f) ; 
    fread(&elf.e_shentsize, 2, 1, f) ; 
    fread(&elf.e_shnum, 2, 1, f) ; 
    fread(&elf.e_shstrndx, 2, 1, f) ; 

    return elf ;
}