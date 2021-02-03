 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB07: DESEVENDA UMA MENSAGEM EMBARALHADA - A PARTIR DE UMA 'CHAVE/SENHA'.
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// RECEBE UMA ÁRVORE E DELETA TODOS OS SEUS NÓS - LIBERANDO A MEMÓRIA.
void apagaArvore(p_mensagem raiz){
    if(raiz == NULL)
        return;

    apagaArvore(raiz->esq);
    apagaArvore(raiz->dir);

    free(raiz->mensagem);
    free(raiz);
}

// CONCATENA TODAS AS MENSAGENS (DE UMA SEQUÊNCIA DE CARTÕES) EM UMA ÚNICA FRASE (CARTÃO).
void criaMensagem(p_mensagem raiz, char **fraseFinal){
    if (raiz != NULL) {
        criaMensagem(raiz->esq, fraseFinal);
        *fraseFinal = strcat(*fraseFinal, raiz->mensagem);
        criaMensagem(raiz->dir, fraseFinal);
    }
}

// INICIALIZA UMA NOVA ÁRVORE.
p_mensagem criarArvore(){
    return NULL;
}

// INSERE UM NOVO NÓ NA ÁRVORE - ALOCANDO MEMÓRIA PARA TODAS AS SUAS INFORMAÇÕES.
// RETORNA A NOVA ÁRVORE AGORA COM O NÓ ALOCADO.
p_mensagem inserirMensagem(p_mensagem raiz, int chaveAutoridade, char *mensagem){
    p_mensagem novaMensagem = NULL;

    if(raiz == NULL){
        novaMensagem = malloc(sizeof(Mensagem));

        if(novaMensagem == NULL) exit(1);

        // ALOCA UMA FRASE DE TAMANHO PROPORCIONAL A MENSAGEM QUE FOI FORMADA.
        novaMensagem->mensagem = malloc((strlen(mensagem) + 1) * sizeof(char)); 

        if(novaMensagem->mensagem == NULL) exit(1);

        for(int x = 0; x < strlen(mensagem) + 1; x++)
            novaMensagem->mensagem[x] = '\0';

        novaMensagem->esq = novaMensagem->dir = NULL;
        novaMensagem->chaveAutoridade = chaveAutoridade;
        novaMensagem->mensagem = strcpy(novaMensagem->mensagem, mensagem);

        return novaMensagem;
    }

    if(chaveAutoridade < raiz->chaveAutoridade)
        raiz->esq = inserirMensagem(raiz->esq, chaveAutoridade, mensagem);
    else
        raiz->dir = inserirMensagem(raiz->dir, chaveAutoridade, mensagem);
    
    return raiz;
}

// ACHA O MENOR VALOR DA ÁRVORE.
// RETORNA ESSE NÓ.
p_mensagem achaMinimo(p_mensagem raiz){
    if (raiz == NULL || raiz->esq == NULL)
        return raiz;
    
    return achaMinimo(raiz->esq);
}

// ACHA QUEM É O SUCESSOR DO NÓ A SER REMOVIDO, PARA SUBSTITUI-LO NA ÁRVORE.
void removerSucessor(p_mensagem raiz) {
    p_mensagem min = raiz->dir; // MENOR VALOR DA SUB-ÁRVORE DIREITA.
    p_mensagem pai = raiz; // INFORMAÇÃO SOBRE QUEM É O PAI DO NÓ.
    
    while (min->esq != NULL) {
        pai = min;
        min = min->esq;
    }

    if (pai->esq == min)
        pai->esq = min->dir;
    else
        pai->dir = min->dir;
    
   
    raiz->chaveAutoridade = min->chaveAutoridade; 

    // TROCANDO O CONTEUDO DO SUCESSOR COM O NÓ DA RAIZ.
    raiz->mensagem = realloc(raiz->mensagem, strlen(min->mensagem) + 1);

    if(raiz->mensagem == NULL) exit(1);

    raiz->mensagem = strcpy(raiz->mensagem, min->mensagem);

    free(min->mensagem);
    free(min);  
}

// REMOÇÃO DE UM NÓ ESPECIFICO DA ÁRVORE.
// BUSCA FEITA COM BASE EM UMA CHAVE FORNECIDA.
// RETORNA A NOVA ÁRVORE SEM O NÓ EM QUESTÃO. 
p_mensagem removerRecursivo(p_mensagem raiz, int chave){
    if(raiz == NULL)
        return NULL;
    if(chave < raiz->chaveAutoridade)
        raiz->esq = removerRecursivo(raiz->esq, chave);
    else if(chave > raiz->chaveAutoridade)
        raiz->dir = removerRecursivo(raiz->dir, chave);
    else if(raiz->esq == NULL){
        // SE O NÓ SÓ TEM FILHO A DIREITA - BASTA 'PULAR ELE' RETORNANDO O FILHO.
        p_mensagem aux = raiz->dir;

        free(raiz->mensagem);
        free(raiz);

        return aux;
    }
    else if(raiz->dir == NULL){
        // SE O NÓ SÓ TEM FILHO A ESQUERDA - BASTA 'PULAR ELE' RETORNANDO O FILHO.
        p_mensagem aux = raiz->esq;

        free(raiz->mensagem);
        free(raiz);
        
        return aux;
    }
    else
        removerSucessor(raiz); // TEM OS DOIS FILHOS.

   return raiz;
}

