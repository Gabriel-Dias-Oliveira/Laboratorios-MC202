 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB06: GERENCIAMENTO DAS FILAS DE PACIÊNTES DO HOSPITAL (CECOM).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 50
#define CONSULTORIOS 9
#define CLINICO_GERAL 10
#define RADIOLOGISTA 2
#define ENFEREMEIRO 5
#define OTORRINO 3
#define PNEUMOLOGISTA 4
#define DERMATOLOGISTA 7
#define NEUROLOGISTA 2 
#define ONCOLOGISTA 1
#define PSIQUIATRA 4

// LISTA DE CONSULTAS QUE UM PACIENTE FARÁ.
typedef struct Consultas{
    int especialidade;
    struct Consultas *prox;
} Consultas;

typedef Consultas * p_consultas;

// 'CRIA' UMA PESSOA NO SISTEMA E SEUS ATRIBUTOS.
typedef struct Pacientes{
    char *nome;
    int tipoAtendimento, tempoAtendimento, statusAtendimento;
    p_consultas consultasPaciente;
    struct Pacientes *prox;
} Pacientes;

typedef Pacientes * p_pacientes;

// LISTA/BASE DA FILA DOS CONSULTÓRIOS.  
typedef struct Consultorios{
    p_pacientes pacientesFila;
    struct Consultorios *prox, *ant; 
} Consultorios;

typedef Consultorios * p_consultorios;

// FILAS DE ATENDIMENTO DE CADA CONSULTÓRIO.
typedef struct FilaAtendimento{
    p_consultorios inicio, fim; 
    int qtdMedicos;
} FilaAtendimento;

typedef FilaAtendimento * p_fila;

// LISTA PARA GUARDAR OS PACIENTES.
typedef struct ListaPacientes{
    Pacientes paciente;
    struct ListaPacientes *prox;
} ListaPacientes;

typedef ListaPacientes * p_lstpacientes;

// CRIA UMA LISTA DE PACIENTES VAZIA.
p_lstpacientes criarPaciente(){
    return NULL;
}

// CRIA UMA LISTA DE CONSULTAS VAZIA.
p_consultas criarConsulta(){
    return NULL;
}

// CRIA UMA FILA DE ATENDIMENTOS VAZIA.
// A FILA TAMBÉM ARMAZENA A QUANTIDADE DE MÉDICOS ATENDENDO.
p_fila criarFila(int qtdMedicos){
    p_fila filaAtendimento = malloc(sizeof(FilaAtendimento));

    filaAtendimento->inicio = filaAtendimento->fim = NULL;
    filaAtendimento->qtdMedicos = qtdMedicos;

    return filaAtendimento;
}

// INICIALIZA TODAS AS FILAS DO PROGRAMA E SEUS RESPECTIVOS NÚMEROS DE MÉDICOS.
void iniciaFilas(p_fila filas[]){
    filas[0] = criarFila(CLINICO_GERAL); filas[1] = criarFila(RADIOLOGISTA);
    filas[2] = criarFila(ENFEREMEIRO); filas[3] = criarFila(OTORRINO);
    filas[4] = criarFila(PNEUMOLOGISTA); filas[5] = criarFila(DERMATOLOGISTA);
    filas[6] = criarFila(NEUROLOGISTA); filas[7] = criarFila(ONCOLOGISTA);
    filas[8] = criarFila(PSIQUIATRA);
}

// CRIA UMA CÓPIA DAS CONSULTAS PARA ATRIBUI-LA AO PACIENTE. 
// RETORNA UMA NOVA LISTA DE CONSULTAS.
p_consultas copiarConsultas(p_consultas consultas) {
    p_consultas novaLista;

    if(consultas == NULL)
        return NULL;

    novaLista = malloc(sizeof(Consultas));
    novaLista->especialidade = consultas->especialidade;
    novaLista->prox = copiarConsultas(consultas->prox);

    return novaLista;
}

