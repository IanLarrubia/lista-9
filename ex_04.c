#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

typedef struct _CONTEUDO{
    char linha[MAX];
} CONTEUDO;

int quant = 0;
CONTEUDO lista[MAX];

void pesquisa(char *argv){
    char pesquisado[MAX], strings[MAX][100]; /*pesquisa a string no arquivo*/
    int i, counter = 0, aux; 
    FILE *arquivoRead;
    arquivoRead = fopen(argv, "r");
    
    if (arquivoRead == NULL) {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }

    printf("Digite o trecho a ser pesquisado:\n");
    scanf ("%s", pesquisado);
    
    for (i = 0; !feof(arquivoRead); i++) {
        fgets(strings[i], 100, arquivoRead);
    }

    for (aux = 0; aux <= i; aux++) {
        if (strstr(strings[aux], pesquisado) != 0) {
            printf("\n");
            printf("Palavra encontrada na linha: %d - %s", aux, strings[aux]);
            counter++;
        }
    }

    if (counter == 0) printf("Nenhuma correspondencia");

    fclose(arquivoRead);
}

int main(int argc, char *argv[]){

    char nomeArquivo[100];
    
    strcpy(nomeArquivo, argv[1]);
    strcat(nomeArquivo, ".txt");
    
    pesquisa(nomeArquivo);

    return 0;
}