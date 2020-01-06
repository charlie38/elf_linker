#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "elf.h"

#include "fusion_symtab.h"

int fusion_symtab(FILE *A,FILE *B,Elf32_Sym symtabA[],Elf32_Sym symtabB[],int nb_symbA,int nb_symbB){

    /*Déclaration des variables - tableaux*/
    int i;
    int j;
    int save_j;
    int indice_sym = 0;

    Elf32_Sym symtab_fu[max(nb_symbA,nb_symbB)*2];  //symtab_fu est la symtab finale , après fusion
    char strsymtab[NMAX]; //strsymbtab est  la table pour les noms des symboles après fusion

    int traite[nb_symbB]; //Si la valeur est 1 , alors il a été traité (pour les cas avec GLOBAL non défini)

    /*Traitement de tous les symboles du fichier A ( avec ceux en communs du B )*/
    for(i=0;i<nb_symbA;i++){
        save_j = 0;
        switch(ELF32_ST_BIND(symtabA[i].st_info)){

            case STB_LOCAL: //Si c'est LOCAL , alors on met le symbole dans tous les cas

                for(j=0;j<nb_symbB;j++){ //Test pour voir si un symbole du fichier B est identique , ausquel cas il sera en une fois.
                    if(symtabB[j] = symtabA[i]){
                        traite[j] = 1; //On le marque donc
                        save_j = j;
                        j+= nb_symbB;
                    }
                }
                /*Ajout du symbole , correction de l'offset pour la valeur et ajout du nom dans la strsymtab*/
                symtab_fu[indice_sym] = symtabA[i];
                ajouter_nom(strsymtab,symtabA[i].st_name);
                break;

            case STB_GLOBAL: //Si c'est GLOBAL , alors il faut vérifier les différents cas

                for(j=0;j<nb_symbB;j++){
                    if(get_name(symtabA[i]) = get_name(symtabB[j])){ //Test des noms identiques
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
                            printf("Erreur , impossible d'avoir 2 symboles de type GLOBAL du même nom !");
                            return 5;
                        }
                        traite[j] = 1; //Symbole marque
                    }
                }
                if(save_j != 0){
                    /*Ajout du symbole , correction de l'offset pour la valeur et ajout du nom dans la strsymtab*/
                    symtab_fu[indice_sym] = symtabB[save_j];
                    ajouter_nom(strsymtab,symtabB[save_j].st_name);
                }
                else {
                    /*Ajout du symbole , correction de l'offset pour la valeur et ajout du nom dans la strsymtab*/
                    symtab_fu[indice_sym] = symtabA[i];
                    ajouter_nom(strsymtab,symtabA[i].st_name);
                }
                break;
        }
    }

    /*Traitement de tous les symboles du fichier B pas encore traites*/
    for(i=0;i<nb_symbB;i++){
        if(traite[i] != 1){
            symtab_fu[nb_symbA+i] = symtabB[i];
        }
    }
    return 0;
}