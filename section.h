#ifndef SECTION_H
#define SECTION_H
#define SIZE_MAX 50000

typedef struct{
  int offset;
  int taille;
  char content[SIZE_MAX];
} section;

typedef struct{
  section T[SIZE_MAX];
  int nb;
} tab_section;

void creer_section(section *S, int offSet);

void ajouter_char_section(section *S, char c);

void ajouter_str_section(section *S, char *s) ;

void creer_tab_section(tab_section *T, int offSet);

void ajouter_tab_section(tab_section *T, section S);

void afficher_une_section(section S);

void afficher_sections(tab_section tab);

void concat(section* A, section B);

#endif