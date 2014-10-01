/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 30/9/2014
***************************************************************************************************
* Arquivo:  "parser.h"
* Dependências: "auto_symbol_coment.c" "auto_cahr.c" "scanner.c" "auto_ident_pChave.c" "auto_int_float.c"
*               "scanner.h" "parser.c"
***************************************************************************************************
* Descrição: Contém a todas as definições das funções do parser
*/

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "scanner.h"

/** Parser */
void parser(FILE *inArquivo);
void p_programa(FILE *inArquivo, TOKEN *token);
void p_bloco(FILE *inArquivo, TOKEN *token);
int  p_declVar(FILE *inArquivo, TOKEN *token);
void p_atribuicao(FILE* inArquivo, TOKEN *token);
void p_exprArit(FILE *inArquivo, TOKEN *token);
void p_termo(FILE *inArquivo, TOKEN *token);
void p_fator(FILE *inArquivo, TOKEN *token);
void p_ifElse(FILE *inArquivo, TOKEN *token);
int  p_comando(FILE *inArquivo, TOKEN *token);
void p_comandoBasico(FILE *inArquivo, TOKEN *token);
void p_exprRelac(FILE *inArquivo, TOKEN *token);
void p_iteracao(FILE *inArquivo, TOKEN *token);



/** Auxiliares */
void p_chamaScanner(FILE *inArquivo, TOKEN *token);
void p_erroMsg(TOKEN token, char *msg);

#endif // PARSER_H_INCLUDED
