#include <stdio.h>
#include <stdlib.h>
#include "util_bis.h"
#include "string.h"
#include "elf.h"

int maxi(int a,int b){
	if(a>b)return a;
	else return b;
}

void espaces(int n){
	int i;
	for(i=0;i<n;i++) printf(" ");
}

int afficher_nom(char strtab[],int i){
	int j = 0;
	while(strtab[j] != '\0'){
		j++;
	}
	printf("%s",&strtab[i]);
	return j;
}

char *get_name(char strtab[],int i){
	return &strtab[i];
}

int strcat2(char *dest,char *src,int taille){
	int len_src = strlen(src);
	if(len_src == 0){
		dest[taille] = '\0';
		return taille;
	}
	else{
	int i;
	int t = taille;
	for(i=0;i<len_src+1;i++){
		dest[t] = src[i];
		t++;
	}
	return t;
	}
}