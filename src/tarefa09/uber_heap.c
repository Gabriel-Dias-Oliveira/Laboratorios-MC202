 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB09: GERENCIAR OS GASTOS E A FILA DE PASSAGEIROS DE UM MOTORISTA DE UBER ("DIA DE UBER").

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "uber_heap.h"

// FUNÇÃO BASE PARA TROCAR DUAS INFORMAÇÕES DE LUGAR - MUITO UTILIZADA AO LONGO DO CÓDIGO.
// TROCA O CONTEÚDO DA POSIÇÃO 'A' PELO DA POSIÇÃO 'B'.
void trocaValores(p_passageiro a, p_passageiro b){ 
    Passageiro aux = *a;
    *a = *b;
    *b = aux;
}

// POSICIONA CORRETAMENTE UM NOVO PASSAGEIRO NA FILA DE ESPERA.
// O NOVO PASSAGEIRO - ALOCADO NO FINAL DO VETOR - DEVE SUBIR NA FILA ATÉ A POSIÇÃO CORRETA.
void subirNaFila(p_uber filaUber, int posicaoAtual){
    if(posicaoAtual > 0 && 
        filaUber->passageiros[PAI(posicaoAtual)].avaliacao < filaUber->passageiros[posicaoAtual].avaliacao){
        
        trocaValores(&filaUber->passageiros[posicaoAtual], &filaUber->passageiros[PAI(posicaoAtual)]);
        
        subirNaFila(filaUber, PAI(posicaoAtual));
    }
}

// APÓS O VALOR MÁXIMO SER REMOVIDO DEVEMOS 'DESCER' O VALOR QUE ASSUME A POSIÇÃO.
void desceNaFila(p_uber filaUber, int posAtual){
    int maiorValor;
    
    if(FILHO_ESQUERDO(posAtual) < filaUber->quatidadePassageiros){
        maiorValor = FILHO_ESQUERDO(posAtual);
        
        if(FILHO_DIREITO(posAtual) < filaUber->quatidadePassageiros && 
        filaUber->passageiros[FILHO_ESQUERDO(posAtual)].avaliacao < filaUber->passageiros[FILHO_DIREITO(posAtual)].avaliacao)
            
            maiorValor = FILHO_DIREITO(posAtual);
            
        if(filaUber->passageiros[posAtual].avaliacao < filaUber->passageiros[maiorValor].avaliacao){
            trocaValores(&filaUber->passageiros[posAtual], &filaUber->passageiros[maiorValor]);
            desceNaFila(filaUber, maiorValor);
        }
    }
}

// INSERE UM NOVO PASSAGEIRO NA FILA UBER.
void inserePassageiro(p_uber filaUber, p_passageiro passageiro){
    filaUber->passageiros[filaUber->quatidadePassageiros] = *passageiro;
    
    filaUber->passageiros[filaUber->quatidadePassageiros].nome = malloc(MAX_NAME * sizeof(char));
    
    if(filaUber->passageiros[filaUber->quatidadePassageiros].nome == NULL)
        exit(1);

    filaUber->passageiros[filaUber->quatidadePassageiros].nome = 
    strcpy(filaUber->passageiros[filaUber->quatidadePassageiros].nome, passageiro->nome);
    
    free(passageiro->nome);
    free(passageiro);

    filaUber->quatidadePassageiros++;

    subirNaFila(filaUber, filaUber->quatidadePassageiros - 1);
}

// LIBERA AS INFORMAÇÕES ALOCADAS RELACIONADAS A FILA E AO MOTORISTA.
void destruirListas(p_motorista motoristaUber){
    free(motoristaUber->filaUber->passageiros);
    free(motoristaUber->filaUber);
    free(motoristaUber);
}

// RETORNA A 'POSIÇÃO' NA FILA DE UM PASSAGEIRO.
// BUSCA A PARTIR DO NOME.
int posicaoPassageiro(p_uber filaUber, char *nomeBusca){
    for(int x = 0; x < filaUber->quatidadePassageiros; x++)
        if(strcmp(filaUber->passageiros[x].nome, nomeBusca) == 0){
            return x;
        }

    return -1;
}

// CALCULA A DISTÂNCIA ENTRE DOIS PONTOS. "TAMANHO DA VIAGEM FEITA PELO MOTORISTA".
// |Xorigem - Xdestino| + |Yorigem - Ydestino|.
double distanciaPontos(double aX, double bX, double aY, double bY){
    return fabs(aX - bX) + fabs(aY - bY);
}

