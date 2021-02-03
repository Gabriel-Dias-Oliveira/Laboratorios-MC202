 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB02: PROGRAMA PARA GERENCIAMENTRO DE INFORMAÇÕES DAS TURMAS/ALUNOS DO PROFESSOR CARLOS.

#include <stdio.h>
#include "professor_carlos.h"
#define MAX_TURMAS 50
#define MAX_ALUNOS 40
#define MAX_NOME 14
#define MAX_OPERACAO 100
#define MAX_SUBSTRING 6

// INSERE UM NOVO ALUNO EM UMA DETERMINADA TURMA.
void adicionar_aluno(Turma turmas[], int j){
    Aluno aluno;

    scanf("%s %s %d %d %d ", aluno.nome, aluno.sobrenome, &aluno.nascimento.dia, &aluno.nascimento.mes, &aluno.nascimento.ano);
    turmas[j].qtd  = add_aluno(turmas, aluno, j);
}

// RECEBENDO UMA STRING (VETOR CHAR), LIMPA O CONTEÚDO DESSE VETOR.
void limpaVetor(char subString[]){
    int x;

    for(x = 0; x < 6; x++){
        subString[x] = '\0';
    }
}

// RECEBENDO A OPERAÇÃO QUE O USUÁRIO DESEJA FAZER, A QUANTIDADE DE TURMAS E AS TURMAS.
// O PROGRAMA PODE FAZER AS AÇÕES BÁSICAS QUE LHE SÃO ATRIBUÍDAS ~ MANIPULAR ALUNOS E TURMAS.
void realiza_acoes(int numOperacao, int numeroTurmas, Turma turmas[]){
    Aluno aluno;
    char subString[MAX_SUBSTRING]; 
    int turmaEscolhida;

    if(numOperacao == 1){
        scanf("%d", &turmaEscolhida);
        aluno = procura_novo_na_turma(turmas, numeroTurmas, turmaEscolhida);
        printf("%s\n", aluno.nome);
    }
    else if(numOperacao == 2){
        scanf("%d", &turmaEscolhida);
        aluno = procura_velho_na_turma(turmas, numeroTurmas, turmaEscolhida);
        printf("%s\n", aluno.sobrenome);
    }
    else if(numOperacao == 3){
        aluno = procura_velho_todas_turmas(turmas, numeroTurmas);
        printf("%s\n", aluno.nome);
    }
    else if(numOperacao == 4){
        aluno = procura_novo_todas_turmas(turmas, numeroTurmas);
        printf("%s\n", aluno.sobrenome);
    }
    else if(numOperacao == 5){ 
        // PROCURA A PRESENÇA DE UM PADRÃO NO NOME DOS ESTUDANTES.
        limpaVetor(subString);
        scanf("%s", subString);

        printf("%d\n", conta_substrings(turmas, numeroTurmas, subString));
    }
    else if(numOperacao == 6){
        scanf("%d ", &turmaEscolhida);
        adicionar_aluno(turmas, turmaEscolhida);

        printf("%d\n", turmas[turmaEscolhida].qtd);
    }
    else if(numOperacao == 7){
        scanf("%d", &turmaEscolhida);
        turmas[turmaEscolhida].qtd = remove_aluno(turmas, turmaEscolhida);
        printf("%d\n", turmas[turmaEscolhida].qtd);
    }
}

int main(){
    int i, qtdAlunos, numeroTurmas, numeroOperacoes, opcao;
    Turma turmas[MAX_TURMAS];

    scanf("%d %d ", &numeroTurmas, &numeroOperacoes);

    for(i = 0; i < numeroTurmas; i++){
        // PREENCHE TODAS AS TURMAS COM AS RESPECTIVAS QUANTIDADES DE ALUNOS.
        scanf("%d ", &qtdAlunos);
        turmas[i].qtd = 0; 

        while (qtdAlunos != 0){
            adicionar_aluno(turmas, i);
            qtdAlunos--;           
        }       
    }

    while (numeroOperacoes != 0){
        // REALIZA AS 'N' OPERAÇÕES DEFINIDAS PELO PROFESSOR CARLOS.
        scanf("%d", &opcao);

        realiza_acoes(opcao, numeroTurmas, turmas);   

        numeroOperacoes--;       
    }

    return 0;
}