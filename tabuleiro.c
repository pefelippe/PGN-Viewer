/*OBS: A notação das peças está em inglês:
   R - Torre    (Rook)
   N - Cavalo   (Knight)
   K - Rei      (King)
   Q - Rainha   (Queen)
   B - Bispo    (Bishop)
   p - Peão     (resolvi indicar 'p' para peão)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabuleiro.h"

/* Funções Estruturais */

Tabuleiro* criarTabuleiro(Tabuleiro *tab)
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
            novo->tipo ='0';
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
            novo->corFundo = corFundo(c, l);

            inicializar_tab(tab, c, l); //inserir as peças
            
        }
    }

    return tab;
}

Casa* inicializar_tab (Tabuleiro *tab, int col, int linha)
{
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
        e->peca = RAINHA_BRANCA;
        e->tipo = 'Q';
        e->cor = 'B';
    }

    else if (linha == 0 && col == 4){
        e->peca = REI_BRANCO;
        e->tipo = 'K';
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
        e->peca = RAINHA_PRETA;
        e->tipo = 'Q';
        e->cor = 'P';
    }

    else if (linha == 7 && col == 4){
        e->peca = REI_PRETO;
        e->tipo = 'K';
        e->cor = 'P';
    }

    else if (linha == 7 && col == 1 || linha == 7 && col == 6){
        e->peca = CAVALO_PRETO;
        e->tipo = 'N';
        e->cor = 'P';
    }
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

/* Funções Funcionais */

void printarTabuleiro(Tabuleiro *tab)
{   
    setlocale(LC_CTYPE, "");

    printf("\t       SIMULAÇÃO XADREZ  \n\n");
    for (int l = 0; l < 8; l = l+2)
    {
        printf("\t%d ", l+1);
        printf(" %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", CASA_ESCURA, obter_cor_peca(tab, 0, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 1, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 2, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 3, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 4, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 5, l), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 6, l), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 7, l), CASA_CLARA);
        printf("\t%d ", l+2);
        printf(" %lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", CASA_CLARA, obter_cor_peca(tab, 0, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 1, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 2, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 3, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 4, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 5, l+1), CASA_ESCURA, CASA_CLARA, obter_cor_peca(tab, 6, l+1), CASA_CLARA, CASA_ESCURA, obter_cor_peca(tab, 7, l+1), CASA_ESCURA);
   }
    printf("\t    a  b  c  d  e  f  g  h  \n");
}

void iniciarXadrez(Tabuleiro *tab, char const *arquivo)
{
    FILE *arq = fopen (arquivo, "r");
    if (!arq){ 
        printf("Erro ao ler arquivo. \n");
        exit(1);
    }
    // assumindo que o tamanho do cabeçalho é fixo (9 + 1 linha em branco)
    char lixo[10000];

    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    fgets(lixo, 10000, arq);
    int contador = 0;
    while (!feof(arq))
    { 
        int num[1];
        char jogadaB[10];
        char jogadaP[10];
        char lixo[1];
        
        fscanf(arq, "%d%c%s %s ", num, lixo, jogadaB, jogadaP); // vai bugar se a jogada branca for a última.
        contador++;
        lerJogada(tab, jogadaB, "Brancas", contador, num[0]);
        lerJogada(tab, jogadaP, "Pretas", contador, num[0]); 
        
    }
}

int lerJogada(Tabuleiro *tab, char *jogada, char  *cor, int numero, int aux)
{
    clear_screen();
    if ((testar(tab, jogada, cor)) == 1)
    {
        printarTabuleiro(tab);
        printf("\t   Jogada %s (%d): %s \n\t \n", cor, numero, jogada);
        printf("\n   Pressione ENTER para ver a próxima jogada.");
        getchar();
    } 

    else if (((strcmp(jogada, "1-0")) == 0) || ((strcmp(jogada, "1/2-1/2")) == 0)  || ((strcmp(jogada, "0-1")) == 0)){
        printarTabuleiro(tab);
        printf("\n   Fim da simulação.\n");
        printf("   Resultado: %s\n\n",  jogada);
    }
    else if (aux == 0)
    {
        printarTabuleiro(tab);
        printf("\n   Fim da simulação.\n");
        printf("   Resultado: 0 - 1 \n");
    }
    else if (aux == 1)
    {
        printarTabuleiro(tab);
        printf("\n   Fim da simulação.\n");
        printf("   Resultado: 1/2 - 1/2 \n");
    }
    else
    {
        printarTabuleiro(tab);
        printf("Erro na jogada de número %d das peças %s - %s\n", numero, cor, jogada);
    }
}

