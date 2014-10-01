/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 19/9/2014
***************************************************************************************************
* Arquivo: "auto_cahr.c"
* Dependências: "scanner.c" "scanner.h"
***************************************************************************************************
* Descrição: Contém a função auto_symbol_coment() e suas sub funções, que reconhece e classica char.
*/

#include "scanner.h"

int auto_char(FILE *inArquivo, _TOKEN *token)
{
    int cont = 0;
    int estado = 0;

    while(TRUE)
    {
        switch(estado)
        {
        case ESTADO_Q0:
            estado = auto_char_Q0(token);
            break;
        case ESTADO_Q1:
            estado = auto_char_Q1(inArquivo, token, &cont);
            break;
        case ESTADO_Q2:
            estado = auto_char_Q2(inArquivo, token, &cont);
            break;
        case ESTADO_Q3:
            estado = auto_char_Q3(inArquivo, token, &cont);
            break;
        case RECONHECE:
            return estado;
        case EOF:
            return EOF;
        case NAO_RECONHECE:
            return NAO_RECONHECE;
        }
    }
}

int auto_char_Q0(_TOKEN *token)
{
    if((*token).lookupAhead == '\'')
    {
        return ESTADO_Q1;
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

int auto_char_Q1(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if(isalpha((*token).lookupAhead) || isdigit((*token).lookupAhead))
    {
        return ESTADO_Q2;
    }
    printf(COR_VERMELHO"ERRO na linha %d, coluna %d, ultimo token "
            "lido %s: char mau formado!\n"
            RESET_COR, (*token).linha, (*token).coluna, (*token).lexema);
    exit(EXIT_FAILURE);
}

int auto_char_Q2(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if((*token).lookupAhead == '\'')
    {
        return ESTADO_Q3;
    }
    printf(COR_VERMELHO"ERRO na linha %d, coluna %d, ultimo token "
            "lido %s: char mau formado!\n"
            RESET_COR, (*token).linha, (*token).coluna, (*token).lexema);
    exit(EXIT_FAILURE);
}

int auto_char_Q3(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    (*token).classificacao = CLASSE_T_CHAR;
    return RECONHECE;
}
