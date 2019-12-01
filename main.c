/*
    Desenvolvido por: Pedro Felippe - 418806 e José Eduardo - 421873
    Disciplina: CK0226 - Programação
    Professor: Miguel Franklin de Castro
 */

#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"

int main(int argc, char const *argv[])
{
    Tabuleiro *tab;
    tab = NULL;
    tab = criarTabuleiro(tab);
    printarTabuleiro(tab);
	iniciarXadrez(tab, argv[1]);
    liberarTabuleiro(tab);

    return 0;
}                                                                                                                                                                                                                                     