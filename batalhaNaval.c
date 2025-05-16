#include <stdio.h>

// Desafio Batalha Naval 

// Função para inicializar o tabuleiro
void InicializarTabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}


// Função para verificar se o posicionamento do navio é válido
int PosicaoValida(int tabuleiro[10][10], int linha, int coluna, int tamanho, int direcao) {
    if (direcao == 0) { // Horizontal
        if (coluna + tamanho > 10) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] == 3) return 0;
        }
    } else if (direcao == 1) { // Vertical
        if (linha + tamanho > 10) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] == 3) return 0;
        }
    } else if (direcao == 2) { // Diagonal superior direita
        if (linha - tamanho + 1 < 0 || coluna + tamanho > 10) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha - i][coluna + i] == 3) return 0;
        }
    } else if (direcao == 3) { // Diagonal inferior direita
        if (linha + tamanho > 10 || coluna + tamanho > 10) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna + i] == 3) return 0;
        }
    } else if (direcao == 4) { // Diagonal superior esquerda
        if (linha - tamanho + 1 < 0 || coluna - tamanho + 1 < 0) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha - i][coluna - i] == 3) return 0;
        }
    } else if (direcao == 5) { // Diagonal inferior esquerda
        if (linha + tamanho > 10 || coluna - tamanho + 1 < 0) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna - i] == 3) return 0;
        }
    }
    return 1;
}


// Função para posicionar um navio
void PosicionarNavio(int tabuleiro[10][10], int linha, int coluna, int tamanho, int direcao) {
    if (PosicaoValida(tabuleiro, linha, coluna, tamanho, direcao)) {
        for (int i = 0; i < tamanho; i++) {
            if (direcao == 0) tabuleiro[linha][coluna + i] = 3;       // Horizontal
            else if (direcao == 1) tabuleiro[linha + i][coluna] = 3;  // Vertical
            else if (direcao == 2) tabuleiro[linha - i][coluna + i] = 3; // Diagonal superior direita
            else if (direcao == 3) tabuleiro[linha + i][coluna + i] = 3; // Diagonal inferior direita
            else if (direcao == 4) tabuleiro[linha - i][coluna - i] = 3; // Diagonal superior esquerda
            else if (direcao == 5) tabuleiro[linha + i][coluna - i] = 3; // Diagonal inferior esquerda
        }
    } else {
        printf("Erro: O navio não pode ser posicionado nesta coordenada.\n");
    }
}


// Função para exibir o tabuleiro
void ExibirTabuleiro(int tabuleiro[10][10]) {
    printf("\nTabuleiro:\n");
    printf("    A B C D E F G H I J\n\n");
    for (int i = 0; i < 10; i++) {
        printf("%d  ", i + 1);
        if(i + 1 < 10){
            printf(" ");
        }
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}


int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.
    int tabuleiro[10][10];

    // Inicializa o tabuleiro com água
    InicializarTabuleiro(tabuleiro);

    // Posiciona dois navios (Horizontal = 1, Vertical = 0)
    PosicionarNavio(tabuleiro, 2, 3, 3, 1);  // Navio horizontal de 3 posições
    PosicionarNavio(tabuleiro, 6, 6, 3, 0);  // Navio vertical de 3 posições
    PosicionarNavio(tabuleiro, 7, 2, 3, 3); // Navio Diagonal inferior direita
    PosicionarNavio(tabuleiro, 5, 7, 3, 4); // Navio Diagonal superior esquerda

    // Exibe o tabuleiro atualizado
    ExibirTabuleiro(tabuleiro);

   

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}
