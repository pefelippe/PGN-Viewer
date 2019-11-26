#include "xadrez.h"

#define MAXSEQ 1000000
#define clear_screen() printf("\033[H\033[J");

typedef struct casa_
{
    wint_t peca;
    wint_t cor;
    char col;
    int linha;
    int qntMov;
    struct casa_ *cima, *baixo; 
    struct casa_ *ant, *prox;
}Casa;

typedef struct tabuleiro
{
    Casa *inicio;
}Tabuleiro;


Tabuleiro* criarTabuleiro(Tabuleiro *tab);
void liberarTabuleiro(Tabuleiro *tab); 
void printarTabuleiro(Tabuleiro *tab);
char corrigirColuna(int c);
Casa * inicializar_tab (Tabuleiro *tab, int col, int linha);

Casa* obter_peca(Tabuleiro *tab, int col, int linha ); 
void excluir_peca (Tabuleiro *tab, int col, int linha);
wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha );
void inserir_peca (Tabuleiro *tab, int col, int linha, wint_t peca);

void carregar(Tabuleiro *tab, char const *arquivo);
void rodar(Tabuleiro *tab, char *jogada, char* cor, char *numero);
int verificarJogada(Tabuleiro *tab, char* jogada, char *cor);
