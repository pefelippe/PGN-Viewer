// Falta fazer (ou terminar)
// - Promoção do Peão (CORRIGIR)
// - Movimentação : BISPO, RAINHA, REI, TORRE
// - ROQUE
// - ambiguidade da torre

// R - Torre
// N - Cavalo
// K - Rei
// Q - Rainha
// p - Peão 
// B - Bispo


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabuleiro.h"

/* Funções Estruturais */

Tabuleiro* criarTabuleiro(Tabuleiro *tab){
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
            novo->qntMov = 0;    

            if(tab->inicio == NULL) 
            {
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

                else
                    novo->cima = NULL; // elementos da primeira linha tem topo NULO

            }

            // determinar cor tabuleiro
            if(c != 0)
            {
                if(auxCor == CASA_ESCURA) auxCor = CASA_CLARA;
                else auxCor = CASA_ESCURA;
            }

            novo->corFundo = auxCor;

            inicializar_tab(tab, c, l); //inserir as peças
    
        }
    }

    return tab;
}

Casa* inicializar_tab (Tabuleiro *tab, int col, int linha){
    Casa * e = obter_peca(tab, col, linha);
    e->peca = VAZIO;

    // Peças Brancas

    if (linha == 0 && col == 7 || linha == 0 && col == 0){
        e->peca = TORRE_BRANCA;
        e->tipo = 'R';
        e->cor = 'B';

    }
    else if(linha == 1){
        e->peca = PEAO_BRANCO;
        e->tipo = 'p';
        e->cor = 'B';
    }
    else if (linha == 0 && col == 2 || linha == 0 && col == 5){
        e->peca = BISPO_BRANCO;
        e->tipo = 'B';
        e->cor = 'B';
    }
    
    else if (linha == 0 && col == 3){
        e->peca = REI_BRANCO;
        e->tipo = 'K';
        e->cor = 'B';
    }

    else if (linha == 0 && col == 4){
        e->peca = RAINHA_BRANCA;
        e->tipo = 'Q';
        e->cor = 'B';
    }

    else if (linha == 0 && col == 1 || linha == 0 && col == 6){
        e->peca = CAVALO_BRANCO;
        e->tipo = 'N';
        e->cor = 'B';
    }

    // Peças pretas

    if (linha == 7 && col == 7 || linha == 7 && col == 0){
        e->peca = TORRE_PRETA;
        e->tipo = 'R';
        e->cor = 'P';
    }
    
    else if(linha == 6){
        e->peca = PEAO_PRETO;
        e->tipo = 'p';
        e->cor = 'P';
    }

    else if (linha == 7 && col == 2 || linha == 7 && col == 5){
        e->peca = BISPO_PRETO;
        e->tipo = 'B';
        e->cor = 'P';
    }
    
    else if (linha == 7 && col == 3){
        e->peca = REI_BRANCO;
        e->tipo = 'K';
        e->cor = 'P';
    }

    else if (linha == 7 && col == 4){
        e->peca = RAINHA_PRETA;
        e->tipo = 'Q';
        e->cor = 'P';
    }

    else if (linha == 7 && col == 1 || linha == 7 && col == 6){
        e->peca = CAVALO_PRETO;
        e->tipo = 'N';
        e->cor = 'P';
    }
}

/* Funções Essenciais */

