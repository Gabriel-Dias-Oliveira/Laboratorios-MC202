 // GABRIEL DIAS DE OLIVEIRA. RA: 176495.
 // LAB04: SOLUCIONADOR DE 'CAÇA-PALAVRAS' UTILIZANDO BACKTRACKING.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ESTRUTURA PARA ARMAZENAR AS PALAVRAS A SEREM BUSCADAS
typedef struct palavras{
    char *palavra;
} Palavras;

// A FUNÇÃO CRIA O 'TABULEIRO' DE LETRAS A SEREM ANALISADAS.
// A PARTIR DE UM CHAR ** E SABENDO A QUANTIDADE DE LINHAS E COLUNAS, ALOCA O ESPAÇO NECESSÁRIO. 
void criaTabuleiro(char **tabuleiro, int numLinhas, int numColunas){
    for(int i = 0; i < numLinhas; i++)
        tabuleiro[i] = malloc(numColunas * sizeof(char));
}

// A FUNÇÃO ARMAZENA ESPAÇO PARA SALVAR AS PALAVRAS QUE IRÃO SER BUSCADAS.
// RECEBE COMO PARÂMETTRO A QUANTIDADE DE PALAVRAS E UMA STRUCT.
void criaPistas(Palavras *pistas, int numPalavras){
    for(int x = 0; x < numPalavras; x++)
        pistas[x].palavra = malloc(21 * sizeof(char));
}

// LIBERA TODOS OS ESPAÇOS QUE EM ALGUM MOMENTO FORAM ALOCADOS EVITANDO VAZAMENTOS DE MEMÓRIA!
void freeConteudo(char **tabuleiro, Palavras *pistas, int numLinhas, int numPalavras){
    for(int i = 0; i < numLinhas; i++)
        free(tabuleiro[i]);

    for(int i = 0; i < numPalavras; i++)
        free(pistas[i].palavra);

    free(tabuleiro);
    free(pistas);
}

// FUNÇÃO PARA RECEBER AS ENTRADAS DO USUÁRIO:
// RECEBE TANTO A ENTRADA DAS LETRAS DO TABULEIRO COMO AS PALAVRAS QUE DEVEM SER PROCURADAS.
void defineTabuleiroPistas(char **tabuleiro, Palavras *pistas, int numLinhas, int numColunas, int numPalavras){
    for(int i = 0; i < numLinhas; i++) 
        for(int j = 0; j < numColunas; j++)
            scanf(" %c", &tabuleiro[i][j]); // SALVANDO NO TABULEIRO.
    
    for(int x = 0; x < numPalavras; x++)
        scanf(" %s", pistas[x].palavra); // SALVANDO UMA PISTA EM SUA RESPECTIVA STRUCT.
}

