#ifndef FUSION_PROGBITS_H
#define FUSION_PROGBITS_H

void fus_all_progbits(FILE* A, FILE* B, tab_sections* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTab[]) ;

#endif
