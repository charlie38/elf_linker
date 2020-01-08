#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "util.h"

#include "write_elf_section_header.h"
#include "write_elf_head.h"


void write_section_header(FILE *f, Elf32_Shdr section_tab[],uint32_t offset,uint32_t nb_sect){
    
    int i = 0;

    fseek(f,offset,SEEK_SET); //Placement de l'indicateur de position au niveau de l'entete de la table des sections

    for(i=0;i<nb_sect;i++){
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
    	
        fwrite(&section_tab[i].sh_name,sizeof(Elf32_Word),1,f);    //Ecriture du name
        fwrite(&section_tab[i].sh_type,sizeof(Elf32_Word),1,f);    //Ecriture du type
        fwrite(&section_tab[i].sh_flags,sizeof(Elf32_Word),1,f);   //Ecriture des flags
        fwrite(&section_tab[i].sh_addr,sizeof(Elf32_Addr),1,f);    //Ecriture de l'adresse
        fwrite(&section_tab[i].sh_offset,sizeof(Elf32_Off),1,f);  //Ecriture de l'offset
        fwrite(&section_tab[i].sh_size,sizeof(Elf32_Word),1,f);     //Ecriture de la taille
        fwrite(&section_tab[i].sh_link,sizeof(Elf32_Word),1,f);     //Ecriture du lien
        fwrite(&section_tab[i].sh_info,sizeof(Elf32_Word),1,f);    //Ecriture de l'info
        fwrite(&section_tab[i].sh_addralign,sizeof(Elf32_Word),1,f);  //Ecriture de l'addralign
        fwrite(&section_tab[i].sh_entsize,sizeof(Elf32_Word),1,f);   //Ecriture de l'entsize

        //Inversion selon l'endianness (ici on inverse)



    }

    return;
}
