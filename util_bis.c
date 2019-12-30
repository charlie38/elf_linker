#include <stdio.h>
#include <stdlib.h>
#include "util_bis.h"

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