void iniciarXadrez(Tabuleiro *tab, char const *arquivo){
    // abre o arquivo uma vez, procurando onde começar a ler as instruções
    int linhasignoradas = 1;       
    char ch;
    FILE *arq = fopen (arquivo, "r");
    if (!arq)
    { 
        printf("Erro ao ler arquivo. \n");
        exit(1);
    }
    while ((ch = fgetc(arq)) != EOF){ if(ch == '[') linhasignoradas++; }
    fclose(arq);

    // abre mais uma vez, pulando para a linha desejada (só consegui ler corretamente assim) #gambiarra
    char aux = 0; 
    int auxcont = 0;
    FILE *arq2 = fopen (arquivo, "r");
    while(!feof(arq2))
    {
        aux = fgetc(arq2);
        if(aux == '\n') auxcont++;
        if(auxcont == linhasignoradas)
        {
            while(!feof(arq2))
            {
                char auxnum[3];
                char jogadaB[10];
                char jogadaP[10];

                fscanf(arq2, "%c.%s %s ", auxnum, jogadaB, jogadaP);
                int num = auxnum[0] - '0';

                lerJogada(tab, jogadaB, "Brancas", num);
                lerJogada(tab, jogadaP, "Pretas", num);   
            }
        }
    }
}

void printarTabuleiro(Tabuleiro *tab){ // corrigir rainha preta  
    setlocale(LC_CTYPE, "");

    printf("\n SIMULAÇÃO XADREZ v1.0 \n\n\n");
    for (int l = 0; l < 8; l = l+2)
    {
        printf("%d ", l+1);
        printf(" %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", CASA_ESCURA, obter_cor_peca(tab, 0, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 1, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 2, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 3, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 4, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 5, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 6, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 7, l), CASA_CLARA);
        printf("%d ", l+2);
        printf(" %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", CASA_CLARA, obter_cor_peca(tab, 0, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 1, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 2, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 3, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 4, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 5, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 6, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 7, l+1), CASA_ESCURA);
   }
    printf("    a  b  c  d  e  f  g  h  \n");
}

void lerJogada (Tabuleiro *tab, char *jogada, char  *cor, int numero){
    clear_screen();

    if ((testar(tab, jogada, cor)) == 1)
    {
        printarTabuleiro(tab);
        printf("Jogada: %s \n", jogada);
        printf("\nPressione ENTER para ver a próxima jogada. \n");
        getchar();
        return;  
    } 

    else if ((testar(tab, jogada, cor)) == -1){
        printarTabuleiro(tab);
        printf("\n\tFim da simulação. \n");
    } 

    else
    {
        printarTabuleiro(tab);
        printf("Erro na jogada de número %d das peças %s - %s\n", numero, cor, jogada);
        exit(1);
    }
}

// Promoção do Peão (CORRIGIR)
void verificarPromocao(Tabuleiro *tab){
    Casa *aux;

    for(int c = 0; c<8; c++){
        aux = obter_peca(tab, c, 0);
        if(aux->peca == PEAO_PRETO)
            aux->peca = RAINHA_PRETA;
    }

    for(int c = 0; c<8; c++){
        aux = obter_peca(tab, c, 0);
        if(aux->peca == PEAO_BRANCO)
            aux->peca = RAINHA_BRANCA;
    }
}

