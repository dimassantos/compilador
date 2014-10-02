/*
 * compilador.c
 *
 * Copyright 2014 Dimas Santos
 *
 */


#include "parser.h"

void help(void)
{
    printf("\nAjuda: <compilador v1.0 - 09/2014>");
    printf("\nUtilizaca: \n    compilador <fileName>");
    printf("\n    compilador [opcao]");
    printf("\nOpcoes:");
    printf("\n    -h Exibe esta ajuda");
    printf("\n    -a Exibe informacoes sobre esse compilador.\n\n");
}

int main(int argc, char *argv[])
{
    FILE *arquivo = NULL;

    if(argc != 2)
    {
        printf("\ncompilador: utilizacao incorreta...\n");
        help();
    }
    else if(0 == strcmp(argv[1], "-h"))
    {
        help();
    }
    else if(0 == strcmp(argv[1], "-a"))
    {
        printf("\nAluno: Dimas Santos \nPeriodo: 5\nUNICAP - 2014\n");
    }
    else
    {
        arquivo = fopen(argv[1], "r");
        printf("FILENAME: %s", argv[1]);
        if(arquivo==NULL)
        {
            printf("\ncompilador: Nao foi possivel abrir o arquivo,"
               "verifique o nome e se estah em local acessivel para leitura.\n");
            return 0;
        }
        parser(arquivo);
        printf("\nCompilado com sucesso!\n");
    }

    return (0);
}
