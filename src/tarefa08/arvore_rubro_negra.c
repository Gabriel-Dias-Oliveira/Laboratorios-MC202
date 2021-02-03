 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB08: CRIAR E MANTER LISTAS LEGAIS!.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arvore_rubro_negra.h"

// SOBE A COR VERMELHA PARA QUE AS RESTRIÇÕES DA ÁRVORE RUBRO-NEGRA ESQUEDISTA SEJA ATENDIDA.
void sobeVermelho(p_numeros raiz){
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

// VERIFICA SE UM NÓ É VERMELHO. 
// RETORNA 'TRUE (1) OU FALSE (0)' SE O NÓ FOR (OU NÃO) VERMELHO.
int verificaVermelho(p_numeros raiz){
    if(raiz  == NULL)
        return 0;

    return raiz->cor == VERMELHO;
}

// VERIFICA SE UM NÓ É PRETO. 
// RETORNA 'TRUE (1) OU FALSE (0)' SE O NÓ FOR (OU NÃO) PRETO.
int verificaPreto(p_numeros raiz){
    if(raiz == NULL)
        return 1;

    return raiz->cor == PRETO;
}

// VERIFICA SE UMA LISTA É LEGAL OU NÃO.
// EDITA A VARIÁVEL 'SOMA' PARA SABER QUANTOS VALORES DEVEM SER REMOVIDOS - PARA SE TORNAR UMA LISTA LEGAL.
void validarListaLegal(p_numeros raiz, long int *soma){
    if(raiz == NULL)
        return;
    
    // TEMOS QUE VER TODOS OS VALORES QUE ESTÃO NA LISTA.
    validarListaLegal(raiz->dir, soma);
    validarListaLegal(raiz->esq, soma);
    
    // SE O NUMERO DE APARIÇÕES DO VALOR É DIFERENTE DESSE MESMO VALOR, ENTÃO É INDICADA SUA REMOÇÃO.
    if(raiz->numeroLegal != raiz->qtdVezes && raiz->qtdVezes < raiz->numeroLegal){
        // SE O NÚMERO DE APARIÇÕES É MENOR QUE O PRÓPRIO VALOR, É IDEAL REMOVER TODAS AS APARIÇÕES DESSE VALOR.
        *soma += raiz->qtdVezes;
    }    
    else if(raiz->numeroLegal != raiz->qtdVezes){
        // CASO AS APARIÇÕES SEJAM MAIORES QUE OS VALORES, DEVEMOS REMOVER O EXCESSO DE APARIÇÕES.  
        *soma += raiz->qtdVezes - raiz->numeroLegal;
    }
}

// DESTROI TODOS OS NÓS ALOCADOS PARA A ÁRVORE.
void apagaArvore(p_numeros raiz){
    if(raiz == NULL)
        return;

    apagaArvore(raiz->esq);
    apagaArvore(raiz->dir);

    free(raiz);
}

// INICIA UMA NOVA LISTA (ÁRVORE).
p_numeros criarArvore(){
    return NULL;
}

// ROTACIONA UM CONJUNTO DE NÓS DA ÁRVORE PARA A ESQUERDA.
// FUNDAMENTAL PARA GARANTIR AS PROPRIEDADES DA ÁRVORE EM QUESTÃO.
// RETORNA O NÓ (RAÍZ) ROTACIONADO. 
p_numeros rotacionaEsquerda(p_numeros raiz){
    p_numeros x = raiz->dir;

    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return x;
}

// ROTACIONA UM CONJUNTO DE NÓS DA ÁRVORE PARA A DIREITA.
// FUNDAMENTAL PARA GARANTIR AS PROPRIEDADES DA ÁRVORE EM QUESTÃO.
// RETORNA O NÓ (RAÍZ) ROTACIONADO. 
p_numeros rotacionaDireita(p_numeros raiz){
    p_numeros x = raiz->esq;

    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return x;
}

// ACHA O MENOR VALOR DA ÁRVORE.
// RETORNA ESSE NÓ (VALOR) OU NULL CASO NÃO EXISTA NENHUM ELEMENTO.
p_numeros achaMinimo(p_numeros raiz){
    // O MENOR VALOR SE ENCOTRA SEMPRE MAIS A ESQUERDA DA ÁRVORE! 
    if (raiz == NULL || raiz->esq == NULL)
        return raiz;
    
    return achaMinimo(raiz->esq);
}

// ACHA O MAIOR VALOR DA ÁRVORE.
// RETORNA ESSE NÓ (VALOR) OU NULL CASO NÃO EXISTA NENHUM ELEMENTO.
p_numeros achaMaximo(p_numeros raiz){
    // O MENOR VALOR SE ENCOTRA SEMPRE MAIS A DIREITA DA ÁRVORE!
    if (raiz == NULL || raiz->dir == NULL)
        return raiz;
    
    return achaMaximo(raiz->dir);
}

// BUSCA POR UM VALOR ESPECIFICO QUE FOI FORNECIDO.
// RETORNA ESSE VALOR, CASO ELE ESTEJA NA ÁRVORE, OU NULL, CASO ELE NÃO ESTEJA.
p_numeros buscaValor(p_numeros raiz, long int numeroLegal){
    if (raiz == NULL || numeroLegal == raiz->numeroLegal)
        // O VALOR FOI ACHADO OU A BUSCA ACHOU UM 'NULL' (O VALOR NÃO PODE ESTAR NA ÁRVORE).
        return raiz;
    if (numeroLegal < raiz->numeroLegal) 
        // SE O VALOR ATUAL É MAIOR DO QUE O BUSCADO DEVEMOS IR PARA A ESQUERDA - VALORES MENORES.
        return buscaValor(raiz->esq, numeroLegal);
    else
        // SE O VALOR ATUAL É MENOR DO QUE O BUSCADO DEVEMOS IR PARA A DIREITA - VALORES MAIORES.
        return buscaValor(raiz->dir, numeroLegal);
}

// CRIA, EFETIVAMENTE, UM NOVO NÓ PARA A ÁRVORE.
// RETORNA A NOVA ÁRVORE COM O VALOR ALOCADO.
p_numeros adicionaArvore(p_numeros raiz, long int numeroLegal){
    p_numeros novo;
    
    // ALOCANDO O NÓ.
    if(raiz == NULL){
        novo = malloc(sizeof(NumerosLegais));

        if(novo == NULL)
            exit(1);

        novo->esq = novo->dir = NULL;
        novo->numeroLegal = numeroLegal;
        novo->qtdVezes = 1; // TODO VALOR INSERIDO INICIA COM 1 APARIÇÃO.
        novo->cor = VERMELHO;
        return novo;
    }
    
    // POSICIONAMENTO DO NÓ.
    if(numeroLegal < raiz->numeroLegal)
        raiz->esq = adicionaArvore(raiz->esq, numeroLegal);
    else
        raiz->dir = adicionaArvore(raiz->dir, numeroLegal);

    // VALIDAÇÃO DAS PROPRIEDADES DA ÁRVORE RUBRO-NEGRA ESQUERDISTA.
    if(verificaVermelho(raiz->dir) && verificaPreto(raiz->esq))
        raiz = rotacionaEsquerda(raiz);
    
    if(verificaVermelho(raiz->esq) && verificaVermelho(raiz->esq->esq))
        raiz = rotacionaDireita(raiz);
    
    if(verificaVermelho(raiz->esq) && verificaVermelho(raiz->dir))
        sobeVermelho(raiz);
    
    return raiz;
}

// VERIFICA SE O VALOR DEVE SER ALOCADO OU SE ELE JÁ EXISTE NA ÁRVORE.
// RETORNA A RAIZ EM AMBOS OS CASOS (ELA EDITADA OU NÃO).
p_numeros adicionaNovoNumero(p_numeros raiz, long int numeroLegal){
    p_numeros busvaNumero = buscaValor(raiz, numeroLegal);
   
    if(busvaNumero == NULL){
        // SE AO FAZER A BUSCA O VALOR NÃO FOI ACHADO, IREMOS ALOCA-LO.
        raiz = adicionaArvore(raiz, numeroLegal);
        raiz->cor = PRETO;
    }
    else
        // SE O VALOR FOI ACHADO, APENAS ADICIONAMOS 1 EM SUA APARIÇÃO NA LISTA.
        busvaNumero->qtdVezes++; 
    
    return raiz;
}