// REMOVE UM PASSAGEIRO DA FILA - SUA CORRIDA IRÁ SER REALIZADA.
// RETORNA O PASSAGEIRO REMOVIDO.
Passageiro removePassageiro(p_uber filaUber){
    Passageiro passageiro = filaUber->passageiros[0];
    
    trocaValores(&filaUber->passageiros[0], &filaUber->passageiros[filaUber->quatidadePassageiros - 1]);
    filaUber->quatidadePassageiros--;

    desceNaFila(filaUber, 0);
       
    return passageiro;
}

// REALIZA EFETIVAMENTE A CORRIDA DO PASSAGEIRO.
// CALCULA E CONTABILIZA AS ESTATÍSTICAS PARA O MOTORISTA.
void realizaCorrida(p_motorista motorista, Passageiro passageiroCorrida){
    // DISTÂNCIA DA POSIÇÃO ATUAL ATÉ O PASSAGEIRO.
    motorista->distanciaRodada += distanciaPontos(motorista->x, passageiroCorrida.xOrigem, 
                                  motorista->y, passageiroCorrida.yOrigem);
                                
    // DISTÂNCIA DO PASSAGEIRO ATÉ O DESTINO.
    motorista->distanciaRodada += distanciaPontos(passageiroCorrida.xOrigem, passageiroCorrida.xDestino, 
                                  passageiroCorrida.yOrigem, passageiroCorrida.yDestino);

    // DISTÂNCIA REAL = GANHOS. APENAS A DISTÂNCIA DO PASSAGEIRO ATÉ O SEU DESTINO.
    // DISTÂNCIA ATÉ A POSIÇÃO DO PASSAGEIRO NÃO CONTABILIZA LUCRO!
    motorista->distanciaReal += distanciaPontos(passageiroCorrida.xOrigem, passageiroCorrida.xDestino, 
                                passageiroCorrida.yOrigem, passageiroCorrida.yDestino);

    // AO FINAL, A POSIÇÃO DO MOTORISTA É A DO DESTINO DO CLIENTE.
    motorista->x = passageiroCorrida.xDestino; motorista->y = passageiroCorrida.yDestino;
}

// O PASSAGEIRO PODE OPTAR POR CANCELAR A CORRIDA, NESSE CASO ELE É REMOVIDO DA LISTA.
void cancelaCorrida(p_motorista motorisa, char *nome){
    int posicao = posicaoPassageiro(motorisa->filaUber, nome);

    motorisa->filaUber->passageiros[posicao].avaliacao = 11; // MUDA SUA PRIORIDADE PRA FÁCIL REMOÇÃO.
    motorisa->ganhoCancelamento += 7; // O MOTORISTA GANHA UMA TAXA POR CANCELAMENTO.

    subirNaFila(motorisa->filaUber, posicao);
    Passageiro removido = removePassageiro(motorisa->filaUber);

    free(removido.nome);
}

// CRIA UM NOVO PASSAGEIRO - AGRUPA AS INFORMAÇÕES FORNCEIDAS A RESPEITO DO NOVO PASSAGEIRO.
p_passageiro criaPassageiro(char *nome, double avaliacao, double xO, double yO, double xD, double yD){
    // xO e yO - ORIGEM | xD e yD - DESTINO.
    
    p_passageiro passageiro = malloc(sizeof(Passageiro));

    if(passageiro == NULL)
        exit(1);

    passageiro->nome = malloc(MAX_NAME * sizeof(char));

    if(passageiro->nome == NULL)
        exit(1);

    passageiro->nome = strcpy(passageiro->nome, nome);
    passageiro->avaliacao = avaliacao;
    passageiro->xOrigem = xO; passageiro->xDestino = xD;
    passageiro->yOrigem = yO; passageiro->yDestino = yD;

    return passageiro;
}

// ALOCA TODA A FILA DO UBER.
p_uber criaFilaUber(){
    p_uber uber = malloc(sizeof(Uber));

    if(uber == NULL)
        exit(1);

    uber->passageiros = malloc(MAX_PASSAGEIROS * sizeof(Passageiro)); // LISTA DE PASSAGEIROS.
    
    if(uber->passageiros == NULL)
        exit(1);

    uber->quatidadePassageiros = 0;
    uber->tamanhoFila = MAX_PASSAGEIROS;

    return uber;
}

// INICIALIZA AS INFORMAÇÕES E ESTATISTICAS DO MOTORISTA!
p_motorista criaMotorista(){
    p_motorista novoMotorista = malloc(sizeof(Motorista));

    if(novoMotorista == NULL)
        exit(1);
        
    novoMotorista->x = novoMotorista->y = 0; 
    novoMotorista->emCorrida = novoMotorista->ganhoCancelamento = novoMotorista->distanciaRodada = 0; 
    novoMotorista->distanciaReal = 0;
    novoMotorista->filaUber = criaFilaUber();

    return novoMotorista;
}