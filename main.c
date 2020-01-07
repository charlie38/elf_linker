#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"
#include "elf_linker-1.0/util.h"
#include "util_bis.h"
#include "string.h"

#include "read_elf_sect.h"
#include "read_elf_head.h"
#include "read_elf_symt.h"
#include "read_elf_rel.h"
#include "print_elf_head.h"
#include "print_elf_sect.h"
#include "print_elf_symt.h"
#include "print_elf_rel.h"

/*Utilisation :
Argument 1 : Le fichier à traiter ( exemple : exemple1.o )
Argument 2-n : Les options à choisir ( -s , -a , -h , -S , -r)
*/


int main(int argc,char *argv[]){


    //Gestion erreurs nombre argument
    if(argc < 3){
        printf("Erreur, pas de fichier/arguments donné(s) !\n");
        return 3;
    }


    //Ouverture fichier
    FILE *f;
    f = NULL;
    f = fopen(argv[1],"r");


    //Gestion erreurs sur le fichier en lecture
    if(f==NULL) {
        printf("Erreur, fichier inexistant ou non ouvrable en lecture !\n");
        return 4;
    }


    //Declaration des variables et lectures
    Elf32_Ehdr head;
    Elf32_Shdr section_tab[30];
    Elf32_Sym symtab[30];

    int opt;
    int index;
    int nb_symb;
    int num_sec;

    //Lecture de l'entête
    head = read_header(f);
    
    //Lecture de l'entête des sections (SHT)
    read_section(f,section_tab,head.e_shoff,head.e_shnum);


    //Initialisation des tables des noms des sections et des noms des symboles
    char strtab[section_tab[head.e_shstrndx].sh_size];
    char strsymtab[section_tab[head.e_shstrndx+2].sh_size];

    //Lecture des tables de noms : sections , symboles
    read_string_table(f,head,section_tab,strtab,head.e_shstrndx);
    read_string_table(f,head,section_tab,strsymtab,head.e_shstrndx+2);

    //Numéro de la section de la table des symboles
    index = index_symtab(section_tab);
    nb_symb = section_tab[index].sh_size/sizeof(Elf32_Sym);

    //Lecture de la table des symboles
    read_symtab(f,symtab,section_tab,section_tab[index].sh_offset,nb_symb);

    for(opt=2;opt<argc;opt++){
        //Affichage de toutes les options
        if(strcmp(argv[opt],"-a") == 0){
            print_elf_head(head);
            afficher_sht(section_tab,head.e_shnum,strtab);
            afficher_rel(f,head,section_tab,strtab,symtab);
            afficher_symb_tab(symtab,nb_symb,strsymtab);
        }
        //Affichage de l'entête du fichier
        if((strcmp(argv[opt],"-h") == 0)){
            print_elf_head(head);
        }
        //Affichage de la table des entêtes de sections
        if((strcmp(argv[opt],"-S") == 0)){
            afficher_sht(section_tab,head.e_shnum,strtab);
        }
        //Affichage d'une section ( à donner en entrée )
        if(strcmp(argv[opt],"-x") == 0){
            printf("Veuillez rentrez un numéro de section : ");
            scanf("%d",&num_sec);
            if(num_sec > head.e_shnum){
                printf("Erreur , la section n'existe pas !\n");
                return 5;
            }
            else{
                afficher_section_hexa(f,section_tab,num_sec,strtab);
            }
        }
        //Affichage de la table des symboles
        if((strcmp(argv[opt],"-s") == 0)){
            afficher_symb_tab(symtab,nb_symb,strsymtab);
        }
        //Affichage des relocations
        if((strcmp(argv[opt],"-r") == 0)){
            afficher_rel(f,head,section_tab,strtab,symtab);
        }
    }
    fclose(f);
    return 0;
}
