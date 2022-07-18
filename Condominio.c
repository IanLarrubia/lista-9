#include <stdio.h>
#include <stdlib.h>

typedef struct _APARTAMENTO 
{
    int num_apt;
    char proprietario[50];
    struct _APARTAMENTO *next;
} APARTAMENTO;

typedef struct _BLOCO 
{
    int num_bloco;
    int qnt_ap;
    int qnt_andares;
    struct _BLOCO *next;
    struct APARTAMENTO *head_apt;
} BLOCO;

typedef struct _CONDOMINIO
{
    int num_condo;
    struct _CONDOMINIO *next;
    struct _BLOCO *head_bloco;
} CONDOMINIO;
 
CONDOMINIO *comecar_lista_condo(int num_condo);
CONDOMINIO *add_condominio(CONDOMINIO *head, int num_condo);
void print_list(CONDOMINIO *head);
void criar_blocos(CONDOMINIO *cond);
void _criar_blocos(BLOCO* bloco_head, int qnt_andares, int qnt_ap, int num_bloco);
void print_blocos(CONDOMINIO *cond);

int main(int argc, char *argv[])
{
    CONDOMINIO *head = comecar_lista_condo(5);
    criar_blocos(head);
    print_blocos(head);
    return 0;
}

void print_blocos(CONDOMINIO *cond) 
{
    BLOCO *current = cond->head_bloco;

    while (current != NULL)
    {
        printf("Numero do predio -> %d || Quantidade de andares -> %d || Quantidadade de apartamentos por andar -> %d\n", current->num_bloco, current->qnt_andares, current->qnt_ap);
        current = current->next;
    }
}

void _criar_apt(BLOCO* bloco_head, int qnt_andares, int qnt_ap, int num_bloco)  
{
    BLOCO *current = bloco_head;
    
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (BLOCO*)malloc(sizeof(BLOCO));
    current->next->next = NULL;
    current->next->num_bloco = num_bloco;
    current->next->qnt_andares = qnt_andares;
    current->next->qnt_ap = qnt_ap;
}
/*
void criar_apt(BLOCO *bloq) 
{
    int num, i;
    printf("\nQuantos blocos(predios) deseja adicionar ao condominio de numero %d?: ", cond->num_condo);
    scanf("%d", &num);

    cond->head_bloco = (BLOCO*)malloc(sizeof(BLOCO));
    cond->head_bloco->next = NULL;

    BLOCO *current_bloco = cond->head_bloco;
    current_bloco->next = NULL;

	int num_predio, qnt_andares, qnt_ap_andar;
	printf("\nNumero do predio | Quantidade de andares | Quantidade de apartamentos por andar: ");
    scanf("%d %d %d", &num_predio, &qnt_andares, &qnt_ap_andar);
    current_bloco->num_bloco = num_predio;
    current_bloco->qnt_andares = qnt_andares;
    current_bloco->qnt_ap = qnt_ap_andar;

    for (i = 0; i < num-1; i++)
    {
        printf("\nNumero do predio | Quantidade de andares | Quantidade de apartamentos por andar: ");
        scanf("%d %d %d", &num_predio, &qnt_andares, &qnt_ap_andar);
        _criar_blocos(current_bloco, qnt_andares, qnt_ap_andar, num_predio);
    }
}
*/
void _criar_blocos(BLOCO* bloco_head, int qnt_andares, int qnt_ap, int num_bloco)  
{
    BLOCO *current = bloco_head;
    
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (BLOCO*)malloc(sizeof(BLOCO));
    current->next->next = NULL;
    current->next->num_bloco = num_bloco;
    current->next->qnt_andares = qnt_andares;
    current->next->qnt_ap = qnt_ap;
}

void criar_blocos(CONDOMINIO *cond) 
{
    int num, i;
    printf("\nQuantos blocos(predios) deseja adicionar ao condominio de numero %d?: ", cond->num_condo);
    scanf("%d", &num);

    cond->head_bloco = (BLOCO*)malloc(sizeof(BLOCO));
    cond->head_bloco->next = NULL;

    BLOCO *current_bloco = cond->head_bloco;
    current_bloco->next = NULL;

	int num_predio, qnt_andares, qnt_ap_andar;
	printf("\nNumero do predio | Quantidade de andares | Quantidade de apartamentos por andar: ");
    scanf("%d %d %d", &num_predio, &qnt_andares, &qnt_ap_andar);
    current_bloco->num_bloco = num_predio;
    current_bloco->qnt_andares = qnt_andares;
    current_bloco->qnt_ap = qnt_ap_andar;

    for (i = 0; i < num-1; i++)
    {
        printf("\nNumero do predio | Quantidade de andares | Quantidade de apartamentos por andar: ");
        scanf("%d %d %d", &num_predio, &qnt_andares, &qnt_ap_andar);
        _criar_blocos(current_bloco, qnt_andares, qnt_ap_andar, num_predio);
    }
}

void print_list(CONDOMINIO *head)
{
    CONDOMINIO *current = head;
    while (current != NULL)
    {
        printf("Valor: %d ", current->num_condo);
        current = current->next;
    }
}

CONDOMINIO *add_condominio(CONDOMINIO *head, int num_condo)
{
    CONDOMINIO *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
 
    current->next = (CONDOMINIO*)malloc(sizeof(CONDOMINIO));
    current->next->next = NULL;
    current->next->num_condo = num_condo;
   
    return current->next;
}

CONDOMINIO *comecar_lista_condo(int num_condo)
{
    CONDOMINIO *head = NULL;
    head = (CONDOMINIO*)malloc(sizeof(CONDOMINIO));
    head->next = NULL;
    head->num_condo = num_condo;
    if (head == NULL) return 1;
    return head;
}

