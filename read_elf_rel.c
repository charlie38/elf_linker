#include <stdio.h>
#include <stdlib.h>
#include "elf.h"
#include "elf_linker-1.0/util.h"

#include "read_elf_rel.h"

Elf32_Rel read_rel_entry(FILE *f,uint32_t section_offset){
    Elf32_Rel rel;

    fseek(f,section_offset,SEEK_SET);

    fread(&rel.r_offset,sizeof(Elf32_Addr),1,f);
    fread(&rel.r_info,sizeof(Elf32_Word),1,f);

    //Selon l'endianess on reverse (ici , il faut le faire)

    rel.r_offset = reverse_4(rel.r_offset);
    rel.r_info = reverse_4(rel.r_info);

    return rel;
}


Elf32_Rela read_rela_entry(FILE *f,uint32_t section_offset){
    Elf32_Rela rela;

    fseek(f,section_offset,SEEK_SET);

    fread(&rela.r_offset,sizeof(Elf32_Addr),1,f);
    fread(&rela.r_info,sizeof(Elf32_Word),1,f);
    fread(&rela.r_addend,sizeof(Elf32_Sword),1,f);

    //Selon l'endianess on reverse (ici , il faut le faire)

    rela.r_offset = reverse_4(rela.r_offset);
    rela.r_info = reverse_4(rela.r_info);
    rela.r_addend = reverse_4(rela.r_addend);

    return rela;
}