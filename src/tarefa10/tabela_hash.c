 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB10: DICIONÁRIO PARA CORRREÇÃO DE PALAVRAS.
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

// FUNÇÃO QUE GERA O HASH DE CADA PALAVRA E O RETORNA.
// UTILIZA O MÉTODO DA DIVISÃO!
int funcaoHash(char *chave) {
    int chavePalavra = 0;

    for (int i = 0; i < strlen(chave); i++)
        chavePalavra = (256 * chavePalavra + chave[i]) % HASH_TABLE_SIZE;
    
    return chavePalavra;
}

// CRIA A TABELA DE HASH E INICIALIZA SUAS POSIÇÕES.
// RETORNA A NOVA TABELA CRIADA.
p_hash criaHash(){
    p_hash tabelaHash = malloc(sizeof(HashTable));

    if(tabelaHash == NULL) exit(1);

    for(int x = 0; x < HASH_TABLE_SIZE; x++){
        tabelaHash->palavrasHash[x] = malloc(sizeof(p_palavras));

        if(tabelaHash->palavrasHash[x] == NULL)  exit(1);

        *tabelaHash->palavrasHash[x] = NULL;
    }

    return tabelaHash;
}

// CRIA UM NOVO 'NÓ' (PALAVRA) NA LISTA CORRESPONDENDE.
// RETORNA A NOVA LISTA COM O ELEMENTO ADICIONADO.
p_palavras inserirPalavra(p_palavras *listaPalavras, char *palavra){
    p_palavras novaPalavra = malloc(sizeof(Palavras));

    if(novaPalavra == NULL) exit(1);

    novaPalavra->palavra = malloc(MAX_CARACTERES * sizeof(char));
    
    if(novaPalavra->palavra == NULL) exit(1);

    novaPalavra->palavra = strcpy(novaPalavra->palavra, palavra);
    novaPalavra->prox = *listaPalavras;
    
    return novaPalavra;
}

// BUSCA UMA PALAVRA EM UMA DETERMINADA LISTA.
// RETORNA: 1 - PALAVRA ACHADA OU 0 - PALAVRA NÃO ACHADA.
int buscarLista(p_palavras *listaPalavras, char *palavraBuscada){
    for(p_palavras atual = *listaPalavras; atual != NULL; atual = atual->prox)
        if(strcmp(atual->palavra, palavraBuscada) == 0) 
            // SE A PALAVRA ESTÁ NA LISTA COM A RESÉCTIVA HASH
            return 1;

    return 0;
}

// ENCONTRA O HASH DE UMA PALAVRA PARA FAZER A BUSCA NA LISTA CORRETA!
// RETORNA: 1 - PALAVRA ACHADA OU 0 - PALAVRA NÃO ACHADA.
int buscarPalavra(p_hash hashTabel, char *palavraBuscada){
    int chaveHash = funcaoHash(palavraBuscada);

    return buscarLista(hashTabel->palavrasHash[chaveHash], palavraBuscada);
}

// VALIDA A POSSÍVEL SITUAÇÃO DO USUÁRIO TER DIGITADO UMA LETRA A MAIS.
// RETORNA: 1 - PALAVRA ACHADA OU 0 - PALAVRA NÃO ACHADA.
int removeLetras(p_hash hashTabel, char *palavraBuscada){
    char *copiaPalavra;
    int k = 0;
    copiaPalavra = malloc(MAX_CARACTERES * sizeof(char));
    
    if(copiaPalavra == NULL) exit(1);
    
    copiaPalavra = strcpy(copiaPalavra, palavraBuscada); 

    for(int x = 0; x < strlen(palavraBuscada); x++){
        for(int i = 0; i < strlen(palavraBuscada); i++){
            // COPIA AS 'N-1' LETRADAS DA PALAVRA.
            // NÃO COPIA O INDICE 'X' - OBS: REMOVE UMA LETRA POR VEZ.
            if(i != x){
                copiaPalavra[k] = palavraBuscada[i];
                k++;
            }
        }

        copiaPalavra[k] = '\0';

        if(buscarPalavra(hashTabel, copiaPalavra)){
            // SE A PALAVRA COM A LETRA REMOVIDA ESTÁ NA TABELA.
            free(copiaPalavra);
            return 1;
        }

        k = 0;
        copiaPalavra = strcpy(copiaPalavra, palavraBuscada); 
    }

    free(copiaPalavra);
    return 0;
}

