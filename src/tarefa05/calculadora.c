 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB05: CALCULADORA PARA NÚMEROS GIGANTES UTILIZANDO A ESTRUTURA DE LISTAS LIGADAS.

#include <stdio.h>
#include <stdlib.h>
#define NUM_LISTAS 3 

// LISTA LIGADA PARA REPRESENTAÇÃO DOS DIGITOS.
typedef struct Digitos{
    int digito;
    struct Digitos *prox;
} Digitos;

typedef struct Digitos * p_digitos;

// INICIALIZA UMA NOVA LISTA VAZIA.
p_digitos criarListas(){
    return NULL;
}

// CRIA AS 3 LISTAS QUE SERÃO UTILIZADAS NO PROGRAMA.
void iniciaListas(p_digitos listas[]){
    listas[0] = criarListas(); // NÚMERO 1.
    listas[1] = criarListas(); // NÚMERO 2.
    listas[2] = criarListas(); // RESULTADO.
}

// DESTROI TODA A LISTA.
void destruirListas(p_digitos lista){
    if (lista != NULL) {
        destruirListas(lista->prox);
        free(lista);
    }
}

// DESTROI AS 3 LISTAS QUE O CÓDIGO UTILIZA.
void destroiListas(p_digitos listas[]){
    destruirListas(listas[0]);
    destruirListas(listas[1]);
    destruirListas(listas[2]);
}

// CRIA UM NOVO ELEMENTO EM ALGUMA DAS LISTAS LIGADAS.
// RETORNA O NOVO 'ELEMENTO' ALOCADO.
p_digitos adicionarElemento(p_digitos lista, int algarismo) {
    p_digitos novoAlgarismo;

    novoAlgarismo = malloc(sizeof(Digitos));

    if(novoAlgarismo == NULL)
        exit(1);

    novoAlgarismo->digito = algarismo;
    novoAlgarismo->prox = lista;
    return novoAlgarismo;
}

// INVERTE A LISTA QUE É PASSADA COMO PARÂMETRO.
// RETORNA UMA NOVA LISTA, PORÉM INVERTIDA.
p_digitos inverteLista(p_digitos lista) {
    p_digitos atual, ant, invertida = NULL;
    atual = lista;
    
    while (atual != NULL) {
        ant = atual;
        atual = ant->prox;
        ant->prox = invertida;
        invertida = ant;
    }

    return invertida;
}

// IMPRIME TODOS OS ELENTOS DA LISTA PASSADA.
void imprimeElementos(p_digitos lista) {
    p_digitos atual;
    
    for (atual = lista; atual != NULL; atual = atual->prox)
        printf("%d", atual->digito);
}

// REALIZA A SOMA DE DOIS NÚMEROS DADOS.
// RETORNA UMA LISTA - QUE REPRESENTA A SOMA DOS VALORES DADOS.
p_digitos somaNumeros(p_digitos primeiroNumero, p_digitos segundoNumero, p_digitos resultado){
    int sobra = 0, conta = 0;

    // ENQUANTO AINDA EXISITEM ALGARISMOS É NECESSÁRIO FAZER A SOMA: 
    while(primeiroNumero != NULL || segundoNumero != NULL){
        // CASO O 1º TERMINE, MAS O 2º NÃO, ENTÃO, A SOMA É APENAS O DÍGITO DO 2º NÚMERO.
        if(primeiroNumero == NULL && segundoNumero != NULL){      
            conta = segundoNumero->digito;
            segundoNumero = segundoNumero->prox;
        }
        else if(segundoNumero == NULL && primeiroNumero != NULL){
            // ANALOGAMENTE CASO O 2º TERMINE E O 1º NÃO, A SOMA É APENAS O DÍGITO DO 1º NÚMERO.
            conta = primeiroNumero->digito;
            primeiroNumero = primeiroNumero->prox;
        }
        else{
            // CASO OS DOIS NÃO SEJAM NULL, FAZEMOS A SOMA DE SEUS DÍGITOS.
            conta = primeiroNumero->digito + segundoNumero->digito;
            primeiroNumero = primeiroNumero->prox;
            segundoNumero = segundoNumero->prox;
        }
        
        resultado = adicionarElemento(resultado, ((conta + sobra) % 10));
        sobra = (conta + sobra) / 10; // SOBRA = O QUE EXCEDE OS ALGARISMOS DE [0-9].
    }
    
    if(sobra != 0) // CASO O LAÇO TERMINE, MAS AINDA SEJA NECESSÁRIO ADICIONAR UM NÚMERO:
        resultado = adicionarElemento(resultado, sobra);

    return resultado; 
}

