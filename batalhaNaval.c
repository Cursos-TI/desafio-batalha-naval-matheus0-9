#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro 10x10
#define TAM_NAVIO 3  // Cada navio ocupa 3 posições

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // 1. Inicializar o tabuleiro com 0 (água)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Coordenadas iniciais dos navios
    // Dois navios "retos" (horizontal e vertical)
    int linha_navio1 = 2, coluna_navio1 = 1; // horizontal
    int linha_navio2 = 5, coluna_navio2 = 7; // vertical

    // Dois navios diagonais
    int linha_navio3 = 0, coluna_navio3 = 0; // diagonal principal (↘)
    int linha_navio4 = 6, coluna_navio4 = 9; // diagonal secundária (↙)

    // 3. Posicionar o navio 1 (horizontal)
    if (coluna_navio1 + TAM_NAVIO <= TAM) {
        for (j = coluna_navio1; j < coluna_navio1 + TAM_NAVIO; j++) {
            if (tabuleiro[linha_navio1][j] == 0)
                tabuleiro[linha_navio1][j] = 3;
            else
                printf("⚠️ Sobreposição detectada em (%d, %d)\n", linha_navio1, j);
        }
    }

    // 4. Posicionar o navio 2 (vertical)
    if (linha_navio2 + TAM_NAVIO <= TAM) {
        for (i = linha_navio2; i < linha_navio2 + TAM_NAVIO; i++) {
            if (tabuleiro[i][coluna_navio2] == 0)
                tabuleiro[i][coluna_navio2] = 3;
            else
                printf("⚠️ Sobreposição detectada em (%d, %d)\n", i, coluna_navio2);
        }
    }

    // 5. Posicionar o navio 3 (diagonal principal ↘)
    if (linha_navio3 + TAM_NAVIO <= TAM && coluna_navio3 + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            int linha = linha_navio3 + i;
            int coluna = coluna_navio3 + i;
            if (tabuleiro[linha][coluna] == 0)
                tabuleiro[linha][coluna] = 3;
            else
                printf("⚠️ Sobreposição detectada em (%d, %d)\n", linha, coluna);
        }
    }

    // 6. Posicionar o navio 4 (diagonal secundária ↙)
    if (linha_navio4 + TAM_NAVIO <= TAM && coluna_navio4 - (TAM_NAVIO - 1) >= 0) {
        for (i = 0; i < TAM_NAVIO; i++) {
            int linha = linha_navio4 + i;
            int coluna = coluna_navio4 - i;
            if (tabuleiro[linha][coluna] == 0)
                tabuleiro[linha][coluna] = 3;
            else
                printf("⚠️ Sobreposição detectada em (%d, %d)\n", linha, coluna);
        }
    }

    // 7. Exibir o tabuleiro no console
    printf("\n=== TABULEIRO BATALHA NAVAL (NÍVEL INTERMEDIÁRIO) ===\n\n");

    // Cabeçalho de colunas
    printf("   ");
    for (j = 0; j < TAM; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Imprimir o tabuleiro linha por linha
    for (i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