// REMOVE UMA SÉRIE DE CARTÕES FORNECIDOS.
// RMEOÇÃO DOS CARTÕES JÁ USADOS DA ÁRVORE ('SACOLA') DO MENSAGEIRO.
void removeCartoes(p_mensagem *mensagemArvore, p_mensagem respostaArvore){
    if(respostaArvore == NULL)
        return;

    // PERCORRE TODA A ÁRVORE DE RESPOSTA 
    removeCartoes(mensagemArvore, respostaArvore->esq);
    removeCartoes(mensagemArvore, respostaArvore->dir);

    // ELIMINANDO OS NÓS DA ÁRVORE ORIGINAL.
    *mensagemArvore = removerRecursivo(*mensagemArvore, respostaArvore->chaveAutoridade);
}

// BUSCA O PRÓXIMO VALOR A SER TESTADO NA COMBINAÇÃO DA SOMA.
// RETORNA O NÓ QUE MELHOR SE ADAPTA A BUSCA OU NULL (NENHUM NÓ VÁLIDO).
p_mensagem buscaProximo(p_mensagem raiz, int chave){
    if(raiz == NULL || chave == raiz->chaveAutoridade)
        // VALOR NULL OU VALOR PROCURADO ENCONTRADO!
        return raiz;
    if(chave < raiz->chaveAutoridade)
        // SE A CHAVE É MENOR, DEVEMOS IR PARA A ESQUERDA -- MESMO Q CHEGUEMOS EM NULL.
        // NULL = SOMA ERRADA E NÃO PODE SER FINALIZADA.
        return buscaProximo(raiz->esq, chave);
    else if((raiz->dir != NULL && raiz->dir->chaveAutoridade <= chave) || 
            (raiz->dir != NULL && achaMinimo(raiz->dir)->chaveAutoridade <= chave))
    
        // SE EXISTE FILHO A DIREITA E A CHAVE DELE PROSEGUE SENDO <= QUE A BUSCA ENTÃO VAMOS PARA DIREITA.
        // OU AINDA, EXISTE UM NÓ NA SUB-ÁRVORE A DIREITA QUE PODE SER O VALOR DESEJADO OU <= A ELE. 
        return buscaProximo(raiz->dir, chave);
    else 
        // CASO O PRÓXIMO VALOR SEJA MAIOR QUE A CHAVE OU NÃO TENHA MAIS NENHUM VALOR COMPATIVEL RETORNA O NÓ.
        return raiz;
}

// FUNÇÃO PARA DECIFRAR A MENSAGEM (ACHAR A COMBINAÇÃO DE CARTÕES).
// PARA USO DA PRÓPRIA FUNÇÃO RETURN: 0 - PARAR SEQUẼNCIA E RETORNAR UM NÓ | 1 - SEQUÊNCIA ACHADA.
int decifraMensagem(p_mensagem raiz, p_mensagem *answerTree, p_mensagem atual, int valorAutoridade, 
                    int minimo, int somaAtual, int digitos){
    int firstTime = 1; // 1º VEZ NA FUNÇÃO.

    if(somaAtual == valorAutoridade && digitos == 3)
        // SE TEMOS 3 DIGITOS E A SOMA FOI ACHADA - RETURN 1 (SUCESSO).
        return 1;
    else if(digitos == 3 || somaAtual > valorAutoridade)
        // CASO DIGITOS SEJA 3 OU A SOMA ULTRAPASSE O VALOR BUSCADO - RETURN 0 (VOLTA UM NÍVEL NA BUSCA).
        return 0;

    while(1){ // A SOMA SEMPRE SERÁ ACHADA.
        if(firstTime){
            // CASO SEJA A 1º VEZ, BUSCAMOS O VALOR RESTANTE QUE FALTA PRA COMPLETAR A SOMA.
            // VALOR DESEJADO - SOMA ATUAL.
            firstTime = 0; 
            atual = buscaProximo(raiz, valorAutoridade - somaAtual);
        }
        else{
            // CASO NÃO SEJA A 1º VEZ, VERIFICAMOS SE AINDA EXISTE ALGUM NÓ VÁLIDO NA ÁRVORE PARA SER TESTADO.
            // CASO TENHA, BUSCAMOS O VALOR ATUAL (O VALOR TESTADO SEM SUCESSO) - 1.
            // POIS ASSIM TEREMOS O PRÓXIMO VALOR NA ÁRVORE - POSTERIOR AO ATUAL.
            if(atual->chaveAutoridade - 1 >= minimo)
                atual = buscaProximo(raiz, atual->chaveAutoridade - 1);
            else 
                atual = NULL;
        }
        
        if(atual == NULL) return 0; // SE NENHUM VALOR VÁLIDO FOR ACHADO A BUSCA TAMBÉM FRACASSOU.

        // ADICIONA O NÓ ATUAL A SOMA E A ÁRVORE DE RESPOSTA.
        somaAtual += atual->chaveAutoridade;
        digitos++;
        *answerTree = inserirMensagem(*answerTree, atual->chaveAutoridade, atual->mensagem);

        if(decifraMensagem(raiz, answerTree, NULL, valorAutoridade, minimo, somaAtual, digitos))
            return 1;
        
        // SE O NÓ FALHOU, REMOVE-O DA SOMA E O REMOVE DA ÁRVORE.
        somaAtual -= atual->chaveAutoridade;
        digitos--;
        *answerTree = removerRecursivo(*answerTree, atual->chaveAutoridade);
    }

    return 0;
}

// PREPARA E CONFIGURA A CHAMADA DA FUNÇÃO DE DECIFRAR A MENSAGEM.
void desembaralhaMensagem(p_mensagem raiz, p_mensagem *answerTree, int valorAutoridade){
    int minimo = achaMinimo(raiz)->chaveAutoridade;

    decifraMensagem(raiz, answerTree, NULL, valorAutoridade, minimo, 0, 0);
}   