// GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB11: ACHA O CAMINHO NO QUAL O TREINADOR JOGA POR MAIS TEMPO E AINDA CAPTURA UM POKEMOM.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafo.h"
#include "fila.h"

// FUNÇÃO PARA FAZER A TROCA RÁPIDA DE DOIS VALORES - POSIÇÕES NO VETOR.
void trocaValores(p_paradas a, p_paradas b){ 
    Paradas aux = *a;
    *a = *b;
    *b = aux;
}

// CRIANDO O HEAP COM A QUANTIDADE DE PARADAS QUE O GRAFO CONTEM.
p_fila criarFila(int sizeFila){
     p_fila filaParadas = malloc(sizeof(Paradas));

    if(filaParadas == NULL) exit(1);

    filaParadas->paradas = malloc(sizeFila * sizeof(Paradas)); // LISTA DE PARADAS.
    
    if(filaParadas->paradas == NULL) exit(1);

    filaParadas->quatidadeParadas = 0;
    filaParadas->tamanhoFila = sizeFila;

    return filaParadas;
}

// SUBIR NA FILA CASO A PRIORIDADE SE ALTERE, OU SEJA, A DISTÂNCIA DIMINUA. 
void subirNaFila(p_fila filaParadas, int posicaoAtual){
    // SE EXISTE UM ELEMNETO ACIMA DA POSIÇÃO ATUAL.
    // SE ESSE ELEMENTO FOR MAIOR QUE O VÉRTICE NO QUAL ESTAMPS INTERESSADOS, TROCAMOS OS DOIS DE LUGAR.
    if(posicaoAtual > 0 && 
        filaParadas->paradas[PAI(posicaoAtual)].distancia > filaParadas->paradas[posicaoAtual].distancia){
        
        trocaValores(&filaParadas->paradas[posicaoAtual], &filaParadas->paradas[PAI(posicaoAtual)]);
        
        subirNaFila(filaParadas, PAI(posicaoAtual));
    }
}

// APÓS O VALOR MÍNIMO SER REMOVIDO DEVEMOS 'DESCER' O VALOR QUE ASSUME A POSIÇÃO.
void desceNaFila(p_fila filaParadas, int posAtual){
    int menorValor;
    
    if(FILHO_ESQUERDO(posAtual) < filaParadas->quatidadeParadas){
        // SE TIVER FILHO ESQUERDO, ASSUMIMOS ELE COMO O MÍNIMO.
        menorValor = FILHO_ESQUERDO(posAtual);
        
        if(FILHO_DIREITO(posAtual) < filaParadas->quatidadeParadas && 
            filaParadas->paradas[FILHO_ESQUERDO(posAtual)].distancia > 
            filaParadas->paradas[FILHO_DIREITO(posAtual)].distancia)
            // SE O VALOR DO FILHO DIREITO FOR MENOR QUE O DO ESQUERDO, ENTÃO ELE É O MÍNIMO.
            
            menorValor = FILHO_DIREITO(posAtual);
            
        // SE O VALOR DA POSIÇÃO ATUAL FOR MAIOR QUE O MÍNIMO, ENTÃO TROCAMOS OS DOIS VALORES.
        if(filaParadas->paradas[posAtual].distancia > filaParadas->paradas[menorValor].distancia){
            trocaValores(&filaParadas->paradas[posAtual], &filaParadas->paradas[menorValor]);
            desceNaFila(filaParadas, menorValor);
        }
    }
}

// ALTERA A PRIORIDADE DE UM VALOR DENTRO DA FILA.
void mudaPrioridade(p_fila filaParadas, int k, double valor){
    int chave = -1;
    
    // ENCONTRAMOS EM QUAL POSIÇÃO O ID DESEJADO ESTÁ.
    for(int x = 0; x < filaParadas->quatidadeParadas; x++)
        if(filaParadas->paradas[x].idParada == k){ 
            chave = x; 
            break;
        }

    if(chave == -1) return;

    // MUDAMOS Ã PRIORIDADE DESTA POSIÇÃO.
    // DEPENDENDO DA MUDANÇA DEVEMOS SUBIR OU DESCER NO HEAP.
    if(filaParadas->paradas[chave].distancia > valor){
        filaParadas->paradas[chave].distancia = valor;
        subirNaFila(filaParadas, chave);
    } 
    else{
        filaParadas->paradas[chave].distancia = valor;
        desceNaFila(filaParadas, chave);
    }
}

// ALOCANDO UMA NOVA PARADA NA FILA (DEFININDO SEUS ATRIBUTOS).
void insereParadaFila(p_fila filaParadas, int idParada, double distancia, char tipoPosicao){
    filaParadas->paradas[filaParadas->quatidadeParadas].idParada = idParada;
    filaParadas->paradas[filaParadas->quatidadeParadas].distancia = distancia;
    filaParadas->paradas[filaParadas->quatidadeParadas].tipoPosicao = tipoPosicao;
    filaParadas->paradas[filaParadas->quatidadeParadas].prox = NULL;

    filaParadas->quatidadeParadas++;

    subirNaFila(filaParadas, filaParadas->quatidadeParadas - 1);
}

// REMOVE O ELEMENTO COM "MENOR PRIORIDADE" (MENOR DISTÂNCIA).
Paradas removeParada(p_fila filaParadas){
    Paradas parada = filaParadas->paradas[0];
    
    // TROCAMOS ELE COM O ULTIMO ELEMENTO (REMOÇÃO FACILITADA)
    trocaValores(&filaParadas->paradas[0], &filaParadas->paradas[filaParadas->quatidadeParadas - 1]);
    filaParadas->quatidadeParadas--;

    // RE-ALOCAMOS O ELEMENTO Q ASSUME A POSIÇÃO 0 DA FILA.
    desceNaFila(filaParadas, 0);
       
    return parada;
}

// DESTROI O ELEMENTO 'FILA'.
void destruirFila(p_fila fila){
    free(fila->paradas);
    free(fila);
}

// VERIFICA SE A FILA POSSUI 0 ELEMENTOS (ESTÁ VAZIA).
int filaVazia(p_fila filaParada){
    return filaParada->quatidadeParadas == 0;
}