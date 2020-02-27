#include "analyseur_lexical.h"
#include "errors.h"

char *TokenNames[] = {
        "NUM_TOKEN",
        "VAR_TOKEN",
        "IF_TOKEN",
        "ELSE_TOKEN",
        "WHILE_TOKEN",
        "FOR_TOKEN",
        "IN_TOKEN",
        "PV_TOKEN",
        "PT_TOKEN",
        "PLUS_TOKEN",
        "MOINS_TOKEN",
        "MULT_TOKEN",
        "DIV_TOKEN",
        "VIR_TOKEN",
        "AFF_TOKEN",
        "INF_TOKEN",
        "INFEG_TOKEN",
        "SUP_TOKEN",
        "SUPEG_TOKEN",
        "DIFF_TOKEN",
        "PO_TOKEN",
        "PF_TOKEN",
        "ID_TOKEN",
        "ERREUR_TOKEN",
        "EOF_TOKEN",
        "EG_TOKEN",
        "REPEAT_TOKEN",
        "OF_TOKEN",
        "PP_TOKEN",
        "AO_TOKEN",
        "AF_TOKEN",
        "RETURN_TOKEN",
        "FUNCTION_TOKEN",
        "HASH_TOKEN",
        "IFELSE_TOKEN",
        "TRUE_TOKEN",
        "FALSE_TOKEN",
        "AND_TOKEN",
        "OR_TOKEN",
        "REPEAT_TOKEN",
        "BREAK_TOKEN",
        "PRINT_TOKEN",


};


void afficher_Token()
{
    if (Sym_Cour.cls != EOF)
    {
        if (Sym_Cour.cls != ERREUR_TOKEN)
            printf("%s \n", TokenNames[Sym_Cour.cls]);
        else
            afficher_Erreur(ERREUR_TOKEN);
    }
}

int lire_comm()
{
    if (Car_Cour == '#')
    {
        while ((fgetc(file) != '\n'))
        {
        }
        col = 1;
        ligne++;
        Car_Cour = fgetc(file);
        return 1;
    }
    return 0;
}

int isseparateur()
{
    if (isspace(Car_Cour) || Car_Cour == '#')
    {
        col++;
        if (Car_Cour == '#')
            return lire_comm();
        else
            Car_Cour = fgetc(file);
        return 1;
    }
    return 0;
}

void lire_nombre()
{
    while (isdigit(Car_Cour))
    {
        *chaine_p++ = Car_Cour;
        Car_Cour = fgetc(file);
        col++;
    }
    *chaine_p = '\0';
    strcpy(Sym_Cour.nom, chaine);

    Sym_Cour.cls = NUM_TOKEN;
}

void lire_mot()
{
    while (isdigit(Car_Cour) || isalpha(Car_Cour))
    {
        *chaine_p++ = Car_Cour;
        Car_Cour = fgetc(file);
        col++;
    }
    *chaine_p = '\0';
    strcpy(Sym_Cour.nom, chaine);
    if (!strcasecmp(chaine, "if"))
        Sym_Cour.cls = IF_TOKEN;
    else if (!strcasecmp(chaine, "else"))
        Sym_Cour.cls = ELSE_TOKEN;
    else if (!strcasecmp(chaine, "while"))
        Sym_Cour.cls = WHILE_TOKEN;
    else if (!strcasecmp(chaine, "else"))
        Sym_Cour.cls = ELSE_TOKEN;
    else if (!strcasecmp(chaine, "for"))
        Sym_Cour.cls = FOR_TOKEN;
    else if (!strcasecmp(chaine, "in"))
        Sym_Cour.cls = IN_TOKEN;
    else if (!strcasecmp(chaine, "repeat"))
        Sym_Cour.cls = REPEAT_TOKEN;
    else if (!strcasecmp(chaine, "ifelse"))
        Sym_Cour.cls = IFELSE_TOKEN;
    else if (!strcasecmp(chaine, "function"))
        Sym_Cour.cls = FUNCTION_TOKEN;
    else if (!strcasecmp(chaine, "TRUE"))
        Sym_Cour.cls = TRUE_TOKEN;
    else if (!strcasecmp(chaine, "FALSE"))
        Sym_Cour.cls = FALSE_TOKEN;
    else if (!strcasecmp(chaine, "REPEAT"))
        Sym_Cour.cls = REPEAT_TOKEN;
    else if (!strcasecmp(chaine, "break"))
        Sym_Cour.cls = BREAK_TOKEN;   
    else if (!strcasecmp(chaine, "print"))
        Sym_Cour.cls = PRINT_TOKEN;  
    else
        Sym_Cour.cls = ID_TOKEN;
}

