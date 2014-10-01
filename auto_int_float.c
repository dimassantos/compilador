/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 19/9/2014
***************************************************************************************************
* Arquivo:  "auto_int_float.c"
* Dependências: "scanner.c" "scanner.h"
***************************************************************************************************
* Descrição: Contém a função auto_int_float() e suas sub funções, que reconhece e classifica inteiros e floats.
*/

#include "scanner.h"

int auto_int_float(FILE *inArquivo, _TOKEN *token)
{
    int cont=0;
    int estado=0;
    while(TRUE)
    {
        switch(estado)
        {
        case ESTADO_Q0:
            estado = auto_int_float_estado_Q0(token);
            break;
        case ESTADO_Q1:
            estado = auto_int_float_estado_Q1(inArquivo, token, &cont);
            break;
        case ESTADO_Q2:
            estado = auto_int_float_estado_Q2(inArquivo, token, &cont);
            break;
        case ESTADO_Q3:
            estado = auto_int_float_estado_Q3(token);
            break;
        case ESTADO_Q4:
            estado = auto_int_float_estado_Q4(token);
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

int auto_int_float_estado_Q0(_TOKEN *token)
{
    if(isdigit((*token).lookupAhead))
    {
        return ESTADO_Q1;
    }
    else if((*token).lookupAhead == '.')
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

int auto_int_float_estado_Q1(FILE* inArquivo, _TOKEN *token, int *cont)
{
    while(isdigit((*token).lookupAhead) && (*token).lookupAhead != EOF)
    {
        novo_lookupAhead(inArquivo, token, cont);
    }
    if((*token).lookupAhead == '.')
    {
        return ESTADO_Q2;
    }
    return ESTADO_Q4;
}

int auto_int_float_estado_Q2(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if(!isdigit((*token).lookupAhead))
    {
        printf(COR_VERMELHO"ERRO na linha %d, coluna %d, ultimo token lido %s: float mau formado!\n"RESET_COR, (*token).linha, (*token).coluna, (*token).lexema);
        exit(EXIT_FAILURE);
    }
    while(isdigit((*token).lookupAhead) && (*token).lookupAhead != EOF)
    {
        novo_lookupAhead(inArquivo, token, cont);
    }
    return ESTADO_Q3;
}

int auto_int_float_estado_Q3(_TOKEN *token)
{
    (*token).classificacao = CLASSE_T_FLOAT;
    return RECONHECE;
}

int auto_int_float_estado_Q4(_TOKEN *token)
{
    (*token).classificacao = CLASSE_T_INTEIRO;
    return RECONHECE;
}
