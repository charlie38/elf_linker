#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "elf.h"
#include "util_bis.h"


void afficher_sht(Elf32_Shdr section_tab[], int taille, char strtab[]){
	int i;
	int j;
	int k;
	char mot[50];
	printf("[Nr]            Name                  Type            Addr    Offs      Size  ES       Flg  Lk Inf  Al\n");
	
	for(i=0; i<taille; i++){
		if(i<10) printf("[ %d]",i);
		else printf("[%d]",i);


		//NAME:

		j =section_tab[i].sh_name;
		espaces(3);
		k = afficher_nom(strtab,j);
		k = 20-k;
		//if(k==20) k = k-1;
		espaces(k);
    	
    	//TYPE:
		strcpy(mot, "");

		switch(section_tab[i].sh_type){
			case SHT_NULL: strcpy(mot,"NULL"); break; 
			case SHT_PROGBITS: strcpy(mot,"PROGBITS"); break; 
			case SHT_SYMTAB: strcpy(mot,"SYMTAB"); break; 
			case SHT_STRTAB: strcpy(mot,"STRTAB"); break; 
			case SHT_RELA: strcpy(mot,"RELA"); break;  
			case SHT_HASH: strcpy(mot,"HASH"); break; 
			case SHT_DYNAMIC: strcpy(mot,"DYNAMIC"); break; 
			case SHT_NOTE: strcpy(mot,"NOTE"); break; 
			case SHT_NOBITS: strcpy(mot,"NOBIT"); break; 
			case SHT_REL: strcpy(mot,"RELA"); break; 
			case SHT_SHLIB: strcpy(mot,"SHLIB"); break; 
			case SHT_DYNSYM: strcpy(mot,"DYNSYM"); break; 
			case SHT_LOPROC: strcpy(mot,"LOPROC"); break; 
			case SHT_HIPROC: strcpy(mot,"HIPROC"); break; 
			case SHT_LOUSER: strcpy(mot,"LOUSER"); break; 
			case SHT_HIUSER: strcpy(mot,"HIUSER");  break;
			case SHT_ARM_EXIDX: strcpy(mot,"ARM_EXIDX"); break;
			case SHT_ARM_PREEMPTMAP: strcpy(mot,"ARM_PREEMPTMAP"); break;
			case SHT_ARM_ATTRIBUTES: strcpy(mot,"ARM_ATTRIBUTES") ; break;
			default: strcpy(mot, "");
		}
	    
		espaces(16-strlen(mot));
		printf("%s",mot);
    
    
    	//ADDR
    
		espaces(8);
		printf("%8.8x", section_tab[i].sh_addr);
    
		//OFFSET
		
		espaces(2);
		printf("%6.6x", section_tab[i].sh_offset);
    
    
    	//SIZE
    
		espaces(2);    
		printf("%8.8x", section_tab[i].sh_size);
    
        //ENTSIZE
    
		espaces(2);
		printf("%2.2x", section_tab[i].sh_entsize);
    
    	
    
    //FLAG
    
		    	
		strcpy(mot,"");  
		  	    
		if( section_tab[i].sh_flags & SHF_WRITE ) strcat(mot,"W");
		if( section_tab[i].sh_flags & SHF_ALLOC ) strcat(mot,"A");
		if( section_tab[i].sh_flags & SHF_EXECINSTR ) strcat(mot,"X");
		if( section_tab[i].sh_flags & SHF_MERGE ) strcat(mot, "M");
		if( section_tab[i].sh_flags & SHF_STRINGS ) strcat(mot, "S");
		if( section_tab[i].sh_flags & SHF_MERGE ) strcat(mot, "M");
		if( section_tab[i].sh_flags & SHF_INFO_LINK ) strcat(mot, "I");
	    
		espaces(10-strlen(mot));
		printf("%s",mot);
   		
    

    
    
    	//LINK
		espaces(2);
		if(section_tab[i].sh_link<10) printf(" %d", section_tab[i].sh_link);
		else printf("%d",section_tab[i].sh_link);
    
    	//INFO
    	
		espaces(2);
     
		if(section_tab[i].sh_info<10) printf(" %d", section_tab[i].sh_info);
		else printf("%d",section_tab[i].sh_info);
    
    	//ADDRALIGN
		espaces(2);
		printf("%d", section_tab[i].sh_addralign);
    
		printf("\n");

	}
	
	
	return;	
}


void afficher_section_hexa(FILE* f, Elf32_Shdr section_tab[],int num_sect,char strtab[]){
    int offset=section_tab[num_sect].sh_offset;
    int taille=section_tab[num_sect].sh_size;
	afficher_nom(strtab,section_tab[num_sect].sh_name);
	printf("\n");
    fseek(f,offset,SEEK_SET);
    int i=0;
	printf("\n0x%8.8x  ",i);
    for(i=0; i<taille; i++){
		if(i%4 == 0 && i!=0) printf("  ");
		if(i%16 == 0 && i!=0) printf("\n0x%8.8x  ",i);
        printf("%2.2x", fgetc(f));
    }
	printf("\n");
}