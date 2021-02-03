 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB08: CRIAR E MANTER LISTAS LEGAIS!.

#ifndef ARVORE_RUBRO_NEGRA_H
#define ARVORE_RUBRO_NEGRA_H

enum Cor {VERMELHO , PRETO};


// ESTRUTURA DAS LISTAS (ÁRVORE RUBRO-NEGRA ESQUERDISTA).
typedef struct NumerosLegais{
    long int numeroLegal, qtdVezes;
    enum Cor cor;
    struct NumerosLegais *esq, *dir;
} NumerosLegais;

typedef NumerosLegais * p_numeros;

// INICIALIZA UMA NOVA LISTA LEGAL (ÁRVORE).
p_numeros criarArvore();

// INSERE UM NOVO NÚMERO LEGAL A UMA LISTA FORNECIDA.
p_numeros adicionaNovoNumero(p_numeros raiz, long int numeroLegal);

// BUSCA UM VALOR FORNECIDO E VERIFICA SE ELE ESTÁ NA LISTA DESEJADA.
p_numeros buscaValor(p_numeros raiz, long int numeroLegal);

// ACHA O MAIOR VALOR DA LISTA.
p_numeros achaMaximo(p_numeros raiz);

// ACHA O MENOR VALOR DA LISTA.
p_numeros achaMinimo(p_numeros raiz);

// VERIFICA SE UMA LISTA É LEGALE INDICA QUANTOS VALORES DEVEM SER REMOVIDOS PARA QUE ELA SE TORNE UMA. 
void validarListaLegal(p_numeros raiz, long int *soma);

// DESTROI TODOS OS NÓS ALOCADOS PARA A LISTA.
void apagaArvore(p_numeros raiz);

#endif