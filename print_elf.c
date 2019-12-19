#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "elf.h"


void print_header(Elf32_Ehdr elf)
{
    printf("ELF Header:\n") ;
}

void print_magic(Elf32_Ehdr elf)
{
    printf("  Magic:  ") ;

    int i ;
    
    for(i = 0 ; i < EI_NIDENT ; i++)
    {
        printf("%x ", elf.e_ident[i]) ;
    }
    
    printf("\n") ;
}

void print_class(Elf32_Ehdr elf)
{
    printf("  Class:                             ") ;
    
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
    printf("  Data:                              ") ;

    switch (elf.e_ident[EI_DATA])
    {
        case ELFDATANONE : printf("Invalid data encoding\n"); break;
        case ELFDATA2LSB : printf("2's complement, little endian\n"); break;
        case ELFDATA2MSB : printf("2's complement, big endian\n"); break;
        default: break;
    }
}

void print_version_magic(Elf32_Ehdr elf)
{
    printf("  Version:                           %d\n", elf.e_ident[EI_VERSION]) ;
}

void print_os_abi(Elf32_Ehdr elf)
{
    printf("  OS/ABI:                            ") ;

    switch (elf.e_ident[EI_OSABI])
    {
        case ELFOSABI_NONE : printf("UNIX System V\n"); break;
        case ELFOSABI_HPUX : printf("HP-UX\n"); break;
        case ELFOSABI_NETBSD : printf("NetBSD\n"); break;
        case ELFOSABI_GNU : printf("object uses GNU ELF extensions\n"); break;
        //case ELFOSABI_LINUX : printf("Compatibility alias\n"); break;
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

void print_version_abi(Elf32_Ehdr elf)
{
    printf("  ABI Version:                       %d\n",elf.e_ident[EI_ABIVERSION]) ;
}

void print_type(Elf32_Ehdr elf)
{
    printf("  Type:                              ") ;

    switch (elf.e_type) 
    {
        case ET_NONE : printf("No file type\n") ; break ;
        case ET_REL : printf("Relocatable file\n") ; break ;
        case ET_EXEC : printf("Executable file\n") ; break ;
        case ET_DYN : printf("Shared object file\n") ; break ;
        case ET_CORE : printf("Core file\n") ; break ;
        case ET_LOPROC : 
        case ET_HIPROC : printf("Processor-specific\n") ;
    }
}

void print_machine(Elf32_Ehdr elf)
{
    printf("  Machine:                           ") ;

    switch (elf.e_machine) 
    {
        case ET_NONE : printf("No machine\n") ; break ;  
        case EM_M32 : printf("AT&T WE 32100\n") ; break ;  
        case EM_SPARC : printf("SPARC\n") ; break ;  
        case EM_386 : printf("Intel Architecture\n") ; break ;  
        case EM_68K : printf("Motorola 68000\n") ; break ;  
        case EM_88K : printf("Motorola 88000\n") ; break ;  
        case EM_860 : printf("Intel 80860\n") ; break ;  
        case EM_MIPS : printf("MIPS RS3000 Big-Endian\n") ; break ;  
        case EM_MIPS_RS3_LE : printf("MIPS RS4000 Big-Endian\n") ; break ;
        case EM_ARM: printf("ARM\n"); break;
        //case RESERVED : printf("Reserved for future use\n") ;
    }
}

void print_version(Elf32_Ehdr elf)
{
    printf("  Version:                           ") ;
    printf("0x%x\n",elf.e_version);
    /*switch (elf.e_version) 
    {
        case EV_NONE : printf("0 (invalid version)\n") ; break ;
        case EV_CURRENT : printf("1 (current version)\n") ; break;
        case EV_NUM : printf("2"); break;
    }*/
}

void print_entry(Elf32_Ehdr elf)
{
    printf("  Entry point access:                0x%x\n", elf.e_entry) ;
}

void print_start_prog_headers(Elf32_Ehdr elf)
{
    printf("  Start of program headers:          ") ;

    switch (elf.e_phoff)
    {
        case 0 : printf("%d (bytes into file)\n", elf.e_phoff) ; break ;
        default : printf("%d (bytes into file)\n", elf.e_phoff) ;
    }
}

void print_start_sect_headers(Elf32_Ehdr elf)
{
    printf("  Start of section headers:          ") ;

    switch (elf.e_shoff)
    {
        case 0 : printf("No section headers table\n") ; break ;
        default : printf("%d (bytes into file)\n",elf.e_shoff) ;
    }
}

void print_flags(Elf32_Ehdr elf)
{
    printf("  Flags:                             0x%x\n", elf.e_flags) ;
}

void print_header_size(Elf32_Ehdr elf)
{
    printf("  Size of this headers:              %d (bytes)\n", elf.e_ehsize) ;
}

void print_prog_header_size(Elf32_Ehdr elf)
{
    printf("  Size of program headers:           %d (bytes)\n", elf.e_phentsize) ;
}

void print_prog_header_num(Elf32_Ehdr elf)
{
    printf("  Number of program headers:         %d\n", elf.e_phnum) ;
}

void print_sect_header_size(Elf32_Ehdr elf)
{
    printf("  Size of section headers:           %d (bytes)\n", elf.e_shentsize) ;
}

void print_sect_header_num(Elf32_Ehdr elf)
{
    printf("  Number of section headers:         %hd\n", elf.e_shnum) ;
}

void print_table_index(Elf32_Ehdr elf)
{
    printf("  Section header string table index: %d\n", elf.e_shstrndx) ;
}

void print_elf(Elf32_Ehdr elf)
{ 
    print_header(elf) ;
    print_magic(elf) ;
    print_class(elf) ;
    print_data(elf) ;
    print_version_magic(elf) ;
    print_os_abi(elf) ;
    print_version_abi(elf) ;
    print_type(elf) ;
    print_machine(elf) ;
    print_version(elf) ;
    print_entry(elf) ;
    print_start_prog_headers(elf) ;
    print_start_sect_headers(elf) ;
    print_flags(elf) ;
    print_header_size(elf) ;
    print_prog_header_size(elf) ;
    print_prog_header_num(elf) ;
    print_sect_header_size(elf) ;
    print_sect_header_num(elf) ;
    print_table_index(elf) ;
}