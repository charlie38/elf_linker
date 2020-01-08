#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "elf.h"

#include "util_bis.h"
#include "fusion_symtab.h"
#include "print_elf_symt.h"

/*Fonction comparant deux symboles , renvoie 0 si ils sont égaux*/
int comparer_symbole(Elf32_Sym symA,Elf32_Sym symB){
    int res = 0;
    if(symA.st_name != symB.st_name) res = 1;
    if(symA.st_value != symB.st_value) res = 1;
    if(symA.st_size != symB.st_size) res = 1;
    if(symA.st_info != symB.st_info) res = 1;
    if(symA.st_other != symB.st_other) res = 1;
    if(symA.st_shndx != symB.st_shndx) res = 1;
    return res;
}

int fusion_symtab(Elf32_Sym symtabA[],Elf32_Sym symtabB[],int nb_symbA,int nb_symbB,char strtabA[],char strtabB[]){

    /*Déclaration des variables - tableaux*/
    int i;
    int j;
    int save_j;
    int indice_sym = 0;
    int i_name;

    Elf32_Sym symtab_fu[maxi(nb_symbA,nb_symbB)*2];  //symtab_fu est la symtab finale , après fusion
    StrsymFu strfu; //strsymtab est  la table pour les noms des symboles après fusion 
    strfu.taille = 1;
    strfu.strsymtab[0] = '\0'; 

    int ind_strsymt = 1;

    int traite[nb_symbB]; //Si la valeur est 1 , alors il a été traité (pour les cas avec GLOBAL non défini)

    /*Traitement de tous les symboles du fichier A ( avec ceux en communs du B )*/
    for(i=0;i<nb_symbA;i++){
        if(i>3)symtabB[i].st_value = 1;
        save_j = 0;
        switch(ELF32_ST_BIND(symtabA[i].st_info)){

            case STB_LOCAL: //Si c'est LOCAL , alors on met le symbole dans tous les cas
                for(j=0;j<nb_symbB;j++){ //Test pour voir si un symbole du fichier B est identique , ausquel cas il sera en une fois.
                    if(comparer_symbole(symtabB[j],symtabA[i]) == 0){
                        traite[j] = 1; //On le marque donc
                        save_j = j;
                        j+= nb_symbB;
                    }
                }
                /*Ajout du symbole , correction de l'offset pour la valeur et ajout du nom dans la strsymtab*/
                symtab_fu[indice_sym] = symtabA[i];
                strfu.taille = strcat2(strfu.strsymtab,get_name(strtabA,symtabA[i].st_name),strfu.taille);
                if(symtabA[i].st_name != 0)
                ind_strsymt+=strlen(get_name(strtabA,symtabA[i].st_name))+1;
                printf("Valeur de l'indice : %d\n",ind_strsymt);
                break;

            case STB_GLOBAL: //Si c'est GLOBAL , alors il faut vérifier les différents cas
                for(j=0;j<nb_symbB;j++){
                    if(!strcmp(get_name(strtabA,symtabA[i].st_name),get_name(strtabB,symtabB[j].st_name)) && ELF32_ST_BIND(symtabB[j].st_info) == STB_GLOBAL ){ //Test des noms identiques
                        /*Cas où le symbole du fichier B est défini , mais pas dans le A --> choix pour le fichier B*/
                        if(symtabA[i].st_shndx == STN_UNDEF && symtabB[j].st_shndx != STN_UNDEF){
                            save_j = j;
                            j+= nb_symbB;
                        }
                        /*Cas où le symbole du fichier A est défini , mais pas dans le B --> choix pour le fichier A*/
                        if(symtabA[i].st_shndx != STN_UNDEF && symtabB[j].st_shndx == STN_UNDEF){
                            j+= nb_symbB;
                        }
                        /*Cas où deux symboles ne sont pas définis , choix arbitraire pour le fichier A*/
                        if(symtabA[i].st_shndx == STN_UNDEF && symtabB[j].st_shndx == STN_UNDEF){
                            j+= nb_symbB;
                        }
                        /*Cas où même nom , mais tous les deux définis dans chacune des tables*/
                        if(symtabA[i].st_shndx != STN_UNDEF && symtabB[j].st_shndx != STN_UNDEF){
                            printf("Erreur , impossible d'avoir 2 symboles de type GLOBAL du même nom !\n");
                            return 5;
                        }
                        traite[j] = 1; //Symbole marque
                    }
                }
                if(save_j != 0){
                    /*Ajout du symbole , correction de l'offset pour la valeur et ajout du nom dans la strsymtab*/
                    symtab_fu[indice_sym] = symtabB[save_j];
                    strfu.taille = strcat2(strfu.strsymtab,get_name(strtabB,symtabB[save_j].st_name),strfu.taille);
                    if(symtabB[save_j].st_name != 0)
                    ind_strsymt+=strlen(get_name(strtabB,symtabB[save_j].st_name))+1;
                    printf("Valeur de l'indice : %d\n",ind_strsymt);
                }
                else {
                    /*Ajout du symbole , correction de l'offset pour la valeur et ajout du nom dans la strsymtab*/
                    symtab_fu[indice_sym] = symtabA[i];
                    strfu.taille = strcat2(strfu.strsymtab,get_name(strtabA,symtabA[i].st_name),strfu.taille);
                    if(symtabA[i].st_name != 0)
                    ind_strsymt+=strlen(get_name(strtabA,symtabA[i].st_name))+1;
                    printf("Valeur de l'indice : %d\n",ind_strsymt);

                }
                break;
        }
        indice_sym+=1;
    }

    /*Traitement de tous les symboles du fichier B pas encore traites*/
    for(i=0;i<nb_symbB;i++){
        if(traite[i] != 1){
            symtab_fu[indice_sym] = symtabB[i];
            i_name = search_name(strfu.strsymtab,get_name(strtabB,symtabB[i].st_name),strfu.taille);
            if(i_name == -1){
                strfu.taille = strcat2(strfu.strsymtab,get_name(strtabB,symtabB[i].st_name),strfu.taille);
                symtab_fu[indice_sym].st_name = ind_strsymt;
                ind_strsymt+=strlen(get_name(strtabB,symtabB[i].st_name))+1;
                printf("Valeur de l'indice : %d\n",ind_strsymt);
            }
            else{
                symtab_fu[indice_sym].st_name = i_name;
            }
            indice_sym+=1;
        }
    }
    afficher_symb_tab(symtab_fu,indice_sym,strfu.strsymtab);
    return indice_sym;
}