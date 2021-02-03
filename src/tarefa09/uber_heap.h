 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
// LAB09: GERENCIAR OS GASTOS E A FILA DE PASSAGEIROS DE UM MOTORISTA DE UBER ("DIA DE UBER").

#ifndef UBER_HEAP_H
#define UBER_HEAP_H

#define MAX_NAME 16
#define MAX_PASSAGEIROS 250
// DEFINES DO HEAP 
#define FILHO_ESQUERDO(i) (2 * i + 1)
#define FILHO_DIREITO(i) (2 * i + 2)
#define PAI(i) ((i - 1) / 2)

// INFORMAÇÕES DOS PASSAGEIROS.
typedef struct Passageiro{
    char *nome;    
    double avaliacao, xOrigem, yOrigem, xDestino, yDestino;
} Passageiro;

typedef Passageiro * p_passageiro;

// INFORMAÇÕES DO HEAP (FILA) DE PASSAGEIROS PARA O UBER.
typedef struct Uber{
    Passageiro *passageiros;    
    int quatidadePassageiros, tamanhoFila;
} Uber;

typedef Uber * p_uber;

// INFORMAÇÕES DO MOTORISTA.
typedef struct Motorista{
    p_uber filaUber; // FILA CORRESPONDENTE A ELE.
    Passageiro passageiroAtual;    
    int emCorrida;
    double x, y, distanciaRodada, distanciaReal, ganhoCancelamento;
} Motorista;

typedef Motorista * p_motorista;

// INSERE UM NOVO PASSAGEIRO NA FILA DE ESPERA.
void inserePassageiro(p_uber filaUber, p_passageiro passageiro);

// REALIZA UMA CORRIDA (COMPUTA OS DADOS AO TÉRMINO DE UMA CORRIDA).
void realizaCorrida(p_motorista motorista, Passageiro passageiroCorrida);

// CANCELA A CORRIDA DE UM PASSAGEIRO ESPECIFICO. 
void cancelaCorrida(p_motorista motorisa, char *nome);

// LIBERA TODA A MEMÓRIA ALOCADA PARA A FILA.
void destruirListas(p_motorista motoristaUber);

// INICIA A "JORNADA" DO NOVO MOTORISTA - INICALIZA SUA LISTA DE PASSAGEIROS. 
p_motorista criaMotorista(); 

// CRIA UM NOVO PASSAGEIRO.
p_passageiro criaPassageiro(char *nome, double avaliacao, double xO, double yO, double xD, double yD);

// REMOVE UM PASSAGEIRO DA FILA DO UBER.
Passageiro removePassageiro(p_uber filaUber);

#endif