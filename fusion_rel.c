#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "string.h"
#include "elf.h"

#include "util_bis.h"
#include "fusion_rel.h"
#include "section.h"

#define STRING_SIZE_MAX 10000

void fusion_rel(tab_section *tab, char strtab[], Elf32_Sym symtab[], int newOffSet,
            FILE *f1, Elf32_Ehdr header1, Elf32_Shdr sections1[], char strtab1[],
            FILE *f2, Elf32_Ehdr header2, Elf32_Shdr sections2[], char strtab2[])
{
    int num_sec, num_sec_bis ;
    int section_type, section_type_bis ;
    memorize_read memorize_read ;
    section section, section_bis ;
    // Pour sauvegarder les sections lues dans f2
    create_memorize_read(&memorize_read) ;
    // On parcourt toutes les sections de f1
    for (num_sec = 0 ; num_sec < header1.e_shnum ; num_sec ++)
    {
        section_type = sections1[num_sec].sh_type ;
        // On lit les sections de relocation
        if (section_type == SHT_REL || section_type == SHT_RELA) 
        {
            section = read_rel_section(section_type == SHT_RELA, f1, num_sec, 
                                        sections1, symtab, strtab1, strtab, newOffSet) ;
            // On regarde si il en existe une de meme nom dans le deuxieme fichier     
            for (num_sec_bis = 0 ; num_sec_bis < header2.e_shnum ; num_sec_bis ++)
            {
                section_type_bis = sections2[num_sec_bis].sh_type ;
                // Si oui la lit
                if (section_type_bis == SHT_REL || section_type_bis == SHT_RELA) 
                {
                    section_bis = read_rel_section(section_type_bis == SHT_RELA, f2, 
                                                num_sec_bis, sections2, symtab, strtab2, strtab, newOffSet) ;          
                    // On la concatene
                    concat(&section, section_bis) ; 
                    // On memorise l'indice pour ne pas relire cette section
                    add_memorize_read(&memorize_read, num_sec_bis) ;
                    // Seulement une seule possible donc on sort
                    break ;
                }
            }
            // On sauvegarde
            ajouter_tab_section(tab, section) ;   
        }
    }
    // On finit en parcourant toutes les sections de f2
    for (num_sec = 0 ; num_sec < header2.e_shnum ; num_sec ++)
    {
        section_type = sections2[num_sec].sh_type ;
        // On lit les sections de relocation qui n'ont pas deja ete lues
        if (section_type == SHT_REL || section_type == SHT_RELA
            && ! is_in_memorize_read(memorize_read, num_sec)) 
        {
            section = read_rel_section(section_type == SHT_RELA, f2, num_sec, 
                                        sections2, symtab, strtab2, strtab, newOffSet) ;
            // On sauvegarde
            ajouter_tab_section(tab, section) ;   
        }
    }
}

/** Lit la section 'rel' ou 'rela' dans f, definie par les parametres **/
section read_rel_section(bool is_rela, FILE *f, int num_sec, Elf32_Shdr sections[], 
                            Elf32_Sym symtab[], char old_strtab[], char new_strtab[], int offSet)
{
    int entry ;
    section section ;
    // On creer la stucture pour accueillir la section
    creer_section(&section, offSet) ; //sections1[num_sec].sh_offset) ;
    // On parcourt la section
    for (entry = 0 ; entry < sections[num_sec].sh_size ; entry += 8)
    {
         // On se positionne
        fseek(f, sections[num_sec].sh_offset + entry, SEEK_SET) ;
        // On recupere le 'rel'
        Elf32_Addr rel_offset = read_rel_offset(f) ;
        Elf32_Word rel_info = read_rel_info(f, old_strtab, new_strtab) ;
        // Et on sauvegarde
        ajouter_str_section(&section, sprintf("%d", rel_offset)) ;
        ajouter_str_section(&section, sprintf("%d", rel_info)) ;
        // Et son addend si c'est un 'rela' defini sur une section
        if (is_rela && ELF32_ST_TYPE(symtab[ELF32_R_SYM(reverse_4(rel_info))].st_info) == STT_SECTION)
        {
            Elf32_Sword rel_addend = read_rel_addend(f, rel_info) ;
            ajouter_str_section(&section, sprintf("%d", rel_addend)) ;
        }
        
    }

    return section ;
}

