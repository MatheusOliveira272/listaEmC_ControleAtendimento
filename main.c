#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
  char letra;
  int num;
  struct NO *prox; // ponteiro para proximo NO
} NO;

typedef struct FILA {
  NO *ini; // ponteiro para inicio da fila
  NO *fim; // ponteiro para o fim da fila
} FILA;

void inicializaFila(FILA *f) {

  f->ini = NULL;
  f->fim = NULL;
}

void enfileira(char letra, int num,
               FILA *f) { // função de enfileiramento recebe Os dados do nó
                          // (letra e num ) e a fila por referencia
  NO *ptr =
      (NO *)malloc(sizeof(NO)); // ptr indica um novo nó (ponteiro auxiliar)
  if (ptr == NULL) {
    printf("Erro de alocação");
    return;
  } else {
    // tratando a fila vazia
    // inicializando no com os dados que ele possui e o prox com NULL
    ptr->letra = letra;
    ptr->num = num;
    ptr->prox = NULL;
    if (f->ini == NULL) {
      f->ini = ptr;
    } else {
      f->fim->prox = ptr;
    }
    f->fim = ptr; // sempre o fim vai ser atualizado para um novo no que entrou
                  // no fim
    return;
  }
}

void desenfileira(FILA *f) { // remove E digo qual fila tO trmovendo
  NO *ptr = f->ini;          // ponteiro para nó aux
  char letra;                // variavel para retornar dado depois
  int num;                   // variavel para retornar dado depois
  if (ptr != NULL) {
    f->ini = ptr->prox; // atualizo o valor de inicio com o proximo nó
    ptr->prox = NULL;
    ptr->letra = letra;
    num = ptr->num;
    free(ptr);
    if (f->ini == NULL) {
      f->fim = NULL;
    }
   // printf(" %c %d ", letra, num);

  } else {
    printf("\nFila vazia");
  }
}

void imprimeFila(FILA *f) {
  NO *ptr = f->ini;  // no auxiliar ptr que aponta para o inicio
  if (ptr != NULL) { // se fila não vazia
    while (ptr != NULL) {
      printf("\n * %c%d ", ptr->letra, ptr->num);

      ptr = ptr->prox;
    }
  } else { // se a fila tiver vazia
    printf("\nFila vazia.");
    return;
  }
}
void detroiFila(FILA *f) {
 NO *ptr = f->ini;          // ponteiro para nó aux
                   // variavel para retornar dado depois
  if (ptr != NULL) {
    f->ini = ptr->prox; // atualizo o valor de inicio com o proximo nó
    free(ptr);
    if (f->ini == NULL) {
      f->fim = NULL;
      
    }
    printf("Fila Destruida");

  } else {
    printf("Fila Destruida");
  }
}
void proxAtendimento(FILA *f) {
  NO *ptr = f->ini;  // no auxiliar ptr que aponta para o inicio
  if (ptr != NULL) { // se fila não vazia
    printf("%c%d ", ptr->letra, ptr->num);
  } else { // se a fila tiver vazia
    printf("\nSem clientes!");
    return;
  }
}

void tamanhofila(FILA *f) {
  NO *ptr = f->ini; // no auxiliar ptr que aponta para o inicio
  int cont = 0;
  if (ptr != NULL) { // se fila não vazia
    while (ptr != NULL) {
      cont++;
      ptr = ptr->prox;
    }
    printf("Número de clientes:  %i", cont);
  } else { // se a fila tiver vazia
    printf("\nSem clientes!");
    return;
  }
}

int main(void) {
  // criando e inicializando uma fila de decolagem
  FILA *prioritaria = (FILA *)malloc(sizeof(FILA));
  FILA *normal = (FILA *)malloc(sizeof(FILA));
  if (prioritaria == NULL || normal == NULL) {
    printf("Erro de alocação");
    exit(-1);
  } else {
    inicializaFila(prioritaria);
    inicializaFila(normal);
    int op, dp, n=0;
    char l;
    int cont =0;

    do {
        

      printf("\n\n******************************************\n");
      printf("**        Controle de Atendimento       **\n");
      printf("******************************************\n");
      printf("** 1- Adicionar cliente na fila         **\n");
      printf("** 2- Lista de clientes aguardando      **\n");
      printf("** 3- Proximo cliente a ser atendido    **\n");
      printf("** 4- Chamar cliente para atendimento   **\n");
      printf("** 0- Sair                              **\n");
      printf("******************************************\n");

      printf("Informe uma opção: ");
      scanf("%i", &op);

      switch (op) {
      case 1:
        printf("Inserindo um cliente na fila: \n");
        printf("Informe o tipo: \n *P: prioritário\n *N: normal\n -> ");
        scanf("%c", &l);
        l = getchar();
        n++;
        if(l=='P'||l=='p'){
          enfileira(l, n, prioritaria);  
        }else if(l=='N' || l=='n'){
          enfileira(l, n, normal);
        }else{
          printf("Código inválido tente novamente!");
        }
      break;

    case 2:

      printf("Listando os clientes: \n");
      printf("1- Prioritario\n2-Normal\n-> ");
      scanf("%i", &dp);
      if (dp == 1) {
        printf("Prioritários...\n");
        tamanhofila(prioritaria);
        printf("\nClientes: ");
        imprimeFila(prioritaria);

      } else if (dp == 2) {
        printf("Normal...\n");
        tamanhofila(normal);
        printf("\nClientes: ");
        imprimeFila(normal);

      } else {
        printf("Opção inválida!\nTente Novamente!");
      }

      break;

    case 3:
    
      printf("Próximo cliente a ser atendido: \n");
      if(normal->ini==NULL){
        printf("Atendimento Prioritário cliente: ");
        proxAtendimento(prioritaria);
      }else if(prioritaria->ini!=NULL && cont<2){
        printf("Atendimento Prioritário cliente: ");
        proxAtendimento(prioritaria);
        
      }else if(normal->ini!=NULL){
        printf("Atendimento Normal: ");
        proxAtendimento(normal);
      }else{
        printf("Sem clientes...");
      }
      break;

    case 4:
      printf("Solicitar cliente para atendimento: \n");
      if(normal->ini==NULL){
       cont++;
          printf("Atendimento Prioritário cliente: ");
          proxAtendimento(prioritaria);
          desenfileira(prioritaria);
      }else if(prioritaria->ini!=NULL && cont<2){
        if(cont==2){
          cont=0;
        }else{
          cont++;
          printf("Atendimento Prioritário cliente: ");
          proxAtendimento(prioritaria);
          desenfileira(prioritaria);
        }
      }else if(normal->ini!=NULL){
        if(cont==2){
          cont=0;
        }
        printf("Atendimento Normal: ");
        proxAtendimento(normal);
        desenfileira(normal);
      }else{
        printf("Sem clientes...");
      }
      break;

    case 0:
      printf("Finalizando Programa...\n\n");
      printf("Destruindo fila Normal...\n");
      detroiFila(normal);
      printf("\n\nDestruindo fila Prioritária...\n");
      detroiFila(prioritaria);

      break;

    default:
      printf("Opção inválida!\nTente Novamente!");
    }
  }
  while (op != 0);
}
return 0;
}