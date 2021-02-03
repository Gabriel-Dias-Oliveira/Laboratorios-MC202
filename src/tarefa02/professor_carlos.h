 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB02: PROGRAMA PARA GERENCIAMENTRO DE INFORMAÇÕES DAS TURMAS/ALUNOS DO PROFESSOR CARLOS.
 
#ifndef PROFESSOR_CARLOS_H
#define PROFESSOR_CARLOS_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct aluno {
    Data nascimento;
    char nome[15];
    char sobrenome[15];
} Aluno;

typedef struct turma {
    Aluno alunos[50];
    int qtd;
} Turma;

// A funcao recebe todas as turma e a turma escolhida,
// retornando o aluno mais novo da turma escolhida.
Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j);

// A funcao recebe todas as turmas e retorna o aluno mais novo dentre todas as turmas.
Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas);

// A funcao recebe todas as turma e o indice da turma escolhida,
// retornando o aluno mais velho da turma escolhida.
Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j);

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas);
// A funcao recebe todas as turmas e retorna o aluno mais velho dentre todas as turmas.

// A funcao recebe todoas as turmas e uma string,
// retornando a quantidade de alunos que a string aparece em seu nome.
int conta_substrings(Turma t[], int qtd_turmas, char *padrao);

// Adiciona o aluno A na turma j, retornando a quantidade de alunos da turma j.
int add_aluno(Turma t[], Aluno A, int j);

// Remove o ultimo aluno adicionado na turma j,
// retornando a quantidade de alunos restante na turma j.
int remove_aluno(Turma t[], int j);

#endif
