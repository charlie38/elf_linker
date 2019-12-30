#include <stdio.h>
#include <stdlib.h>
#include "elf.h"
#include "print_elf_symt.h"
#include "util_bis.h"


void afficher_symb_tab(Elf32_Sym symtab[],int nb_symb,char strsymtab[]){
    int i;
    printf("Num :        Value    Size    Type     Bind    Vis       Ndx     Name\n");
    for(i=0;i<nb_symb;i++){

        //NUM
        if(i<10) printf("    %d:",i);
        else printf("   %d:",i);

        espaces(4);

        //VALUE
        printf("%8.8x",symtab[i].st_value);

        //SIZE

        espaces(5);

        printf("%d",symtab[i].st_size);

        //TYPE

        espaces(3);

        switch(ELF32_ST_TYPE(symtab[i].st_info)){
            case STT_NOTYPE: printf("NOTYPE "); break;
            case STT_SECTION: printf("SECTION"); break;
            case STT_OBJECT: printf("OBJECT"); break;
            case STT_FUNC: printf("FUNC"); break;
            case STT_FILE: printf("FILE"); break;
            case STT_COMMON: printf("COMMON"); break;
            case STT_TLS: printf("TLS"); break;
            case STT_NUM: printf("NUM"); break;
            case STT_LOOS: printf("LOOS"); break;
            case STT_HIOS: printf("HIOS"); break;
            case STT_LOPROC: printf("LOPROC"); break;
            case STT_HIPROC: printf("HIPROC"); break;
        }


        //BIND 

        espaces(5);

        switch(ELF32_ST_BIND(symtab[i].st_info)){
            case STB_LOCAL: printf("LOCAL "); break;
            case STB_GLOBAL: printf("GLOBAL"); break;
            case STB_WEAK: printf("WEAK  "); break;
            case STB_NUM: printf("NUM   "); break;
            case STB_LOOS: printf("LOOS  "); break;
            case STB_HIOS: printf("HIOS  "); break;
            case STB_LOPROC: printf("LOPROC"); break;
            case STB_HIPROC: printf("HIPROC"); break;

        }

        espaces(2);

        //VIS
        
        switch(ELF32_ST_VISIBILITY(symtab[i].st_other)){
            case STV_DEFAULT: printf("DEFAULT"); break;
        }

        espaces(3);

        //NDX
        
        if(symtab[i].st_shndx == STN_UNDEF) printf("UND");
        else printf("%d",symtab[i].st_shndx);

        espaces(6);

        //NAME
        
        afficher_nom(strsymtab,symtab[i].st_name);
        printf("\n");
    }
}