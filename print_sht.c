#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "elf.h"

void espaces(int n){
	int i;
	for(i=0;i<n;i++) printf(" ");
}

void afficher_table_sections(Elf32_Shdr TS[], int taille, char strtab[]){
	int i;
	char mot[50];
	printf("[Nr]            Type            Addr      Offs      Size    ES   Flg  Lk  Inf  Al\n");
	
	for(i=0; i<taille; i++){
		if(i<10) printf("[ %d]",i);
		else printf("[%d]",i);
    	//NAME: 
    	
		//printf("Nom : %s  | ", strtab[TS[i].sh_name]);
    	//mot=strtab[TS[i].sh_name];
    	//espaces(20);
    	//printf("%s",mot);
    	
    	//TYPE:
      strcpy(mot, "");

	    switch(TS[i].sh_type){
	      case SHT_NULL: strcpy(mot,"NULL");
	      case SHT_PROGBITS: strcpy(mot,"PROGBITS");
	      case SHT_SYMTAB: strcpy(mot,"SYMTAB");
	      case SHT_STRTAB: strcpy(mot,"STRTAB");
	      case SHT_RELA: strcpy(mot,"RELA");
	      case SHT_HASH: strcpy(mot,"HASH");
	      case SHT_DYNAMIC: strcpy(mot,"DYNAMIC");
	      case SHT_NOTE: strcpy(mot,"NOTE");
	      case SHT_NOBITS: strcpy(mot,"NOBIT");
	      case SHT_REL: strcpy(mot,"RELA");
	      case SHT_SHLIB: strcpy(mot,"SHLIB");
	      case SHT_DYNSYM: strcpy(mot,"DYNSYM");
	      case SHT_LOPROC: strcpy(mot,"LOPROC");
	      case SHT_HIPROC: strcpy(mot,"HIPROC");
	      case SHT_LOUSER: strcpy(mot,"LOUSER");
	      case SHT_HIUSER: strcpy(mot,"HIUSER");      
        default: strcpy(mot, "");
	    }
	    
	    espaces(16-strlen(mot));
    	printf("%s",mot);
    
    
    	//ADDR
    
    	espaces(8);
    	printf("%8.8x", TS[i].sh_addr);
    
		//OFFSET
		
    	espaces(2);
    	printf("%8.8x", TS[i].sh_offset);
    
    
    	//SIZE
    
    	espaces(4);    
    	printf("%6.6x", TS[i].sh_size);
    
        //ENTSIZE
    
    	espaces(4);
    	printf("%2.2x", TS[i].sh_entsize);
    
    	
    
    //FLAG
    
    	
		strcpy(mot,"");  
		  	    
	    if( TS[i].sh_flags & SHF_WRITE ) strcat(mot,"W");
	    if( TS[i].sh_flags & SHF_ALLOC ) strcat(mot,"A");
	    if( TS[i].sh_flags & SHF_EXECINSTR ) strcat(mot,"I");
	    //if( TS[i].sh_flags & SHF_MASKPROC ) mot=strcat(mot, "X");
	    
	    espaces(6-strlen(mot));
    
   		
    

    
    
    	//LINK
    	espaces(2);
    	printf("%2.2x", TS[i].sh_link);
    
    	//INFO
    	
    	espaces(2);
    	printf("%2.2x", TS[i].sh_info);
    
    
    	//ADDRALIGN
    	espaces(2);
    	printf("%2.2x", TS[i].sh_addralign);
    
    	printf("\n");

	}
	
	
	return;	
}