int testar(Tabuleiro *tab, char *jogada, char *cor) // verificar jogadas e definir as posições corretas
{
    int coluna = 0;
    int linha = 0;
    char colunaDestino = 0;
    int linhaDestino = 0;
    char peca;
    int verificador = 0;   // se 0 - jogada invalida, se 1 - jogada valida, se  2 - ambiguidade.
    int naoinserir = 0;

    if(strcmp(jogada, "O-O") == 0 ){
        printf("Roque");
        linhaDestino = 1; // só p n dar erro. apagar dps;
        verificador = 0;
        naoinserir = 1;
    }

    else if ((strcmp(jogada, "O-O-O") == 0 ))
    {
        printf("Roque2");
        linhaDestino = 1; // só p n dar erro. apagar dps;
        naoinserir = 1;
        verificador = 0;
    }
    else if((strcmp(jogada, "1-0") == 0) || (strcmp(jogada, "0-1") == 0 ) || (strcmp(jogada, "1/2-1/2") == 0 )){
        return -1;
    }

    // ler a jogada e definir o DESTINO da peça:
    else if(strlen(jogada) == 2) // peão
    {
        peca = 'p';
        linhaDestino = jogada[1] - '0'; // converte em int
        colunaDestino = jogada[0];
    }

    else if ((strlen(jogada) == 4) && (jogada[3] != '+') && (jogada[3] != '?')) // se a jogada tem tam = 4, ou é captura ou jogada de desambiguidade
    {
        peca = jogada[0];
        colunaDestino = jogada[2];
        linhaDestino = jogada[3] - '0';
        
        if (jogada[1] == 'x') // indica captura
        {
            if (islower(jogada[0])) // ambiguidade de peões 
                peca = 'p';
        }
        else    // indica jogada de desambiguidade
        {
            peca = jogada[0];
            coluna = converter_coluna_int(jogada[1]);
            // precisa procurar a linha somente
        }
        
    }

    else // demais jogadas
    {
        peca = jogada[0];
        colunaDestino = jogada[1];
        linhaDestino = jogada[2] - '0';
    }

    colunaDestino = converter_coluna_int(colunaDestino); // coluna recebe char, converter para int é necessário para utilizar a função de busca
    linhaDestino = linhaDestino - 1 ;// no caso da implementação, começamos com 0


    // pré-testes
    if (colunaDestino > 7 || colunaDestino < 0) return 0; // fora dos limites do xadrez
    if (linhaDestino > 7 || linhaDestino < 0) return 0;
    Casa *teste = obter_peca(tab, colunaDestino, linhaDestino);
    //if(teste->peca != VAZIO  && jogada[1] != 'x') return 0; // querer colocar a peça em uma posição ocupada NAO TA FUNCUIONADO BLZ


    // ler a jogada e definir a ORIGEM da peça:
    Casa *aux = tab->inicio;
    while(aux->prox != NULL) // procurar casa a casa uma peça válida para realizar a jogada
    {
        // se tem strlen = 4 (desambiguação) -> procurar linha
        // jogada normal: procurar linha e coluna

        if(aux->tipo == peca && aux->cor == cor[0])
        {
            
            if(peca == 'p') // PEAO 
            { 
                coluna = colunaDestino;
                if(cor[0] == 'B')
                {
                    if(jogada[1] == 'x'){
                        linha = linhaDestino-1;
                        coluna = converter_coluna_int(jogada[0]);
                        verificador=1;
                    }

                    else {

                        if ((aux->col == colunaDestino) && ((linhaDestino - aux->linha) == 1) ){
                            verificador++;
                            linha = aux->linha;
                        }
                        else if ((aux->col == colunaDestino) && ((linhaDestino - aux->linha) == 2) && (aux->qntMov == 0))
                        {
                            verificador++;
                            linha = aux->linha;
                        }
                    }
                }

                else if(cor[0] == 'P')
                {
                    if (jogada[1] == 'x'){
                        linha = linhaDestino+1;  
                        coluna = converter_coluna_int(jogada[0]);
                        verificador = 1;
                    }
                    else {
                        if ((aux->col == colunaDestino) && ((aux->linha - linhaDestino) == 2) && (aux->qntMov == 0)) // peão q ainda n se moveu pode se mexer 2 casas
                        {
                            verificador++;
                            linha = aux->linha;
                        }
                        else if ((aux->col == colunaDestino) && ((aux->linha - linhaDestino) == 1 ))
                        {
                            verificador++;
                            linha = aux->linha;
                        }
                        
                    }
                }
            }
            
            else if (peca == 'N') // CAVALO
            {
                if((strlen(jogada) == 4) && (jogada[3] != '+') && (jogada[3] != '?')) // retirar ambiguidade
                {
                    if(aux->col == coluna)
                        linha = aux->linha;
                        verificador = 1;
                }
                else 
                {
                    if(abs(colunaDestino - aux->col) == 2 && abs(linhaDestino - aux->linha) == 1){
                        linha = aux->linha;
                        coluna = aux->col;
                        verificador = 1;
                    }
                    else if (abs(colunaDestino - aux->col) == 1 && abs(linhaDestino - aux->linha) == 2){
                        linha = aux->linha;
                        coluna = aux->col;
                        verificador = 1;
                    }
                }

            } 

            else if (peca == 'B') // BISPO
            {
                /*if((strlen(jogada) == 4) && (jogada[3] != '+') && (jogada[3] != '?')) // ambiguidade
                {
                    if(aux->col == coluna && aux->peca == 'B')
                        printf("LINHA BISPO DENTRO: %d", linha);
                        linha = aux->linha;
                        verificador = 1;
                }      
                else if (aux->peca == 'B')// verificar as diagonais
                {
                    printf("COLUNA BISPO: %d \n", aux->col);


                    coluna = aux->col;
                    linha = aux->linha;
                }*/
  
            }

            else if (peca == 'R') // TORRE esta ambigua kkk
            {
                /*if((strlen(jogada) == 4) && (jogada[3] != '+') && (jogada[3] != '?')) // ambiguidade prov n funciona
                {
                    linha = linhaDestino;
                } 
                else{
                    if(aux->linha ==  linhaDestino){
                        linha = linhaDestino;
                        coluna = aux->col;
                        verificador = 1;
                    }
                    else if(aux->col == colunaDestino){
                        coluna = colunaDestino;
                        linha = aux->linha;
                        verificador = 1;
                    }
                }  */             
            }

            else if (peca == 'K')
            {
                if (aux->peca == 'K'){
                    coluna = aux->col;
                    linha = aux->linha;
                }
            }
            else if(peca == 'Q')
            {

            }
        }

        aux = aux->prox;
    }
    printf("Antes: ");
    printf("%c-", corrigir_coluna_char(coluna));
    printf("%d\n", linha+1);
    printf("Depois: ");
    printf("%c-", corrigir_coluna_char(colunaDestino));
    printf("%d\n", linhaDestino+1);


    if(verificador == 1 &&  naoinserir == 0)  // insere no tab
    { 
        inserir(tab, coluna, linha, colunaDestino, linhaDestino);
    }
        verificador = 1;        // retirar ao acabar a função
        return verificador;
    
}