int testar(Tabuleiro *tab, char *jogada, char *cor) // verificar jogadas e definir as posições corretas
{
    int coluna;
    int linha;
    int linhaDestino;
    char colunaDestino;
    char peca;

  
    int desambiguidadeCol = 0;
    int desambiguidadeLinha = 0;

    int verificador = 0;   // 0 - jogada inválida, 1 - jogada válida

    // Realizar o Roque:
    if(strcmp(jogada, "O-O") == 0 || (strcmp(jogada, "O-O-O") == 0 )) // adcionar os movimetnso
        return roque(tab, jogada, cor);

    // Definir peça, e coordenadas de DESTINO:
    if (strlen(jogada) == 2 || (jogada[2] == '=' ) || ( (strlen(jogada) == 3 || strlen(jogada) == 4) && (jogada[2] == '?' || jogada[2] == '+') ) ) // Mov. Padrão do Peão OU Promoção
    {
        peca = 'p';
        linhaDestino = jogada[1] - '0'; // converte em int
        colunaDestino = jogada[0];
    }

    else if (jogada[1] == 'x') // Jogada de Captura (ok)
    {
        peca = jogada[0];
        colunaDestino = jogada[2];
        linhaDestino = jogada[3] - '0';

        if (islower(jogada[0])) // ambiguidade de peões  
            peca = 'p';
    }

    else if (jogada[2] == 'x') // Jogada de Captura + Desambiguação (ok)
    {
        peca = jogada[0];
        coluna = converter_coluna_int(jogada[1]);
        desambiguidadeCol = 1;

        if(isdigit(jogada[1])) // desambiguidade de linha
        {
            linha = jogada[1] - '0';
            linha = linha - 1;
            desambiguidadeLinha = 1;
            desambiguidadeCol = 0;
        }

        colunaDestino = jogada[3];
        linhaDestino = jogada[4] - '0';

        if (islower(jogada[0])) // ambiguidade de peões  
            peca = 'p';
    }

    else if ((strlen(jogada) >= 4) && jogada[1] != 'x' && jogada[2] != 'x' && jogada[3] != '+' && jogada[3] != '?') // Jogada de desambiguidade
    {
        peca = jogada[0];
        coluna = converter_coluna_int(jogada[1]);
        desambiguidadeCol = 1;

        if(isdigit(jogada[1]))
        {
            linha = jogada[1] - '0';
            linha = linha - 1;
            desambiguidadeLinha = 1;
            desambiguidadeCol = 0;
        }

        colunaDestino = jogada[2];
        linhaDestino = jogada[3] - '0';
    }

    else  // Demais Jogadas (com strlen = 3 OU com comentários) (ok)
    {
        peca = jogada[0];
        colunaDestino = jogada[1];
        linhaDestino = jogada[2] - '0';
    }

    
    colunaDestino = converter_coluna_int(colunaDestino);    // Converter para int é necessário para utilizar a função obter_peca.
    linhaDestino = linhaDestino - 1 ;                      // Pois começamos com 0.

    // Pequenos Testes de Parâmetro:
    if (colunaDestino > 7 || colunaDestino < 0) return 0;
    if (linhaDestino > 7  || linhaDestino < 0)  return 0;

    // Definir as coordenadas de ORIGEM:

    Casa *aux = tab->inicio;

    while(aux != NULL) // Procura pelo Tabuleiro.
    {
        // Desambiguação -> Procurar Linha (Coluna já é fornecida).
        // Jogada Normal -> Procurar Linha e Coluna.

        if(aux->tipo == 'p' && aux->cor == cor[0] && peca == 'p') // PEÃO
        {
            coluna = colunaDestino;

            if(jogada[1] == 'x') // captura.
            {
                coluna = converter_coluna_int(jogada[0]);
                verificador = 1;

                if(cor[0] == 'B') 
                    linha = linhaDestino - 1;
                else 
                    linha = linhaDestino + 1;
           
            }
        
            else 
            {
                 if (aux->col == colunaDestino)
                {
                    if ( (linhaDestino - aux->linha == 1 || (linhaDestino - aux->linha == 2 && aux->qntMov == 0) ) && cor[0] == 'B'){                        
                        linha = aux->linha;
                        verificador = 1;
                    }

                    else if ( (aux->linha - linhaDestino == 1 || (aux->linha-linhaDestino  == 2 && aux->qntMov == 0) ) && cor[0] == 'P'){                        
                        linha = aux->linha;
                        verificador = 1;
                    }
                }
            }
        } 
            
        else if (peca == 'N' && aux->cor == cor[0]) // CAVALO
        {
            /// desambiguidade  ou desambiguidade e captura
            if(aux->tipo == 'N'){
                if((strlen(jogada) == 4 && jogada[3] != '+' && jogada[3] != '?' && jogada[1] != 'x') || (jogada[2] == 'x'))
                {
                    if (abs(colunaDestino - coluna) == 2 && abs(linhaDestino - aux->linha) == 1 || (abs(colunaDestino - coluna)) == 1 && (abs(linhaDestino - aux->linha) == 2 ))
                    {
                        linha = aux->linha;
                        Casa *aux = obter_peca (tab, coluna, linha);
                        if (aux->tipo == 'N'){
                            inserir(tab, coluna, linha,colunaDestino, linhaDestino, jogada);
                            return 1;
                        }
                        
                    }
                }

                else // JOGADA NORMAL
                {
                    if (abs(colunaDestino - aux->col) == 2 && abs(linhaDestino - aux->linha) == 1 || (abs(colunaDestino - aux->col)) == 1 && (abs(linhaDestino - aux->linha) == 2))
                    {
                        linha = aux->linha;
                        coluna = aux->col;
                        Casa *aux = obter_peca (tab, coluna, linha);
                        if (aux->tipo == 'N'){
                            inserir(tab, coluna, linha,colunaDestino, linhaDestino, jogada);
                            return 1;
                        }
                    }
                }
            }
        }

        else if (peca == 'B' && aux->tipo == 'B' && aux->cor == cor[0]) // BISPO
        {
            // verifica a cor da casa destino
            // pois para cada jogador, UM dos bispo só anda nas casas BRANCAS e o outros nas casas PRETAS
            // só procurar pelo bispo que esta nas casas da cor destino

            Casa *auxBispo = obter_peca (tab, colunaDestino, linhaDestino); // Checa a Diagonal.
            if (aux->corFundo == auxBispo->corFundo)
            {
                coluna = aux->col;
                linha = aux->linha;
                verificador = checar_diagonal(tab, coluna, linha, colunaDestino, linhaDestino);

            }              
        }

        else if (peca == 'R' && aux->tipo == 'R' && aux->cor == cor[0]) // TORRE 
        {


            if(aux->linha == linhaDestino && aux->cor == cor[0]) // Movimento no Eixo X.
            {
                int verifLinha = checar_linha(tab, linhaDestino, aux->col, colunaDestino);
                
                if(verifLinha == 1)
                {
                    if(desambiguidadeCol == 0) coluna = aux->col;
                        
                    if(desambiguidadeLinha == 0) linha = linhaDestino;
                        
                    if (aux->tipo == 'R')
                    {
                        inserir(tab, coluna, linha, colunaDestino, linhaDestino, jogada);
                        return 1;
                    }
                    
                }
            }

            else if(aux->col == colunaDestino && aux->cor == cor[0]) // Movimento no Eixo Y.
            { 
                int verifColuna = checar_coluna(tab, colunaDestino, aux->linha, linhaDestino);
                
                if(verifColuna == 1)
                {
                    if(desambiguidadeCol == 0) coluna = colunaDestino;
                        
                    if(desambiguidadeLinha == 0) linha = aux->linha;

                    if (aux->tipo == 'R')
                    {
                        inserir(tab,coluna, linha, colunaDestino, linhaDestino, jogada);
                        return 1;
                    }
                }

            }
            
        }

        else if (peca == 'K' && (aux->tipo == 'K') && aux->cor == cor[0]) // REI
        {
            coluna = aux->col;
            linha = aux->linha;
            if (abs(colunaDestino - coluna ) == 2 || abs(linhaDestino - linha) == 2) return 0;
            verificador = 1;     
        }

        else if(peca == 'Q' && aux->tipo == 'Q' && aux->cor == cor[0]) //RAINHA
        {
            if(aux->linha == linhaDestino) 
            {
                int verifLinha = checar_linha(tab, aux->linha, aux->col, colunaDestino); // checa eixo X.
                if(verifLinha == 1){

                    if(desambiguidadeCol == 0) coluna = aux->col;
                        
                    if(desambiguidadeLinha == 0) linha = linhaDestino;

                    verificador = 1;
                }
            }

            else if(aux->col == colunaDestino) 
            {
                int verifColuna = checar_coluna(tab, aux->linha, aux->col, colunaDestino); // checa eixo Y.
                if(verifColuna == 1)
                {
                    if(desambiguidadeLinha == 0) linha = aux->linha;
                    if(desambiguidadeCol == 0) coluna = colunaDestino;
                    verificador = 1;
                }
            }

            else
            {
                Casa *auxBispo = obter_peca (tab, colunaDestino, linhaDestino); // checar as Diagonais.

                if (aux->corFundo == auxBispo->corFundo)
                {
                    coluna = aux->col;
                    linha = aux->linha;
                    verificador = checar_diagonal(tab, coluna, linha, colunaDestino, linhaDestino);
                }
            }
        }

        aux = aux->prox;
    }


    if(verificador == 1) // Não há problemas detectados.
        inserir(tab, coluna, linha, colunaDestino, linhaDestino, jogada);

    return verificador;
}

