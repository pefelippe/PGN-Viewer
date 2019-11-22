// corrigir rainha preta 

#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "xadrez.h"

/* Funções referente ao Tabuleiro*/

Tabuleiro * criarTabuleiro(Tabuleiro *tab)
{
    tab = (Tabuleiro *) malloc(sizeof(Tabuleiro));
    if (!tab) return NULL;

    Casa *auxCima;
    wint_t auxCor = CASA_ESCURA;

    for (int l = 0 ; l < 8; l++)
    {
        for (int c = 0; c < 8; c++)
        {
            Casa *novo = (Casa*) malloc(sizeof(Casa));
            if(!novo) return NULL;
            
            novo->col = c;             
            novo->linha = l;   
            novo->peca = VAZIO;       

            if(tab->inicio == NULL) 
            {
                novo->peca = TORRE_BRANCA;
                novo->ant = NULL;
                novo->prox = NULL;

                tab->inicio = novo; 
                auxCima = novo;
            }

            else 
            {
                Casa *aux = tab->inicio;
            
                while (aux->prox != NULL) 
                    aux = aux->prox;

                // ponteiros para os lados:
                novo->prox = NULL;
                novo->ant = aux;
                aux->prox = novo;

                // ponteiros para cima e baixo:
                if (!l==0)
                {
                    novo->cima = auxCima;
                    auxCima->baixo = novo;
                    auxCima = auxCima->prox; // parte para o prox elemento
                }

                else{
                    novo->cima = NULL; // elementos da primeira linha tem topo NULO
                }

                // cor tabuleiro
                if(c != 0)
                {
                    if(auxCor == CASA_ESCURA) auxCor = CASA_CLARA;
                    else auxCor = CASA_ESCURA;
                }

                novo->cor = auxCor;

                inicializar_peca(tab, c, l); // inserir a peça no tabuleiro
            }
        }
    }

    return tab;
}

void printarTabuleiro(Tabuleiro *tab) // necessita-se arrumar essa função (printar a linha debaixo com casa diferentes)
{
    setlocale(LC_CTYPE, "");
    printf("\n");
    for (int l = 0; l < 8; l = l+2){
        //printf("%d ", 8-l);
        printf("%d", l);
        printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", CASA_ESCURA, obter_cor_peca(tab, 0, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 1, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 2, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 3, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 4, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 5, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 6, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 7, l), CASA_CLARA);
        //printf("%d ", 7-l);
        printf("%d", l+1);
        printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", CASA_CLARA, obter_cor_peca(tab, 0, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 1, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 2, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 3, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 4, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 5, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 6, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 7, l+1), CASA_ESCURA);
   }
    printf("   a  b  c  d  e  f  g  h - COLUNAS\n");
}

void liberarTabuleiro(Tabuleiro *tab)
{
    Casa *coluna = tab->inicio;
    Casa *linha;
    Casa *aux;

    while(coluna)
    {
        linha = coluna->prox;

        while(linha)
        {
            aux = linha->prox;
            free(linha);
            linha = aux;
        }

    aux = coluna->baixo;
    free(coluna);
    coluna = aux;

    }

    free(tab);
}

/* Funções referente as Peças */

Casa * inicializar_peca (Tabuleiro *tab, int col, int linha)
{
    Casa * e = obter_peca(tab, col, linha);
    e->peca = VAZIO;

    // Peças Brancas

    if (linha == 0 && col == 7)
        e->peca = TORRE_BRANCA;
    
    else if(linha == 1)
        e->peca = PEAO_BRANCO;

    else if (linha == 0 && col == 2 || linha == 0 && col == 5)
        e->peca = BISPO_BRANCO;
    
    else if (linha == 0 && col == 3)
        e->peca = REI_BRANCO;

    else if (linha == 0 && col == 4)
        e->peca = RAINHA_BRANCA;

    else if (linha == 0 && col == 1 || linha == 0 && col == 6 )
        e->peca = CAVALO_BRANCO;   

    // Peças pretas

    if (linha == 7 && col == 7 || linha == 7 && col == 0)
        e->peca = TORRE_PRETA;
    
    else if(linha == 6)
        e->peca = PEAO_PRETO;

    else if (linha == 7 && col == 2 || linha == 7 && col == 5)
        e->peca = BISPO_PRETO;
    
    else if (linha == 7 && col == 3)
        e->peca = REI_BRANCO;

    else if (linha == 7 && col == 4)
        e->peca = RAINHA_PRETA;

    else if (linha == 7 && col == 1 || linha == 7 && col == 6 )
        e->peca = CAVALO_PRETO;   

}

Casa * obter_peca(Tabuleiro *tab, int col, int linha )
{
    int i = 0;
    Casa *e = tab->inicio; 

    for( i = 0; i < linha ; i++) //procura em qual linha o elemento está
         e = e->baixo;

    for( i = 0; i < col; i++ )  // procura em qual coluna
        e = e->prox;

    return e;
}

wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha )
{

    Casa *e = obter_peca(tab, col, linha );

    if(e->peca == VAZIO) return e->cor;
    return e->peca;
}

Casa * excluir_peca (Tabuleiro *tab, int col, int linha)
{
    Casa *e = obter_peca (tab, col, linha);
    e->peca = VAZIO;
}

Casa * inserir_peca (Tabuleiro *tab, int col, int linha, wint_t peca)
{
    Casa *e = obter_peca (tab, col, linha);
    e->peca = peca;
}