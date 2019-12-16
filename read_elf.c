#include <stdio.h>
#include <elf.h>


Elf32_Ehdr read_header(FILE *f)
{
    Elf32_Ehdr elf = malloc(sizeof(Elf32_Ehdr)) ;

    fread(&elf.e_ident[EI_MAG0], 1, 1, f) ; 
    fread(&elf.e_ident[EI_MAG1], 1, 1, f) ; 
    fread(&elf.e_ident[EI_MAG2], 1, 1, f) ; 
    fread(&elf.e_ident[EI_MAG3], 1, 1, f) ; 
    fread(&elf.e_ident[EI_CLASS], 1, 1, f) ; 
    fread(&elf.e_ident[EI_DATA], 1, 1, f) ; 
    fread(&elf.e_ident[EI_VERSION], 1, 1, f) ; 
    fread(&elf.e_ident[EI_PAD], 1, 1, f) ; 
    fread(&elf.e_ident[EI_NIDENT], 1, 1, f) ; 
    fread(&elf.e_type, 1, 1, f) ; 
    fread(&elf.e_machine, 1, 1, f) ; 
    fread(&elf.e_version, 1, 1, f) ; 
    fread(&elf.e_entry, 1, 1, f) ; 
    fread(&elf.e_phoff, 1, 1, f) ; 
    fread(&elf.e_shoff, 1, 1, f) ; 
    fread(&elf.e_flags, 1, 1, f) ; 
    fread(&elf.e_ehsize, 1, 1, f) ; 
    fread(&elf.e_phentsize, 1, 1, f) ; 
    fread(&elf.e_phnum, 1, 1, f) ; 
    fread(&elf.e_shentsize, 1, 1, f) ; 
    fread(&elf.e_shnum, 1, 1, f) ; 
    fread(&elf.e_shstrndx, 1, 1, f) ; 

    return elf ;
}