// DEFINE QUAL É DAS LISTAS (NÚMEROS) É MAIOR E QUAL É MENOR. 
void max_min(p_digitos listas[], int *max, int *min){
    *max = *min = 0;
    p_digitos primeiroNumero = listas[0], segundoNumero = listas[1]; 

    while(primeiroNumero != NULL || segundoNumero != NULL){
        if(primeiroNumero == NULL && segundoNumero != NULL){      
            *max = 1; *min = 0;
            segundoNumero = segundoNumero->prox;
            break;
        }
        else if(segundoNumero == NULL && primeiroNumero != NULL){
            *max = 0; *min = 1;
            primeiroNumero = primeiroNumero->prox;
            break;
        }
        else if(primeiroNumero->digito > segundoNumero->digito){
            *max = 0; *min = 1;
            primeiroNumero = primeiroNumero->prox;
            segundoNumero = segundoNumero->prox;
        }
        else if(segundoNumero->digito > primeiroNumero->digito){
           *max = 1; *min = 0;
            primeiroNumero = primeiroNumero->prox;
            segundoNumero = segundoNumero->prox; 
        }
        else{
            primeiroNumero = primeiroNumero->prox;
            segundoNumero = segundoNumero->prox; 
        }
    }
}

// FUNÇÃO PARA SUBTRAIR DOIS NÚMEROS.
// A FUNÇÃO TRABALHA COM UM PONTEIRO (*) PARA O RESULTADO, POR ISSO NÃO HÁ RETORNO. 
void subtrairNumeros(p_digitos listas[]){
    int sobra = 0, conta = 0, maximo = 0, minimo = 0, tamanhoNumero = 0, listaCheia = 0;
    p_digitos primeiroNumero, segundoNumero, saveList; 
    max_min(listas, &maximo, &minimo);

    // DEFINE QUAL NÚMERO É MAIOR E QUAL É O MENOR (A ORDEM NA SUBTRAÇÃO FAZ DIFERENÇA!).
    primeiroNumero = listas[maximo]; segundoNumero = listas[minimo];

    while(primeiroNumero != NULL || segundoNumero != NULL){
        if(segundoNumero == NULL && primeiroNumero != NULL){
            // CASO O NÚMERO MAIOR NÃO TENHA ACABADO, MAS O MENOR SIM:

            if(sobra == 0)
                // NÃO HÁ 'RESTOS' NA SUBTRAÇÃO, POR ISSO O RESULTADO É APENAS O DÍGITO.
                conta = primeiroNumero->digito;
            else{
                // CASO CONTRARIO, 'DESCONTAMOS' DO DÍGITO ATUAL -1.
                conta = primeiroNumero->digito - 1;

                // SE O RESULTADO FOR >= 0 NÃO HÁ PORQUÊ CONTINUAR FAZENDO DESCONTOS.
                if(conta >= 0)
                    sobra = 0;
            }
            
            primeiroNumero = primeiroNumero->prox;
        }
        else{
            if(sobra != 0){
                primeiroNumero->digito = primeiroNumero->digito - 1;
                sobra = 0;
            }

            conta = primeiroNumero->digito - segundoNumero->digito;
            
            // CASO A CONTA SEJA NEGATIVA, PRECISAMOS SOMAR 10 A ELA.
            // POSTERIORMENTE FAREMOS OS 'DESCONTOS' (-1) NOS OUTROS DÍGITOS.
            if(conta < 0)
                sobra += 10;

            primeiroNumero = primeiroNumero->prox;
            segundoNumero = segundoNumero->prox;
        }

        tamanhoNumero++;

        // CASO O NÚMERO MAIOR ACABE E O RESULTADO SEJA 0 E O NÚMERO TENHA TAMANHO >1.
        // O ALGARISMO '0' NÃO PRECISA SER ADICIONADO. (EX: 08 DEVE SER APENAS 8). 
        if(primeiroNumero == NULL && conta == 0 && tamanhoNumero > 1) 
            break;

        listas[2] = adicionarElemento(listas[2], ((conta + sobra)));
    }

    saveList = listas[2];

    // VERIFICA SE ALGUM ELEMENTO DO NÚMERO É != 0.
    while(saveList != NULL){
        if(saveList->digito != 0){
            listaCheia = 1;
            break;
        }

        saveList = saveList->prox;
    }

    p_digitos aux = NULL;
    // SE TODOS OS ELEMENTOS FOREM 0, ENTÃO DESTROI A LISTA E A RECRIA CONTENDO APENAS '0'. 
    if(!listaCheia){
        destruirListas(listas[2]);
        listas[2] = criarListas();
        listas[2] = adicionarElemento(listas[2], 0);
    }
    else{
        // CASO CONTRÁRIO REMOVE APENAS OS 0 A ESQUERDA.
        while(listas[2]->digito == 0 || listas[2] == NULL){
            aux = listas[2]; 
            listas[2] = listas[2]->prox;
            free(aux);
        }
    }
}

