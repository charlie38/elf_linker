#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "read_sect_elf.h"
#include "read_elf.h"
#include "print_elf.h"
#include "print_sht.h"

int main(int argc,char *argv[]){

    if(argc != 2){
        printf("Erreur, pas de fichier donnée !\n");
        return 3;
    }

    FILE *f;
    f = NULL;
    f = fopen(argv[1],"r");

    if(f==NULL) {
        printf("Erreur, fichier inexistant ou non ouvrable en lecture !\n");
        return 4;
    }

    Elf32_Ehdr elf;
    Elf32_Shdr section_tab[30];

    elf = read_header(f);
    print_elf(elf);


    read_section(f,section_tab,elf.e_shoff,elf.e_ehsize,elf.e_shnum);
    afficher_table_sections(section_tab,elf.e_shnum);

    fclose(f);
    return 0;
}