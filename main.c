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

    Elf32_Ehdr head;
    Elf32_Shdr section_tab[30];

    head = read_header(f);
    print_elf(head);


    read_section(f,section_tab,head.e_shoff,head.e_shnum);
    afficher_table_sections(section_tab,head.e_shnum);

    fclose(f);
    return 0;
}