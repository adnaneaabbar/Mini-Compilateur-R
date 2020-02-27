#include "global.h"
#include "analyseur_syntaxique.h"
#include "pseudo_code.h"


int main(int argc, char **argv)
{  
    if (argc != 2){
        printf("no input file\n");
        printf("Usage : %s FILE\n", argv[0]);
        exit(0);
    }
    printf("La liste des tokens : \n");
    ligne = 1;
    col = 1;
    init_table_symbole();
    init_pseudo_code();
    file = fopen(argv[1], "r+");
    Car_Cour = fgetc(file);
    do
    {
        sym_suiv();
        INST();
    } while(Car_Cour!=EOF);

    afficher_table_symbole();
    printf("Le pseudo-code :\n\n");
    for (int i = 0; i <= PC; i++)
    {
        if (PCode[i].mne == LDI || PCode[i].mne == LDA || PCode[i].mne == INT || PCode[i].mne == BZE || PCode[i].mne == BRN)
        {
            printf("%3d : %s %d\n",i, MNEMONIQUESNAMES[PCode[i].mne], PCode[i].suite);
        }
        else
        {
            printf("%3d : %s\n",i, MNEMONIQUESNAMES[PCode[i].mne]);
        }
    }
}