/** Retourne l'offset 'du 'rel' a la position de courante de f,
    en effectuant des modifications **/
Elf32_Addr read_rel_offset(FILE *f)
{ 


    // TODO RECUPERER l'offset de Nico



    Elf32_Addr offset ;
    // On lit la variable
    fread(&offset, sizeof(Elf32_Addr), 1, f) ;
    // On change le boutisme
    offset = reverse_4(offset) ;
    // On rechange le boutisme
    offset = reverse_4(offset) ;

    return offset ;
}

/** Retourne l'info 'du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Word read_rel_info(FILE *f, char old_strtab[], char new_strtab[])
{
    Elf32_Word info ;
    // On lit la variable
    fread(&info, sizeof(Elf32_Word), 1, f) ;
    // On change le boutisme
    info = reverse_4(info) ;
    // On change le numero de symbole (index)
    Elf32_Word old_sym_index = ELF32_R_SYM(info) ;
    Elf32_Word new_sym_index = find_new_sym_index(old_sym_index, old_strtab, new_strtab) ;
    info &= 256 ;
    info |= new_sym_index << 8 ;
    // On rechange le boutisme
    info = reverse_4(info) ;

    return info ;
}

/** Retourne l'addend du 'rel' a la position de courante de f, 
    en effectuant des modifications **/
Elf32_Sword read_rel_addend(FILE *f, Elf32_Word rel_info)
{
    

    // TODO RECUPERER l'offset de HUGO



    Elf32_Sword addend ;
    // On lit la variable
    fread(&addend, sizeof(Elf32_Sword), 1, f) ;
    // On change le boutisme
    addend = reverse_4(addend) ;
    // On rajoute l'offset de la concatenation
    switch(ELF32_R_TYPE(inverse_4(rel_info)))        
    {
        case R_ARM_ABS32 : 
            addend += newOffSet ;
            break;
        case R_ARM_CALL : 
        case R_ARM_JUMP24 : 
            addend += newOffSet / 4 ;
    }
    // On rechange le boutisme
    addend = reverse_4(addend) ;

    return addend ;
}

/** Retourne le nouvel index associe au string donne **/
Elf32_Word find_new_sym_index(int old_index, char old_strtab[], char new_strtab[])
{
    char sym[STRING_SIZE_MAX] ;
    int i = 0, j, last_i ;
    int sym_size ;
    // On recupere le string
    get_sym_from_index(sym, old_index, old_strtab) ;
    sym_size = strlen(sym) ;
    // Puis on cherche dans la nouvelle table jusqu'a retrouver le nouvel indice de depart
    while (true)
    {
        last_i = i ;

        for (j = 0 ; j < sym_size ; j ++)
        {
            if (! sym[j] == new_strtab[i])
            {
                break ;
            }

            if (j == sym_size - 1)
            {
                return last_i ;
            }

            i ++ ;
        }
    }

    return 0 ;
}

/** Cherche le string associe a l'index donne **/
void get_sym_from_index(char *sym, int index, char strtab[])
{
    int i ;

    for (i = index ; strtab[i] != '\0' ; i ++)
    {
        *(sym + i) = strtab[i] ;
    }

    *(sym + i) = '\0' ;
}

/** Struct **/

void create_memorize_read(memorize_read *m)
{
    m->size = 0 ;
}

void add_memorize_read(memorize_read *m, int element)
{
    m->elements[m->size] = element ;
    m->size ++ ;
}

bool is_in_memorize_read(memorize_read m, int element)
{
    int i ;

    for (i = 0 ; i < m.size ; i ++)
    {
        if (m.elements[i] == element)
        {
            return true ;
        }
    } 

    return false ;
}