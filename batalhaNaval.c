#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro
void InicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se o posicionamento do navio é válido (incluindo diagonal)
int PosicaoValida(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int direcao) {
    if (direcao == 0) { // Horizontal
        if (coluna + tamanho > TAMANHO) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] == NAVIO) return 0;
        }
    } else if (direcao == 1) { // Vertical
        if (linha + tamanho > TAMANHO) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] == NAVIO) return 0;
        }
    } else if (direcao == 2) { // Diagonal superior direita
        if (linha - tamanho + 1 < 0 || coluna + tamanho > TAMANHO) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha - i][coluna + i] == NAVIO) return 0;
        }
    } else if (direcao == 3) { // Diagonal inferior direita
        if (linha + tamanho > TAMANHO || coluna + tamanho > TAMANHO) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna + i] == NAVIO) return 0;
        }
    } else if (direcao == 4) { // Diagonal superior esquerda
        if (linha - tamanho + 1 < 0 || coluna - tamanho + 1 < 0) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha - i][coluna - i] == NAVIO) return 0;
        }
    } else if (direcao == 5) { // Diagonal inferior esquerda
        if (linha + tamanho > TAMANHO || coluna - tamanho + 1 < 0) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna - i] == NAVIO) return 0;
        }
    }
    return 1;
}

// Função para posicionar um navio
void PosicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int direcao) {
    if (PosicaoValida(tabuleiro, linha, coluna, tamanho, direcao)) {
        for (int i = 0; i < tamanho; i++) {
            if (direcao == 0) tabuleiro[linha][coluna + i] = NAVIO;       // Horizontal
            else if (direcao == 1) tabuleiro[linha + i][coluna] = NAVIO;  // Vertical
            else if (direcao == 2) tabuleiro[linha - i][coluna + i] = NAVIO; // Diagonal superior direita
            else if (direcao == 3) tabuleiro[linha + i][coluna + i] = NAVIO; // Diagonal inferior direita
            else if (direcao == 4) tabuleiro[linha - i][coluna - i] = NAVIO; // Diagonal superior esquerda
            else if (direcao == 5) tabuleiro[linha + i][coluna - i] = NAVIO; // Diagonal inferior esquerda
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

// Função para criar a matriz de habilidade em cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i >= centro && j >= centro - (i - centro) && j <= centro + (i - centro)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int centroHabilidade = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTabuleiro = linhaOrigem - centroHabilidade + i;
                int colunaTabuleiro = colunaOrigem - centroHabilidade + j;
                if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO && colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = 5; // Marca como área afetada
                }
            }
        }
    }
}


int main() {
    int tabuleiro[TAMANHO][TAMANHO], opcao;
    int habilidadeCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa o tabuleiro com água
    InicializarTabuleiro(tabuleiro);

    // Posiciona três navios, incluindo um na diagonal
    PosicionarNavio(tabuleiro, 2, 3, 3, 1);  // Navio horizontal de 3 posições
    PosicionarNavio(tabuleiro, 6, 6, 3, 0);  // Navio vertical de 3 posições
    PosicionarNavio(tabuleiro, 7, 2, 3, 3); // Navio Diagonal inferior direita
    PosicionarNavio(tabuleiro, 5, 7, 3, 4); // Navio Diagonal superior esquerda

    // Exibe o tabuleiro atualizado
    ExibirTabuleiro(tabuleiro);

    printf("\nEscolha a habilidade especial para aplicar no tabuleiro:\n");
    printf("(1) Cone\n");
    printf("(2) Cruz\n");
    printf("(3) Octaedro\n");

    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            // Habilidade em Cone
            criarHabilidadeCone(habilidadeCone);
            int linhaOrigemCone = 2;
            int colunaOrigemCone = 2;
            aplicarHabilidade(tabuleiro, habilidadeCone, linhaOrigemCone, colunaOrigemCone);
            printf("Tabuleiro com Habilidade em Cone (origem: %d,%d):\n", linhaOrigemCone, colunaOrigemCone);
            break;
        case 2:
            // Habilidade em Cruz
            criarHabilidadeCruz(habilidadeCruz);
            int linhaOrigemCruz = 4;
            int colunaOrigemCruz = 5;
            aplicarHabilidade(tabuleiro, habilidadeCruz, linhaOrigemCruz, colunaOrigemCruz);
            printf("Tabuleiro com Habilidade em Cruz (origem: %d,%d):\n", linhaOrigemCruz, colunaOrigemCruz);
            break;
        case 3:
            // Habilidade em Octaedro
            criarHabilidadeOctaedro(habilidadeOctaedro);
            int linhaOrigemOctaedro = 7;
            int colunaOrigemOctaedro = 3;
            aplicarHabilidade(tabuleiro, habilidadeOctaedro, linhaOrigemOctaedro, colunaOrigemOctaedro);
            printf("Tabuleiro com Habilidade em Octaedro (origem: %d,%d):\n", linhaOrigemOctaedro, colunaOrigemOctaedro);    
            break;
        default:
            printf("Opção inválida!\n");
            return 0;
    }
    

    ExibirTabuleiro(tabuleiro);


    return 0;
}
