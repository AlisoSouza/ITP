#include <stdio.h>
#include <stdlib.h>


typedef struct {
  char **matriz;
  int *col;
  int *pos_diag;
  int *neg_diag;
  int tamanho;
} Tabuleiro;


int algoritmo_backtrack(int linha, Tabuleiro *tabuleiro);
char **aloca_memoria(int tamanho);
void imprime_matriz(Tabuleiro tabuleiro);
void libera_memoria(Tabuleiro tabuleiro, int tamanho);
Tabuleiro preenche_matriz(int tamanho);


int main()
{
  int tamanho, matriz_ok = 0;

  printf("Qual o tamanho do tabuleiro? ");
  scanf("%d", &tamanho);
  if (tamanho <= 0)
  {
    printf("Tamanho inválido\n");
    return 1;
  }
  Tabuleiro tabuleiro = preenche_matriz(tamanho);
  algoritmo_backtrack(0, &tabuleiro);
  libera_memoria(tabuleiro, tamanho);
  return 0;
}


char **aloca_memoria(int tamanho)
{
  int i=0, j=0;
  char **matriz = malloc(tamanho * sizeof(char *));

  if (matriz == NULL)
  {
    printf("Erro na alocação de memória\n");
    return NULL;
  }

  for (i = 0; i < tamanho; i++)
  {
    matriz[i] = malloc(tamanho * sizeof(char *));
  }
  return matriz;
}


void imprime_matriz(Tabuleiro tabuleiro)
{
  int i=0, j=0;
  for (i = 0; i < tabuleiro.tamanho; i++)
  {
    for (j = 0; j < tabuleiro.tamanho; j++)
    {
      printf("%c ", tabuleiro.matriz[i][j]);
    }
    printf("\n");
  }

}

int algoritmo_backtrack(int linha, Tabuleiro *tabuleiro)
{
  // printf("Linha %d\n", linha);
  int tamanho = tabuleiro->tamanho;

  if (linha == tamanho)
  {
    imprime_matriz(*tabuleiro);
    return 1;
  }

  for (int c=0; c<tamanho; c++)
  {
    if (tabuleiro->col[c] || tabuleiro->pos_diag[linha+c] || tabuleiro->neg_diag[linha-c+tamanho-1]) {
      continue;
    }

    tabuleiro->col[c] = 1;
    tabuleiro->pos_diag[linha+c] = 1;
    tabuleiro->neg_diag[linha-c + tamanho -1] = 1;
    tabuleiro->matriz[linha][c] = 'Q';

    if (algoritmo_backtrack(linha+1, tabuleiro))
    {
      return 1;
    }

    tabuleiro->col[c] = 0;
    tabuleiro->pos_diag[linha+c] = 0;
    tabuleiro->neg_diag[linha-c + tamanho -1] = 0;
    tabuleiro->matriz[linha][c] = '.';
  }
  return 0;
}

Tabuleiro preenche_matriz(int tamanho)
{
  Tabuleiro tabuleiro;
  tabuleiro.matriz = aloca_memoria(tamanho);
  tabuleiro.col = calloc(tamanho, sizeof(int));
  tabuleiro.pos_diag = calloc(2 * tamanho - 1, sizeof(int));
  tabuleiro.neg_diag = calloc(2 * tamanho - 1, sizeof(int));
  tabuleiro.tamanho = tamanho;

  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      tabuleiro.matriz[i][j] = '.';
    }
  }

  return tabuleiro;
}


void libera_memoria(Tabuleiro tabuleiro, int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    free(tabuleiro.matriz[i]);
  }
  free(tabuleiro.matriz);
  free(tabuleiro.col);
  free(tabuleiro.pos_diag);
  free(tabuleiro.neg_diag);
}

