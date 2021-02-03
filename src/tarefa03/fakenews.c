 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB03: DESCOBRIR QUAL FOI A RELEVÂNCIA DE UM TERMO EM UM DETERMINADO PERÍODO.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// TERMOS E SUAS ESTATÍSTICAS.
typedef struct termo{
    char *termoPesquisado;
    double media, desvioPadrao, minimo, maximo;
} Termo;

// LISTA CONTENDO OS TERMOS EM CADA CLASSIFICAÇÃO.
typedef struct classificacao{
    char *termosClassificados;
    int qtd;
} Classificacao;

// CALCULA O VALOR DA RELEVÂNCIA MÉDIA DO TERMO.
double calculaMedia(double *dados, int qtdDados){
    double media = 0;

    for(int x = 0; x < qtdDados; x++)
        media += (dados[x] / qtdDados);
    
    return media;
}

// CALCULA QUAL FOI A MÁXIMA E A MÍNIMA RELEVÂNCIA DO TERMO NO PERÍODO ANALISADO.
void calculaMaximoMinimo(double *dados, double *minimo, double *maximo, int qtdDados){
    *maximo = *minimo = dados[0];

    for(int x = 0; x < qtdDados; x++){
        if(dados[x] < *minimo)
            *minimo = dados[x];
        
        if(dados[x] > *maximo)
            *maximo = dados[x];
    }
}

// RETORNA O DESVIO PADRÃO DO CONJUNTO DE DADOS FORNECIDO.
double calculaDesvioPadrao(double *dados, double media, int qtdDados){
    double somatorio = 0;

    for(int x = 0; x < qtdDados; x++)
        somatorio += pow(dados[x] - media, 2);

    return sqrt(somatorio / qtdDados);
}

// DIZ QUAL É A CLASSIFICAÇÃO DO TERMO DE ACORDO COM AS ESTATÍSICAS FORNECIDAS.
void verificaClassificacao(Termo *termo, Classificacao *classificacao){
    int i = -1;

    if((termo->media) >= 60 && (termo->desvioPadrao) > 15) // BOT.
        i = 0;    
    else if((termo->media) >= 60 && (termo->desvioPadrao) <= 15) // EVENTO SURPREENDENTE.
        i = 1;
    else if((termo->media) < 60 && (termo->maximo) >= 80 && (termo->minimo) > 20) // EVENTO NORMAL.
        i = 2;
    else if((termo->media) < 60 && (termo->maximo) >= 80 && (termo->minimo) <= 20) // EVENTO LOCAL.
        i = 3;
    else if((termo->media) < 60 && (termo->maximo) < 80) // EVENTO IRRELEVANTE
        i = 4;

    strcat(classificacao[i].termosClassificados, " ");
    strcat(classificacao[i].termosClassificados, termo->termoPesquisado);

    classificacao[i].qtd++;
}

// IMPRIME O RESULTADO POR CLASSIFICAÇÃO.
void imprimeResultado(char *categoria, char *nomes, int qtd){
    printf("%s (%d): %s\n", categoria, qtd, nomes);
}

int main(){
    Termo *termos;
    Classificacao *classificacao;
    int numeroTermos, numeroDias, k, contador = 0;
    double *dadosAnalisados;

    scanf("%d %d ", &numeroTermos, &numeroDias);
    
    k = numeroTermos;

    termos = malloc(numeroTermos * sizeof(Termo));
    classificacao = malloc(5 * sizeof(Classificacao));
    
    // ALOCA E CONFIGURA A LISTA DE TERMOS. 
    for(int i = 0; i < numeroTermos; i++){
        termos[i].termoPesquisado = malloc(26 * sizeof(char));
        termos[i].media = termos[i].maximo = termos[i].minimo = termos[i].desvioPadrao = 0;
        strcpy(termos[i].termoPesquisado, "");
    }

    // ALOCA E CONFIGURA A LISTA DE CLASSIFICAÇÕES. 
    for(int i = 0; i < 5; i++){
        classificacao[i].termosClassificados = malloc((26 * numeroTermos) * sizeof(char));
        strcpy(classificacao[i].termosClassificados, "");
        classificacao[i].qtd = 0;
    }

    dadosAnalisados = malloc(numeroDias * sizeof(double));

    // PARA O NÚMERO DE TERMOS:
    // COLETA QUAL É O TERMO E QUAIL FOI SUA RELEVÂNCIA NO PERÍODO ANALISADO.
    // CALCULA SUAS ESTATISTICAS E AS IMPRIMI.
    while(numeroTermos > 0){
        scanf("%s", termos[contador].termoPesquisado);

        for(int x = 0; x < numeroDias; x++)
            scanf("%lf", &dadosAnalisados[x]); 

        termos[contador].media = calculaMedia(dadosAnalisados, numeroDias);

        calculaMaximoMinimo(dadosAnalisados, &(termos[contador].minimo), &(termos[contador].maximo), numeroDias);

        termos[contador].desvioPadrao = calculaDesvioPadrao(dadosAnalisados, termos[contador].media, numeroDias);

        // TAMBÉM ALOCA O TERMO EM UMA DAS CLASSIFICAÇÕES.
        verificaClassificacao(&termos[contador], classificacao);

        printf("%s %.2lf %.2lf %.2lf %.2lf\n", termos[contador].termoPesquisado, termos[contador].maximo, 
        termos[contador].minimo, termos[contador].media, termos[contador].desvioPadrao);

        contador++;
        numeroTermos--;
    }

    // POR FIM IMPRIME O RESULTADO DA CLASSIFICAÇÃO DOS TERMOS (POR CATEGORIA).
    printf("\nRESULTADO:\n");

    imprimeResultado("Bot", classificacao[0].termosClassificados, classificacao[0].qtd);
    imprimeResultado("Surpreendente", classificacao[1].termosClassificados, classificacao[1].qtd);
    imprimeResultado("Normal", classificacao[2].termosClassificados, classificacao[2].qtd);
    imprimeResultado("Local", classificacao[3].termosClassificados, classificacao[3].qtd);
    imprimeResultado("Irrelevante", classificacao[4].termosClassificados, classificacao[4].qtd);

    for (int i = 0; i < k; i++)
        free(termos[i].termoPesquisado);

    for (int i = 0; i < 5; i++)
        free(classificacao[i].termosClassificados);
    
    free(termos);
    free(classificacao);
    free(dadosAnalisados);

    return 0;
}