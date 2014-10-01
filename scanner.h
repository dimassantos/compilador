/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 19/9/2014
***************************************************************************************************
* Arquivo:  "scanner.h"
* Dependências: "auto_symbol_coment.c" "auto_cahr.c" "scanner.c" "auto_ident_pChave.c" "auto_int_float.c"
***************************************************************************************************
* Descrição: Contém a todas as definições necessarias para o funcionamento do scanner
*/

#ifndef FUNCTIONS_SCANNER_INCLUDED
#define FUNCTIONS_SCANNER_INCLUDED

#define RESET_COR     "\e[m"
#define COR_VERMELHO  "\e[31m"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

#define FROM_TOKEN 0
#define FROM_VARIAVEIS 1

#define RECONHECE       -21
#define NAO_RECONHECE   -22

typedef struct TOKEN
{
    char lexema[256];
    int classificacao;
    float valor;
    int linha;
    int coluna;
}TOKEN;

typedef struct _TOKEN
{
    //Parte Compativel com TOKEN
    char lexema[256];
    int classificacao;
    float valor;
    //
    int linha;
    int coluna;
    char lookupAhead;
}_TOKEN;

/** Tabela de classificação */

#define CLASSE_T_INTEIRO       11
#define CLASSE_T_FLOAT         12
#define CLASSE_T_CHAR          13

#define CLASSE_IDENTIFICADOR   14

#define CLASSE_MAIOR           20
#define CLASSE_MAIOR_IGUAL     21
#define CLASSE_MENOR           22
#define CLASSE_MENOR_IGUAL     23
#define CLASSE_IGUAL           24
#define CLASSE_DIFERENTE       25

#define CLASSE_SOMA            30
#define CLASSE_SUBTRACAO       31
#define CLASSE_MULTIPLCACAO    32
#define CLASSE_DIVISAO         33
#define CLASSE_ATRIBUICAO      34

#define CLASSE_FECHA_PARENTESE 40
#define CLASSE_ABRI_PARENTESE  41
#define CLASSE_ABRI_CHAVE      42
#define CLASSE_FECHA_CHAVES    43
#define CLASSE_VIRGULA         44
#define CLASSE_PONTO_VIRGULA   45

#define CLASSE_KW_MAIN         50
#define CLASSE_KW_IF           51
#define CLASSE_KW_ELSE         52
#define CLASSE_KW_WHILE        53
#define CLASSE_KW_DO           54
#define CLASSE_KW_FOR          55
#define CLASSE_KW_INT          56
#define CLASSE_KW_FLOAT        57
#define CLASSE_KW_CHAR         58

#define CLASSE_COMENT          60
#define CLASSE_MULTCOMENT      61

/** Automato char: Prototipos de funções */
int auto_char(FILE *inArquivo, _TOKEN *token);
int auto_char_Q0(_TOKEN *token);
int auto_char_Q1(FILE* inArquivo, _TOKEN *token, int *cont);
int auto_char_Q2(FILE* inArquivo, _TOKEN *token, int *cont);
int auto_char_Q3(FILE* inArquivo, _TOKEN *token, int *cont);


/** Automato Id PC: Prototipos de funções */
int auto_id_pc(FILE *inArquivo, _TOKEN *token);
int auto_id_pc_estado_Q0(_TOKEN *token);
int auto_id_pc_estado_Q1(FILE *inAquivo, _TOKEN *token, int *cont);
int auto_id_pc_estado_Q2(FILE *inAquivo, _TOKEN *token, int *cont);
int auto_id_pc_estado_Q3(_TOKEN *token);
int auto_id_pc_estado_Q4(_TOKEN *token);

