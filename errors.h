//
// Created by AIT RAMI on 2/10/2020.
//

#ifndef COMPILATEURR_ERRORS_H
#define COMPILATEURR_ERRORS_H

#include "global.h"

typedef enum
{
    ERR_FICH_VID,
    ERR_CAR_INC,
    ERR_ID_LONG,
    ERR_NUM_LONG,
    ERR_END_COM,
} Erreurs;

typedef enum
{
    PROGRAM_ERR,
    NUM_ERR,
    CONST_ERR,
    VAR_ERR,
    BEGIN_ERR,
    END_ERR,
    IF_ERR,
    THEN_ERR,
    WHILE_ERR,
    DO_ERR,
    READ_ERR,
    WRITE_ERR,
    PV_ERR,
    PT_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    VIR_ERR,
    AFF_ERR,
    INF_ERR,
    INFEG_ERR,
    SUP_ERR,
    SUPEG_ERR,
    DIFF_ERR,
    PO_ERR,
    PF_ERR,
    FIN_ERR,
    ID_ERR,
    ERREUR_ERR,
    EOF_ERR,
    EG_ERR,
    ELSE_ERR,
    FOR_ERR,
    INTO_ERR,
    DOWNTO_ERR,
    UNTIL_ERR,
    CASE_ERR,
    OF_ERR,
    PP_ERR,
    CONST_VAR_BEGIN_ERR,
    VAR_BEGIN_ERR,
    MOINS_PLUS_ERR,
    MULT_DIV_ERR,
    FACT_ERR,
    INTO_DOWNTO_ERR,
    SYMBOLE_EXIST_ERR,
    SYMBOLE_NOT_DECLARED_ERR,
    SYMBOLE_CONST_MODIF_ERR,
    SYMBOLE_PROGID_MODIF_ERR,AO_ERR,AF_ERR,
    IN_ERR,FUNCTION_ERR,REPEAT_ERR,
    BREAK_ERR,
    PRINT_ERR
} ERREUR_TOKENS;

Erreurs Sym_Erreur;

void afficher_Erreur(ERREUR_TOKENS COD_ERR);
void afficher_erreur_semantique(char *Symbole);

#endif //COMPILATEURR_ERRORS_H
