#include <stdio.h>

#include "elf.h"
#include "elf_linker-1.0/util.h"

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
    fread(&elf.e_type, sizeof(Elf32_Half), 1, f) ; //Lecture du type
    fread(&elf.e_machine, sizeof(Elf32_Half), 1, f) ; //Lecture de la machine
    fread(&elf.e_version, sizeof(Elf32_Word), 1, f) ; //Lecture de la version
    fread(&elf.e_entry, sizeof(Elf32_Addr), 1, f) ; //Lecture de l'entree
    fread(&elf.e_phoff, sizeof(Elf32_Off), 1, f) ; //Lecture de l'offset ph
    fread(&elf.e_shoff, sizeof(Elf32_Off), 1, f) ; //Lecture de l'offset section header
    fread(&elf.e_flags, sizeof(Elf32_Word), 1, f) ;  //Lecture des flags
    fread(&elf.e_ehsize, sizeof(Elf32_Half), 1, f) ; //Lecture de la taille de l'entête
    fread(&elf.e_phentsize, sizeof(Elf32_Half), 1, f) ;  //Lecture de la taille de ph
    fread(&elf.e_phnum, sizeof(Elf32_Half), 1, f) ;  //Lecture du nombre de ph
    fread(&elf.e_shentsize, sizeof(Elf32_Half), 1, f) ; //Lecture de la taille de section header 
    fread(&elf.e_shnum, sizeof(Elf32_Half), 1, f) ; //Lecture du nombre de sections
    fread(&elf.e_shstrndx, sizeof(Elf32_Half), 1, f) ; //Lecture de la section 

    //Inversion selon l'endianness (ici on inverse)

    elf.e_type = reverse_2(elf.e_type);
    elf.e_machine = reverse_2(elf.e_machine);
    elf.e_version = reverse_4(elf.e_version);
    elf.e_entry = reverse_4(elf.e_entry);
    elf.e_phoff = reverse_4(elf.e_phoff);
    elf.e_shoff = reverse_4(elf.e_shoff);
    elf.e_flags = reverse_4(elf.e_flags);
    elf.e_ehsize = reverse_2(elf.e_ehsize);
    elf.e_phentsize = reverse_2(elf.e_phentsize);
    elf.e_phnum = reverse_2(elf.e_phnum); 
    elf.e_shentsize = reverse_2(elf.e_shentsize);
    elf.e_shnum = reverse_2(elf.e_shnum);
    elf.e_shstrndx = reverse_2(elf.e_shstrndx);

    return elf ;
}