// GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB11: ACHA O CAMINHO NO QUAL O TREINADOR JOGA POR MAIS TEMPO E AINDA CAPTURA UM POKEMOM.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafo.h"
#include "fila.h"

// ADICIONA UMA POSIÇÃO A LISTA DE POSIÇÕES.
p_posicoes adicionarPosicoes(p_posicoes lista, int idPosicao, double x, double y, char tipoPosicao){
    p_posicoes novaPosicao;

    novaPosicao = malloc(sizeof(Posicoes));

    if(novaPosicao == NULL) exit(1);

    novaPosicao->idPosicao = idPosicao;
    novaPosicao->x = x;
    novaPosicao->y = y;
    novaPosicao->tipoPosicao = tipoPosicao;
    novaPosicao->prox = lista;

    return novaPosicao;
}

// CALCULO DA DISTÂNCIA EUCLIDIANA ENTRE DOIS PONTOS.
// OBS: Distancia = sqrt((x1 - x2)² + (y1 - y2)²).
double distanciaPontos(double aX, double bX, double aY, double bY){
    return sqrt(pow((aX - bX), 2) + pow((aY -   bY), 2));
}

// CRIA UMA "PARADA", OU SEJA, ALOCANDO AS ARESTAS QUE UNEM DOIS VÉRTICES (POSIÇÕES) NO GRAFO!
p_paradas adicionarParada(p_paradas lista, int idParada, double xO, double yO, 
                            double xD, double yD, char tipoPosicao){
    p_paradas novaParada;

    novaParada = malloc(sizeof(Posicoes));

    if(novaParada == NULL) exit(1);

    novaParada->idParada = idParada;
    novaParada->distancia = distanciaPontos(xO, xD, yO, yD);
    novaParada->tipoPosicao = tipoPosicao;
    novaParada->prox = lista;

    return novaParada;
}

// TEMOS QUE O NOSSO GRAFO É COMPLETO. DESSE MODO, TODOS OS VÉRTICES POSSUEM CONEXÃO.
// PORTANTO TEMOS QUE PERCORRER O VETOR DE POSIÇÕES PARA CADA NÓ E CRIAR A ARESTA COM TODOS OS DEMAIS.
void inserindoCaminho(p_grafo grafo, p_posicoes listaParadas){
    for(p_posicoes u = listaParadas; u != NULL; u = u->prox){
        for(p_posicoes v = u->prox; v != NULL; v = v->prox){
            grafo->adjacencia[v->idPosicao] = adicionarParada(grafo->adjacencia[v->idPosicao], 
                u->idPosicao, u->x, u->y, v->x, v->y, u->tipoPosicao);
            grafo->adjacencia[u->idPosicao] = adicionarParada(grafo->adjacencia[u->idPosicao], 
                v->idPosicao, v->x, v->y, u->x, u->y, v->tipoPosicao);
        }
    }
}

// INICIALIZA O GRAFO, ASSIM COMO OS CAMINHOS/ARESTAS E DEMAIS LISTAS.
p_grafo iniciarGrafo(p_posicoes listaParadas, int qtdParadas, int qtdLugias, int *indexLugias){
    p_grafo grafo = malloc(sizeof(Grafo));
    
    grafo->qtdParadas = qtdParadas;
    grafo->qtdLugias = qtdLugias;
    grafo->adjacencia = malloc(qtdParadas * sizeof(p_paradas));
    grafo->indexLugias = indexLugias;

    for(int i = 0; i < qtdParadas; i++)
        grafo->adjacencia[i] = NULL;

    inserindoCaminho(grafo, listaParadas);

    return grafo;
}

