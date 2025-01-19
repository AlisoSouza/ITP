#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 9

typedef struct {
  char tabuleiro[3][3];
  int coordenadas[9][2];
  int vencedor;
  int acao_jogador;
  int acao_pc;
  int num_jogadas;
  int *pos_validas;
  int tamanho;
} JogoDaVelha;

JogoDaVelha inicializa_jogo();
void imprime_matriz(JogoDaVelha jogo);
void imprime_vetor(JogoDaVelha jogo);
void inicializa_vetor(int *pos_validas);
int valida_jogada(int posicao, JogoDaVelha *jogo);
void remove_valor(JogoDaVelha *jogo);
void substitui_valor(JogoDaVelha *jogo, int x, int y, char valor);
void verifica_resultado(JogoDaVelha *jogo);
int check_linhas(JogoDaVelha jogo, char char_jogador);
int check_diagonais(JogoDaVelha jogo, char char_jogador);
int check_colunas(JogoDaVelha jogo, char char_jogador);
int jogada_pc(JogoDaVelha jogo);

void acao_jogador(JogoDaVelha* jogo)
{

  int _posicao, posicao;
  int x, y;

  printf("Escolha sua posição: ");
  scanf("%d", &_posicao);
  posicao = _posicao-1;
  if (valida_jogada(_posicao, jogo))
    {
      remove_valor(jogo);
      x = jogo->coordenadas[posicao][0];
      y = jogo->coordenadas[posicao][1];
      substitui_valor(jogo, x, y, 'X');
      jogo->acao_jogador = 0;
      jogo->acao_pc = 1;
    }
    else
    {
      printf("Jogada inválida, tente novamente\n");
      acao_jogador(jogo);
    }
}

void acao_pc(JogoDaVelha* jogo)
{

  int _posicao, posicao;
  int x, y;

  printf("O computador está jogando ... \n");
  _posicao = jogada_pc(*jogo);
  posicao = _posicao-1;
  valida_jogada(_posicao, jogo);
  remove_valor(jogo);
  printf("PC escolheu: %d\n", _posicao);
  x = jogo->coordenadas[posicao][0];
  y = jogo->coordenadas[posicao][1];
  substitui_valor(jogo, x, y, 'O');
  jogo->acao_jogador = 1;
  jogo->acao_pc = 0;
}

int continua_jogo(JogoDaVelha jogo)
{
  if ((jogo.num_jogadas> 9 || jogo.tamanho == 0) && jogo.vencedor == -1)
  {
    printf("Empate!\n");
    return 0;
  }
  else if (jogo.vencedor == 0)
  {
    printf("O jogador venceu!\n");
    return 0;
  }
  else if (jogo.vencedor == 1)
  {
    printf("O computador venceu!\n");
    return 0;
  }
  return 1;
}


int main(int argc, char *argv[])
{
  JogoDaVelha jogo = inicializa_jogo();
  int _posicao, posicao;
  int x, y;

  printf("------------------------------------\n");
  imprime_matriz(jogo);
  printf("------------------------------------\n");

  while (continua_jogo(jogo)) {

    printf("------------------------------------\n");
    verifica_resultado(&jogo);

    if (!continua_jogo(jogo))
    {
      break;
    }

    imprime_vetor(jogo);
    if (jogo.acao_jogador)
    {
      acao_jogador(&jogo);
    }
    imprime_matriz(jogo);
    verifica_resultado(&jogo);
    if (!continua_jogo(jogo))
    {
      break;
    }

    if (jogo.acao_pc)
    {
      acao_pc(&jogo);
    }
    imprime_matriz(jogo);
    verifica_resultado(&jogo);
    if (!continua_jogo(jogo))
    {
      break;
    }
    printf("------------------------------------\n");

  }
  free(jogo.pos_validas);
  return 0;
}


JogoDaVelha inicializa_jogo()
{

  JogoDaVelha jogo = {
    .coordenadas= {
      {0, 0},
      {0, 1},
      {0, 2},
      {1, 0},
      {1, 1},
      {1, 2},
      {2, 0},
      {2, 1},
      {2, 2},
    },
    .tabuleiro = {
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'},
    },
    .vencedor = -1,
    .acao_jogador = 1,
    .acao_pc = 0,
    .num_jogadas = 0,
    .tamanho = TAM,
  };
  jogo.pos_validas = malloc(TAM* sizeof(int));
  inicializa_vetor(jogo.pos_validas);
  return jogo;
}


