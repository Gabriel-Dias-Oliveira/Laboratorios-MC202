 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB02: PROGRAMA PARA GERENCIAMENTRO DE INFORMAÇÕES DAS TURMAS/ALUNOS DO PROFESSOR CARLOS.

#include <stdio.h>
#include "professor_carlos.h"

// A FUNÇÃO RECEBE O CONTEÚDO DAS TURMAS, A TURMA ESPECÍFICA E O ALUNO MAIS NOVO (POR PADRÃO O 1º ALUNO DA TURMA).
// A PARTIR DA COMPARAÇÃO DA DATA DE NASCIMENTO RETORNA QUEM É O ALUNO MAIS NOVO DA(s) TURMA(s). 
Aluno acha_mais_novo(Turma t[], int j, Aluno maisNovo){
    int i, x, comparaNome = 0;

    for(i = 0; i < t[j].qtd; i++){
         /* 
            NOTA-SE QUE QUANTO MAIOR O ANO, MÊS E DIA DO NASCIMENTO DO ALUNO MAIS NOVO ELE É.
            DESSE MODO, SE A DATA DO ALUNO É MAIOR QUE A DO 'MAIS NOVO', ENTÃO ELE É MAIS NOVP.
            EM CASO DE ÚLTIMO EMPATE (DATAS IGUASIS), COMPARA-SE OS NOMES E SOBRENOME CHAR A CHAR DOS ESTUDANTES.
        */

        if(t[j].alunos[i].nascimento.ano > maisNovo.nascimento.ano){
            maisNovo = t[j].alunos[i];
        }
        else if(t[j].alunos[i].nascimento.ano == maisNovo.nascimento.ano){
            if(t[j].alunos[i].nascimento.mes > maisNovo.nascimento.mes){
                maisNovo = t[j].alunos[i];
            }
            else if(t[j].alunos[i].nascimento.mes == maisNovo.nascimento.mes){
                if(t[j].alunos[i].nascimento.dia > maisNovo.nascimento.dia){
                    maisNovo = t[j].alunos[i];
                }
                else if(t[j].alunos[i].nascimento.dia == maisNovo.nascimento.dia){
                    for(x = 0; t[j].alunos[i].nome[x] != '\0'; x++){
                        if(t[j].alunos[i].nome[x] < maisNovo.nome[x]){
                            maisNovo = t[j].alunos[i];
                            comparaNome = 0;
                            break;
                        }
                         else if(t[j].alunos[i].nome[x] > maisNovo.nome[x]){
                            comparaNome = 0;
                            break;
                        }
                        else if(t[j].alunos[i].nome[x] == maisNovo.nome[x])
                            comparaNome = 2;
                    } 
                    if(comparaNome == 2){
                        for(x = 0; t[j].alunos[i].sobrenome[x] != '\0'; x++){
                            if(t[j].alunos[i].sobrenome[x] < maisNovo.sobrenome[x]){
                                maisNovo = t[j].alunos[i];
                                break;
                            }
                            else if(t[j].alunos[i].sobrenome[x] > maisNovo.sobrenome[x])
                                break;
                        }
                    }
                }
            }
        }
    }

    return maisNovo;
}

