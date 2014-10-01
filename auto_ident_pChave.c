/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 19/9/2014
***************************************************************************************************
* Arquivo: "auto_ident_pChave.c"
* Dependências: "scanner.c" "scanner.h"
***************************************************************************************************
* Descrição: Contém a função auto_symbol_coment() e suas sub funções, que reconhece e classica identificadores e palavras chaves.
*/

#include "scanner.h"

int auto_id_pc(FILE *inArquivo, _TOKEN *token)
{
    int cont=0;
    int estado=0;
    while(TRUE)
    {
        switch(estado)
        {
        case ESTADO_Q0:
            estado = auto_id_pc_estado_Q0(token);
            break;
        case ESTADO_Q1:
            estado = auto_id_pc_estado_Q1(inArquivo, token, &cont);
            break;
        case ESTADO_Q2:
            estado = auto_id_pc_estado_Q2(inArquivo, token, &cont);
            break;
        case ESTADO_Q3:
            estado = auto_id_pc_estado_Q3(token);
            break;
        case ESTADO_Q4:
            estado = auto_id_pc_estado_Q4(token);
            break;
        case RECONHECE:
            return RECONHECE;
        case NAO_RECONHECE:
            return NAO_RECONHECE;
        case EOF:
            return EOF;
        }
    }
}

int auto_id_pc_estado_Q0(_TOKEN *token)
{
    if((*token).lookupAhead == '_')
    {
        return ESTADO_Q1;
    }
    else if(isalpha((*token).lookupAhead))
    {
        return ESTADO_Q2;
    }
    else if((*token).lookupAhead == EOF)
    {
        return EOF;
    }
    else
    {
        return NAO_RECONHECE;
    }
}

int auto_id_pc_estado_Q1(FILE *inArquivo, _TOKEN *token, int *cont)
{
    while((isalpha((*token).lookupAhead) || (*token).lookupAhead == '_' || isdigit((*token).lookupAhead)) &&
          ((*token).lookupAhead != EOF))
    {
        novo_lookupAhead(inArquivo, token, cont);
    }
    return ESTADO_Q3;
}

int auto_id_pc_estado_Q2(FILE *inArquivo, _TOKEN *token, int *cont)
{
    while(isalpha((*token).lookupAhead) && (*token).lookupAhead != EOF)
    {
        novo_lookupAhead(inArquivo, token, cont);
    }
    if((*token).lookupAhead == '_' || isdigit((*token).lookupAhead))
    {
        return ESTADO_Q1;
    }
    return ESTADO_Q4;
}

int auto_id_pc_estado_Q3(_TOKEN *token)
{
    (*token).classificacao = CLASSE_IDENTIFICADOR;
    return RECONHECE;
}

int auto_id_pc_estado_Q4(_TOKEN *token)
{
    int i;
    static char pReservadas [9][6] = {"main", "if", "else", "while", "do", "for", "int", "float", "char"};
    for(i=0; i<9; i++)
    {
        if(0 == strcmp((*token).lexema, pReservadas[i]))
        {
            switch(i)
            {
            case 0:
                (*token).classificacao = CLASSE_KW_MAIN;
                break;
            case 1:
                (*token).classificacao = CLASSE_KW_IF;
                break;
            case 2:
                (*token).classificacao = CLASSE_KW_ELSE;
                break;
            case 3:
                (*token).classificacao = CLASSE_KW_WHILE;
                break;
            case 4:
                (*token).classificacao = CLASSE_KW_DO;
                break;
            case 5:
                (*token).classificacao = CLASSE_KW_FOR;
                break;
            case 6:
                (*token).classificacao = CLASSE_KW_INT;
                break;
            case 7:
                (*token).classificacao = CLASSE_KW_FLOAT;
                break;
            case 8:
                (*token).classificacao = CLASSE_KW_CHAR;
                break;
            }
            return RECONHECE;
        }
    }
    return ESTADO_Q3;
}





