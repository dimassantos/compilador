#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "scanner.h"

int parser(FILE *inArquivo);
void p_programa(FILE *inArquivo, TOKEN *token);
void p_bloco(FILE *inArquivo, TOKEN *token);
void p_declVar(FILE *inArquivo, TOKEN *token);
void p_atribuicao(FILE* inArquivo, TOKEN *token);
void p_exprArit(FILE *inArquivo, TOKEN *token);
void p_termo(FILE *inArquivo, TOKEN *token);
void p_fator(FILE *inArquivo, TOKEN *token);
/////ok testado

void p_comando(FILE *inArquivo, TOKEN *token);
void p_comandoBasico(FILE *inArquivo, TOKEN *token);
void p_exprRelac(FILE *inArquivo, TOKEN *token);
void p_iteracao(FILE *inArquivo, TOKEN *token);




void p_chamaScanner(FILE *inArquivo, TOKEN *token);
void p_erroMsg(TOKEN token, char *msg);

#endif // PARSER_H_INCLUDED
