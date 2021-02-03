 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB01: PROGRAMA PARA DISTRIBUIÇÃO DE PRÊMIOS DA MEGA SENA.

#include <stdio.h>
#define MAX_LINHAS 6
#define MAX_COLUNAS 10
#define MAX_USUARIOS 1000
#define NUMEROS_JOGO 6

// A FUNÇÃO RECEBE AS INFORMAÇÕES DE QUANTAS CARTELAS DEVEM SER CADASTRADAS ('N' APOSTADORES).
// SENDO ASSIM, ELA PREENCHE A CARTELA DOS 'N' DE APOSTADORES.  
void coletaCartelas(int numApostadores, int cartelasSena[][MAX_COLUNAS][MAX_USUARIOS]){
    int i, j, k;

    for(k = 0; k < numApostadores; k++)
        for(i = 0; i < MAX_LINHAS; i++)
            for(j = 0; j < MAX_COLUNAS; j++)
                scanf("%d", &cartelasSena[i][j][k]);
}

// RECEBENDO AS INFORMAÇÕES ESSÊNCIAS DO JOGO (CARTELA, NÚMERO DE APOSTADORES E NÚMEROS SORTEADOS).
// A FUNÇÃO CALCULA QUANTOS ACERTOS CADA JOGADOR OBTEVE - COM BASE NOS NÚMEROS SORTEADOS.
void calculaAcertos(int numApostadores, int numerosJogados[], int numeroAcertos[], int cartelasSena[][MAX_COLUNAS][MAX_USUARIOS]){
    int i, k, linha, coluna;

    for(i = 0; i < NUMEROS_JOGO; i++){
        scanf("%d", &numerosJogados[i]);

        linha = (numerosJogados[i] - 1) / (MAX_COLUNAS);
        coluna = (numerosJogados[i] - 1) % (MAX_COLUNAS);

        for(k = 0; k < numApostadores; k++)
            if(cartelasSena[linha][coluna][k] == 1)
                numeroAcertos[k] += 1;     
    }
}

// A FUNÇÃO RECEBE AS ESTATÍSTICAS DO JOGO - NÚMERO DE ACERTOS QUE CADA JOGADOR OBTEVE.
// DESSE MODO, ELA ATRIBUI A PARCELA DE PRÊMIO PROPORCIONAL AOS ACERTOS E AO NÚMERO DE APOSTADORES EM CADA FAIXA.
void definePremio(int numApostadores, double faixaAcertos[3], int numeroAcertos[MAX_USUARIOS], double valorPremio){
    int i;

    for(i = 0; i < numApostadores; i++){
        if(numeroAcertos[i] == 6)
            faixaAcertos[0] += 1;
        else if(numeroAcertos[i] == 5)
            faixaAcertos[1] += 1;
        else if(numeroAcertos[i] == 4)
            faixaAcertos[2] += 1;
    }

    // DIVISÃO DO PRÊMIO DE ACORDO COM OS CRITÉRIOS ESTABELECIDOS.

    for(i = 0; i < 3; i++){
        if(i == 0)
            faixaAcertos[i] = (0.62 * valorPremio) / faixaAcertos[i];
        else
            faixaAcertos[i] = (0.19 * valorPremio) / faixaAcertos[i];
    }   
}

// A FUNÇÃO RECEBENDO TODOS OS DADOS ANTERIORMENTE TRATADOS IMPRIME O PRÊMIO QUE CADA JOGADOR OBTEVE.
void imprimeResultado(int numApostadores, double faixaAcertos[3], int numeroAcertos[MAX_USUARIOS]){
    int i;
    double premio;

    for(i = 0; i < numApostadores; i++){
        premio = 0;

        if(numeroAcertos[i] == 6)
            premio = faixaAcertos[0];
        else if(numeroAcertos[i] == 5)
            premio = faixaAcertos[1];
        else if(numeroAcertos[i] == 4)
            premio = faixaAcertos[2];

        printf("%.2lf\n", premio);            
    }    
}

int main(){
    int i, numApostadores, numerosJogados[NUMEROS_JOGO], numeroAcertos[MAX_USUARIOS], matrizApostadores[MAX_LINHAS][MAX_COLUNAS][MAX_USUARIOS];
    double valorPremio, faixaAcerto[3] = {0, 0, 0};

    scanf("%d %lf", &numApostadores, &valorPremio); // RECEBE O NÚMERO DE APOSTADORES E QUAL O PRÊMIO A SER DIVIDIDO.

    for(i = 0; i < numApostadores; i++)
        numeroAcertos[i] = 0;

    // BASEADO NISSO, OS DADOS COMEÇAM A SER TRATADOS.
    // DESDE A COLETA DAS CARTELAS ATÉ O RESULTADO FINAL.

    coletaCartelas(numApostadores, matrizApostadores);
    calculaAcertos(numApostadores, numerosJogados, numeroAcertos, matrizApostadores);
    definePremio(numApostadores, faixaAcerto, numeroAcertos, valorPremio);
    imprimeResultado(numApostadores, faixaAcerto, numeroAcertos);

    return 0;
}