#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "elf_linker-1.0/util.h"

#include "read_elf_sect.h"
#include "read_elf_head.h"


void read_section(FILE *f, Elf32_Shdr section_tab[],uint32_t offset,uint32_t nb_sect){
    
    int i = 0;

    fseek(f,offset,SEEK_SET); //Placement de l'indicateur de position au niveau de l'entête de la table des sections

    for(i=0;i<nb_sect;i++){
        fread(&section_tab[i].sh_name,sizeof(Elf32_Word),1,f);    //Lecture du name
        fread(&section_tab[i].sh_type,sizeof(Elf32_Word),1,f);    //Lecture du type
        fread(&section_tab[i].sh_flags,sizeof(Elf32_Word),1,f);   //Lecture des flags
        fread(&section_tab[i].sh_addr,sizeof(Elf32_Addr),1,f);    //Lecture de l'adresse
        fread(&section_tab[i].sh_offset,sizeof(Elf32_Off),1,f);  //Lecture de l'offset
        fread(&section_tab[i].sh_size,sizeof(Elf32_Word),1,f);     //Lecture de la taille
        fread(&section_tab[i].sh_link,sizeof(Elf32_Word),1,f);     //Lecture du lien
        fread(&section_tab[i].sh_info,sizeof(Elf32_Word),1,f);    //Lecture de l'info
        fread(&section_tab[i].sh_addralign,sizeof(Elf32_Word),1,f);  //Lecutre de l'addralign
        fread(&section_tab[i].sh_entsize,sizeof(Elf32_Word),1,f);   //Lecture de l'entsize

        //Inversion selon l'endianness (ici on inverse)

        section_tab[i].sh_name=reverse_4(section_tab[i].sh_name);
        section_tab[i].sh_type=reverse_4(section_tab[i].sh_type);
        section_tab[i].sh_flags=reverse_4(section_tab[i].sh_flags);
        section_tab[i].sh_addr=reverse_4(section_tab[i].sh_addr);
        section_tab[i].sh_offset=reverse_4(section_tab[i].sh_offset);
        section_tab[i].sh_size=reverse_4(section_tab[i].sh_size);
        section_tab[i].sh_link=reverse_4(section_tab[i].sh_link);
        section_tab[i].sh_info=reverse_4(section_tab[i].sh_info);
        section_tab[i].sh_addralign=reverse_4(section_tab[i].sh_addralign);
        section_tab[i].sh_entsize=reverse_4(section_tab[i].sh_entsize);

    }

    return;
}

void read_string_table(FILE *f,Elf32_Ehdr head,Elf32_Shdr section_tab[],char strtab[],int j){
    fseek(f,section_tab[j].sh_offset,SEEK_SET);
    int i;
    for(i=0;i<section_tab[j].sh_size;i++){
        fread(&strtab[i],1,1,f);
    }
    printf("\n");
    return;
}
