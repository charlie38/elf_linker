#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "string.h"
#include "elf.h"
#include "util_bis.h"
#include "fusion_rel.h"
#include "read_elf_rel.h"

#define STRING_SIZE_MAX 10000

void fusion_rel(section_tab *tab, char strtab[], Elf32_Sym symtab[], int newOffSet,
            FILE *f1, Elf32_Ehdr header1, Elf32_Shdr sections1[], char strtab1[],
            FILE *f2, Elf32_Ehdr header2, Elf32_Shdr sections2[], char strtab2[])
{
    int num_sec ;
    // On parcourt toutes les sections de f1
    for (num_sec = 0 ; num_sec < header1.e_shnum ; num_sec ++)
    {
        // On lit les sections de relocation
        if (sections1[num_sec].sh_type == SHT_REL) 
        {
            add_section_to_tab(tab, read_rel_section(false, f1, num_sec, sections1, 
                                symtab, strtab1, strtab, newOffSet)) ;
        }
        else if (sections1[num_sec].sh_type == SHT_RELA)
        {
            add_section_to_tab(tab, read_rel_section(true, f1, num_sec, sections2, 
                                symtab, strtab1, strtab, newOffSet)) ;
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
    create_rel_section(&section, offSet) ; //sections1[num_sec].sh_offset) ;
    // On parcourt la section
    for (entry = 0 ; entry < sections[num_sec].sh_size ; entry += 8)
    {
         // On se positionne
        fseek(f, sections[num_sec].sh_offset + entry, SEEK_SET) ;
        // On recupere le 'rel'
        Elf32_Addr rel_offset = read_rel_offset(f) ;
        Elf32_Word rel_info = read_rel_info(f, old_strtab, new_strtab) ;
        // Et son addend si c'est un 'rela' defini sur une section
        if (is_rela && symtab[ELF32_R_SYM(reverse_4(rel_info))] == STT_SECTION)
        {
            Elf32_Sword rel_addend = read_rel_addend(f, rel_info) ;
        }
        // Et on sauvegarde
        add_rel_to_section() ;
    }

    return section ;
}

/** Retourne l'offset 'du 'rel' a la position de courante de f **/
Elf32_Addr read_rel_offset(FILE *f)
{
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

/** Structs **/

void create_rel_section(section *section, int offSet)
{
    section->size = 0 ;
    section->offSet = offSet ;
}

void add_rel_to_section(section *section, char *rel)
{
    section->content[section->size] = rel ;
    section->size ++ ;
}

void create_sections_tab(section_tab *tab)
{
    tab->size = 0 ;
}

void add_section_to_tab(section_tab *tab, char *section)
{
    tab->content[tab->size] = section ;
    tab->size ++ ;
}