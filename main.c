//Trabalho feito por João Manoel - 27/03/2023
//Sistema de atendimento da UPA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct node
{
  char name[45];
  int priority;
  struct node *next;
} Node;

// Função para inserir pacientes
void priority_insert(Node **fila, char name[45], int priority)
{
  Node *aux, *new = malloc(sizeof(Node));

  if (new)
  {
    new->next = NULL;
    new->priority = priority;
    strcpy(new->name, name);

    if (*fila == NULL)
    {
      *fila = new;
    }
    else
    {
      if (new->priority > 1)
      {
        if (((*fila)->priority < 5) && (new->priority == 5))
        {
          new->next = *fila;
          *fila = new;
        }
        else if (((*fila)->priority < 4) && (new->priority == 4))
        {
          new->next = *fila;
          *fila = new;
        }
        else if (((*fila)->priority < 3) && (new->priority == 3))
        {
          new->next = *fila;
          *fila = new;
        }
        else if (((*fila)->priority < 2) && (new->priority == 2))
        {
          new->next = *fila;
          *fila = new;
        }
        else
        {
          aux = *fila;
          while (aux->next && aux->next->priority > (new->priority - 1))
          {
            aux = aux->next;
          }
          new->next = aux->next;
          aux->next = new;
        }
      }
      else
      {
        aux = *fila;
        while (aux->next)
        {
          aux = aux->next;
        }
        aux->next = new;
      }
    }
  }
  else
  {
    printf("\nErro em alocação de memoria\n");
  }
}

// Função para remover/atender pacientes
Node *pop(Node **fila)
{
  Node *remove = NULL;
  if (*fila)
  {
    remove = *fila;
    *fila = remove->next;
  }
  else
  {
    printf("\nFila está vazia!\n");
  }
  return remove;
}

// Função para mostrar pacientes
void show(Node *fila)
{
  printf("\n---------FILA:---------\n");
  while (fila)
  {
    printf("(%d)-> %s", fila->priority, fila->name);
    fila = fila->next;
  }
  printf("\nLegenda:\n1 - Não urgente | 2 - Pouco urgente | 3 - Urgente | 4 - Muito urgente | 5 - Emergência");
  printf("\n_______________________\n");
}

int main()
{
  Node *r, *fila = NULL;
  int option, priority;
  char name[45], buffer;

  setlocale(LC_ALL, "Portuguese"); // Usado para resolver o problema de acentuação, mas algumas acentuações continuam sem funcionar
  do
  {
    printf("\t\n---------ATENDIMENTO DA UPA---------\n");
    printf("1 - Ver a lista\n2 - Inserir paciente\n3 - Atender(remover) paciente\n4 - Sair\n");
    printf("\nSua escolha: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      show(fila);
      break;
    case 2:
      printf("\n---------CADASTRO DE PACIENTE---------\n");
      printf("Digite o nome do paciente: ");
      scanf("%c", &buffer); // Colocado aqui para resolver buffer do teclado, sem essa linha não é possível digitar o nome!
      fgets(name, 45, stdin);
      printf("\n5 - Emergência\n4 - Muito urgente\n3 - Urgente\n2 - Pouco urgente\n1 - Não urgente\n");
      printf("Digite o nivel de prioridade do paciente: ");
      scanf("%d", &priority);
      if ((0 < priority) && (priority < 6))
      {
        priority_insert(&fila, name, priority);
      }
      else
      {
        printf("\nPrioridade não encontrada...Por favor, cadastre o paciente novamente!\n");
      }
      break;
    case 3:
      r = pop(&fila);
      if (r)
      {
        printf("\n---------ATENDENDO PACIENTES---------");
        printf("\nPaciente atendido: %s\n", r->name);
        free(r);
      }
      break;
    default:
      if (option != 4)
      {
        printf("\nDigite uma alternativa válida!\n");
      }
    }
  } while (option != 4);

printf("\nObrigado por usar o programa!");
  return 0;
}
