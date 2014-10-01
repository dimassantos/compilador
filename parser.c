/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 30/9/2014
***************************************************************************************************
* Arquivo:  "parser.c"
* Dependências: "auto_symbol_coment.c" "auto_cahr.c" "scanner.c" "auto_ident_pChave.c" "auto_int_float.c"
*               "scanner.h" "parser.h"
***************************************************************************************************
* Descrição: Contém a todas as funções do parser
*/
#include "parser.h"


void parser(FILE *inArquivo)
{
    TOKEN token;
    p_chamaScanner(inArquivo, &token);
    p_programa(inArquivo, &token);
}

/** PROGRAMA */
void p_programa(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_KW_INT )
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_KW_MAIN)
        {
            p_chamaScanner(inArquivo, token);
            if((*token).classificacao == CLASSE_ABRI_PARENTESE)
            {
                p_chamaScanner(inArquivo, token);
                if((*token).classificacao == CLASSE_FECHA_PARENTESE)
                {
                    p_chamaScanner(inArquivo, token);
                    p_bloco(inArquivo, token);
                    if((*token).classificacao != EOF)
                    {
                        p_erroMsg((*token), "o token esperado era EOF");
                    }
                }
                else{
                    p_erroMsg((*token), "o token esperado era )");
                }
            }
            else{
                p_erroMsg((*token), "o token esperado era (");
            }
        }
        else{
            p_erroMsg((*token), "a funcao main deve ser declarada apos int");
        }
    }
    else{
        p_erroMsg((*token), "a funcao main deve precedida de int");
    }
}//FIM DE PROGRAMA

/** BLOCO */
void p_bloco(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_ABRI_CHAVE)
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_KW_INT || (*token).classificacao == CLASSE_KW_FLOAT ||
                (*token).classificacao ==  CLASSE_KW_CHAR )
        {
               while(p_declVar(inArquivo, token));
        }

        while(p_comando(inArquivo, token));

        if((*token).classificacao == CLASSE_FECHA_CHAVES)
        {
            p_chamaScanner(inArquivo, token);
        }
        else{
            p_erroMsg((*token), "o token esperado era }");
        }
    }
    else{
        p_erroMsg((*token), "o token esperado era {");
    }
}//FIM DE BLOCO

/** DECL_VAR */
int p_declVar(FILE *inArquivo, TOKEN *token)
{
    //printf("\nChama p_declVar -  lexema %s   -  Classificacao %i\n",(*token).lexema, (*token).classificacao );
    if((*token).classificacao == CLASSE_KW_INT || (*token).classificacao == CLASSE_KW_FLOAT ||
                (*token).classificacao ==  CLASSE_KW_CHAR )
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_IDENTIFICADOR)
        {
            p_chamaScanner(inArquivo, token);
            while((*token).classificacao == CLASSE_VIRGULA)
            {
                p_chamaScanner(inArquivo, token);
                if((*token).classificacao == CLASSE_IDENTIFICADOR)
                {
                    p_chamaScanner(inArquivo, token);

                }
                else if((*token).classificacao == CLASSE_PONTO_VIRGULA)
                {
                    break;
                }
                else{
                    p_erroMsg((*token), "o token esperado era um identificador");
                }
            }
        }
        else{
            p_erroMsg((*token), "o token esperado era um identificador");
        }

        if((*token).classificacao != CLASSE_PONTO_VIRGULA)
        {
            p_erroMsg((*token), "o token esperado era ;");
        }
        p_chamaScanner(inArquivo, token);
        return (1);
    }
    return (0);
}//FIM DE DECL_VAR

/** COMANDO */
int p_comando(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_IDENTIFICADOR || (*token).classificacao == CLASSE_ABRI_CHAVE)
    {
        p_comandoBasico(inArquivo, token);
    }
    else if((*token).classificacao == CLASSE_KW_DO || (*token).classificacao == CLASSE_KW_WHILE)
    {
        p_iteracao(inArquivo, token);
    }
    else if((*token).classificacao == CLASSE_KW_IF)
    {
        p_ifElse(inArquivo, token);
    }
    else{
        return (0);
    }
    return (1);
}//FIM DE COMANDO

