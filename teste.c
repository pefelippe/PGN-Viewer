                // --- INICIALIZANDO PEÇAS ---
                if (l == 1 && c == 1)
                    novo->peca = TORRE_BRANCA;
                //else if(l==1)
                    //novo->peca = PEAO_PRETO;
                
                else if(l==6) 
                    novo->peca = PEAO_BRANCO;
                
                

                else // necessita arrumar a cor das casas.
                {
                    if(auxCor == 0){
                        novo->cor = CASA_CLARA;
                        if(c != 7)
                            auxCor++; 
                    }else{
                        novo->cor = CASA_ESCURA;
                        auxCor--;
                    }
                                     
                }