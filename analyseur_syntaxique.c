#include "analyseur_syntaxique.h"

void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR)
{
    if (Sym_Cour.cls == cl)
    {
        sym_suiv();
    }
    else
        afficher_Erreur(COD_ERR);
}

void AFF(){
    ajouter_symbole();
    generer_val(INT, offset + 1);
    generer_val(LDA, table_symbole[symbole_existe()].addresse);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    EXPR();
    generer(STO);
}

void FACT()
{
    switch (Sym_Cour.cls)
    {
        case ID_TOKEN:
            if(symbole_specifique_existe(Sym_Cour.nom) == -1) afficher_erreur_semantique(Sym_Cour.nom);
            generer_val(LDA, table_symbole[symbole_existe()].addresse);
            generer(LDV);
            sym_suiv();
            break;
        case NUM_TOKEN:
            generer_val(LDI, atoi(chaine));
            sym_suiv();
            break;
        case PO_TOKEN:
            sym_suiv();
            EXPR();
            Test_Symbole(PF_TOKEN, PF_ERR);
            break;
        default:
            afficher_Erreur(FACT_ERR);
    }
}
void MULT_DIV(){
    switch (Sym_Cour.cls)
    {
        case MULT_TOKEN:
            sym_suiv();
            PH_generer(MUL);
            break;
        case DIV_TOKEN:
            sym_suiv();
            PH_generer(DIV);
            break;
        default:
            afficher_Erreur(MULT_DIV_ERR);
    }
}

void PLUS_MOINS(){
    switch (Sym_Cour.cls)
    {
        case PLUS_TOKEN:
            sym_suiv();
            PH_generer(ADD);
            break;
        case MOINS_TOKEN:
            sym_suiv();
            PH_generer(SUB);
            break;
        default:
            afficher_Erreur(MOINS_PLUS_ERR);
    }
}

void TERM(){
    FACT();
    if (Sym_Cour.cls == DIV_TOKEN || Sym_Cour.cls == MULT_TOKEN)
    {
        MULT_DIV();
        FACT();
        generer(SommetPileHisto().mne);
    }
}

void EXPR(){
    TERM();
    if (Sym_Cour.cls == PLUS_TOKEN || Sym_Cour.cls == MOINS_TOKEN)
    {
        PLUS_MOINS();
        TERM();
        generer(SommetPileHisto().mne);
    }
}

void COND(){
    EXPR();
    switch (Sym_Cour.cls)
    {
        case EG_TOKEN:
            PH_generer(EQL);
            break;
        case DIFF_TOKEN:
            PH_generer(NEQ);
            break;
        case INF_TOKEN:
            PH_generer(LSS);
            break;
        case SUP_TOKEN:
            PH_generer(GTR);
            break;
        case INFEG_TOKEN:
            PH_generer(LEQ);
            break;
        case SUPEG_TOKEN:
            PH_generer(GEQ);
            break;
        default:
            afficher_Erreur(ERREUR_ERR);
    }
    sym_suiv();
    EXPR();
}

//SI := IF(COND){INST} [ELSE{INST}|e]
void SI()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    COND();
    int pc = PC +1;
    generer_val(BZE, pc);
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN,AO_ERR);
    do
    {
        sym_suiv();
        INST();
    } while(Sym_Cour.cls != AF_TOKEN);
    int _pc = PC + 1;
    generer_val(BRN, _pc);
    PCode[pc].suite = PC + 1;
    //} while(Car_Cour != '}');
    //INST();
    Test_Symbole(AF_TOKEN,AF_ERR);
    if (Sym_Cour.cls == ELSE_TOKEN) {
        Test_Symbole(AO_TOKEN,AO_ERR);
        sym_suiv();
        INST();
        PCode[_pc].suite = PC + 1;
        Test_Symbole(AF_TOKEN,AF_ERR);
    }
}

void TANTQUE(){
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    COND();
    int pc = PC + 1;
    generer_val(BZE, pc);
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN, AO_ERR);
    do
    {
        sym_suiv();
        INST();
    } while(Sym_Cour.cls != AF_TOKEN);

    Test_Symbole(AF_TOKEN,AF_ERR);
    PCode[pc].suite = PC + 1;
}

void POUR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    ajouter_symbole();
    generer_val(INT, offset + 1);
    generer_val(LDA, table_symbole[symbole_existe()].addresse);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(IN_TOKEN, IN_ERR);
    generer_val(LDI, atoi(chaine));
    generer(STO);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(PP_TOKEN,PP_ERR);
    int end = atoi(chaine);
    generer_val(LDA, table_symbole[symbole_existe()].addresse);
    int pc = PC;
    generer(LDV);
    generer_val(LDI, end);
    generer(LEQ);
    int _pc = PC;
    generer_val(BZE, PC + 1);
    Test_Symbole(NUM_TOKEN,NUM_ERR);
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN,AO_ERR);
    do
    {
        sym_suiv();
        INST();
    } while(Sym_Cour.cls != AF_TOKEN);
    generer_val(LDA, table_symbole[symbole_existe()].addresse);
    generer_val(LDA, table_symbole[symbole_existe()].addresse);
    generer(LDV);
    generer_val(LDI, 1);
    generer(ADD);
    generer(STO);
    generer_val(BRN, pc);
    PCode[_pc].suite = PC+1;
    Test_Symbole(AF_TOKEN,AF_ERR);
}


void REPEAT(){
    Test_Symbole(REPEAT_TOKEN,REPEAT_ERR);
    int pc = PC;
    Test_Symbole(AO_TOKEN,AO_ERR);

    while(Sym_Cour.cls != IF_TOKEN)
    {
        INST();
        sym_suiv();
    }
    //if(Sym_Cour.cls == IF_TOKEN){
    Test_Symbole(IF_TOKEN,IF_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    COND();
    generer_val(BZE, pc + 1);
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(BREAK_TOKEN,BREAK_ERR);

    Test_Symbole(AF_TOKEN,AF_ERR);
}



void INST()
{
    switch(Sym_Cour.cls)
    {
        case ID_TOKEN: AFF(); break;
        case IF_TOKEN: SI(); break;
        case WHILE_TOKEN:   TANTQUE(); break;
        case FOR_TOKEN: POUR(); break;
        case REPEAT_TOKEN: REPEAT(); break;

    }
}