void imprime_matriz(JogoDaVelha jogo){
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
      printf(
        "%c ", jogo.tabuleiro[i][j]);
    }
    printf("\n");
  }
}


void imprime_vetor(JogoDaVelha jogo)
{
  printf("\nJogadas validas restantes: ");
  for (int i=0; i<jogo.tamanho; i++){
    if (jogo.pos_validas[i] != -1){
      printf("%d ", jogo.pos_validas[i]);
    }
  }
  printf("\n");
}


void inicializa_vetor(int *pos_validas)
{
  for (int i = 0; i < TAM; i++) {
    pos_validas[i] = i + 1;
  }
}


int valida_jogada(int posicao, JogoDaVelha *jogo)

{
  int valido = 0;

  if (posicao < 1 || posicao > TAM){
    valido = 0;
    return valido;
  }

  for(int i=0; i<TAM; i++){
    if (posicao == jogo->pos_validas[i]){
      valido = 1;
      jogo->pos_validas[i] = -1;
      (jogo->num_jogadas)++;
      break;
    }
  }
  return valido;
}


void remove_valor(JogoDaVelha *jogo)
{
  int _tamanho = 0, j=0;
  for (int i=0; i<jogo->tamanho; i++)
  {
    if (jogo->pos_validas[i] != -1){
      _tamanho++;
    }
  }

  int *_vetor = malloc(_tamanho*sizeof(int));

  for (int i=0; i<jogo->tamanho; i++){
    if (jogo->pos_validas[i] != -1){
      _vetor[j] = (jogo->pos_validas[i]);
      j++;
    }
  }

  free(jogo->pos_validas);
  jogo->pos_validas = _vetor;
  jogo->tamanho = _tamanho;
}


void substitui_valor(JogoDaVelha *jogo, int x, int y, char valor)
{
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
      jogo->tabuleiro[x][y] = valor;
    }
  }
}


void verifica_resultado(JogoDaVelha *jogo)
{
  // checa diagonais
  if (check_diagonais(*jogo, 'X'))
  {
    jogo->vencedor = 0;
  }
  else if (check_diagonais(*jogo, 'O'))
  {
    jogo->vencedor = 1;
  }

  // checa linhas
  if (check_linhas(*jogo, 'X'))
  {
    jogo->vencedor = 0;
  }
  else if (check_linhas(*jogo, 'O'))
  {
    jogo->vencedor = 1;
  }

  // checa colunas
  if (check_colunas(*jogo, 'X'))
  {
    jogo->vencedor = 0;
  }
  else if (check_colunas(*jogo, 'O'))
  {
    jogo->vencedor = 1;
  }
}


int check_diagonais(JogoDaVelha jogo, char char_jogador)
{
  if (jogo.tabuleiro[0][0] == char_jogador && jogo.tabuleiro[1][1] == char_jogador && jogo.tabuleiro[2][2] == char_jogador){
    return 1;
  }
  else if (jogo.tabuleiro[0][2] == char_jogador && jogo.tabuleiro[1][1] == char_jogador && jogo.tabuleiro[2][0] == char_jogador){
    return 1;
  }
  return 0;
}


int check_linhas(JogoDaVelha jogo, char char_jogador)
{
  int linha_completa = 0;
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++)
    {
      if (jogo.tabuleiro[i][j] == char_jogador)
      {
        linha_completa = 1;
      }
      else {
        linha_completa = 0;
        break;
      }
    }
    if (linha_completa)
    {
      return linha_completa;
    }
  }
  return linha_completa;
}


int check_colunas(JogoDaVelha jogo, char char_jogador)
{
  int coluna_completa = 0;
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++)
    {
      if (jogo.tabuleiro[j][i] == char_jogador)
      {
        coluna_completa = 1;
      }
      else {
        coluna_completa = 0;
        break;
      }
    }
    if (coluna_completa)
    {
      return coluna_completa;
    }
  }
  return coluna_completa;
}


int jogada_pc(JogoDaVelha jogo)
{
  srand(time(NULL));
  int posicao = rand() % jogo.tamanho; // 0 a 9
  return jogo.pos_validas[posicao];
}
