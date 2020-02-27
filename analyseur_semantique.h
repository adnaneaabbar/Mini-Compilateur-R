#ifndef COMPILATEURR_ANALYSEUR_SEMANTIQUE_H
#define COMPILATEURR_ANALYSEUR_SEMANTIQUE_H

#include "global.h"
void init_table_symbole();
static void changer_taille();
boolean ajouter_symbole();
int get_address();
int symbole_existe();
void afficher_table_symbole();
int symbole_specifique_existe(char *symbole);

#endif //COMPILATEURR_ANALYSEUR_SEMANTIQUE_H