// FUNÇÃO PARA CRIAR UM NOVO PACIENTE E ATRIBUI-LO A LISTA DE PACIENTES DO HOSPITAL.
// RETORNA A NOVA LISTA DE PACIENTES COM O NOVO PACIENTE JÁ INSERIDO.
p_lstpacientes adicionarPacientes(p_lstpacientes paciente, int tipoAtendimento, char *nome, p_consultas consultas) {
    Pacientes novoPaciente;
    p_lstpacientes novaLstPaciente;

    novaLstPaciente = malloc(sizeof(ListaPacientes));
    novoPaciente.nome = malloc(MAX_NOME * sizeof(char));
    
    if(novaLstPaciente == NULL || novoPaciente.nome == NULL)
        exit(1);

    novoPaciente.nome = strcpy(novoPaciente.nome, nome);
    novoPaciente.tipoAtendimento = tipoAtendimento;
    novoPaciente.consultasPaciente = copiarConsultas(consultas); 
    novoPaciente.tempoAtendimento = 0;
    novoPaciente.statusAtendimento = 0;

    novaLstPaciente->paciente = novoPaciente;
    novaLstPaciente->prox = paciente;

    return novaLstPaciente;
}

// ADICIONA UMA NOVA CONSULTA (IDENTIFICADA POR UM CÓDIGO DE 1-9) A LISTA DE CONSULTAS PASSADA.
// RETORNA A NOVA LISTA COM A NOVA CONSULTA AGENDADA.
p_consultas adicionarConsulta(p_consultas consultas, int especialidade) {
    p_consultas novaConsulta;

    novaConsulta = malloc(sizeof(Consultas));

    if(novaConsulta == NULL)
        exit(1);

    novaConsulta->especialidade = especialidade;
    novaConsulta->prox = consultas;
    return novaConsulta;
}

// LIBERA A MEMÓRIA ALOCADA POR UMA LISTA DE CONSULTAS.
void destruirConsultas(p_consultas consultas){
    if (consultas != NULL) {
        destruirConsultas(consultas->prox);
        free(consultas);
    }
}

// INVERTE A LISTA DE CONSULTAS PARA QUE ELA VÁ DA 1º CONSULTA ATÉ A ÚLTIMA.
// RETORNA A LISTA NA ORDEM CORRETA.
p_consultas inverteConsultas(p_consultas consultas) {
    p_consultas atual, ant, invertida = NULL;
    atual = consultas;
    
    while (atual != NULL) {
        ant = atual;
        atual = ant->prox;
        ant->prox = invertida;
        invertida = ant;
    }

    return invertida;
}

// LISTA PARA REMOVER UMA CONSULTA QUE JÁ TENHA SIDO REALIZADA PELO PACIENTE.
// DEVOLVE A LISTA SEM ESSA CONSULTA.
p_consultas removeConsultas(p_consultas consultas) {
    if(consultas->prox == NULL){
        free(consultas);
        return NULL;
    }

    p_consultas novasConsultas = consultas;
    novasConsultas = novasConsultas->prox;
    free(consultas);

    return novasConsultas;
}

// LIBERA A MEMÓRIA ALOCADA POR UMA LISTA DE PACIENTES.
void destruirPacientes(p_lstpacientes pacientes){
    if (pacientes != NULL) {
        destruirPacientes(pacientes->prox);
        free(pacientes);
    }
}

// INVERTE A LISTA DE PACIENTES PARA QUE ELA FIQUE NA ORDEM DE CHEGADA.
// RETORNA A LISTA NA ORDEM DE CHEGADA DOS PACIENTES.
p_lstpacientes invertePacientes(p_lstpacientes pacientes) {
    p_lstpacientes atual, ant, invertida = NULL;
    atual = pacientes;
    
    while (atual != NULL) {
        ant = atual;
        atual = ant->prox;
        ant->prox = invertida;
        invertida = ant;
    }

    return invertida;
}

// INSERE NO COMEÇO DA FILA PACIENTES QUE SÃO PREFERENCIAIS.
void inserePreferencial(p_fila fila, p_pacientes paciente){
    p_consultorios novoPreferencial = malloc(sizeof(Consultorios));

    novoPreferencial->pacientesFila = paciente;
    novoPreferencial->ant = NULL;
    novoPreferencial->prox = fila->inicio;
    novoPreferencial->pacientesFila->statusAtendimento = 1; // PACIENTE COM ATENDIMENTO.
    
    if(fila->inicio == NULL)
        fila->fim = novoPreferencial;
    else
        fila->inicio->ant = novoPreferencial;
    
    fila->inicio = novoPreferencial;
}

