// GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB11: ACHA O CAMINHO NO QUAL O TREINADOR JOGA POR MAIS TEMPO E AINDA CAPTURA UM POKEMOM.

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

// DESTROI OS COMPONENTES UTILIZADOS PELA 'MAIN'.
void destruirComponentes(Paradas *pai, p_posicoes posicoes, p_grafo grafoParadas, char *tiposParadas, char *tipoParada){
    destruirListasPosicoes(posicoes);
    destruirGrafo(grafoParadas);
    free(tipoParada);
    free(tiposParadas);
    free(pai);
}

// COLETA AS INFORMAÇÕES SOBRE AS POSIÇÕES (TIPOS) E INFORMAÇÕES SOBRE AS LUGIAS (QUANTIDADES E INDEXES).
void coletaPosicoesLugias(p_posicoes posicoes, int *indexLugias, int *qtdLugias, char *tiposParadas){
    int count = 0;

    for(p_posicoes x = posicoes; x != NULL; x = x->prox){
        tiposParadas[count] = x->tipoPosicao;
        count++;    

        if(x->tipoPosicao == 'L'){
            indexLugias[*qtdLugias] = x->idPosicao;
            *qtdLugias = *qtdLugias + 1;
        }
    }
}

int main(){
    p_posicoes posicoes = NULL;
    p_grafo grafoParadas = NULL;
    Paradas *pai;
    int id = 0, qtdLugias = 0;
    int *indexLugias;
    double xP = 0, yP = 0;
    char *tipoParada = malloc(10 * sizeof(char)), *tiposParadas;

    if(tipoParada == NULL) exit(1);

    scanf("%lf %lf", &xP, &yP); // TREINADOR.
    tipoParada[0] = 'T';

    posicoes = adicionarPosicoes(posicoes, id, xP, yP, tipoParada[0]);
    
    while(1){
        // ENQUANTO TIVER NOVAS POSIÇÕES ADICIONAMOS ELAS:  
        id++;

        if(scanf("%lf %lf %s", &xP, &yP, tipoParada) == EOF) break; 

        posicoes = adicionarPosicoes(posicoes, id, xP, yP, tipoParada[0]);
    }

    indexLugias = malloc(id * sizeof(int));
    tiposParadas = malloc(id * sizeof(char));

    if(indexLugias == NULL || tiposParadas == NULL) exit(1);

    coletaPosicoesLugias(posicoes, indexLugias, &qtdLugias, tiposParadas);

    // CRIA E ALOCA AS INFORMAÇÕES (VÉRTICES E ARESTAS) DOS GRAFOS.
    grafoParadas = iniciarGrafo(posicoes, id, qtdLugias, indexLugias);

    // BUSCA O MENOR CAMINHO ATÉ CADA VÉRTICE ("O PAI DE CADA UM").
    pai = buscaCaminho(grafoParadas, tiposParadas);

    // A PARTIR DO PAI PODEMOS BUUSCA A LUGIA QUE TEM A "MENOR MAIOR" ARESTA NO CAMINHO.
    // NOSSA RESPOSTA:
    printf("%.0f\n", achaMenorMaiorAresta(grafoParadas, pai));

    // DEVOLVE A MEMÓRIA ALOCADA.
    destruirComponentes(pai, posicoes, grafoParadas, tiposParadas, tipoParada);

    return 0;
}