// A FUNÇÃO RECEBE O CONTEÚDO DAS TURMAS, A TURMA ESPECÍFICA E O ALUNO MAIS VELHO (POR PADRÃO O 1º ALUNO DA TURMA).
// A PARTIR DA COMPARAÇÃO DA DATA DE NASCIMENTO RETORNA QUEM É O ALUNO MAIS VELHO DA(s) TURMA(s). 
Aluno acha_mais_velho(Turma t[], int j, Aluno maisVelho){ 
    int i, x, comparaNome = 0;

    for(i = 0; i < t[j].qtd; i++){
        /* 
            NOTA-SE QUE QUANTO MENOR O ANO, MÊS E DIA DO NASCIMENTO DO ALUNO MAIS VELHO ELE É.
            DESSE MODO, SE A DATA DO ALUNO É MENOR QUE A DO 'MAIS VELHO', ENTÃO ELE É MAIS VELHO.
            EM CASO DE ÚLTIMO EMPATE (DATAS IGUASIS), COMPARA-SE OS NOMES E SOBRENOME CHAR A CHAR DOS ESTUDANTES.
        */

        if(t[j].alunos[i].nascimento.ano < maisVelho.nascimento.ano){
            maisVelho = t[j].alunos[i];
        }
        else if(t[j].alunos[i].nascimento.ano == maisVelho.nascimento.ano){
            if(t[j].alunos[i].nascimento.mes < maisVelho.nascimento.mes){
                maisVelho = t[j].alunos[i];
            }
            else if(t[j].alunos[i].nascimento.mes == maisVelho.nascimento.mes){
                if(t[j].alunos[i].nascimento.dia < maisVelho.nascimento.dia){
                    maisVelho = t[j].alunos[i];
                }
                else if(t[j].alunos[i].nascimento.dia == maisVelho.nascimento.dia){

                    for(x = 0; t[j].alunos[i].nome[x] != '\0'; x++){
                        if(t[j].alunos[i].nome[x] < maisVelho.nome[x]){
                            maisVelho = t[j].alunos[i];
                            comparaNome = 0;
                            break;
                        }
                        else if(t[j].alunos[i].nome[x] > maisVelho.nome[x]){
                            comparaNome = 0;
                            break;
                        }
                        else if(t[j].alunos[i].nome[x] == maisVelho.nome[x])
                            comparaNome = 2;
                    } 
                    if(comparaNome == 2){

                        for(x = 0; t[j].alunos[i].sobrenome[x] != '\0'; x++){
                            if(t[j].alunos[i].sobrenome[x] < maisVelho.sobrenome[x]){
                                maisVelho = t[j].alunos[i];
                                break;
                            }
                            else if(t[j].alunos[i].sobrenome[x] > maisVelho.sobrenome[x])
                                break;
                        }
                    }
                }
            }
        }
    }

    return maisVelho;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
    Aluno maisNovo = t[j].alunos[0];

    maisNovo = acha_mais_novo(t, j, maisNovo);
    return maisNovo;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
    int i;
    Aluno maisNovo = t[0].alunos[0];

    for(i = 0; i < qtd_turmas; i++){
        maisNovo = acha_mais_novo(t, i, maisNovo);
    }

    return maisNovo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    Aluno maisVelho = t[j].alunos[0];

    maisVelho = acha_mais_velho(t, j, maisVelho);

    return maisVelho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    int i;
    Aluno maisVelho = t[0].alunos[0];

    for(i = 0; i < qtd_turmas; i++){
        maisVelho = acha_mais_velho(t, i, maisVelho);
    }

    return maisVelho;
}

// A FUNÇÃO RECEBE UM TEXTO E RETORNA O NÚMERO DE CARACTERES DO TEXTO.
int conta_caracteres(char padrao[]){
    int i;

    for(i = 0; padrao[i] != '\0'; i++);
    
    return i;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao){
    int i, j, k, pos, contador = 0, verifica = 0;

    for(i = 0; i < qtd_turmas; i++){
        for(j = 0; j < t[i].qtd; j++){
            for(pos = 0; pos < conta_caracteres(t[i].alunos[j].nome); pos++){
                verifica = 0;

                for(k = 0; padrao[k] != '\0'; k++){
                    if(t[i].alunos[j].nome[pos + k] == '\0' || (t[i].alunos[j].nome[pos + k] != padrao[k])){
                        break;
                    }
                    else if((t[i].alunos[j].nome[pos + k] == padrao[k])){
                        verifica++;
                    }
                }

                if(verifica == (conta_caracteres(padrao))){
                    contador++;
                    break; 
                }
            }
        }
    }

    return contador;
}

int add_aluno(Turma t[], Aluno A, int j){
    t[j].alunos[t[j].qtd] = A;

    return (t[j].qtd + 1);
}

int remove_aluno(Turma t[], int j){
    return (t[j].qtd - 1);
}