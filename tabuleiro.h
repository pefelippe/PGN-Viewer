#define MAXSEQ 1000000
#include "xadrez.h"

typedef struct casa_
{
    wint_t peca;
    wint_t cor;
    int col, linha;
    struct casa_ *cima, *baixo; 
    struct casa_ *ant, *prox;

}Casa;

typedef struct tabuleiro_{
    Casa *inicio;
}Tabuleiro;

Tabuleiro * criarTabuleiro(Tabuleiro *tab);
void liberarTabuleiro(Tabuleiro *tab); 
Casa* obter_peca(Tabuleiro *tab, int col, int linha ); 
wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha );
Casa * inicializar_peca (Tabuleiro *tab, int col, int linha);
void printarTabuleiro(Tabuleiro *tab);

//proximo passo:
    //void carregarPGN(Casa **tab, char *arquivo);
    //int verificarJogada(Casa *tab);

 // https://pt.stackoverflow.com/questions/236842/como-criar-uma-matriz-din%C3%A2mica-usando-lista-encadeada-na-linguagem-c