void inserir(Tabuleiro *tab, int coluna, int linha, int colunaDestino, int linhaDestino){
        Casa *ant = obter_peca(tab, coluna, linha);
        Casa *novo = obter_peca(tab, colunaDestino, linhaDestino);

        novo->peca = ant->peca;
        novo->tipo = ant->tipo;
        novo->qntMov = ant->qntMov++;
        ant->peca = VAZIO;
        ant->tipo = '\0';

        verificarPromocao(tab);
}

/* Funções Auxiliares */

Casa * obter_peca(Tabuleiro *tab, int col, int linha ){
    int i = 0;
    Casa *e = tab->inicio; 

    for( i = 0; i < linha ; i++) 
         e = e->baixo;

    for( i = 0; i < col; i++)  
        e = e->prox;

    return e;
}

wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha ){
    Casa *e = obter_peca(tab, col, linha );

    if(e->peca == VAZIO) return e->corFundo;
    return e->peca;
}

int converter_coluna_int(char c){
    if (c == 'a')   return 0;
    else if(c=='b') return 1;
    else if(c=='c') return 2;
    else if(c=='d') return 3;
    else if(c=='e') return 4;
    else if(c=='f') return 5;
    else if(c=='g') return 6;
    else return 7;
}

char corrigir_coluna_char(int c){
    if (c == 0)   return 'a';
    else if(c==1) return 'b';
    else if(c==2) return 'c';
    else if(c==3) return 'd';
    else if(c==4) return 'e';
    else if(c==5) return 'f';
    else if(c==6) return 'g';
    else return 'h';
}


/* Liberar Memória */

void liberarTabuleiro(Tabuleiro *tab){
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