void inserir(Tabuleiro *tab, int coluna, int linha, int colunaDestino, int linhaDestino, char *jogada)
{
        Casa *ant = obter_peca(tab, coluna, linha);
        Casa *novo = obter_peca(tab, colunaDestino, linhaDestino);
        novo->cor = ant->cor;
        novo->peca = ant->peca;
        novo->tipo = ant->tipo;
        novo->qntMov = ant->qntMov + 1;

        ant->qntMov = 0;
        ant->peca = VAZIO;
        ant->tipo = '\0';

        if(jogada[2] == '=') // Jogada de Promoção.
            {
                novo->tipo = jogada[3];
                wint_t auxcor;

                     if (jogada[3] == 'Q' && novo->cor == 'B') auxcor = RAINHA_BRANCA;
                else if (jogada[3] == 'Q' && novo->cor == 'P') auxcor = RAINHA_PRETA;
                else if (jogada[3] == 'R' && novo->cor == 'B') auxcor = TORRE_BRANCA;
                else if (jogada[3] == 'R' && novo->cor == 'P') auxcor = TORRE_PRETA;
                else if (jogada[3] == 'B' && novo->cor == 'B') auxcor = BISPO_BRANCO;
                else if (jogada[3] == 'B' && novo->cor == 'P') auxcor = BISPO_PRETO;
                else if (jogada[3] == 'N' && novo->cor == 'B') auxcor = CAVALO_BRANCO;
                else if (jogada[3] == 'N' && novo->cor == 'P') auxcor = CAVALO_PRETO;
                novo->peca = auxcor;
            }
}

