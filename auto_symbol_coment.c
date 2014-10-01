/**
* Aluno: Dimas Francisco dos Santos - Matricula: 201210796.8
* Data: 19/9/2014
***************************************************************************************************
* Arquivo: "auto_symbol_coment.c"
* Dependências:  "scanner.c" "scanner.h"
***************************************************************************************************
* Descrição: Contém a função auto_symbol_coment() e suas sub funções, que reconhece e classifica oprelacional, oparitmético, especial e comentarios.
*/

#include "scanner.h"

int auto_symbol_coment(FILE *inArquivo, _TOKEN *token)
{
    int cont = 0;
    int estado = ESTADO_Q0;
    while(TRUE)
    {
        switch(estado)
        {
        case ESTADO_Q0:
            estado = auto_symbol_coment_Q0(token);
            break;
        case ESTADO_Q1:
            estado = auto_symbol_coment_Q1(inArquivo,token, &cont);
            break;
        case ESTADO_Q2:
            estado = auto_symbol_coment_Q2(inArquivo,token, &cont);
            break;
        case ESTADO_Q3:
            estado = auto_symbol_coment_Q3(inArquivo,token, &cont);
            break;
        case ESTADO_Q4:
            estado = auto_symbol_coment_Q4(inArquivo,token, &cont);
            break;
        case ESTADO_Q5:
            estado = auto_symbol_coment_Q5(inArquivo,token, &cont);
            break;
        case ESTADO_Q6:
            estado = auto_symbol_coment_Q6(inArquivo,token, &cont);
            break;
        case ESTADO_Q7:
            estado = auto_symbol_coment_Q7(inArquivo,token, &cont);
            break;
        case ESTADO_Q8:
            estado = auto_symbol_coment_Q8(inArquivo,token, &cont);
            break;
        case ESTADO_Q9:
            estado = auto_symbol_coment_Q9(inArquivo,token, &cont);
            break;
        case ESTADO_Q10:
            estado = auto_symbol_coment_Q10(inArquivo,token, &cont);
            break;
        case ESTADO_Q11:
            estado = auto_symbol_coment_Q11(inArquivo,token, &cont);
            break;
        case ESTADO_Q12:
            estado = auto_symbol_coment_Q12(inArquivo,token, &cont);
            break;
        case ESTADO_Q13:
            estado = auto_symbol_coment_Q13(inArquivo,token, &cont);
            break;
        case ESTADO_Q14:
            estado = auto_symbol_coment_Q14(inArquivo, token);
            break;
        case ESTADO_Q15:
            estado = auto_symbol_coment_Q15(inArquivo, token);
            break;
        case ESTADO_Q16:
            estado = auto_symbol_coment_Q16(inArquivo, token);
            break;
        case ESTADO_Q17:
            estado = auto_symbol_coment_Q17(inArquivo, token);
            break;
        case ESTADO_Q18:
            estado = auto_symbol_coment_Q18(inArquivo, token);
            break;
        case ESTADO_Q19:
            estado = auto_symbol_coment_Q19(token);
            break;
        case ESTADO_Q20:
            estado = auto_symbol_coment_Q20(token);
            break;
        case ESTADO_Q21:
            estado = auto_symbol_coment_Q21(token);
            break;
        case ESTADO_Q22:
            estado = auto_symbol_coment_Q22(token);
            break;
        case ESTADO_Q23:
            estado = auto_symbol_coment_Q23(token);
            break;
        case ESTADO_Q24:
            estado = auto_symbol_coment_Q24(token);
            break;
        case ESTADO_Q25:
            estado = auto_symbol_coment_Q25(token);
            break;
        case ESTADO_Q26:
            estado = auto_symbol_coment_Q26(token);
            break;
        case ESTADO_Q27:
            estado = auto_symbol_coment_Q27(token);
            break;
        case ESTADO_Q28:
            estado = auto_symbol_coment_Q28(token);
            break;
        case ESTADO_Q29:
            estado = auto_symbol_coment_Q29(token);
            break;
        case ESTADO_Q30:
            estado = auto_symbol_coment_Q30(token);
            break;
        case ESTADO_Q31:
            estado = auto_symbol_coment_Q31(token);
            break;
        case ESTADO_Q32:
            estado = auto_symbol_coment_Q32(token);
            break;
        case ESTADO_Q33:
            estado = auto_symbol_coment_Q33(token);
            break;
        case ESTADO_Q34:
            estado = auto_symbol_coment_Q34(token);
            break;
        case ESTADO_Q35:
            estado = auto_symbol_coment_Q35(inArquivo,token, &cont);
            break;
        case ESTADO_Q36:
            estado = auto_symbol_coment_Q36(token);
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

int auto_symbol_coment_Q0(_TOKEN *token)
{
    switch((*token).lookupAhead)
    {
    case '/':
        return ESTADO_Q1;
    case '=':
        return ESTADO_Q2;
    case '>':
        return ESTADO_Q3;
    case '<':
        return ESTADO_Q4;
    case '+':
        return ESTADO_Q5;
    case '-':
        return ESTADO_Q6;
    case '*':
        return ESTADO_Q7;
    case '(':
        return ESTADO_Q8;
    case ')':
        return ESTADO_Q9;
    case '{':
        return ESTADO_Q10;
    case '}':
        return ESTADO_Q11;
    case ',':
        return ESTADO_Q12;
    case ';':
        return ESTADO_Q13;
    case '!':
        return ESTADO_Q35;
    case EOF:
        return EOF;
    default:
        return NAO_RECONHECE;
    }
}

int auto_symbol_coment_Q1(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if((*token).lookupAhead == '/')
    {
        (*cont)=0;
        return ESTADO_Q15;
    }
    if((*token).lookupAhead == '*')
    {
        (*cont)=0;
        return ESTADO_Q14;
    }
    return ESTADO_Q19;
}

int auto_symbol_coment_Q2(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if((*token).lookupAhead == '=')
    {
        novo_lookupAhead(inArquivo, token, cont);
        return ESTADO_Q20;
    }
    return ESTADO_Q21;
}

int auto_symbol_coment_Q3(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if((*token).lookupAhead == '=')
    {
        novo_lookupAhead(inArquivo, token, cont);
        return ESTADO_Q22;
    }
    return ESTADO_Q23;
}

int auto_symbol_coment_Q4(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if((*token).lookupAhead == '=')
    {
        novo_lookupAhead(inArquivo, token, cont);
        return ESTADO_Q24;
    }
    return ESTADO_Q25;
}

int auto_symbol_coment_Q5(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q26;
}

int auto_symbol_coment_Q6(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q27;
}

int auto_symbol_coment_Q7(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q28;
}

int auto_symbol_coment_Q8(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q29;
}

int auto_symbol_coment_Q9(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q30;
}
int auto_symbol_coment_Q10(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q31;
}
int auto_symbol_coment_Q11(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q32;
}
int auto_symbol_coment_Q12(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q33;
}

int auto_symbol_coment_Q13(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    return ESTADO_Q34;
}

int auto_symbol_coment_Q14(FILE *inArquivo, _TOKEN *token)
{
    (*token).lookupAhead = fgetc(inArquivo);
    (*token).coluna++;
    if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
    {
        (*token).linha++;
        (*token).coluna = 0;
    }
    while((*token).lookupAhead != '*' && (*token).lookupAhead != EOF)
    {
        (*token).lookupAhead = fgetc(inArquivo);
        (*token).coluna++;
        if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
        {
            (*token).linha++;
            (*token).coluna = 0;
        }
    }
    if((*token).lookupAhead == EOF)
    {
        printf(COR_VERMELHO"ERRO na linha %d, coluna %d"
            ": Nao delimitou o comentario de multiplas linhas, faltou o */ \n"
            RESET_COR, (*token).linha, (*token).coluna);
        exit(EXIT_FAILURE);
    }
    return ESTADO_Q16;
}

int auto_symbol_coment_Q15(FILE *inArquivo, _TOKEN *token)
{
    while((*token).lookupAhead != EOF)
    {
        (*token).lookupAhead = fgetc(inArquivo);
        (*token).coluna++;
        if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
        {
            (*token).linha++;
            (*token).coluna = 0;
            break;
        }
    }
    return ESTADO_Q17;
}

int auto_symbol_coment_Q16(FILE *inArquivo, _TOKEN *token)
{
    while((*token).lookupAhead == '*' && (*token).lookupAhead != EOF)
    {
        (*token).lookupAhead = fgetc(inArquivo);
        (*token).coluna++;
        if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
        {
            (*token).linha++;
            (*token).coluna = 0;
            break;
        }
    }
    if((*token).lookupAhead == EOF)
    {
        printf(COR_VERMELHO"ERRO na linha %d, coluna %d"
            ": Nao delimitou o comentario de multiplas linhas, faltou o */ \n"
            RESET_COR, (*token).linha, (*token).coluna);
        exit(EXIT_FAILURE);
    }
    if((*token).lookupAhead == '/')
    {
        return ESTADO_Q18;
    }
    return ESTADO_Q14;
}

int auto_symbol_coment_Q17(FILE *inArquivo, _TOKEN *token)
{
    (*token).lookupAhead = fgetc(inArquivo);
    (*token).coluna++;
    if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
    {
        (*token).linha++;
        (*token).coluna = 0;
    }

    (*token).lexema[0] = '\0';
    (*token).classificacao = CLASSE_COMENT;
    return RECONHECE;
}

int auto_symbol_coment_Q18(FILE *inArquivo, _TOKEN *token)
{
    (*token).lookupAhead = fgetc(inArquivo);
    (*token).coluna++;
    if((*token).lookupAhead == 13 || (*token).lookupAhead == 10)
    {
        (*token).linha++;
        (*token).coluna = 0;
    }
    (*token).lexema[0] = '\0';
    (*token).classificacao = CLASSE_MULTCOMENT;
    return RECONHECE;
}

int auto_symbol_coment_Q19(_TOKEN *token)
{
    (*token).classificacao = CLASSE_DIVISAO;
    return RECONHECE;
}

int auto_symbol_coment_Q20(_TOKEN *token)
{
    (*token).classificacao = CLASSE_IGUAL;
    return RECONHECE;
}

int auto_symbol_coment_Q21(_TOKEN *token)
{
    (*token).classificacao = CLASSE_ATRIBUICAO;
    return RECONHECE;
}

int auto_symbol_coment_Q22(_TOKEN *token)
{
    (*token).classificacao = CLASSE_MAIOR_IGUAL;
    return RECONHECE;
}

int auto_symbol_coment_Q23(_TOKEN *token)
{
    (*token).classificacao = CLASSE_MAIOR;
    return RECONHECE;
}

int auto_symbol_coment_Q24(_TOKEN *token)
{
    (*token).classificacao = CLASSE_MENOR_IGUAL;
    return RECONHECE;
}

int auto_symbol_coment_Q25(_TOKEN *token)
{
    (*token).classificacao = CLASSE_MENOR;
    return RECONHECE;
}

int auto_symbol_coment_Q26(_TOKEN *token)
{
    (*token).classificacao = CLASSE_SOMA;
    return RECONHECE;
}

int auto_symbol_coment_Q27(_TOKEN *token)
{
    (*token).classificacao = CLASSE_SUBTRACAO;
    return RECONHECE;
}

int auto_symbol_coment_Q28(_TOKEN *token)
{
    (*token).classificacao = CLASSE_MULTIPLCACAO;
    return RECONHECE;
}

int auto_symbol_coment_Q29(_TOKEN *token)
{
    (*token).classificacao = CLASSE_ABRI_PARENTESE;
    return RECONHECE;
}

int auto_symbol_coment_Q30(_TOKEN *token)
{
    (*token).classificacao = CLASSE_FECHA_PARENTESE;
    return RECONHECE;
}

int auto_symbol_coment_Q31(_TOKEN *token)
{
    (*token).classificacao = CLASSE_ABRI_CHAVE;
    return RECONHECE;
}

int auto_symbol_coment_Q32(_TOKEN *token)
{
    (*token).classificacao = CLASSE_FECHA_CHAVES;
    return RECONHECE;
}

int auto_symbol_coment_Q33(_TOKEN *token)
{
    (*token).classificacao = CLASSE_VIRGULA;
    return RECONHECE;
}

int auto_symbol_coment_Q34(_TOKEN *token)
{
    (*token).classificacao = CLASSE_PONTO_VIRGULA;
    return RECONHECE;
}

int auto_symbol_coment_Q35(FILE *inArquivo, _TOKEN *token, int *cont)
{
    novo_lookupAhead(inArquivo, token, cont);
    if((*token).lookupAhead == '=')
    {
        novo_lookupAhead(inArquivo, token, cont);
        return ESTADO_Q36;
    }
    printf(COR_VERMELHO"ERRO na linha %d, coluna %d, ultimo token "
            "lido %s: Operador != mal formado!\n"
            RESET_COR, (*token).linha, (*token).coluna, (*token).lexema);
    exit(EXIT_FAILURE);
}

int auto_symbol_coment_Q36(_TOKEN *token)
{
    (*token).classificacao = CLASSE_DIFERENTE;
    return RECONHECE;
}
