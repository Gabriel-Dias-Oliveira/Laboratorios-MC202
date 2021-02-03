 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB08: CRIAR E MANTER LISTAS LEGAIS!.

#include <stdio.h>
#include <stdlib.h>
#include "arvore_rubro_negra.h"

// ADICIONA OS 'N' ELEMENTOS INICIAIS NA LISTA LEGAL.
void adicionaElementosIniciais(p_numeros *listaLegal, int quantidadeInicial){
    long int numeroLegal = 0;

    for(int i = 0; i < quantidadeInicial; i++){
        scanf("%ld", &numeroLegal);
        *listaLegal = adicionaNovoNumero(*listaLegal, numeroLegal);
    }
}

// DEFINE QUEM É O MÁXIMO E O MÍNIMO DA LISTA (ÁRVORE).
void achaMaxMin(p_numeros *maximo, p_numeros *minimo, p_numeros listaLegal){
    *maximo = achaMaximo(listaLegal);
    *minimo = achaMinimo(listaLegal);
}

// PREPARA A LISTA PARA RECEBER UM NOVO VALOR E O INSERE.
void insereNovoValor(p_numeros *listaLegal){
    long int numeroLegal = 0;

    scanf("%ld", &numeroLegal);
            
    *listaLegal = adicionaNovoNumero(*listaLegal, numeroLegal);
}

// FAZ A BUSCA POR UM VALOR PARA DEFINIR QUANTAS VEZES ELE APARECE NA LISTA.
void quantidadeAparicoes(p_numeros listaLegal, p_numeros maximo, p_numeros minimo, long int *aparicoes){
    long int numeroLegal = 0;
    p_numeros listaBusca = criarArvore();

    scanf("%ld", &numeroLegal); 
    
    // EVITA BUSCAS DESNECESSÁRIAS E CUSTOSAS.
    // SE O VALOR É MAIOR QUE O MÁXIMO OU MENOR QUE O MÍNIMO, ELE NÃO ESTÁ NA LISTA!
    if(maximo != NULL && minimo != NULL && 
        numeroLegal >= minimo->numeroLegal && numeroLegal <= maximo->numeroLegal){
                
        listaBusca = buscaValor(listaLegal, numeroLegal);

        if(listaBusca != NULL) // SE O VALOR ESTÁ NA LISTA PEGAMOS QUANTAS VEZES ELE APARECE.
            *aparicoes = listaBusca->qtdVezes;
    }
}

int main(){
    int quantidadeInicial = 0, quantidadeAcoes = 0, acao = 0;
    long int aparicoes = 0, soma = 0;
    p_numeros listaLegal, listaBusca, maximo, minimo;

    listaLegal = listaBusca = maximo = minimo = criarArvore();

    scanf("%d %d", &quantidadeInicial, &quantidadeAcoes);

    adicionaElementosIniciais(&listaLegal, quantidadeInicial);

    achaMaxMin(&maximo, &minimo, listaLegal);

    for(int i = 0; i < quantidadeAcoes; i++){
            scanf("%d", &acao);

        if(acao == 1){
            // OPÇÃO PARA INSERIR UM NOVO VALOR. 
            insereNovoValor(&listaLegal);

            achaMaxMin(&maximo, &minimo, listaLegal);
        }
        else if(acao == 2){
            // OPÇÃO PARA BUSCAR UM VALOR.
            quantidadeAparicoes(listaLegal, maximo, minimo, &aparicoes);
           
            printf("%ld\n", aparicoes);
            
            aparicoes = 0;
        }
        else{
            // VALIDA SE A LISTA É LEGAL OU NÃO!
            validarListaLegal(listaLegal, &soma);

            printf("%ld\n", soma);
            
            soma = 0;
        }
    }

    apagaArvore(listaLegal); // ENCERRA O CÓDIGO LIBERANDO A MEMÓRIA.

    return 0;
}