// ARMAZENA E DEFINE QUAL O PRÓXIMO MOVIMENTO A SER TENTADO PELA RECURSÃO E BACKTRACKING.
void defineMovimento(int linha, int coluna, int movimento, int *novaLinha, int *novaColuna) {
    /* ESQUERDA, DIREITA, CIMA E BAIXO */
    static int movimentos[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    *novaLinha = linha + movimentos[movimento][0];
    *novaColuna = coluna + movimentos[movimento][1];
}

// FUNÇÃO DA RECURSÃO QUE ANALISA E TENTA ENCONTRAR UMA LETRA EM MEIO AO TABULEIRO.
// RECEBE O TABULEIRO, A PALAVRA, A LINHA/COLUNA ONDE A BUSCA ESTÁ SENDO FEITA
// CONTADOR = QUANTAS LETRAS SÃO COMPATIVEIS COM A PALAVRA. RETORNA 1, SE CONTADOR = TAMANHO DA PALAVRA E 0 CASO CONTRÁRIO 
int buscaLetra(char **tabuleiro, char *palavra, int linha, int coluna, int numLinha, int numColuna, int contador){
    int movimento, novaLinha, novaColuna;
    char guardaCaracter; 
    
    // BASE: CONSEGUIMOS ENCONTRAR TODAS AS LETRAS - RESPEITANDO AS REGRAS - NO TABULEIRO!
    if(contador == (strlen(palavra)))
        return 1;
    
    // ANALISA TODAS AS POSSIBILIDADES DE MOVIMENTO.
    for (movimento = 0; movimento < 4; movimento++) {
        defineMovimento(linha, coluna, movimento, &novaLinha, &novaColuna);
        
        // VERIFICA SE A POSIÇÃO PRA QUAL VAMOS É VÁLIDA:
        // RESPEITA O TAMANHO DO TABULEIRO E SE A LETRA AINDA NÃO FOI USADA (!= '1')
        if((novaLinha >= 0) && (novaLinha < numLinha) && (novaColuna >= 0) && (novaColuna < numColuna)
            && (tabuleiro[novaLinha][novaColuna] == palavra[contador]) && 
            (tabuleiro[novaLinha][novaColuna] != '1')) {
            
            contador++;
            guardaCaracter = tabuleiro[novaLinha][novaColuna];
            tabuleiro[novaLinha][novaColuna] = '1'; // LETRA JÁ USADA.

            if(buscaLetra(tabuleiro, palavra, novaLinha, novaColuna, numLinha, numColuna, contador)){
                tabuleiro[novaLinha][novaColuna] = guardaCaracter; // VOLTA O CARACTER ORIGINAL.
                return 1;
            }
            
            tabuleiro[novaLinha][novaColuna] = guardaCaracter;
            contador--; // "VOLTA" UM MOVIMENTO.
        }
    }
    
    return 0; // SE O CASO BASE NÃO ACONTECER RETORNA 0. 
}

// CONFIGURA E CHAMA A FUNÇÃO DE RECURSÃO.
int realizaBusca(char **tabuleiro, char *palavra, int numLinhas, int numColunas){
    int contador = 0, verificaEncontro = 0, linha = 0, coluna = 0;
    char guardaCaracter; 

    // SE A PALAVRA AINDA NÃO FOI ACHADA E TODAS AS POSIÇÕES NÃO FORAM TESTADAS:
    while (!verificaEncontro && (contador < (numLinhas * numColunas))){        
        // CONTADOR = DEFINE QUAL POSIÇÃO VAI SER DADA COMO ORIGEM DA BUSCA.
        linha = (contador) / (numColunas);
        coluna = (contador) % (numColunas);

        guardaCaracter = tabuleiro[linha][coluna];
        tabuleiro[linha][coluna] = '1'; // 1º POSIÇÃO DEFINIDA COMO USADA

        verificaEncontro = buscaLetra(tabuleiro, palavra, linha, coluna, numLinhas, numColunas, 0);
        tabuleiro[linha][coluna] = guardaCaracter;
        contador++;
    }
    
    return verificaEncontro;
}

// SE A PALAVRA FOI ACHADA IMPRIME "SIM" E CASO CONTRÁRIO "NÃO".
void imprimeResultado(int validacao){
    if(validacao)
        printf("sim\n");
    else
        printf("nao\n");
}

// CHAMA A FUNÇÃO DE REALIZAR BUSCA PARA CADA PALAVRA ARMAZENADA.
void executaBusca(char **tabuleiro, Palavras *pistas, int numLInhas, int numColunas, int numPalavras){
    int recebeValidacao = 0;

    for(int i = 0; i < numPalavras; i++){
        recebeValidacao = realizaBusca(tabuleiro, pistas[i].palavra, numLInhas, numColunas);
        
        imprimeResultado(recebeValidacao);
    }
}

int main(){
    int numLinhas, numColunas, numPalavras;
    char **tabuleiro;
    Palavras *pistas;

    // INFORMAÇÕES BÁSICAS PARA O FUNCIONAMENTO DO CÓDIGO.
    scanf("%d %d %d ", &numLinhas, &numColunas, &numPalavras);

    tabuleiro = malloc(numLinhas * sizeof(char *));
    pistas = malloc(numPalavras * sizeof(Palavras));
    
    criaTabuleiro(tabuleiro, numLinhas, numColunas);
    criaPistas(pistas, numPalavras);

    defineTabuleiroPistas(tabuleiro, pistas, numLinhas, numColunas, numPalavras);

    executaBusca(tabuleiro, pistas, numLinhas, numColunas, numPalavras);

    freeConteudo(tabuleiro, pistas, numLinhas, numPalavras);

    return 0;
}