// FUNÇÃO RECURSIVA PARA MULTIPLICAR DOS NÚMEROS GRANDES.
p_digitos multiplicacaoNumeros(p_digitos primeiroNumero, p_digitos segundoNumero, p_digitos atual, p_digitos soma, int resto, int contador){
    p_digitos resultado = NULL;
    int conta = 0;
    
    // CASO BASE: UM DOS DÍGITOS ACABOU.
    if(primeiroNumero == NULL){
        // ADICIONA '0' AO NÚMERO ATUAL, CASO SEJA NECESSÁRIO PARA REALIZAR A SOMA.
        for(int x = 0; x < contador; x++){
            // O DÍGITO PRECISA SER INVERTIDO UMA VEZ, PARA QUE OS '0' SEJAM ALOCADOS NO FINAL DA LISTA.
            if(x == 0)
                atual = inverteLista(atual);
           
            atual = adicionarElemento(atual, 0);
        }
        
        // AO REALIZAR A SOMA PELA 1º VEZ O RESULTADO VEM NA ORDEM CORRETA.
        // PORTANTO, COMO NÃO ACABAMOS AS CONTAS AINDA, PRECISAMOS INVERTER O RESULTADO TAMBÉM!
        if(soma != NULL && contador > 1)
            soma = inverteLista(soma);
   
        resultado = somaNumeros(soma, atual, NULL);
        destruirListas(soma); 
    
        destruirListas(atual);
        return resultado; 
    }

    conta = primeiroNumero->digito * segundoNumero->digito; 
    atual = adicionarElemento(atual, (conta + resto) % 10); 
    resto = (conta + resto) / 10; 

    // ADICIONA UM ÚLTIMO ELEMENTO QUE PODE TER SOBRADO NO RESTO.    
    if(primeiroNumero->prox == NULL && resto != 0) 
        atual = adicionarElemento(atual, resto);

    return multiplicacaoNumeros(primeiroNumero->prox, segundoNumero, atual, soma, resto, contador); 
}

// CHAMA E GERENCIA O CHAMADO DA FUNÇÃO RECURSIVA DA MULTIPLICAÇÃO.
p_digitos multiplica(p_digitos primeiroNumero, p_digitos segundoNumero){
    p_digitos atual = NULL, saveList;
    int contador = 0, listaCheia = 0; 

    // ENQUANTO EXISIR ALGARISMOS PARA MULTIPLICAR CHAMA A FUNÇÃO.
    while(segundoNumero != NULL){
        atual = multiplicacaoNumeros(primeiroNumero, segundoNumero, NULL, atual, 0, contador);
        contador++;
        segundoNumero = segundoNumero->prox;
    }

    // COMO NA FUNÇÃO RECURSIVA INVERTEMOS O RESULTADO, PRECISAMOS 'VOLTA-LO' A FORMA CORRETA.
    if(contador == 1)
        atual = inverteLista(atual);
    
    saveList = atual;

    // ANALOGAMENTE A SUBTRAÇÃO VERIFICA SE EXISTE ALGUM DÍGITO DIFERENTE DE 0.
    while(saveList != NULL){
        if(saveList->digito != 0){
            listaCheia = 1;
            break;
        }

        saveList = saveList->prox;
    }

    // EVITA A OCORRÊNCIA DE EX: 0000.
    if(!listaCheia){
        destruirListas(atual);
        atual = criarListas();
        atual = adicionarElemento(atual, 0);
    }

    return atual;
}

// FUNÇÃO PARA RECEBER OS NÚMEROS A SEREM OPERADOS E ALOCA-LOS NAS RESPECTIVAS LISTAS.
void preencheNumeros(p_digitos listas[]){
    char numeros;
    int x = 0;

    scanf("%c", &numeros);

    do{
        if(numeros == ' ')
            x++;
        else{
            listas[x] = adicionarElemento(listas[x], numeros - '0');
        }
        
        scanf("%c", &numeros);
    }while(numeros != '\n');
}

// VERIFICA QUAL É A OPERAÇÃO QUE O USUÁRIO DESEJA REALIZAR E DIRECIONA OS NÚMEROS PARA ELA.
void realizaOperacao(p_digitos listas[], char operacao){
    if(operacao == '+'){
        listas[2] = somaNumeros(listas[0], listas[1], listas[2]);
    }
    else if(operacao == '-'){
        subtrairNumeros(listas);
    }
    else if(operacao == '*'){
        listas[2] = multiplica(listas[0], listas[1]);
    }

    imprimeElementos(listas[2]);
}

int main(){
    int numOperacoes; 
    char operacao; 
    p_digitos listas[NUM_LISTAS];

    iniciaListas(listas); 

    scanf("%d ", &numOperacoes);  

    // REALIZA AS 'N' OPERAÇÕES DESEJADAS.
    while(numOperacoes > 0){
        scanf("%c ", &operacao);
        
        preencheNumeros(listas);

        realizaOperacao(listas, operacao);        

        printf("\n");
        // "REINICIA" AS LISTAS PARA QUE POSSAM SER REUTILIZADAS.
        destroiListas(listas);
        iniciaListas(listas);
        
        numOperacoes--;
    }
  
    destroiListas(listas);

    return 0;
}