/** Automato Int Float: Prototipos de funções */
int auto_int_float(FILE *inArquivo, _TOKEN *token);
int auto_int_float_estado_Q0(_TOKEN *token);
int auto_int_float_estado_Q1(FILE* inArquivo, _TOKEN *token, int *cont);
int auto_int_float_estado_Q2(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_int_float_estado_Q3(_TOKEN *token);
int auto_int_float_estado_Q4(_TOKEN *token);

/** Scanner: Prototipos de funções */
int scanner(FILE *inArquivo, TOKEN *retorno);
void novo_lookupAhead(FILE *inArquivo, _TOKEN *token, int *cont);
void sincroniza_token_com_variaveis(_TOKEN *token, int *linha, int *coluna, char *lookupAhead, int sinal);
void sincroniza_token__token(TOKEN *tokenDestino, _TOKEN *tokenOrigem);
void ingnora_espacos(FILE *inArquivo, _TOKEN *token);

/** Automato Symbol Coment: Prototipos de funções */
int auto_symbol_coment(FILE *inArquivo, _TOKEN *token);
int auto_symbol_coment_Q0(_TOKEN *token);
int auto_symbol_coment_Q1(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q2(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q3(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q4(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q5(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q6(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q7(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q8(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q9(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q10(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q11(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q12(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q13(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q14(FILE *inArquivo, _TOKEN *token);
int auto_symbol_coment_Q15(FILE *inArquivo, _TOKEN *token);
int auto_symbol_coment_Q16(FILE *inArquivo, _TOKEN *token);
int auto_symbol_coment_Q17(FILE *inArquivo, _TOKEN *token);
int auto_symbol_coment_Q18(FILE *inArquivo, _TOKEN *token);
int auto_symbol_coment_Q19(_TOKEN *token);
int auto_symbol_coment_Q20(_TOKEN *token);
int auto_symbol_coment_Q21(_TOKEN *token);
int auto_symbol_coment_Q22(_TOKEN *token);
int auto_symbol_coment_Q23(_TOKEN *token);
int auto_symbol_coment_Q24(_TOKEN *token);
int auto_symbol_coment_Q25(_TOKEN *token);
int auto_symbol_coment_Q26(_TOKEN *token);
int auto_symbol_coment_Q27(_TOKEN *token);
int auto_symbol_coment_Q28(_TOKEN *token);
int auto_symbol_coment_Q29(_TOKEN *token);
int auto_symbol_coment_Q30(_TOKEN *token);
int auto_symbol_coment_Q31(_TOKEN *token);
int auto_symbol_coment_Q32(_TOKEN *token);
int auto_symbol_coment_Q33(_TOKEN *token);
int auto_symbol_coment_Q34(_TOKEN *token);
int auto_symbol_coment_Q35(FILE *inArquivo, _TOKEN *token, int *cont);
int auto_symbol_coment_Q36(_TOKEN *token);



#define ESTADO_Q0 0
#define ESTADO_Q1 1
#define ESTADO_Q2 2
#define ESTADO_Q3 3
#define ESTADO_Q4 4
#define ESTADO_Q5 5
#define ESTADO_Q6 6
#define ESTADO_Q7 7
#define ESTADO_Q8 8
#define ESTADO_Q9 9
#define ESTADO_Q10 10
#define ESTADO_Q11 11
#define ESTADO_Q12 12
#define ESTADO_Q13 13
#define ESTADO_Q14 14
#define ESTADO_Q15 15
#define ESTADO_Q16 16
#define ESTADO_Q17 17
#define ESTADO_Q18 18
#define ESTADO_Q19 19
#define ESTADO_Q20 20
#define ESTADO_Q21 21
#define ESTADO_Q22 22
#define ESTADO_Q23 23
#define ESTADO_Q24 24
#define ESTADO_Q25 25
#define ESTADO_Q26 26
#define ESTADO_Q27 27
#define ESTADO_Q28 28
#define ESTADO_Q29 29
#define ESTADO_Q30 30
#define ESTADO_Q31 31
#define ESTADO_Q32 32
#define ESTADO_Q33 33
#define ESTADO_Q34 34
#define ESTADO_Q35 35
#define ESTADO_Q36 36
#define ESTADO_Q37 37
#define ESTADO_Q38 38

#endif // FUNCTIONS_SCANNER_INCLUDED
