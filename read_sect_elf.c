#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "read_sect_elf.h"
#include "read_elf.h"

Elf32_Shdr read_section(FILE *f){
    uint_32_t offset;
    uint_32_t size_h;

    Elf32_Ehdr head; 
    elf = read_header(f);

    offset = head.e_shoff;
    size_h = head.e_ehsize;
    
    fread(offset - size_h,offset - size_h,1,f);

    Elf32_Shdr **section;

    while(!eof(f)){
        fread();
        fread();
        fread();
        fread();
    }
    
}