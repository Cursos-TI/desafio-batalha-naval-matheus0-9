#include <stdio.h>
#include <stdlib.h>  /* para abs() */

#define TAM 10        /* tamanho do tabuleiro */
#define TAM_NAVIO 3   /* tamanho de cada navio */
#define HAB_SIZE 5    /* tamanho das matrizes de habilidade (5x5) */
#define NAVIO 3
#define AREA 5
#define AGUA 0

int main(void) {
    int tabuleiro[TAM][TAM];
    int cone[HAB_SIZE][HAB_SIZE];
    int cruz[HAB_SIZE][HAB_SIZE];
    int octaedro[HAB_SIZE][HAB_SIZE];

    int i, j;
    int center;
    int radius;

    /* Coordenadas dos navios (fixas) */
    int linha_navio1, coluna_navio1;
    int linha_navio2, coluna_navio2;
    int linha_navio3, coluna_navio3;
    int linha_navio4, coluna_navio4;

    /* Origens das habilidades no tabuleiro (fixas) */
    int origem_cone_row, origem_cone_col;
    int origem_cruz_row, origem_cruz_col;
    int origem_octa_row, origem_octa_col;

    /* inicializa constantes/posições */
    center = HAB_SIZE / 2; /* para HAB_SIZE=5 => center=2 */
    radius = center;       /* radius = 2 para HAB_SIZE=5 */

    linha_navio1 = 2; coluna_navio1 = 1; /* navio horizontal */
    linha_navio2 = 5; coluna_navio2 = 7; /* navio vertical */
    linha_navio3 = 0; coluna_navio3 = 0; /* diag principal */
    linha_navio4 = 6; coluna_navio4 = 9; /* diag secundária */

    origem_cone_row = 1; origem_cone_col = 3;
    origem_cruz_row = 6; origem_cruz_col = 2;
    origem_octa_row = 4; origem_octa_col = 7;

    /* 1) Inicializa tabuleiro com água (0) */
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    /* 2) Posiciona navios */
    /* Navio 1 - horizontal */
    if (coluna_navio1 + TAM_NAVIO <= TAM) {
        for (j = coluna_navio1; j < coluna_navio1 + TAM_NAVIO; j++) {
            tabuleiro[linha_navio1][j] = NAVIO;
        }
    }

    /* Navio 2 - vertical */
    if (linha_navio2 + TAM_NAVIO <= TAM) {
        for (i = linha_navio2; i < linha_navio2 + TAM_NAVIO; i++) {
            tabuleiro[i][coluna_navio2] = NAVIO;
        }
    }

    /* Navio 3 - diagonal principal (↘) */
    if (linha_navio3 + TAM_NAVIO <= TAM && coluna_navio3 + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha_navio3 + i][coluna_navio3 + i] = NAVIO;
        }
    }

    /* Navio 4 - diagonal secundária (↙) */
    if (linha_navio4 + TAM_NAVIO <= TAM && coluna_navio4 - (TAM_NAVIO - 1) >= 0) {
        for (i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha_navio4 + i][coluna_navio4 - i] = NAVIO;
        }
    }

    /* 3) Construir dinamicamente as matrizes de habilidade (0/1) */

    /* 3.a) Cone (apex no topo, expande para baixo)
       condição: na linha i, coluna j é afetada se abs(j - center) <= i
    */
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) {
            if (abs(j - center) <= i) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    /* 3.b) Cruz (linha == center || coluna == center) */
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) {
            if (i == center || j == center) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }

    /* 3.c) Octaedro (vista frontal -> losango/diamante)
       condição: abs(i-center) + abs(j-center) <= radius
    */
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) {
            if (abs(i - center) + abs(j - center) <= radius) octaedro[i][j] = 1;
            else octaedro[i][j] = 0;
        }
    }

    /* 4) Sobrepor cada matriz de habilidade ao tabuleiro (centrando) */
    /* Aplicar cone */
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) {
            if (cone[i][j] == 1) {
                int tab_r = origem_cone_row + (i - center);
                int tab_c = origem_cone_col + (j - center);
                if (tab_r >= 0 && tab_r < TAM && tab_c >= 0 && tab_c < TAM) {
                    tabuleiro[tab_r][tab_c] = AREA;
                }
            }
        }
    }

    /* Aplicar cruz */
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) {
            if (cruz[i][j] == 1) {
                int tab_r = origem_cruz_row + (i - center);
                int tab_c = origem_cruz_col + (j - center);
                if (tab_r >= 0 && tab_r < TAM && tab_c >= 0 && tab_c < TAM) {
                    tabuleiro[tab_r][tab_c] = AREA;
                }
            }
        }
    }

    /* Aplicar octaedro */
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) {
            if (octaedro[i][j] == 1) {
                int tab_r = origem_octa_row + (i - center);
                int tab_c = origem_octa_col + (j - center);
                if (tab_r >= 0 && tab_r < TAM && tab_c >= 0 && tab_c < TAM) {
                    tabuleiro[tab_r][tab_c] = AREA;
                }
            }
        }
    }

    /* 5) Exibir o tabuleiro final */
    printf("\n=== TABULEIRO COM ÁREAS DE HABILIDADE ===\n\n");

    /* Cabeçalho de colunas */
    printf("   ");
    for (j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");

    for (i = 0; i < TAM; i++) {
        printf("%2d ", i); /* número da linha */
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    /* Mostrar as matrizes de habilidade geradas (0/1) para inspeção */
    printf("\nMATRIZ - CONE (1 = afetado):\n");
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMATRIZ - CRUZ (1 = afetado):\n");
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\nMATRIZ - OCTAEDRO (1 = afetado):\n");
    for (i = 0; i < HAB_SIZE; i++) {
        for (j = 0; j < HAB_SIZE; j++) printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    return 0;
}
