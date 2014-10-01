/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 19/9/2014
***************************************************************************************************
* Arquivo: "scanner.c"
* Dependências: "auto_symbol_coment.c" "auto_cahr.c"  "auto_int_float.c" "auto_ident_pChave.c" "scanner.h"
***************************************************************************************************
* Descrição: Contém a função "scanner" e algumas funções auxiliares utilizadas nos demais arquivos.
*/

#include "scanner.h"


int scanner(FILE *inArquivo, TOKEN *retorno)
{
    static int  linha  = 1;
    static int  coluna = 0;
    static char lookupAhead = ' ';
    int status;
    _TOKEN token;

    sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_VARIAVEIS);
    ingnora_espacos(inArquivo, &token);

    //Automato Symbol Coment
    status = auto_symbol_coment(inArquivo, &token);
    if(status == RECONHECE)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        sincroniza_token__token(retorno, &token);
        return RECONHECE;
    }
    else if(status == EOF)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        return EOF;
    }
    //Automato ID PC
    status = auto_id_pc(inArquivo, &token);
    if(status == RECONHECE)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        sincroniza_token__token(retorno, &token);
        return RECONHECE;
    }
    else if(status == EOF)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        return EOF;
    }
    //Automato INT FLOAT
    status = auto_int_float(inArquivo, &token);
    if(status == RECONHECE)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        sincroniza_token__token(retorno, &token);
        return RECONHECE;
    }
    else if(status == EOF)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        return EOF;
    }
    //Automato CHAR
    status = auto_char(inArquivo, &token);
    if(status == RECONHECE)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        sincroniza_token__token(retorno, &token);
        return RECONHECE;
    }
    else if(status == EOF)
    {
        sincroniza_token_com_variaveis(&token, &linha, &coluna, &lookupAhead, FROM_TOKEN);
        return EOF;
    }
    //Nao reconhece o caracter
     printf(COR_VERMELHO"ERRO na linha %d, coluna %d, ultimo token "
            "lido %s: O caracter '%c' nao faz parte da linguagem!\n"
            RESET_COR, token.linha, token.coluna, token.lexema, token.lookupAhead);
    exit(EXIT_FAILURE);
}

void novo_lookupAhead(FILE *inArquivo, _TOKEN *token, int *cont)
{
    (*token).lexema[(*cont)] = (*token).lookupAhead;
    (*token).lexema[(*cont)+1] = '\0';
    (*cont) = (*cont) + 1;
    (*token).lookupAhead = fgetc(inArquivo);
    (*token).coluna++;
    if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
    {
        //(*token).lookupAhead = fgetc(inArquivo);
        (*token).linha++;
        (*token).coluna = 0;
    }
}

void ingnora_espacos(FILE *inArquivo, _TOKEN *token)
{
    while(isspace((*token).lookupAhead) && ((*token).lookupAhead != EOF))
    {
        (*token).lookupAhead = fgetc(inArquivo);
        (*token).coluna++;
        if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
        {
            (*token).lookupAhead = fgetc(inArquivo);
            (*token).linha++;
            (*token).coluna = 0;
        }
    }
}

void sincroniza_token_com_variaveis(_TOKEN *token, int *linha, int *coluna, char *lookupAhead, int sinal)
{
    if(sinal)
    {
        (*token).linha  = *linha;
        (*token).coluna = *coluna;
        (*token).lookupAhead = *lookupAhead;

    }
    else
    {
        *linha  = (*token).linha;
        *coluna = (*token).coluna;
        *lookupAhead = (*token).lookupAhead;
    }
}

void sincroniza_token__token(TOKEN *tokenDestino, _TOKEN *tokenOrigem)
{
    strcpy((*tokenDestino).lexema, (*tokenOrigem).lexema);
    (*tokenDestino).classificacao = (*tokenOrigem).classificacao;
    (*tokenDestino).valor = (*tokenOrigem).valor;
    (*tokenDestino).linha = (*tokenOrigem).linha;
    (*tokenDestino).coluna = (*tokenOrigem).coluna;
}
