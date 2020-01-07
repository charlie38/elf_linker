#include <stdio.h>
#include <stdlib.h>
#include "fus_progbits.h"
#include "elf.h"
#include "util_bis.h"
#include "section.h"



//fusion et enregistrement

void fus_all_progbits(FILE* A, FILE* B, tab_sections* tab, Elf32_Shdr ShdrA[], 
		int nbsectA, Elf32_Shdr ShdrB[], int nbsectB, char strTab[]){
  int i, j, cond, decalage;
  section a,b;
  
  //cond=1 => ShdrA[i] deja ajoutee a tab
  cond=0;
  int presents[nbsectB]; // ( presents[i]!=-1 => ShdrB[i] a ete concatenee a la section ShdrA[presents[i]] )
  
  //Initialisation de presents
  for(j=0;j<nbsectB;j++) presents[j]=-1;
  
  //Parcours toutes les sections du fichier A
  for(i=0;i<nbsectA;i++){
  
    //Si section est de type PROGBITS
    if (ShdrA[i].sh_type==PROGBITS){
      //Parcours toutes les sections du fichier B
      
      for(j=0; j<nbsectB; j++){
        
        //Si les deux sections ont le meme nom
        if( !strcmp(afficher_nom(strTab, ShdrA[i].sh_name),afficher_nom(strTab, ShdrB[i].sh_name)) ){
          
          //Lecture et enregistrement des deux sections
        	a=read_sect(A,ShdrA[i]);
        	b=read_sect(B,ShdrB[j]);
          
          //Concatenation des deux sections
        	concat(&a,b);
        	a.header.sh_offset+=decalage;
          //Mise a jour du decalage d'offset des sections suivantes
          
        	decalage+=b.header.sh_size;
          //On l'ajoute au tableau final des sections progbits
        	tab->T[tab->nb]=a;
        	tab->nb++;
          
          //Condition = vrai
        	cond=1;
        	presents[j]=i;
        }
        
      }
            
    }
    
    //Si on n'a pas ajoute la section courante, on l'ajoute
    if(cond==0 && ShdrA[i].sh_type != SHT_SYMTAB && ShdrA[i].sh_type != SHT_STRTAB && ShdrA[i].sh_type != SHT_REL){
    	a=read_sect(A,ShdrA[i]);
    	a.header.offset+=decalage;
    	tab->T[tab->nb]=a;
    	tab->nb++;
    }
    
  }
  
  //Tous ceux qui ne sont pas presents dans tab, sont ajoutes a la fin
  for(j=0;j<nbsectB;j++){
  
    //Si la section j de ShdrB n'est pas presente et est de type progbits
  	if(presents[j]==-1 && ShdrB[i].sh_type != SHT_SYMTAB && ShdrB[i].sh_type != SHT_STRTAB && ShdrB[i].sh_type != SHT_REL && ShdrB[i].sh_type != SHT_NULL){
    	b=read_sect(B, ShdrB[j]);
    	tab->T[tab->nb]=b;
    	tab->nb++;
    }
  }
}