// ENCONTRA O "PAI" DE CADA VÉRTICE.
// AO ANDAR SOMENTE PELOS PAIS TEREMOS O MENOR CAMINHO.
// PELO GRAFO SER COMPLETO, SABEMOS QUE É POSSÍVEL CHEGAR EM QUALQUER NÓ A PARTIR DE OUTRO.
// DESSE MODO, NÃO HAVENDO CICLOS É GARANTIDO QUE EXISTE UM CAMINHO ATÉ AS LUGIAS.
Paradas * buscaCaminho(p_grafo grafo, char *tipPosicoes){
    Paradas origem, treinador; 
    Paradas *pai = malloc(grafo->qtdParadas * sizeof(Paradas)); // LISTAS DE PAIS.
    int *visitado = malloc(grafo->qtdParadas * sizeof(int)); // EVITAR REPETIÇÕES.
    // LISTA PARA CONTROLAR QUAL É O MENOR CAMINHO ATÉ UMA ARESTA "X".
    double *pesosArestas = malloc(grafo->qtdParadas * sizeof(double));  
    p_fila fila = criarFila(grafo->qtdParadas); // MIN-HEAP - EXTRAÇÃO DAS MENORES ARESTAS EM O(1).
    int count = 0;

    if(pai == NULL || visitado == NULL || pesosArestas == NULL) exit(1);

    for(int i = grafo->qtdParadas - 1; i >= 0; i--){
        // COMO AS PARAS ESTÃO EM UMA LISTA LIGADA, O TREINADOR É O ID 0, PORÉM ESTÁ NA ULTIMA POSIÇÃO.
        // COUNT TEM A FUNÇÃO DE "AJUSTAR" ISSO.
        // A PRINCIPIO NINGUEM ESTÁ VISITADO E TODAS AS DISTÂNCIAS SÃO MÁXIMAS.
        visitado[count] = 0;
        pesosArestas[count] = __INT_MAX__;
        insereParadaFila(fila, count, __INT_MAX__, tipPosicoes[i]);
        count++;
    }

    treinador.idParada = treinador.distancia = 0; 
    treinador.tipoPosicao = 'T'; 
    treinador.prox = NULL;

    // INSERINDO A 1º POSIÇÃO - EQUIVALENTE AO TREINADOR.
    pai[treinador.idParada] = treinador;
    pesosArestas[0] = 0;
    mudaPrioridade(fila, treinador.idParada, 0);

    while(!filaVazia(fila)) {
        origem = removeParada(fila);

        visitado[origem.idParada] = 1;

        // PARA CADA VIZINO DO VERTICE EXTRAIDO:
        for(p_paradas vizinho = grafo->adjacencia[origem.idParada]; vizinho != NULL; vizinho = vizinho->prox){
            if(!visitado[vizinho->idParada] && vizinho->distancia < pesosArestas[vizinho->idParada]){
                // SE O VIZINHO AINDA NÃO FOI EXTRAÍDO E O CAMINHO ATUAL É MENOR DO QUE O VALOR ANTERIOR.
                // MUDAREMOS ESTE VALOR TANTO NA LISTA DE PESOS QUANTO NO HEAP.
                
                mudaPrioridade(fila, vizinho->idParada, vizinho->distancia);

                pai[vizinho->idParada] = origem;
                pai[vizinho->idParada].distancia = vizinho->distancia; // FACILITANDO NA HORA DE ACHAR A LUGIA.
                pesosArestas[vizinho->idParada] = vizinho->distancia;
            }
        }
    }

    destruirFila(fila); 
    free(visitado);
    free(pesosArestas);

    return pai;
}

// ACHA A MAIOR ARESTA EM UM CAMINHO.
// A FUNÇÃO PARTI DO INDEX DE UMA LUGIA ("PAI DA LUGIA") ATÉ VOLTAR AO VÉRTICE 0.
// PAI DO VÉRTICE 0 = VERTICE 0. 
void achaMaiorAresta(double *maiorAresta, int lugiaAtual, Paradas *pai){    
    if(pai[lugiaAtual].idParada != lugiaAtual)
        achaMaiorAresta(maiorAresta, pai[lugiaAtual].idParada, pai);

    // SIMPLES CHECAGEM DE QUAL É A MAIOR ARESTA.
    if(pai[lugiaAtual].distancia > *maiorAresta)
        *maiorAresta = pai[lugiaAtual].distancia;
}

double achaMenorMaiorAresta(p_grafo grafo, Paradas *pai){
    double maiorArestaCaminho = 0, maiorArestaTotal = INFINITY;

    // PARA CADA LUGIA:
    for(int x = 0; x < grafo->qtdLugias; x++){
        achaMaiorAresta(&maiorArestaCaminho, grafo->indexLugias[x], pai);

        // ACHANDO O CAMINHO COM A "MENOR MAIOR" ARESTA.
        if(maiorArestaCaminho < maiorArestaTotal)
            maiorArestaTotal = maiorArestaCaminho;

        maiorArestaCaminho = 0;
    }

    return ceil(maiorArestaTotal);
}

// DESTRUINDO E LIBERANDO A MEMÓRIA DA LISTA DE POSIÇÕES.
void destruirListasPosicoes(p_posicoes lista){
    if (lista != NULL) {
        destruirListasPosicoes(lista->prox);
        free(lista);
    }
}

// DESTRUINDO E LIBERANDO A MEMÓRIA DA LISTA DE PARADAS.
void destruirListasParadas(p_paradas lista){
    if (lista != NULL) {
        destruirListasParadas(lista->prox);
        free(lista);
    }
}

// DESTRUINDO E LIBERANDO A MEMÓRIA DO GRAFO.
void destruirGrafo(p_grafo grafo){
    // DESTRUINDO CADA LISTA DE ADJACÊNCIA.
    for(int x = 0; x < grafo->qtdParadas; x++)
        destruirListasParadas(grafo->adjacencia[x]);

    free(grafo->adjacencia);
    free(grafo->indexLugias);
    free(grafo);
}