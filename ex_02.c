#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000000

typedef struct _CONTEUDO 
{
    char linha[51];
} CONTEUDO;

char line[51], nova[51];

int quant = 0, i = 0;
CONTEUDO lista[MAX];

void escrever_saida(FILE *arqSaida) 
{
    for (i = quant - 1; i > -1; i--) {
        fputs(lista[i].linha, arqSaida);
    }
    fclose(arqSaida);
}

char *homemade_strrev(char *line)
{
    int size = strlen(line), i, j;

    for (i = size - 1, j = 0; i > -1; i--, j++)
    {
        nova[j] = line[i];
    }
    nova[size] = '\0';
    return nova;
}

void escrever(FILE *arqEntrada, FILE *arqSaida) 
{   /* Escrever o conteúdo no struct */
    while (!feof(arqEntrada))
    {
        CONTEUDO temp;
        fgets(line, 51, arqEntrada);
        strcpy(temp.linha, homemade_strrev(line));
        lista[quant] = temp;
        quant++;
    }    
    escrever_saida(arqSaida);
    fclose(arqEntrada);
}

FILE *open_file (char nomeArq[]) 
{
    FILE *arquivo = fopen(nomeArq, "a+");
    if (arquivo == NULL) 
    {
        printf("Erro ao iniciar o ponteiro!");
        exit(1);
    }
    
    return arquivo;
}

int main(int argc, char *argv[])
{
    FILE *arquivo = open_file(argv[1]);
    FILE *arquivoSaida = open_file(argv[2]);
    
    escrever(arquivo, arquivoSaida);

    return 0;
}