#include "analyseur_semantique.h"


// initialiser la table de symbole
void init_table_symbole() {
    taille_table_symbole = 0;
    taille_max_table_symbole = 10;
    PC = 0;

    table_symbole = malloc(taille_max_table_symbole * sizeof(struct symbole_stocke));
}

// changer la taille de la table de symbole
static void changer_taille() {
    taille_max_table_symbole += 10;
    table_symbole = realloc(table_symbole, taille_max_table_symbole * sizeof(struct symbole_stocke));
}

// ajouter un symbole à la table de symbole
boolean ajouter_symbole() {

    // Vérifier d'abord que le symbole existe dans la table des symboles
    int index = symbole_existe();
    if (index == -1) {
        adresse_offset++;
        // If there are no more space in the symbol table
        if (taille_table_symbole > taille_max_table_symbole) {
            changer_taille();
        }
        // ajout du symbole à la table
        strcpy(table_symbole[taille_table_symbole].nom, Sym_Cour.nom);
        //printf("%s added to the symbol table\n", table_symbole[taille_table_symbole].nom);
        table_symbole[taille_table_symbole].offset   = adresse_offset;
        table_symbole[taille_table_symbole].addresse = adresse_offset + PC++;
        //table_symbole[taille_table_symbole].valeur = atof(chaine);

        // Incrémentation de la taille de la table des symboles
        taille_table_symbole++;
    }
    else{
        return 0;
    }

}

int symbole_existe() {
    for (int i = 0; i < taille_table_symbole; i++) {
        if ( strcmp(table_symbole[i].nom, Sym_Cour.nom) == 0 )
            return i;
    }
    return -1;
}

// Obtenir l'adresse du symbole actuel

int get_address() {
    for (int i = 0; i < taille_table_symbole; i++) {
        if ( strcmp(table_symbole[i].nom, Sym_Cour.nom) == 0 )
            return table_symbole[i].addresse;
    }

    return -1;
}

/* Vérifier si un symbole spécifique existe déjà dans la table des symboles
 * renvoie l'index du symbole dans le tableau s'il existe
 * ou retourner -1 si le symbole n'existe pas dans le tableau
 */

int symbole_specifique_existe(char *symbole) {
    for (int i = 0; i < taille_table_symbole; i++) {
        if ( strcmp(table_symbole[i].nom, symbole) == 0 )
            return i;
    }
    return -1;
}

void afficher_table_symbole(){
    printf("\n\n");
    printf("================================\n");
    printf("====== Table des symboles ======\n");
    printf("================================\n");
    printf(" Symbole  |  Adresse  |  Offset \n");
    for(int i = 0; i < taille_table_symbole ; i++) {
		printf("%10s | %9d | %7d \n", table_symbole[i].nom, table_symbole[i].addresse, table_symbole[i].offset);
	}
    printf("================================\n");
    printf("\n\n");
}