#ifndef COMPILATEURR_ANALYSEUR_SYNTAXIQUE_H
#define COMPILATEURR_ANALYSEUR_SYNTAXIQUE_H

//#include "global.h"
#include "errors.h"
#include "analyseur_lexical.h"
#include "analyseur_semantique.h"


void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR);
// void FUNCTION();

void AFF();
void FACT();
void MULT_DIV();
void PLUS_MOINS();
void TERM();
void EXPR();
void COND();
void SI();
void TANTQUE();
void POUR();
void INST();
void REPEAT();
void PRINT();




#endif //COMPILATEURR_ANALYSEUR_SYNTAXIQUE_H