/** COMANDO BASICO */
void p_comandoBasico(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_IDENTIFICADOR)
    {
        p_atribuicao(inArquivo, token);
    }
    else if((*token).classificacao == CLASSE_ABRI_CHAVE)
    {
        p_bloco(inArquivo, token);
    }
}//FIM DE COMANDO BASICO

/** ATRIBUIÇÃO */
void p_atribuicao(FILE* inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_IDENTIFICADOR)
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_ATRIBUICAO)
        {
            p_chamaScanner(inArquivo, token);
            p_exprArit(inArquivo, token);
            if((*token).classificacao == CLASSE_PONTO_VIRGULA)
            {
                p_chamaScanner(inArquivo, token);
            }
            else{
                p_erroMsg((*token), "o token esperado era ;");
            }
        }
        else{
            p_erroMsg((*token), "o token esperado era =");
        }
    }
    else{
        p_erroMsg((*token), "o token esperado era um identificador");
    }
}//FIM DE ATRIBUIÇÃO

/** EXPR_ARIT */
void p_exprArit(FILE *inArquivo, TOKEN *token)
{
    while((*token).classificacao == CLASSE_IDENTIFICADOR || (*token).classificacao == CLASSE_T_CHAR ||
       (*token).classificacao == CLASSE_T_FLOAT || (*token).classificacao == CLASSE_T_INTEIRO || (*token).classificacao == CLASSE_ABRI_PARENTESE)
    {
        p_termo(inArquivo, token);
        if((*token).classificacao == CLASSE_SOMA || (*token).classificacao == CLASSE_SUBTRACAO)
        {
            p_chamaScanner(inArquivo, token);
            p_exprArit(inArquivo, token);
        }
        else{
            break;
        }
    }
}//FIM DE EXPR_ARIT

/** TERMO */
void p_termo(FILE *inArquivo, TOKEN *token)
{
    while((*token).classificacao == CLASSE_IDENTIFICADOR || (*token).classificacao == CLASSE_T_CHAR ||
       (*token).classificacao == CLASSE_T_FLOAT || (*token).classificacao == CLASSE_T_INTEIRO || (*token).classificacao == CLASSE_ABRI_PARENTESE)
    {
        p_fator(inArquivo, token);
        if((*token).classificacao == CLASSE_MULTIPLCACAO || (*token).classificacao == CLASSE_DIVISAO)
        {
            p_chamaScanner(inArquivo, token);
            p_termo(inArquivo, token);
        }
        else{
            break;
        }
    }
}//FIM DE TERMO

/** FATOR */
void p_fator(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_ABRI_PARENTESE)
    {
        p_chamaScanner(inArquivo, token);
        p_exprArit(inArquivo, token);
        if((*token).classificacao == CLASSE_FECHA_PARENTESE)
        {
            p_chamaScanner(inArquivo, token);
        }
        else{
            p_erroMsg((*token), "o token esperado era )");
        }
    }
    else if((*token).classificacao == CLASSE_IDENTIFICADOR || (*token).classificacao == CLASSE_T_CHAR ||
       (*token).classificacao == CLASSE_T_FLOAT || (*token).classificacao == CLASSE_T_INTEIRO)
    {
        p_chamaScanner(inArquivo, token);
    }
    else{
        p_erroMsg((*token), "o token esperado era um char ou float ou int ou identificador");
    }
}//FIM DE FATOR

/** EXPR_RELAC */
void p_exprRelac(FILE *inArquivo, TOKEN *token)
{
    p_exprArit(inArquivo, token);
    if((*token).classificacao >= 20 && (*token).classificacao <= 25)
    {
        p_chamaScanner(inArquivo, token);
        p_exprArit(inArquivo, token);
    }
    else{
        p_erroMsg((*token), "o token esperado era um operador relacional == ou >= ou > ou < ou <= ou !=");
    }
}//FIM DE EXPR_RELAC

