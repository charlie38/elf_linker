#include <stdio.h>
#include <stdlib.h>
#include "read_elf_symt.h"

#include "elf_linker-1.0/util.h"
#include "elf.h"

int index_strtab(Elf32_Shdr section_tab[])
{
    int i = 0;

    while (section_tab[i].sh_type != SHT_SYMTAB)
	{
        i++;
	}

	return i ;
}

int index_symtab(Elf32_Shdr section_tab[])
{
    int i = 0 ;

    while (section_tab[i].sh_type != SHT_SYMTAB) 
	{
        i ++ ;
    }

    return i ;
}

void read_symtab(FILE *f, Elf32_Sym symtab[],Elf32_Shdr section_tab[],uint32_t offset,uint32_t nb_symb){
    
    int i = 0;

    fseek(f,offset,SEEK_SET); //Placement de l'indicateur de position au niveau de l'entête de la table des symboles

    for(i=0;i<nb_symb;i++){
        fread(&symtab[i].st_name,sizeof(Elf32_Word),1,f);    //Lecture du name
        fread(&symtab[i].st_value,sizeof(Elf32_Addr),1,f);    //Lecture du value
        fread(&symtab[i].st_size,sizeof(Elf32_Word),1,f);     //Lecture de la taille
        fread(&symtab[i].st_info,sizeof(unsigned char),1,f);   //Lecture de info
        fread(&symtab[i].st_other,sizeof(unsigned char),1,f);    //Lecture de other
        fread(&symtab[i].st_shndx,sizeof(Elf32_Section),1,f);  //Lecture section index

        //Inversion selon l'endianness (ici on inverse)

        symtab[i].st_name=reverse_4(symtab[i].st_name);
        symtab[i].st_value=reverse_4(symtab[i].st_value);
        symtab[i].st_size=reverse_4(symtab[i].st_size);
        symtab[i].st_info=symtab[i].st_info;
        symtab[i].st_other=symtab[i].st_other;
        symtab[i].st_shndx=reverse_2(symtab[i].st_shndx);

    }

    return;
}


