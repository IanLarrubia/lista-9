#include <stdio.h>
#include <stdlib.h>
#define ARQ "registros.bin"
#define TRUE 1
#define fw fwrite
#define fr fread

typedef struct {
    int cod, mes;
	double val;
	char nome[42];
} VENDEDOR;

void apagarRegistro(){
	FILE *Arquivo;
	VENDEDOR temp[10000];
	int i = 0, j = 0, codigo;
	
	printf("Codigo: ");
	scanf("%d", &codigo);
	
	if ((Arquivo = fopen(ARQ, "r")) == NULL) {
        printf("\nNao foi possivel abrir o arquivo.");
        exit(1) ;
    }
   
    while(!feof(Arquivo)){
		if(!feof(Arquivo)){
			fr(&temp[i].cod , sizeof (int ) , 1, Arquivo);
			fr(temp[i].nome , sizeof ( char ) , 42, Arquivo);
			fr(&temp[i].val , sizeof (double ) , 1, Arquivo);
			fr(&temp[i].mes , sizeof ( int) , 1, Arquivo);
			i++;
		}
	}
    fclose(Arquivo);
	if ((Arquivo = fopen(ARQ , "w")) == NULL ) {
        printf("\nNao foi possivel abrir o arquivo.");
        exit(1) ;
    }
    
    while(i - j - 1 > 0){
    	if(temp[j].cod!=codigo){
    		fw(&temp[j].cod , sizeof(int), 1, Arquivo);
			fw(temp[j].nome , sizeof(char), 42, Arquivo);
			fw(&temp[j].val , sizeof(double), 1, Arquivo);
			fw(&temp[j].mes , sizeof(int), 1, Arquivo);
		}

		j++;
	}
	fclose(Arquivo);
}

void criarArquivo(){
	FILE *Arquivo;
	if ((Arquivo = fopen(ARQ, "w")) == NULL) {
        printf ("\nNao foi possivel abrir o arquivo.");
        exit(1) ;
    }
	
    fclose(Arquivo);
}

void criarRegistro(){
	FILE *Arquivo;
	VENDEDOR temp;
		
	printf("Codigo: ");
	scanf("%d", &temp.cod);
	
	printf("Nome: ");
	scanf("%s", temp.nome);

	printf("Valor: ");
	scanf("%lf", &temp.val);

	printf("Mes: ");
	scanf("%d", &temp.mes);

	if ((Arquivo = fopen(ARQ, "a")) == NULL ) {
        printf("\nNao foi possivel abrir o arquivo.");
        exit(1) ;
    }

    fw(&temp.cod , sizeof (int ) , 1, Arquivo);
	fw(temp.nome , sizeof ( char ) , 42, Arquivo);
	fw(&temp.val , sizeof (double ) , 1, Arquivo);
	fw(&temp.mes , sizeof ( int) , 1, Arquivo);
	
	fclose(Arquivo);
}

void alterarVal(){
	FILE *Arquivo;
	VENDEDOR temp[10000];
	int i = 0, j = 0, codigo, mesX;
	double valor, newValue;
	
	printf("Codigo:");
	scanf("%d", &codigo);

	printf("Valor:");
	scanf("%lf", &valor);

	printf("Mes:");
	scanf("%d", &mesX);

	printf("Novo Valor: ");
	scanf("%lf", &newValue);
	
	if ((Arquivo = fopen(ARQ, "r")) == NULL ) {
        printf("\nNao foi possivel abrir o arquivo.");
        exit(1) ;
    }
	
    while(!feof(Arquivo)){
		if(!feof(Arquivo)){
			fr(&temp[i].cod , sizeof(int), 1, Arquivo);
			fr(temp[i].nome , sizeof(char), 42, Arquivo);
			fr(&temp[i].val , sizeof(double) , 1, Arquivo);
			fr(&temp[i].mes , sizeof(int), 1, Arquivo);

			if(temp[i].cod == codigo && temp[i].val == valor && temp[i].mes == mesX)
				temp[i].val = newValue;
			i++;
		}
	}

    fclose(Arquivo);
	if ((Arquivo = fopen(ARQ, "w")) == NULL ) {
        printf ("\nNao foi possivel abrir o arquivo.");
        exit(1);
    }
    
    while(i - j - 1 > 0){
    		fw(&temp[j].cod, sizeof(int), 1, Arquivo);
			fw(temp[j].nome, sizeof(char), 42, Arquivo);
			fw(&temp[j].val, sizeof(double), 1, Arquivo);
			fw(&temp[j].mes, sizeof(int), 1, Arquivo);
			j++;
	}

	fclose(Arquivo);
}

void imprime(){
	FILE *Arquivo;
	int cod, mes;
	double val;
	char nome[42];
	
	if ((Arquivo = fopen(ARQ, "r")) == NULL) {
        printf ("\nNao foi possivel abrir o arquivo.");
        exit(1);
    }
	
    while(!feof(Arquivo)) {
    	fr(&cod, sizeof (int), 1, Arquivo);
		fr(nome, sizeof (char), 42, Arquivo);
		fr(&val, sizeof (double), 1, Arquivo);
		fr(&mes, sizeof (int), 1, Arquivo);
		
		if(!feof(Arquivo)){
    		printf("Codigo: %d\nNome:%s\nValor: R$%.2lf\nMes: %d\n", cod, nome, val, mes);
		}
	}

	fclose(Arquivo);
}

int main(void) {
	int opt;

	while(TRUE) {
		printf("\n0 - Finalizar o programa\n1 - Criar o arquivo de dados\n2 - Incluir um determinado registro no arquivo\n3 - Excluir um determinado vendedor no arquivo\n4 - Alterar o valor de uma venda no arquivo\n5 - Imprimir os registros na saida padrao\n6 - Excluir o arquivo de dados\n\n");
		scanf("%d", &opt);

		switch (opt){
			case 0:
				return 1;
				break;
			case 1:
				criarArquivo();
				break;
			case 2:
				criarRegistro();
				break;
			case 3:
				apagarRegistro();
				break;
			case 4:
				alterarVal();
				break;
			case 5:
				imprime();
				break;
			case 6:
				remove(ARQ);
				break;				
		}
	}
	
	return 0;
}