// INSERE NA ORDEM NORMAL (DE CHEGADA) PACIENTES QUE NÃO TEM PREFERÊNCIA.
void insereNormal(p_fila fila, p_pacientes paciente){
    p_consultorios novoNormal = malloc(sizeof(Consultorios));

    novoNormal->pacientesFila = paciente;
    novoNormal->prox = NULL;
    novoNormal->ant = fila->fim;
    novoNormal->pacientesFila->statusAtendimento = 1; // PACIENTE COM ATENDIMENTO.
    
    if(fila->fim == NULL)
        fila->inicio = novoNormal;
    else
        fila->fim->prox = novoNormal;
    
    fila->fim = novoNormal;
}

// REMOVE DA FILA TODOS OS PACIENTES QUE ACABARAM AS CONSULTAS.
void removeInicio(p_fila fila){
    p_consultorios pessoaRemovida = fila->inicio; 

    fila->inicio = pessoaRemovida->prox;
    pessoaRemovida->pacientesFila->statusAtendimento = 0; // PACIENTE SEM ATENDIMENTO.

    if(fila->inicio == NULL)
        fila->fim = NULL;
    else
        fila->inicio->ant = NULL;

    free(pessoaRemovida); 
}

// CONTABILIZA MAIS 10 MIN DE ESPERA PARA OS PACIENTES QUE PERMANECEM EM ALGUMA FILA.
void contabilizaHorario(p_consultorios pacientes){
    while(pacientes != NULL){
        pacientes->pacientesFila->tempoAtendimento += 10;
        pacientes = pacientes->prox;
    }
}

// FUNÇÃO PARA REALIZAÇÃO DAS CONSULTAS SÃO LEVADOS EM CONSIDERÇÃO:
// ESTADO ATUAL DA FILA (TAMANHO) -- QUANTIDADE DE MÉDICOS QUE PODEM ATENDER POR VEZ.
void realizaConsultas(p_fila fila, int qtdMedicos){
    for(int x = 0; x < qtdMedicos && fila->inicio != NULL; x++){
        fila->inicio->pacientesFila->tempoAtendimento += 10; // TEMPO DA CONSULTA.
        removeInicio(fila);
    }

    contabilizaHorario(fila->inicio); // TEMPO DA ESPERA.
}

// LÊ E ALOCA O NOME DO PACIENTE.
void guardaNome(char *nome, char caracter){
    int contador = 0;

    while (caracter != '"'){
        nome[contador] = caracter;
        scanf("%c", &caracter);
        contador++;
    }
}

// LÊ AS CONSULTAS DIGITADAS E AS TRASNFORMAM EM UMA LISTA DE CONSULTAS.
// DEVOLVE A LISTA 'MONTADA'. 
p_consultas guardaConsultas(p_consultas consultas, char caracter){
    do{
        consultas = adicionarConsulta(consultas, (caracter - '0'));
            
        scanf("%c", &caracter); 
            
        if(caracter != '\n')
            scanf("%c", &caracter);
    }while(caracter != '\n');

    return consultas;
}