/** ITERAÇÃO */
void p_iteracao(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_KW_WHILE)
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_ABRI_PARENTESE)
        {
            p_chamaScanner(inArquivo, token);
            p_exprRelac(inArquivo, token);
            if((*token).classificacao == CLASSE_FECHA_PARENTESE)
            {
                p_chamaScanner(inArquivo, token);
                if(!p_comando(inArquivo, token))
                {
                    p_erroMsg((*token), "o while deve conter pelo menos um comando.");
                }
            }
            else{
                p_erroMsg((*token), "o token esperado era um )");
            }
        }
        else{
            p_erroMsg((*token), "o token esperado era um (");
        }
    }
    else if((*token).classificacao == CLASSE_KW_DO)
    {
        p_chamaScanner(inArquivo, token);
        if(!p_comando(inArquivo, token))
        {
            p_erroMsg((*token), "o do-while deve conter pelo menos um comando.");
        }
        if((*token).classificacao == CLASSE_KW_WHILE)
        {
            p_chamaScanner(inArquivo, token);
            if((*token).classificacao == CLASSE_ABRI_PARENTESE)
            {
                p_chamaScanner(inArquivo, token);
                p_exprRelac(inArquivo, token);
                if((*token).classificacao == CLASSE_FECHA_PARENTESE)
                {
                    p_chamaScanner(inArquivo, token);
                    if((*token).classificacao == CLASSE_PONTO_VIRGULA)
                    {
                        p_chamaScanner(inArquivo, token);
                    }
                    else{
                        p_erroMsg((*token), "o token esperado era um ;");
                    }
                }
                else{
                    p_erroMsg((*token), "o token esperado era um )");
                }
            }
            else{
                p_erroMsg((*token), "o token esperado era um (");
            }
        }
        else{
            p_erroMsg((*token), "o token esperado era a palavra chave while");
        }
    }
    else{
        p_erroMsg((*token), "o token esperado era a palavra chave do ou while");
    }
}//FIM DE ITEREÇÃO

/** IF_ELSE */
void p_ifElse(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_KW_IF)
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_ABRI_PARENTESE)
        {
            p_chamaScanner(inArquivo, token);
            p_exprRelac(inArquivo, token);
            if((*token).classificacao == CLASSE_FECHA_PARENTESE)
            {
                p_chamaScanner(inArquivo, token);
                if(!p_comando(inArquivo, token))
                {
                    p_erroMsg((*token), "o if deve conter pelo menos um comando.");
                }
                if((*token).classificacao == CLASSE_KW_ELSE)
                {
                    p_chamaScanner(inArquivo, token);
                    if(!p_comando(inArquivo, token))
                    {
                        p_erroMsg((*token), "o else deve conter pelo menos um comando.");
                    }
                }
            }
            else{
                p_erroMsg((*token), "o token esperado era um )");
            }
        }
        else{
            p_erroMsg((*token), "o token esperado era um (");
        }
    }
}//FIM DE IF_ELSE

/****************************************************************************
*Funções auxiliares do parser
*/
//CHAMA SCANNER
void p_chamaScanner(FILE *inArquivo, TOKEN *token)
{
    int tmp=0;
    do
    {
        tmp = scanner(inArquivo, token);
    }while(((*token).classificacao == CLASSE_COMENT || (*token).classificacao == CLASSE_MULTCOMENT) && tmp != EOF);
    if(tmp == EOF)
    {
        (*token).classificacao = tmp;
    }
}

//CABEÇALHO PADRÃO DE ERRO
void p_erroMsg(TOKEN token, char *msg)
{
    printf("ERRO na linha %i, coluna %i, ultimo token lido %s: %s \n",
               token.linha, token.coluna, token.lexema, msg);
    exit(EXIT_FAILURE);
}
