#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "read_sect_elf.h"
#include "read_elf.h"

void read_section(FILE *f, Elf32_Shdr section_tab[],uint32_t offset,uint32_t size_h,uint32_t nb_sect){
    
    int i = 0;

    fseek(f,offset-size_h,SEEK_SET); //Placement de l'indicateur de position au niveau de l'entête de la table des sections

    for(i=0;i<nb_sect;i++){
        fread(&section_tab[i].sh_name,4,1,f);    //Lecture du name
        fread(&section_tab[i].sh_type,4,1,f);    //Lecture du type
        fread(&section_tab[i].sh_flags,4,1,f);   //Lecture des flags
        fread(&section_tab[i].sh_addr,4,1,f);    //Lecture de l'adresse
        fread(&section_tab[i].sh_offset,4,1,f);  //Lecture de l'offset
        fread(&section_tab[i].sh_size,4,1,f);     //Lecture de la taille
        fread(&section_tab[i].sh_link,4,1,f);     //Lecture du lien
        fread(&section_tab[i].sh_info,4,1,f);    //Lecture de l'info
        fread(&section_tab[i].sh_addralign,4,1,f);  //Lecutre de l'addralign
        fread(&section_tab[i].sh_entsize,4,1,f);   //Lecture de l'entsize
    }

    return;
}