// GERENCIA A FILA:
// DIRECIONANDO OS PACIENTES PRAS RESPECTIVAS FILAS E GERENCIANDO QUEM TERMINA OU NÃO UMA CONSULTA.
// RETORNA O NÚMERO DE PACIENTES QUE JÁ TIVERAM 100% DAS CONSULTAS FEITAS.
int gerenciaFila(p_lstpacientes saveList, p_fila filas[], int qtdPacientes, int pacientesTermino){
    int hora = 0, minuto = 0;

    for(int x = 0; saveList != NULL ; x++){ // PERCORRE TODOS OS PACIENTES:
        if(saveList->paciente.statusAtendimento != 1 && 
            saveList->paciente.consultasPaciente != NULL && saveList->paciente.tipoAtendimento == 0){
            // SE O PACIENTE NÃO ESTIVER SENDO ATENDIDO, TIVER CONSULTAS E NÃO É PREFERENCIAL:
            
            insereNormal(filas[saveList->paciente.consultasPaciente->especialidade - 1], &saveList->paciente);
            saveList->paciente.consultasPaciente = removeConsultas(saveList->paciente.consultasPaciente);  
        }
        else if(saveList->paciente.statusAtendimento != 1 && 
                saveList->paciente.consultasPaciente != NULL && saveList->paciente.tipoAtendimento == 1){
            // SE O PACIENTE NÃO ESTIVER SENDO ATENDIDO, TIVER CONSULTAS E É PREFERENCIAL:
            inserePreferencial(filas[saveList->paciente.consultasPaciente->especialidade - 1], &saveList->paciente);
            saveList->paciente.consultasPaciente = removeConsultas(saveList->paciente.consultasPaciente);   
        }
        else if(saveList->paciente.consultasPaciente == NULL && saveList->paciente.statusAtendimento == 0){
            // CASO AS CONSULTAS DO PACIENTE TENHAM ACABADO IMPRIME SUA SAÍDA:
            pacientesTermino++;
            hora = 8 + (saveList->paciente.tempoAtendimento / 60); 
            minuto = (saveList->paciente.tempoAtendimento % 60);

            if(hora < 10)
                printf("0");
            printf("%d:", hora);

            if(minuto < 10)
                printf("0");
            printf("%d %s", minuto, saveList->paciente.nome);  

            saveList->paciente.statusAtendimento = -1; // STATUS PARA O PACIENTE QUE DEIXA DE SER VERIFICADO.
            printf("\n");
        }
    
            saveList = saveList->prox;
        }

        // REALIZA O GERENCIAMENTO DAS 9 FILAS.
        for(int consultorios = 0; pacientesTermino != qtdPacientes && consultorios < CONSULTORIOS; consultorios++){
            realizaConsultas(filas[consultorios], filas[consultorios]->qtdMedicos);
        }

    return pacientesTermino; 
}

// LIMPA ("DEVOLVE") OS ESPAÇOS DE MEMÓRIA ALOCADOS.
void limparMemoria(char *nome, p_consultas consultas, p_lstpacientes listaPacientes, p_fila filas[]){
    for(int x = 0; x < CONSULTORIOS; x++)
        free(filas[x]);

    for(p_lstpacientes x = listaPacientes; x != NULL; x = x->prox){
        destruirConsultas(x->paciente.consultasPaciente);
        free(x->paciente.nome);
    }

    free(nome);   
    destruirConsultas(consultas);
    destruirPacientes(listaPacientes);
}

int main(){
    int tpAtendimento = -1, qtdPacientes = 0, pacientesTermino = 0;
    char caracter; char *nome = malloc(MAX_NOME * sizeof(char));
    p_lstpacientes listaPacientes = criarPaciente(); 
    p_consultas consultas = criarConsulta();
    p_fila filas[CONSULTORIOS]; 

    if(nome == NULL) 
        exit(1);

    // OS SCANFS() DA MAIN SERVEM, DE MODO GERAL, PARA 'PULAR' ESPAÇOS.

    scanf("%c", &caracter);
    scanf("%c", &caracter);

    while(1){ // ENQUANTO EXISTIR CARACTERES PRA LER (SCANF() != EOF): 
        for(int x = 0; x < 50; x++)
            nome[x] = '\0';

        guardaNome(nome, caracter);
 
        scanf("%c", &caracter);
        scanf("%c", &caracter);
    
        // TIPO DE ATENDIMENTO: normal = 0 e preferencial = 1.
        tpAtendimento = caracter != 'n';   
        
        do{
            scanf("%c", &caracter);
        }while(caracter != ' ');
        
        scanf("%c", &caracter);

        consultas = guardaConsultas(consultas, caracter);

        listaPacientes = adicionarPacientes(listaPacientes, tpAtendimento, nome, consultas);
        listaPacientes->paciente.consultasPaciente = inverteConsultas(listaPacientes->paciente.consultasPaciente);
        
        qtdPacientes++;

        if(scanf("%c", &caracter) == EOF) break; 

        scanf("%c", &caracter);
        destruirConsultas(consultas);
        consultas = criarConsulta();
    }

    iniciaFilas(filas);
    listaPacientes = invertePacientes(listaPacientes);

    while(pacientesTermino != qtdPacientes){ 
        // ENQUANTO EXISTIREM PACIENTES COM CONSULTAS A SEREM REALIZADAS.
        // CONTINUA O GERENCIAMENTO DA FILA.      
        pacientesTermino = gerenciaFila(listaPacientes, filas, qtdPacientes, pacientesTermino);     
    }

    limparMemoria(nome, consultas, listaPacientes, filas);

    return 0;
}