// VALIDA A POSSÍVEL SITUAÇÃO DO USUÁRIO TER TROCADO UMA LETRA.
// RETORNA: 1 - PALAVRA ACHADA OU 0 - PALAVRA NÃO ACHADA.
int letraErrada(p_hash hashTabel, char *palavraBuscada){
    char *copiaPalavra;
    char letra = 'a';

    copiaPalavra = malloc(MAX_CARACTERES * sizeof(char));
    
    if(copiaPalavra == NULL) exit(1);
    
    copiaPalavra = strcpy(copiaPalavra, palavraBuscada); 

    for(int x = 0; x < strlen(palavraBuscada); x++){
        for(int i = 0; i < 26; i++){
            // ALTERA A LETRA DA POSIÇÃO 'X' DA PALAVRA ORIGINAL.
            copiaPalavra[x] = (letra + i);

            if(buscarPalavra(hashTabel, copiaPalavra)){
                // SE A PALAVRA COM A LETRA ALTERADA ESTÁ NA TABELA.
                free(copiaPalavra);
                return 1;
            }            
        }

        copiaPalavra = strcpy(copiaPalavra, palavraBuscada);
    }

    free(copiaPalavra);
    return 0;
}

// VALIDA A POSSÍVEL SITUAÇÃO DO USUÁRIO TER ESQUECIDO DE INSERIR UMA LETRA.
// RETORNA: 1 - PALAVRA ACHADA OU 0 - PALAVRA NÃO ACHADA.
int letraMenos(p_hash hashTabel, char *palavraBuscada){
    char *copiaPalavra;
    char letra = 'a';
    int k = 0;
    
    copiaPalavra = malloc(MAX_CARACTERES * sizeof(char)); 
    
    if(copiaPalavra == NULL) exit(1);

    for(int x = 0; x <= strlen(palavraBuscada); x++){
        
        copiaPalavra = strcpy(copiaPalavra, palavraBuscada); 
        k = 0;

        for(int j = 0; j <= strlen(palavraBuscada); j++){
            // INSERE UMA LETRA A MAIS NA PALAVRA EM UMA POSIÇÃO 'X'. 
            if(x == strlen(palavraBuscada) && j == strlen(palavraBuscada)){
                // CASO A LETRA JÁ TENHA SIDO INSERIDA NAS 'N' POSIÇÕES DA PALAVRA.
                // TESTAMOS O ULTIMO CASO - INSERINDO UMA LETRA EXTRA NO FINAL DA PALAVRA.
                copiaPalavra[j] = letra;
                k++;
                break;
            }
            else if(j == x){
                // INSERINDO A LETRA EXTRA EM UMA POSIÇÃO 'J'.
                copiaPalavra[j] = letra;
                k++;
            }

            // QUANDO INSERIMOS A LETRA EXTRA TEMOS: POSIÇÃO K (J + 1) RECEBE A LETRA DA POSIÇÃO J.
            // QUANDO NÃO INSERIMOS A LETRA EXTRA TEMOS APENAS J = K.
            copiaPalavra[k] = palavraBuscada[j];

            k++;
        }

        copiaPalavra[k] = '\0';

        for(int i = 0; i < 26; i++){
            if(buscarPalavra(hashTabel, copiaPalavra)){
                // SE A PALAVRA COM A LETRA ADICIONADA ESTÁ NA TABELA.
                free(copiaPalavra);
                return 1;            
            }
            copiaPalavra[x] = letra + i;
        }
    }   

    free(copiaPalavra);     
    return 0; 
}

// VERIFICA SE AS FUNÇÕES - QUE VALIDAM EXATAMENTE 1 ERRO POR VEZ - SÃO O SUFICIENTE PARA ACHAR A PALAVRA.
// NESSE CASO, TEMOS APENAS 1 ERRO DE DIGITAÇÃO E A PALAVRA DEVE SER SINALIZADA COMO AMARELA.
int identificaAmarelo(p_hash hashTabel, char *palavraBuscada){
    // SE ALGUM DOS CASOS ACONTECER - LEMBRANDO QUE AS FUNÇÕES VALIDAM EXATAMENTE UM ERRO.
    // TEMOS QUE A PALAVRA É AMARELA.
    return removeLetras(hashTabel, palavraBuscada) || letraErrada(hashTabel, palavraBuscada) || 
            letraMenos(hashTabel, palavraBuscada);        

}

// INSERINDO UM NOVO VALOR NA TABELA DE HASH.
void inserirHash(p_hash hashTable, char *palavra){
    int chaveHash = funcaoHash(palavra);

    *hashTable->palavrasHash[chaveHash] = inserirPalavra(hashTable->palavrasHash[chaveHash], palavra);
}

// DESTROI E LIBERA TODA A MEMÓRIA ALOCADA PELAS LISTAS E SEUS ITENS.
void destruirListas(p_palavras listaPalavras){
    if(listaPalavras != NULL) {
        destruirListas(listaPalavras->prox);
        free(listaPalavras->palavra);
        free(listaPalavras);
    }
}

// DESTROI E LIBERA TODA A MEMÓRIA ALOCADA PELAS LISTAS E PELO DICIONÁRIO.
void destruirHashTable(p_hash hashTable){
    for(int x = 0; x < HASH_TABLE_SIZE; x++){ 
        p_palavras aux = *hashTable->palavrasHash[x];
        destruirListas(aux);
        free(hashTable->palavrasHash[x]);
    }

    free(hashTable);
}