#include <stdio.h>
#include <stdlib.h>
#include "elf.h"
#include "read_sect_elf.h"
#include "read_elf.h"
#include "print_elf.h"

int main(int arg,char *argv[]){
    Elf32_Ehdr elf;
    FILE *f;
    f = NULL;
    f = fopen(argv[1],"r");
    elf = read_header(f);
    print_elf(elf);
    fclose(f);
    return 0;
}