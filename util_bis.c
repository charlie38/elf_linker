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
	if(strtab[i] != '\0')
	while(strtab[i] != '\0'){
		j++;
		i++;
		printf("%c",strtab[i-1]);
	}
	return j;
}

char *get_only_name(char strtab[], int i)
{
	return &strtab[i] ;
}

char *get_name(char strtab[],int i){
	printf("Valeur %d : %s\n",i,&strtab[i]);
	return &strtab[i];
}
