#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main(){
    int numCartoes = 0, numAutoridades = 0, valorCartao = 0, valorAutoridade = 0, contador = 0;
    char caracteres;
    char *mensagens, *fraseFinal;
    p_mensagem mensagemArvore, answerTree;

    mensagemArvore = answerTree = criarArvore();
    mensagens = malloc(MAX_SIZE_MENSAGEM * sizeof(char));
    
    if(mensagens == NULL) exit(1);

    while(1){        
        if(scanf("%d", &numCartoes) == EOF) break; 

        scanf("%d", &numAutoridades);

        fraseFinal = malloc(numCartoes * MAX_SIZE_MENSAGEM * sizeof(char));

        if(fraseFinal == NULL) exit(1);

        while(1){
            // CONFIGURA O MODELO INICIAL DA ÁRVORE ("SACOLA DO MENSAGEIRO").

            for(int x = 0; x < MAX_SIZE_MENSAGEM; x++)
                mensagens[x] = '\0';
            
             for(int x = 0; x < numCartoes * MAX_SIZE_MENSAGEM; x++)
                fraseFinal[x] = '\0';


            // COLETA OS CARTÕES INICIAIS DO MENSAGEIRO.
            scanf("%d", &valorCartao);
            scanf("%c %c", &caracteres, &caracteres);
            scanf("%c", &caracteres);

            // COLETA O TEXTO DA MENSAGEM.
            do{
                mensagens[contador] = caracteres;
                contador += 1;
                scanf("%c", &caracteres);
            }while(caracteres != '"');

            mensagens[contador] = '\0';

            mensagemArvore = inserirMensagem(mensagemArvore, valorCartao, mensagens);

            contador = 0;
            scanf("%c", &caracteres);

            if(caracteres == '\n') break;
        }
        
        for(int x = 0; x < numAutoridades; x++){      
            // PARA CADA AUTORIDADE TENTA ACHAR A SOMA E DESVENDAR A MENSAGEM.

            scanf("%d", &valorAutoridade);

            desembaralhaMensagem(mensagemArvore, &answerTree, valorAutoridade);        

            removeCartoes(&mensagemArvore, answerTree);

             for(int x = 0; x < numCartoes * MAX_SIZE_MENSAGEM; x++)
                fraseFinal[x] = '\0';

            // CRIA E INSERE O NOVO CARTAL - COM A CONCATENAÇÃO DAS MENSAGENS E VALOR DA AUTORIDADE.
            criaMensagem(answerTree, &fraseFinal);

            mensagemArvore = inserirMensagem(mensagemArvore, valorAutoridade, fraseFinal);    
 
            apagaArvore(answerTree);
            answerTree = criarArvore();
        };

        for(int x = 0; x < numCartoes * MAX_SIZE_MENSAGEM; x++)
            fraseFinal[x] = '\0';

        criaMensagem(mensagemArvore, &fraseFinal);
        
        printf("%s\n", fraseFinal);

        // INICIALIZA A ÁRVORE NOVAMENTE PARA SER UTILIZADA COM OS PRÓXIMOS MENSAGEIROS.       
        apagaArvore(answerTree);
        apagaArvore(mensagemArvore);
        free(fraseFinal);
        answerTree = mensagemArvore = criarArvore();
    }
    
    free(mensagens);
    apagaArvore(answerTree);
    apagaArvore(mensagemArvore);

    return 0;
}