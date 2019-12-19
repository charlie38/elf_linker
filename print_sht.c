#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "elf.h"

void espaces(int n){
	int i;
	for(i=0;i<n;i++) printf(" ");
}

int afficher_name(char strtab[],int i){
	int j = 0;
	if(strtab[i] != '\0') printf(".");
	while(strtab[i] != '\0'){
		j++;
		i++;
		printf("%c",strtab[i]);
	}
	return j;
}

void afficher_table_sections(Elf32_Shdr TS[], int taille,char strtab[]){
	int i;
	int j;
	int k;
	char mot[50];
	printf("[Nr]            Name                  Type            Addr    Offs      Size  ES       Flg  Lk Inf  Al\n");
	
	for(i=0; i<taille; i++){
		if(i<10) printf("[ %d]",i);
		else printf("[%d]",i);


		//NAME:

		j = TS[i].sh_name;
		espaces(3);
		k = afficher_name(strtab,j);
		k = 20-k;
		//if(k==20) k = k-1;
		espaces(k);
    	
    	//TYPE:
		strcpy(mot, "");

		switch(TS[i].sh_type){
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
		printf("%8.8x", TS[i].sh_addr);
    
		//OFFSET
		
		espaces(2);
		printf("%6.6x", TS[i].sh_offset);
    
    
    	//SIZE
    
		espaces(2);    
		printf("%8.8x", TS[i].sh_size);
    
        //ENTSIZE
    
		espaces(2);
		printf("%2.2x", TS[i].sh_entsize);
    
    	
    
    //FLAG
    
		    	
		strcpy(mot,"");  
		  	    
		if( TS[i].sh_flags & SHF_WRITE ) strcat(mot,"W");
		if( TS[i].sh_flags & SHF_ALLOC ) strcat(mot,"A");
		if( TS[i].sh_flags & SHF_EXECINSTR ) strcat(mot,"X");
		if( TS[i].sh_flags & SHF_MERGE ) strcat(mot, "M");
		if( TS[i].sh_flags & SHF_STRINGS ) strcat(mot, "S");
		if( TS[i].sh_flags & SHF_MERGE ) strcat(mot, "M");
		if( TS[i].sh_flags & SHF_INFO_LINK ) strcat(mot, "I");
	    
		espaces(10-strlen(mot));
		printf("%s",mot);
   		
    

    
    
    	//LINK
		espaces(2);
		if(TS[i].sh_link<10) printf(" %d", TS[i].sh_link);
		else printf("%d",TS[i].sh_link);
    
    	//INFO
    	
		espaces(2);
     
		if(TS[i].sh_info<10) printf(" %d", TS[i].sh_info);
		else printf("%d",TS[i].sh_info);
    
    	//ADDRALIGN
		espaces(2);
		printf("%d", TS[i].sh_addralign);
    
		printf("\n");

	}
	
	
	return;	
}



void afficher_section(FILE* f, Elf32_Shdr TS[], int s,char strtab[]){
    int offset=TS[s].sh_offset;
    int taille=TS[s].sh_size;
	afficher_name(strtab,TS[s].sh_name);
	printf("\n");
    fseek(f,offset,SEEK_SET);
    int i;
    for(i=0; i<taille; i++){
		if(i%4 == 0 && i!=0) printf("\n");
        printf("%2.2x  ", fgetc(f));
    }
	printf("\n");
}