int roque(Tabuleiro *tab, char *jogada, char *cor)
{
    int colunaRei, colunaTorre, colunaReiDestino, colunaTorreDestino;
    int linhaRei, linhaTorre;
    Casa *aux = tab->inicio;

    while(aux->prox != NULL) // Procurar no Tabuleiro
    {
        if(aux->tipo == 'K' && aux->cor == cor[0] && aux->qntMov == 0)
        {
            colunaRei = aux->col;
            linhaRei  = aux->linha;

            if ((strlen(jogada) == 3) ) // Roque Pequeno.
            {
                colunaTorre = 7;
                Casa *torre = obter_peca(tab,colunaTorre, linhaRei);
                if (torre->qntMov != 0) return 0;
                colunaTorreDestino = colunaRei+1;
                colunaReiDestino = colunaRei+2;             
            }

            else // Roque Grande (lado da Rainha).
            {
                colunaTorre = 0;
                Casa *torre = obter_peca(tab,colunaTorre, linhaRei);
                if (torre->qntMov != 0) return 0;
                colunaTorreDestino = 3;
                colunaReiDestino = 2;
            }

            linhaTorre = linhaRei;
            inserir(tab, colunaTorre, linhaTorre, colunaTorreDestino, linhaTorre, jogada);
            inserir(tab, colunaRei, linhaRei, colunaReiDestino, linhaRei, jogada);
            return 1;      
        }

        aux = aux->prox;
    }
        
    return 0;
}

int checar_linha(Tabuleiro *tab, int linha, int colunaOrigem, int colunaDestino)
{
    // Verifica se é possível mover peças entre a colunaOrigem e a colunaDestino.
    // Se existirem peças no caminho, retorne erro.
    int i, j;

    if(colunaDestino > colunaOrigem)
    {
        i = colunaOrigem+1;
        j = colunaDestino;
    }
    else{
        i = colunaDestino+1;
        j = colunaOrigem;
    }

    while(i<j)
    {

        Casa *aux = obter_peca(tab, i, linha);
        if(aux->peca != VAZIO) return 0;
        i++;
    }

    return 1;
}

