#include "xadrez.h"

#define MAXSEQ 1000000
#define clear_screen() printf("\033[H\033[J");

typedef struct casa_{
    wint_t peca;
    wint_t corFundo;   // para printar
    char cor; // para a função procurar
    char col;
    int linha;
    int qntMov;
    char tipo;

    struct casa_ *cima, *baixo; 
    struct casa_ *ant, *prox;
}Casa;

typedef struct tabuleiro{
    Casa *inicio;
}Tabuleiro;

// Funções Estruturais
    Tabuleiro *criarTabuleiro (Tabuleiro *tab);
    Casa *inicializar_tab (Tabuleiro *tab, int col, int linha);

// Funções Essenciais
    void iniciarXadrez (Tabuleiro *tab, char const *arquivo);
    void printarTabuleiro (Tabuleiro *tab);
    void lerJogada (Tabuleiro *tab, char *jogada, char* cor, char *numero);
     int verificarJogada (Tabuleiro *tab, char* jogada, char *cor);
   int tentar_movimentar (Tabuleiro *tab, char * jogada, char* cor);

// Funções Auxiliares
    Casa *obter_peca (Tabuleiro *tab, int col, int linha ); 
    wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha );
    char corrigir_coluna_char (int c);
    int converter_coluna_int (char c);

// Liberar a Memória
    void liberarTabuleiro (Tabuleiro *tab);

void verificarPromocao(Tabuleiro *tab);
int testar(Tabuleiro *tab, char *jogada, char *cor);