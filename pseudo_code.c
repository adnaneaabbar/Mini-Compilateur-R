#include "pseudo_code.h"

char *MNEMONIQUESNAMES[21] = {
        "NOP",
        "ADD", "SUB",
        "MUL", "DIV",
        "EQL", "NEQ",
        "GTR", "LSS",
        "GEQ", "LEQ",
        "LDA", "LDI",
        "PRN", "INT",
        "HLT", "INN",
        "STO", "LDV",
        "BZE", "BRN"
};

void init_pseudo_code(){
    PC = -1;
    offset = -1;
    PH = -1;
    adresse_offset = 0;
    PCode[0].mne = NOP;
}

void generer(MNEMONIQUES M)
{
    PC = PC + 1;
    PCode[PC].mne = M;
}

void generer_val(MNEMONIQUES M, int val)
{
    PC = PC + 1;
    PCode[PC].mne = M;
    PCode[PC].suite = val;
}

void PH_generer(MNEMONIQUES M)
{
    PH = PH + 1;
    PileHisto[PH].mne = M;
}

void PH_generer_val(MNEMONIQUES M, int val)
{
    PH = PH + 1;
    PileHisto[PH].mne = M;
    PileHisto[PH].suite = val;
}

instruction SommetPileHisto()
{
    if (PH == -1)
    {
        printf("ERREUR PILE VIDE");
        EXIT_FAILURE;
    }
    PH--;
    return PileHisto[PH + 1];
}