int checar_coluna(Tabuleiro *Tab, int coluna, int linhaOrigem, int linhaDestino)
{
    // Verifica se é possível mover peças entre a linhaOrigem e a linhaDestino.
    // Se existirem peças no caminho, retorne erro.
    int i, j;

    if(linhaOrigem > linhaDestino){
        i = linhaDestino;
        j = linhaOrigem;
    }

    else{
        i = linhaOrigem;
        j = linhaDestino;
    }

    i = i+1;
    for(i; i < j; i++) 
    {
        Casa *aux = obter_peca(Tab, coluna, i);
        if(aux->peca != VAZIO) return 0;
    }

    return 1;
}

int checar_diagonal(Tabuleiro *Tab, int coluna, int linha, int colunaDestino, int linhaDestino) // para bispo e rainha
{
    //procurar em cada quadrante:
    //  1º : ESQUERDA e CIMA - 2º: ESQUERDA BAIXO
    //  3 : DIREITA e CIMA - 2º: DIREITA BAIXO
    int c, l;

    if (coluna > colunaDestino) // Procurar a ESQUERDA
    { 
        if(linha > linhaDestino) // procurar p/ CIMA
        {
            c = colunaDestino + 1;
            l = linhaDestino  + 1;

            for(c; c > coluna; c--) 
            {
                Casa *aux = obter_peca(Tab, c, l);
                if(aux->peca != VAZIO) return 0;
                l++;
            }
        }
        else // procurar p/ BAIXO
        {
            c = colunaDestino + 1;
            l = linhaDestino - 1;

            for(c; c > coluna; c--) 
            {
                Casa *aux = obter_peca(Tab, c, l);
                if(aux->peca != VAZIO) return 0;
                l++;
            }
        }
    }

    else // procurar a DIREITA
    {
        if(linha > linhaDestino) // procurar p/ CIMA
        {
            c = colunaDestino - 1;
            l = linhaDestino + 1;

            for(c; c > coluna; c--) 
            {
                Casa *aux = obter_peca(Tab, c, l);
                if(aux->peca != VAZIO) return 0;
                l++;
            }
        }
        else // procurar p/ BAIXO
        {
            c = colunaDestino - 1;
            l = linhaDestino - 1;
            for(l; l > linha; l--) 
            {
                Casa *aux = obter_peca(Tab, c, l);
                if(aux->peca != VAZIO) return 0;
                c--;
            }
        }
    }

    return 1;
}



/* Funções Auxiliares */

Casa * obter_peca(Tabuleiro *tab, int col, int linha )
{
    int i = 0;
    Casa *e = tab->inicio; 

    for( i = 0; i < linha ; i++) 
         e = e->baixo;

    for( i = 0; i < col; i++)  
        e = e->prox;

    return e;
}

wint_t obter_cor_peca (Tabuleiro *tab, int col, int linha )
{
    Casa *e = obter_peca(tab, col, linha );

    if(e->peca == VAZIO) return e->corFundo;
    return e->peca;
}

int converter_coluna_int(char c)
{
    if (c == 'a')   return 0;
    else if(c=='b') return 1;
    else if(c=='c') return 2;
    else if(c=='d') return 3;
    else if(c=='e') return 4;
    else if(c=='f') return 5;
    else if(c=='g') return 6;
    else return 7;
}

char corrigir_coluna_char(int c)
{
    if (c == 0)   return 'a';
    else if(c==1) return 'b';
    else if(c==2) return 'c';
    else if(c==3) return 'd';
    else if(c==4) return 'e';
    else if(c==5) return 'f';
    else if(c==6) return 'g';
    else return 'h';
}

wint_t corFundo (int coluna, int linha)
{
    if(coluna % 2 == 0 && linha % 2 == 0) return CASA_ESCURA;
    else if (coluna %2 != 0 && linha %2 != 0) return CASA_ESCURA;
    else 
        return CASA_CLARA;
}


// versão alternativa de iniciarXadrez:
/*void iniciarXadrez(Tabuleiro *tab, char const *arquivo) //ignorando o cabeçalho
{
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
            int num[1];
            char jogadaB[10];
            char jogadaP[10];
            char lixo[1];

            fscanf(arq, "%d%c%s %s ", num, lixo, jogadaB, jogadaP);

            lerJogada(tab, jogadaB, "Brancas", num[0]);
            lerJogada(tab, jogadaP, "Pretas", num[0]);
                }
        }
    }
}*/
