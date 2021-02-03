// GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB11: ACHA O CAMINHO NO QUAL O TREINADOR JOGA POR MAIS TEMPO E AINDA CAPTURA UM POKEMOM.

#ifndef GRAFO_H
#define GRAFO_H

// SALVA UMA POSIÇÃO INSERIDA PELO TREINADOR.
typedef struct Posicoes{
    int idPosicao;
    double x, y;
    char tipoPosicao;
    struct Posicoes *prox;
} Posicoes;

typedef Posicoes * p_posicoes;

// SIMBOLIZA UM ELEMENTO DO GRAFO - 
// DIFERENTEMENTE DA POSIÇÃO AQUI TEMOS O 'PESO' DA ARESTA (DISTÂNCIA ENTRE SEUS VIZINHOS).
typedef struct Paradas{
    int idParada;
    double distancia; // "PESO"
    char tipoPosicao;
    struct Paradas *prox;
} Paradas;

typedef Paradas * p_paradas;

// GRAFO COM OS VERTICES E SUAS LISTAS DE AJACÊNCIAS.
typedef struct Grafo{
    p_paradas *adjacencia;
    int qtdParadas, qtdLugias; // NÚMERO DE LUGIAS.
    int *indexLugias; // INDEX DESTAS LUGIAS - A SER USADO PARA RÁPIDA IDENTIFICAÇÃO NO CÓDIGO.
} Grafo;

typedef Grafo * p_grafo;

// ADICIONA UMA POSIÇÃO A LISTA DE POSIÇÕES.
p_posicoes adicionarPosicoes(p_posicoes lista, int idPosicao, double x, double y, char tipoPosicao);

// INICIA O GRAFO E TODOS OS SEUS ATRIBUTOS - INCLUSIVE AS LISTAS DE ADJACÊNCIAS.
p_grafo iniciarGrafo(p_posicoes listaParadas, int qtdParadas, int qtdLugias, int *indexLugias);

// FUNÇÃO QUE ACHA O MELHOR CAMINHO ("PAI") DE CADA VERTICE.
Paradas * buscaCaminho(p_grafo grafo, char *tipPosicoes);

// ACHA A LUGIA QUE CONTEM A "MENOR MAIOR" ARESTA - POIS ASSIM, ELE JOGARÁ POR MAIS TEMPO.
double achaMenorMaiorAresta(p_grafo grafo, Paradas *pai);

// DEVOLVE A MEMÓRIA UTILIZADA PELAS LISTAS DE POSIÇÕES.
void destruirListasPosicoes(p_posicoes lista);

// DEVOLVE A MEMÓRIA UTILIZADA PELO GRAFO (E PELO SEUS ATRIBUTOS).
void destruirGrafo(p_grafo grafo);

#endif