void sym_suiv()
{
    chaine_p = chaine;
    int res;

    while(isblank(Car_Cour))
    {
        //printf("skip");
        Car_Cour=fgetc(file);
    }

    if(Car_Cour == '\n' || Car_Cour == '\r') {
        Car_Cour=fgetc(file);
        ligne++;
        col = 1;
        return;
    }

    if(Car_Cour == EOF) return;

    while ((res = isseparateur()))
    {
        if (res == 2)
            return;
    }

    if (isdigit(Car_Cour))
        lire_nombre();
    else
    {
        if (isalpha(Car_Cour))
            lire_mot();
        else
        {
            switch (Car_Cour)
            {
                case '(':
                    Sym_Cour.cls = PO_TOKEN;
                    break;
                case ')':
                    Sym_Cour.cls = PF_TOKEN;
                    break;
                case ';':
                    Sym_Cour.cls = PV_TOKEN;
                    break;
                case '{':
                    Sym_Cour.cls = AO_TOKEN;
                    break;
                case ':':
                    Sym_Cour.cls = PP_TOKEN;
                    break;
                case '}':
                    Sym_Cour.cls = AF_TOKEN;
                    break;
                case ',':
                    Sym_Cour.cls = VIR_TOKEN;
                    break;
                case '=':
                    Car_Cour = fgetc(file);
                    if (Car_Cour == '=')
                    {
                        col++;
                        Sym_Cour.cls = EG_TOKEN;
                    }
                    else{
                        Sym_Cour.cls = AFF_TOKEN;
                        fseek(file, -1, SEEK_CUR);
                    }
                    break;
                case '+':
                    Sym_Cour.cls = PLUS_TOKEN;
                    break;
                case '-':
                    Car_Cour = fgetc(file);
                    if(Car_Cour== '>'){
                        Sym_Cour.cls = AFF_TOKEN;
                    }
                    else
                    {
                        Sym_Cour.cls=MOINS_TOKEN;
                    }
                    break;
                case '*':
                    Sym_Cour.cls = MULT_TOKEN;
                    break;
                case '/':
                    Sym_Cour.cls = DIV_TOKEN;
                    break;
                case '.':
                    Sym_Cour.cls = PT_TOKEN;
                    break;
                case '<':
                    Car_Cour = fgetc(file);
                    if (Car_Cour == '-')
                    {
                        col++;
                        Sym_Cour.cls = AFF_TOKEN;
                    }
                    else
                    if (Car_Cour == '=')
                    { col++;
                        Sym_Cour.cls = INFEG_TOKEN;}

                    else
                    {
                        Sym_Cour.cls = INF_TOKEN;
                    }
                    break;
                case '>':
                    Car_Cour = fgetc(file);
                    if (Car_Cour == '=')
                    {
                        col++;
                        Sym_Cour.cls = SUPEG_TOKEN;
                    }
                    else
                        Sym_Cour.cls = SUP_TOKEN;
                    break;
                case '!':
                    Car_Cour = fgetc(file);
                    if (Car_Cour == '=')
                    {
                        col++;
                        Sym_Cour.cls = DIFF_TOKEN;
                    }
                    break;
                case '&':
                    Sym_Cour.cls = AND_TOKEN;
                    break;
                case '|':
                    Sym_Cour.cls = OR_TOKEN;
                    break;
                default:
                    Sym_Cour.cls = ERREUR_TOKEN;
                    Sym_Erreur = ERR_CAR_INC;
                    Car_Cour = fgetc(file);
            }
            col++;
            Sym_Erreur = ERR_CAR_INC;
            if (Sym_Cour.cls != ERREUR_TOKEN && Sym_Cour.cls != INF_TOKEN && Sym_Cour.cls != SUP_TOKEN)
                Car_Cour = fgetc(file);
        }
    }
    afficher_Token();
}

