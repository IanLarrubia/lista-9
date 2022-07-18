#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30000

typedef struct _CONTATO {
    char nome[42];
    int num;
    char aniv[6];
} CONTATO;
 
CONTATO pAgenda[MAX];

int cont = 0;

void inserirContato(char *nome, long int num, char *aniv) {
    CONTATO temp;
    FILE *Agenda = fopen("agenda.txt", "a+");
    
    if (Agenda == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
        exit(1);
    }
    
    strcpy(temp.nome, nome);
    strcpy(temp.aniv, aniv);
    temp.num = num;

    pAgenda[cont] = temp;    
    cont++;

    fprintf(Agenda, "%s %d %s\n", temp.nome, temp.num, temp.aniv);
    fclose(Agenda);
}

void printarOpcoes() {
    printf("\nA - Inserir contato\nB - Remover contato\nC - Pesquisar um contato pelo nome\nD - Listar todos os contatos\nE - Listar os contatos cujo nome se inicia com uma dada letra\nF - Imprimir os aniversariantes do mes\nG - Encerrar\n");
    fflush(stdin);
}

void ordenarAgenda() {
    int i, j;
    CONTATO aux;

    FILE *Agenda = fopen("agenda.txt", "w+");

    for (i = 0; i < cont - 1; i++) {
        for (j = 0; j < cont - 1; j++) {
            if (strcmp(pAgenda[j].nome, pAgenda[j + 1].nome) > 0) {
                aux = pAgenda[j];
                pAgenda[j] = pAgenda[j + 1];
                pAgenda[j + 1] = aux;
            }
        }
    }

    for(i = 0; i < cont; i++){
        fprintf(Agenda, "%s %d %s\n", pAgenda[i].nome, pAgenda[i].num, pAgenda[i].aniv);
    }
    
    fclose(Agenda);
}

void removerContato(int index) {
    int i;
    FILE *Agenda;
    Agenda = fopen("agenda.txt", "w+");
    
    cont--;
    
    for (i = index; i < cont; i++) {
        pAgenda[i] = pAgenda[i + 1];
    }

    if (Agenda == NULL) {
        printf("Nao foi possivel abrir o arquivo. ");
        exit(1);
    }

    for (i = 0; i < cont; i++) {
        printf("%s %d %s\n\n", pAgenda[i].nome, pAgenda[i].num, pAgenda[i].aniv);
        fprintf(Agenda, "%s %d %s\n", pAgenda[i].nome, pAgenda[i].num, pAgenda[i].aniv);
    } 

    fclose(Agenda);
}

void pesquisarNome() {
    int i;
    char nome[42];
    FILE *Agenda = fopen("agenda.txt", "r");
    if (Agenda == NULL) {
        printf("Nao foi possivel abrir o arquivo!");
    }

    printf("Insira o nome a ser pesquisado: ");
    scanf("%s", nome);

    for (i = 0; i < cont; i++) {
        if (strstr(pAgenda[i].nome, nome) != 0) {
            printf("\n");
            printf("Contato encontrado:\n%s - %d", pAgenda[i].nome, pAgenda[i].num);
        }
    } 

    fclose(Agenda);
}

void pesquisarLetra() {
    int i;    
    char strings[MAX][42], letra;
    FILE *Agenda = fopen("agenda.txt", "r");
    if (Agenda == NULL) {
        printf("Nao foi possivel abrir o arquivo!");
    }

    for (i = 0; !feof(Agenda); i++) {
        fscanf(Agenda, "%s %*d %*s", strings[i]);
    }
    
    scanf("%*c");

    printf("Insira a letra a ser pesquisada: ");

    scanf("%c", &letra);

    printf("Letra scaneada: %c", letra);

    for (i = 0; i < cont; i++) {
        if (pAgenda[i].nome[0] == letra) {
            printf("\n");
            printf("%s - %d - %s", pAgenda[i].nome, pAgenda[i].num, pAgenda[i].aniv);
        }
    }
    
    fclose(Agenda);
}

void aniversariantesMes() {
    int i, aux = 0;
    char mes[6];
    FILE *Agenda = fopen("agenda.txt", "r");
    if (Agenda == NULL) {
        printf("Nao foi possivel abrir o arquivo!");
    }

    scanf("%*c");
    printf("01 - Janeiro\n02 - Fevereiro\n03 - Março\n04 - Abril\n05 - Maio\n06 - Junho\n07 - Julho\n08 - Agosto\n09 - Setembro\n10 - Outubro\n11 - Novembro\n12 - Dezembro\n");
    fgets(mes, 3, stdin);

    for (i = 0; i < cont; i++) {
        if (strcmp(mes, pAgenda[i].aniv + 3) == 0) {
            aux++;
            printf("Nome: %s - %d - %s", pAgenda[i].nome, pAgenda[i].num, pAgenda[i].aniv);
        }
    }
    if (!aux) printf("0 contatos fazem aniversario no mes %d", mes);
}

void printarAgenda() {
    int i;
    ordenarAgenda(); 
    printf("\n");
    for (i = 0; i < cont; i++) {
        printf("Contato [%d] - %s - %d\n", i, pAgenda[i].nome, pAgenda[i].num);
    }
}
 
int main(void) {

    char opc = 'Z';
    char nome[42];
    char aniv[10];
    int num, index;
 
    while (opc != 'g' && opc != 'G') {
        
        printarOpcoes();
        opc = getchar();

        switch(opc) {
            case 'A':    
                scanf("%*c");
                printf("Insira o nome: \n");
                fgets(nome, 42, stdin);

                nome[strlen(nome) - 1] = '\0';

                printf("Insira o numero e aniversario no formato dd/mm: \n");
                scanf("%d %s", &num, aniv);
                
                inserirContato(nome, num, aniv);
                break;

            case 'B':

                printarAgenda();
                printf("Insira o index do contato: ");
                scanf("%d", &index);
                removerContato(index);
                break;

            case 'C':

                pesquisarNome();
                break;

            case 'D':

                printarAgenda();
                break;

            case 'E':
                pesquisarLetra();
                break;

            case 'F':
                aniversariantesMes();
                break;

        }
    }

    return 0;
}