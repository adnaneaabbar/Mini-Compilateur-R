#ifndef COMPILATEURR_GLOBAL_H
#define COMPILATEURR_GLOBAL_H

// includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


// Definitions
#define LONGUEUR_MOT 200
#define TAILLE_TOKEN_LISTE 40
// definition d'un boolean
typedef enum _boolean {
    false, true
} boolean;
// typedef: enum tokens,
typedef enum
{
    NUM_TOKEN,
    VAR_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    WHILE_TOKEN,
    FOR_TOKEN,
    IN_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    ID_TOKEN,
    ERREUR_TOKEN,
    EOF_TOKEN,
    EG_TOKEN,
    REPEAT_TOKEN,
    OF_TOKEN,
    PP_TOKEN,
    AO_TOKEN,
    AF_TOKEN,
    RETURN_TOKEN,
    FUNCTION_TOKEN,
    HASH_TOKEN,
    IFELSE_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
    AND_TOKEN,
    OR_TOKEN,
    BREAK_TOKEN,
    PRINT_TOKEN,
} CODES_TOKENS;

//CODES_TOKENS Sym_Cour, Sym_Prec;

typedef struct
{
    CODES_TOKENS cls;
    char nom[25];
} CODES_LEX;

CODES_LEX Sym_Cour, Sym_Prec;

// structs: symbol,
/*
typedef enum
{
    TYPE_VAR,
    TYPE_CONST,
    TYPE_PROGRAM
} type_symoble;

typedef struct
{
    type_symoble type;
    char nom[20];
    int adresse_val;
} Symbole;

typedef struct
{
    Symbole *tab;
    int taille;
} _tab_symbole;

_tab_symbole tab_symbole;
*/
// Table de symbole

struct symbole_stocke {
    char nom[LONGUEUR_MOT];
    int valeur;
    int addresse;
    int longueur;
    int offset;

    /* Pour les vecteurs */
    //int start;
    //int end;
};



// Variable declaration
FILE *file;
char Car_Cour, Car_Prec;

int ligne, col, i;
char *chaine_p, chaine[100];

int taille_table_symbole;
int taille_max_table_symbole;
struct symbole_stocke *table_symbole;

int offset;



int PC;
int PH;
int adresse_offset;

//void EXPR();
//void INSTS();
//void INST();
//void COND();


typedef enum
{
    NOP,
    ADD,
    SUB,
    MUL,
    DIV,
    EQL,
    NEQ,
    GTR,
    LSS,
    GEQ,
    LEQ,
    LDA,
    LDI,
    PRN,
    INT,
    HLT,
    INN,
    STO,
    LDV,
    BZE,
    BRN,

} MNEMONIQUES;

typedef struct
{
    MNEMONIQUES mne;
    int suite;
} instruction;


instruction PCode[50], PileHisto[50];

char *MNEMONIQUESNAMES[21];

void init_pseudo_code();
void generer(MNEMONIQUES M);
void generer_val(MNEMONIQUES M, int val);
void PH_generer(MNEMONIQUES M);
void PH_generer_val(MNEMONIQUES M, int val);

instruction SommetPileHisto();


#endif //COMPILATEURR_GLOBAL_H
