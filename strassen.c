#include <stdio.h>
#include <stdlib.h>

typedef struct pixel {
    int red;
    int green;
    int blue;
} pixel;

void imprimeMatrizPixel(pixel **matriz, int linha, int coluna) {
    int i, j;
    
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            printf("%d ", matriz[i][j].red);
            printf("%d ", matriz[i][j].green);
            printf("%d ", matriz[i][j].blue);
        }
        printf("\n");
    }
}

void lerMatrizPixel(pixel **matriz, int linha, int coluna) {
    int i, j;
    
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            scanf("%d", &matriz[i][j].red);
            scanf("%d", &matriz[i][j].green);
            scanf("%d", &matriz[i][j].blue);
        }
    }
}

pixel **alocaMatrizPixel(int linha, int coluna) {
    int i;
    pixel **matriz;

// -- Alocando vetor de ponteiros para o número de linhas -- //
    matriz = malloc (linha * sizeof(pixel*));

// -- Alocando toda a matriz continuamente -- //
    matriz[0] = malloc (linha * coluna * sizeof(pixel));

// -- Ajusta os ponteiros de linhas para suas respectivas linhas -- //
    for (i = 1; i < linha; i++) {
        matriz[i] = matriz[0] + i * coluna;
    }

    return matriz;
}

int main (void) {
    int i, j;
    char codificacao[2];
    int altura, largura;
    int maxCor;
    pixel **matriz;
    pixel **matrizFiltro;

// --- Leitura dados iniciais --- //
    scanf(" %s", codificacao);
    scanf(" %d %d", &altura, &largura);
    scanf(" %d", &maxCor);
    
    printf("%s\n", codificacao);
    printf("%d %d\n", altura, largura);
    printf("%d\n", maxCor);

// --- Lendo a Matriz Original --- //
    matriz = alocaMatrizPixel(largura, altura);
    lerMatrizPixel(matriz, largura, altura);
    imprimeMatrizPixel(matriz, largura, altura);

// --- Lendo a Matriz Filtro --- //
    matrizFiltro = alocaMatrizPixel(largura, altura);
    lerMatrizPixel(matrizFiltro, largura, altura);
    imprimeMatrizPixel(matrizFiltro, largura, altura);

// --- Liberando Memória Alocada --- //
    free(matrizFiltro[0]);
    free(matrizFiltro);
    free(matriz[0]);
    free(matriz);

    return 0;
}