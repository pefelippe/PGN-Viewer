#include "xadrez.h"

#define MAXSEQ 1000000
#define clear_screen() printf("\033[H\033[J");

typedef struct casa_{
    wint_t peca;       
    wint_t corFundo;   // *cor da Casa do tabuleiro em que ela está*
    char cor;          // *cor da PRÓPRIA peça*
    char tipo;
    char col;
    int linha;
    int qntMov;

    struct casa_ *cima, *baixo; 
    struct casa_ *ant, *prox;
}Casa;

typedef struct tabuleiro{
    Casa *inicio;
}Tabuleiro;

// Funções Estruturais
    Tabuleiro* criarTabuleiro (Tabuleiro *tab);
    Casa* inicializar_tab (Tabuleiro *tab, int col, int linha);
    void liberarTabuleiro (Tabuleiro *tab);

// Funções Essenciais
    void iniciarXadrez (Tabuleiro *tab, char const *arquivo);
    void printarTabuleiro (Tabuleiro *tab);
    void inserir(Tabuleiro *tab, int coluna, int linha, int colunaDestino, int linhaDestino, char *jogada);
    int lerJogada(Tabuleiro *tab, char *jogada, char  *cor, int numero, int aux);
    int testar(Tabuleiro *tab, char *jogada, char *cor);
    int roque(Tabuleiro *tab, char *jogada, char *cor);
    int checar_coluna(Tabuleiro *Tab, int coluna, int linhaOrigem, int linhaDestino);
    int checar_linha(Tabuleiro *tab, int linha, int colunaOrigem, int colunaDestino);
    int checar_diagonal(Tabuleiro *Tab, int coluna, int linha, int colunaDestino, int linhaDestino);

// Funções Auxiliares
    Casa* obter_peca (Tabuleiro *tab, int col, int linha); 
    wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha);
    wint_t corFundo (int coluna, int linha);
    char corrigir_coluna_char (int c);
    int converter_coluna_int (char c);

    

