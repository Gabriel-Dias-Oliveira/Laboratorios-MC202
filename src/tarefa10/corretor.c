 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB10: DICIONÁRIO PARA CORRREÇÃO DE PALAVRAS.

#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

// INSERE AS 'N' PALAVRAS INICIAIS QUE VÃO COMPOR O DICIONÁRIO.
void inserePalavrasIniciais(p_hash hashTable, int qtdPalavrasDicionario){
    char *palavra = malloc(MAX_CARACTERES * sizeof(1));
    
    if(palavra == NULL) exit(1);

    for(int x = 0; x < qtdPalavrasDicionario; x++){
        scanf("%s", palavra);

        inserirHash(hashTable, palavra);
    }

    free(palavra);
}

// CHECA O STATUS DA PALAVRA:
// VERDE - A PALAVRA ESTÁ CORRETA.
// AMARELA - A PALAVRA POSSUI 1 ERRO DE DIGITAÇÃO.
// VERMELHO - A PALAVRA POSSUI 2 OU MAIS ERROS DE DIGITAÇÃO.
void verificaStatusPalavra(p_hash hashTable){
    char *palavra = malloc(MAX_CARACTERES * sizeof(1));

    if(palavra == NULL) exit(1);

    scanf("%s", palavra);

    if(buscarPalavra(hashTable, palavra)) // PALAVRA ENCONTRADA DIRETAMENTE NA TABELA DE HASH.
        printf("verde\n");
    else if(identificaAmarelo(hashTable, palavra)) // PALAVRA COM EXATAMENTE UM ERRO.
        printf("amarelo\n");
    else // 2 OU MAIS ERROS NA PALAVRA.
        printf("vermelho\n");

    free(palavra);
}

int main(){
    int qtdPalavrasDicionario = 0, qtdPalavrasBusca = 0;
    p_hash hashTable = criaHash();

    scanf("%d %d", &qtdPalavrasDicionario, &qtdPalavrasBusca);

    inserePalavrasIniciais(hashTable, qtdPalavrasDicionario);

    for(int x = 0; x < qtdPalavrasBusca; x++){
        verificaStatusPalavra(hashTable);
    }

    destruirHashTable(hashTable);

    return 0;
}