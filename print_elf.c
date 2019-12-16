#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/usr/include/elf.h"


#define BUFFER


void print_header(Elf32_Ehdr elf)
{
    printf("Ficher: %s\n", ) ; // TODO
    printf("En-tête ELF:") ;
}

void print_magic(Elf32_Ehdr elf)
{
    printf("  Magique:  ") ;

    int i ;
    
    for(i = 0 ; i < EI_NIDENT ; i++)
    {
        printf("%x ", elf.e_ident[i]) ;
    }
    
    printf("\n") ;
}

void print_class(Elf32_Ehdr elf)
{
    printf("  Classe:  ", ); // TODO
    
    switch (elf.e_ident[EI_CLASS])
    {
        case ELFCLASSNONE : printf("AUCUN\n"); break;
        case ELFCLASS32 : printf("ELF32\n"); break;
        case ELFCLASS64 : printf("ELF64\n"); break;
        default : break;
    }
}

void print_data(Elf32_Ehdr elf)
{
    printf("  Données: ");

    switch (elf.e_ident[EI_DATA])
    {
        case ELFDATANONE : printf("Invalid data encoding\n"); break;
        case ELFDATA2LSB : printf("2's complement, little endian\n"); break;
        case ELFDATANUM : printf("2's complement, big endian\n"); break;
        default : break;
    }
}

void print_version(Elf32_Ehdr elf)
{
    printf("  Version:  %c",E.e_version) ;
}

void print_os_abi(Elf32_Ehdr elf)
{
    printf("  OS/ABI:  ") ;
    switch (elf.e_ident[EI_OSABI])
    {
        case ELFOSABI_NONE : printf("UNIX System V ABI\n"); break;
        case ELFOSABI_SYSV : printf("Alias\n"); break;
        case ELFOSABI_HPUX : printf("HP-UX\n"; break;
        case ELFOSABI_NETBSD : printf("NetBSD\n"); break;
        case ELFOSABI_GNU : printf("object uses GNU ELF extensions\n"); break;
        case ELFOSABI_LINUX : printf("Compatibility alias\n"); break;
        case ELFOSABI_SOLARIS : printf("Sun Solaris\n"); break;
        case ELFOSABI_AIX : printf("IBM AIX\n"); break;
        case ELFOSABI_IRIX : printf("SGI Irix\n"); break;
        case ELFOSABI_FREEBSD : printf("FreeBSD\n"); break;
        case ELFOSABI_TRU64 : printf("Compaq TRU64 UNIX\n"); break;
        case ELFOSABI_MODESTO : printf("Novell Modesto\n"); break;
        case ELFOSABI_OPENBSD : printf("OpenBSD\n"); break;
        case ELFOSABI_ARM_AEABI : printf("ARM EABI\n"); break;
        case ELFOSABI_ARM : printf("ARM\n"); break;
        case ELFOSABI_STANDALONE : printf("Standalone (embedded) application\n"); break;
        default : break;
    }
}

void print_abi_version(Elf32_Ehdr elf)
{
    // TODO
}

void print_type(Elf32_Ehdr elf)
{
    printf("  Type:  ") ;// TODO
}

void print_machine(Elf32_Ehdr elf)
{
    printf("  Machine:  ") ;// TODO
}


void print_elf(Elf32_Ehdr elf)
{ 
    print_header(elf) ;
    print_magic(elf) ;
    print_class(elf) ;
    print_data(elf) ;
    print_version(elf) ;
    print_os_abi(elf) ;
    print_abi_version(elf) ;
}