// GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB11: ACHA O CAMINHO NO QUAL O TREINADOR JOGA POR MAIS TEMPO E AINDA CAPTURA UM POKEMOM.

#ifndef FILA_H
#define FILA_H

// DEFINES DO HEAP:
#define FILHO_ESQUERDO(i) (2 * i + 1)
#define FILHO_DIREITO(i) (2 * i + 2)
#define PAI(i) ((i - 1) / 2)
#include "grafo.h"

// CRIANDO UM MIN-HEAP DE PARADAS.
typedef struct FilaParadas{
    Paradas *paradas;    
    int quatidadeParadas, tamanhoFila;
} FilaParadas;

typedef FilaParadas * p_fila;

// CRIANDO O HEAP COM A QUANTIDADE DE PARADAS QUE O GRAFO CONTEM.
p_fila criarFila(int sizeFila);

// REMOVE O VÉRTICE COM MENOR PRIORIDADE ("MENOR DISTÂNCIA").
Paradas removeParada(p_fila filaParadas);

// VERIFICA SE AINDA EXISTE ALGUM ELEMENTO NA FILA PARA SER REMOVIDO.
int filaVazia(p_fila filaParada);

// MUDA A PRIORIDADE DE UM VÉRTICE NA FILA - ATUALIZA O SEU VALOR.
void mudaPrioridade(p_fila filaParadas, int k, double valor);

// DEVOLVE A MEMÓRIA ALOCADA PELA FILA.
void destruirFila(p_fila fila);

// INSERE UM NOVO ELEMENTO NA FILA.
void insereParadaFila(p_fila filaParadas, int idParada, double distancia, char tipoPosicao);

#endif