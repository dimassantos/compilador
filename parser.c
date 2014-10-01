#include "parser.h"


int parser(FILE *inArquivo)
{
    TOKEN token;
    p_chamaScanner(inArquivo, &token);
    p_programa(inArquivo, &token);
    return 1;
}

/** Verifica a estrutura da funcação main */
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
                else
                {
                    p_erroMsg((*token), "o token esperado era )");
                }
            }
            else
            {
                p_erroMsg((*token), "o token esperado era (");
            }
        }
        else
        {
            p_erroMsg((*token), "a funcao main deve ser declarada apos int");
        }
    }
    else
    {
        p_erroMsg((*token), "a funcao main deve precedida de int");
    }
}

/** Verifica a estrutura de um <bloco> := “{“ {<decl_var>}* {<comando>}* “}” */
void p_bloco(FILE *inArquivo, TOKEN *token)
{
    if((*token).classificacao == CLASSE_ABRI_CHAVE)
    {
        p_chamaScanner(inArquivo, token);
        if((*token).classificacao == CLASSE_KW_INT || (*token).classificacao == CLASSE_KW_FLOAT ||
                (*token).classificacao ==  CLASSE_KW_CHAR )
        {
               p_declVar(inArquivo, token);
        }

        p_comando(inArquivo, token);

        if((*token).classificacao == CLASSE_FECHA_CHAVES)
        {
            p_chamaScanner(inArquivo, token);
            printf("Funciona...\n"); //teste
        }
        else
        {
            p_erroMsg((*token), "o token esperado era }");
        }
    }
    else
    {
        p_erroMsg((*token), "o token esperado era {");
    }
}
/** Verifica a estrutura de declaração de uma ou mais variaveis */
void p_declVar(FILE *inArquivo, TOKEN *token)
{
    while((*token).classificacao == CLASSE_KW_INT || (*token).classificacao == CLASSE_KW_FLOAT ||
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
                else
                {
                    p_erroMsg((*token), "o token esperado era um identificador");
                }
            }
        }
        else
        {
            p_erroMsg((*token), "o token esperado era um identificador");
        }

        if((*token).classificacao != CLASSE_PONTO_VIRGULA)
        {
            p_erroMsg((*token), "o token esperado era ;");
        }
        p_chamaScanner(inArquivo, token);
    }

}

/** Verifica a estrutura de declaração de uma ou mais variaveis */
void p_comando(FILE *inArquivo, TOKEN *token)
{
    while(TRUE)
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
            printf("\nchama p_if\n");
            break;
        }
        else
        {
            break;
        }
    }
}

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
}

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
            else
            {
                p_erroMsg((*token), "o token esperado era ;");
            }
        }
        else
        {
            p_erroMsg((*token), "o token esperado era =");
        }
    }
    else
    {
        p_erroMsg((*token), "o token esperado era um identificador");
    }
}

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
        else
        {
            break;
        }
    }
}

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
        else
        {
            break;
        }
    }


}
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
        else
        {
            p_erroMsg((*token), "o token esperado era )");
        }
    }
    else if((*token).classificacao == CLASSE_IDENTIFICADOR || (*token).classificacao == CLASSE_T_CHAR ||
       (*token).classificacao == CLASSE_T_FLOAT || (*token).classificacao == CLASSE_T_INTEIRO)
    {
        p_chamaScanner(inArquivo, token);
    }
    else
    {
        p_erroMsg((*token), "o token esperado era um char ou float ou int ou identificador");
    }
}

void p_exprRelac(FILE *inArquivo, TOKEN *token)
{
    p_exprArit(inArquivo, token);
    if((*token).classificacao >= 20 && (*token).classificacao <= 25)
    {
        p_chamaScanner(inArquivo, token);
        p_exprArit(inArquivo, token);
    }
    else
    {
        p_erroMsg((*token), "o token esperado era um operador relacional == ou >= ou > ou < ou <= ou !=");
    }
}

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
                p_comando(inArquivo, token);
            }
            else
            {
                p_erroMsg((*token), "o token esperado era um )");
            }
        }
        else
        {
            p_erroMsg((*token), "o token esperado era um (");
        }
    }
    else if((*token).classificacao == CLASSE_KW_DO)
    {
        p_chamaScanner(inArquivo, token);
        p_comando(inArquivo, token);
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
                    else
                    {
                        p_erroMsg((*token), "o token esperado era um ;)");
                    }
                }
                else
                {
                    p_erroMsg((*token), "o token esperado era um )");
                }
            }
            else
            {
                p_erroMsg((*token), "o token esperado era um (");
            }
        }
        else
        {
            p_erroMsg((*token), "o token esperado era a palavra chave while");
        }
    }
    else
    {
        p_erroMsg((*token), "o token esperado era a palavra chave do ou while");
    }
}

/****************************************************************************
*Funções auxiliares do parser
*/

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

void p_erroMsg(TOKEN token, char *msg)
{
    printf("ERRO na linha %i, coluna %i, ultimo token lido %s: %s \n",
               token.linha, token.coluna, token.lexema, msg);
    exit(EXIT_FAILURE);
}
