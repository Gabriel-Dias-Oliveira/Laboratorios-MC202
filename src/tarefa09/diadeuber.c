 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB09: GERENCIAR OS GASTOS E A FILA DE PASSAGEIROS DE UM MOTORISTA DE UBER ("DIA DE UBER").

#include <stdio.h>
#include <stdlib.h>
#include "uber_heap.h"

// INSERE UM NOVO PASSAGEIRO NA FILA DE ESPERA.
// CASO O MOTORISTA NÃO ESTEJA EM CORRIDA, A CORRIDA DO PASSAGEIRO JÁ SE INICIA. 
void adicionaPassageiro(p_motorista motoristaUber){
    p_passageiro passageiro = NULL;
    char *nome = malloc(MAX_NAME * sizeof(char));
    double avaliacao = 0, xO = 0, xD = 0, yO = 0, yD = 0;

    if(nome == NULL)
        exit(1);

    // INFORMAÇÕES DE UM PASSAGEIRO.
    scanf("%s %lf %lf %lf %lf %lf", nome, &avaliacao, &xO, &yO, &xD, &yD);

    passageiro = criaPassageiro(nome, avaliacao, xO, yO, xD, yD);

    inserePassageiro(motoristaUber->filaUber, passageiro);

    // SE O MOTORISTA NÃO ESTÁ EM CORRIDA, A CORRIDA DO PASSAGEIRO JÁ É ACEITA. 
    if(!motoristaUber->emCorrida){
        motoristaUber->passageiroAtual = removePassageiro(motoristaUber->filaUber);
        motoristaUber->emCorrida = 1;
    }

    printf("Cliente %s foi adicionado(a)\n", nome);

    free(nome);
}

// TERMINA A CORRIDA DO PASSAGEIRO ATUAL.
void finalizaCorrida(p_motorista motoristaUber){
    realizaCorrida(motoristaUber, motoristaUber->passageiroAtual);

    printf("A corrida de %s foi finalizada\n", motoristaUber->passageiroAtual.nome);

    free(motoristaUber->passageiroAtual.nome);

    if(motoristaUber->filaUber->quatidadePassageiros > 0)
        // PEGA O PROXIMO PASSAGEIRO NA FILA DE ESPERA!
        motoristaUber->passageiroAtual = removePassageiro(motoristaUber->filaUber);
    else
        // SE NÃO EXISTIR MAIS NENHUMA PASSAGEIRO, O MOTORISTA NÃO ENTRA EM NENHUMA CORRIDA.
        motoristaUber->emCorrida = 0;
}

// SE O PASSAGEIRO CANCELOU A CORRIDA, DEVEMOS TRATAR DISSO E REMOVE-LO.
void cancelouCorrida(p_motorista motoristaUber){
    char *nome = malloc(MAX_NAME * sizeof(char));

    if(nome == NULL)
        exit(1);

    scanf("%s", nome);

    cancelaCorrida(motoristaUber, nome);

    printf("%s cancelou a corrida\n", nome);

    free(nome);
}

// FINALIZA A JORNADA DO MOTORISTA FORNECENDO UM RESUMO DAS SUAS ESTATÍSTICAS DO DIA.
void finalizaJornada(p_motorista motoristaUber){
    double rendimentoBruto, despesas, rendimentoLiquido;
    
    // RENDIMENTO BRUTO: R$1.40 POR KM PERCORRIDO COM PASSAGEIRO + CANCELAMENTOS.
    rendimentoBruto = (motoristaUber->distanciaReal * 1.4) + motoristaUber->ganhoCancelamento; 
    
    // GASTOS COM GASOLINA + R$57 ALUGUEL DO VEICULO.
    despesas = ((motoristaUber->distanciaRodada / 10) * 4.104) + 57;
    
    // GANHO REAL: 75% DO RENDIMENTO BRUTO (25% COBRADO NA TAXA DO UBER) E DECONTO DAS DESPESAS. 
    rendimentoLiquido = (rendimentoBruto * 0.75) - despesas;
    
    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %.0lf\nRendimento bruto: %.2lf\nDespesas: %.2lf\nRendimento liquido: %.2lf", 
    motoristaUber->distanciaRodada, rendimentoBruto, despesas, rendimentoLiquido); 

    destruirListas(motoristaUber);
}

int main(){
    p_motorista motoristaUber = criaMotorista();
    char acao;

    while(1){
        scanf("%c", &acao);

        // VERIFICA CADA AÇÃO ATÉ QUE O MOTORISTA DESEJE TERMINAR A JORNADA DE TRABALHO.
        if(acao == 'A'){
            adicionaPassageiro(motoristaUber);
        }
        else if(acao == 'F'){
            finalizaCorrida(motoristaUber);
        }
        else if(acao == 'C'){
            cancelouCorrida(motoristaUber);
        }
        else if(acao == 'T'){
            finalizaJornada(motoristaUber);
            break;
        }
    }

    return 0;
}