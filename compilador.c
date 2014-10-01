/*
 * compilador.c
 *
 * Copyright 2014 SleeepWalker <sleeepwalker@sleeepwalker-OptiPlex-990>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include "parser.h"

int main(int argc, char *argv[])
{
    FILE *arquivo = NULL;

    arquivo = fopen("teste.txt", "r");
    if(arquivo==NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }
    parser(arquivo);
    return (0);
}


/*
int main(int argc, char *argv[])
{
    FILE *arquivo = NULL;
    TOKEN scanRetorno;

    arquivo = fopen("teste.txt", "r");
    if(arquivo==NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    while(scanner(arquivo, &scanRetorno))
        printf("Lexema: %s\t\tClassificacao: %d\n", scanRetorno.lexema, scanRetorno.classificacao);

    return 0;
}*/

