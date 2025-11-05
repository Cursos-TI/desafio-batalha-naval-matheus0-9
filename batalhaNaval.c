#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // 1. Inicializar o tabuleiro com água (0)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Definir coordenadas iniciais dos navios
    int linha_navio1 = 2, coluna_navio1 = 3; // horizontal
    int linha_navio2 = 5, coluna_navio2 = 6; // vertical

    // 3. Validar se cabem no tabuleiro
    if (coluna_navio1 + TAM_NAVIO <= TAM && linha_navio2 + TAM_NAVIO <= TAM) {

        // 4. Posicionar navio 1 (horizontal)
        for (j = coluna_navio1; j < coluna_navio1 + TAM_NAVIO; j++) {
            tabuleiro[linha_navio1][j] = 3;
        }

        // 5. Posicionar navio 2 (vertical)
        for (i = linha_navio2; i < linha_navio2 + TAM_NAVIO; i++) {
            // verificar se já há outro navio ali
            if (tabuleiro[i][coluna_navio2] == 0)
                tabuleiro[i][coluna_navio2] = 3;
            else
                printf("⚠️ Sobreposição detectada na posição (%d, %d)\n", i, coluna_navio2);
        }

    } else {
        printf("Coordenadas inválidas! O navio não cabe no tabuleiro.\n");
        return 1; // encerra o programa
    }

    // 6. Exibir o tabuleiro
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
