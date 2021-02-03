 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB07: DESEVENDA UMA MENSAGEM EMBARALHADA - A PARTIR DE UMA 'CHAVE/SENHA'.

#ifndef MENSAGEIRO_ARVORE_H
#define MENSAGEIRO_ARVORE_H
#define MAX_SIZE_MENSAGEM 6

// ÁRVORE DE MENSAGENS COM O PESO (VALOR) DE CADA 'NÓ' E A MENSAGEM CONTIDA NELE.
typedef struct Mensagem{
    int chaveAutoridade;
    char *mensagem;
    struct Mensagem *esq, *dir;
} Mensagem;

typedef Mensagem * p_mensagem;

// INICIALIZA UMA NOVA ÁRVORE.
p_mensagem criarArvore();

// INSERE UM NOVO NÓ NA ÁRVORE - ALOCANDO MEMÓRIA PARA TODAS AS SUAS INFORMAÇÕES.
// RETORNA A NOVA ÁRVORE AGORA COM O NÓ ALOCADO.
p_mensagem inserirMensagem(p_mensagem raiz, int chaveAutoridade, char *mensagem);

// PREPARA E CONFIGURA A CHAMADA DA FUNÇÃO DE DECIFRAR A MENSAGEM.
void desembaralhaMensagem(p_mensagem raiz, p_mensagem *answerTree, int valorAutoridade);

// REMOVE UMA SÉRIE DE CARTÕES FORNECIDOS.
// RMEOÇÃO DOS CARTÕES JÁ USADOS DA ÁRVORE ('SACOLA') DO MENSAGEIRO.
void removeCartoes(p_mensagem *mensagemArvore, p_mensagem respostaArvore);

// CONCATENA TODAS AS MENSAGENS (DE UMA SEQUÊNCIA DE CARTÕES) EM UMA ÚNICA FRASE (CARTÃO).
void criaMensagem(p_mensagem raiz, char **fraseFinal);

// RECEBE UMA ÁRVORE E DELETA TODOS OS SEUS NÓS - LIBERANDO A MEMÓRIA.
void apagaArvore(p_mensagem raiz);

#endif