#ifndef FUSION_PROGBITS_H
#define FUSION_PROGBITS_H

void fusion_progbits(FILE* A, FILE* B, tab_section* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTab[]) ;

#endif
