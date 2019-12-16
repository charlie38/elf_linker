#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/usr/include/elf.h"


#define BUFFER

void afficher_entete(Elf32_Ehdr E){

//DEBUT
  printf("Ficher: %s\n",argv[1] );
  printf("En-tête ELF:");


//MAGIQUE
  printf("  Magique:  ");
  int i,
  for(i=0;i<EI_NIDENT;i++){
    printf("%x ", E.e_ident[i]);
  }
  printf("\n");
}


//CLASSE
printf("  Classe:  ", );
switch(E.e_ident[EI_CLASS])
{
  case ELFCLASSNONE : printf("AUCUN\n"); break;
  case ELFCLASS32 : printf("ELF32\n"); break;
  case ELFCLASS64 : printf("ELF64\n"); break;
  default : break;
}


//DONNNEES
printf("  Données: ");
switch (E.e_ident[EI_DATA])
{
  case ELFDATANONE : printf("Invalid data encoding\n"); break;
  case ELFDATA2LSB : printf("2's complement, little endian\n"); break;
  case ELFDATANUM : printf("2's complement, big endian\n"); break;
  default : break;
}


//VERSION
printf("  Version:  %c",E.e_version);


//OS/ABI
  printf("  OS/ABI:  ");
  switch (e.e_ident[EI_OSABI])
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

//VERSION ABI































//TYPE
  printf("  Type:  ");

//MACHINE
  printf("  Machine:  ");


int main(int argc,char* argv[]){

  FILE f = fopen(argv[1],"r");


  if (f == NULL)
  return -1;
  if(argc != 2)
  {
    printf("Nombre d'argument incorrect\n");
  }

  fread






printf("nico est pd\n", );
}
