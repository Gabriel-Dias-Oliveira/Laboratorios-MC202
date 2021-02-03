 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB10: DICIONÁRIO PARA CORRREÇÃO DE PALAVRAS.

#ifndef TABELA_HASH_H
#define TABELA_HASH_H

// DEFINIÇÃO DAS CONFIGURAÇÕES DA TABELA DE HASH E SEU CONTEÚDO.
#define MAX_CARACTERES 27 
#define HASH_TABLE_SIZE 347

// ITENS QUE VÃO COMPOR A TABELA DE HASH ~ PALAVRAS DO DICIONÁRIO.
typedef struct Palavras{
    char *palavra;    
    struct Palavras *prox;
} Palavras;

typedef Palavras * p_palavras;

// DICIONÁRIO -- TABELA DE HASH.
typedef struct HashTable{
    p_palavras *palavrasHash[HASH_TABLE_SIZE];    
} HashTable;

typedef HashTable * p_hash;

// CRIA E INICIA AS LISTAS DA TABLEA DE HASH.
p_hash criaHash();

// INSERE UM NOVO VALOR NO DICIONÁRIO - FAZENDO O HASH DA CHAVE (PALAVRA).
void inserirHash(p_hash hashTable, char *palavra);

// APAGA TODO O CONTEÚDO DAS LISTAS E DA TABELA - LIBERANDO A MEMÓRIA.
void destruirHashTable(p_hash hashTable);

// BUSCA UMA PALAVRA DENTRO DO DICIONÁRIO.
int buscarPalavra(p_hash hashTabel, char *palavraBuscada);

// IDENTIFICA SE A PALAVRA POSSUÍ EXATAMENTE 1 ERRO DE DIGITAÇÃO ~ NÍVEL AMARELO.
int identificaAmarelo(p_hash hashTabel, char *palavraBuscada);

#endif