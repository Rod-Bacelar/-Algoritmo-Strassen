#include <stdio.h>
#include <stdlib.h>

typedef struct pixel {
    int red;
    int green;
    int blue;
} pixel;

// -- Função para Imprimir a Matriz de Pixel -- //
void imprimirMatrizPixel(pixel **matriz, int numL, int numC) {
    int i, j;
    
    for (i = 0; i < numL; i++) {
        for (j = 0; j < numC; j++) {
            printf("%d ", matriz[i][j].red);
            printf("%d ", matriz[i][j].green);
            printf("%d ", matriz[i][j].blue);
        }
        printf("\n");
    }
}

// -- Função para Ler uma Entrada de Matriz de Pixel -- //
void lerMatrizPixel(pixel **matriz, int numL, int numC) {
    int i, j;
    
    for (i = 0; i < numL; i++) {
        for (j = 0; j < numC; j++) {
            scanf("%d", &matriz[i][j].red);
            scanf("%d", &matriz[i][j].green);
            scanf("%d", &matriz[i][j].blue);
        }
    }
}

// -- Função para Alocar Dinamicamente uma Matriz de Pixel -- //
pixel **criarMatrizPixel(int numL, int numC) {
    int i;
    pixel **matriz;

// -- Alocando vetor de ponteiros para o número de linhas -- //
    matriz = malloc (numL * sizeof(pixel*));
    if (matriz == NULL) {
        printf("Erro ao Alocar a Matriz");
        exit(1);
    }

// -- Alocando toda a matriz continuamente -- //
    matriz[0] = malloc (numL * numC * sizeof(pixel));

// -- Ajusta os ponteiros de linhas para suas respectivas linhas -- //
    for (i = 1; i < numL; i++) {
        matriz[i] = matriz[0] + i * numC;
    }

    return matriz;
}

// -- Função para Liberar Memória de uma Matriz de Pixel -- //
void liberarMatrizPixel(pixel **matriz) {
    free(matriz[0]);
    free(matriz);
}

// -- Função que Soma Duas Matrizes de Pixel -- //
void somarMatrizPixel(pixel **matrizResul, pixel **matriz1, pixel **matriz2, int numL, int numC) {
    int i, j;

    for (i = 0; i < numL; i++) {
        for (j = 0; j < numC; j++) {
            matrizResul[i][j].red = matriz1[i][j].red + matriz2[i][j].red;
            matrizResul[i][j].green = matriz1[i][j].green + matriz2[i][j].green;
            matrizResul[i][j].blue = matriz1[i][j].blue + matriz2[i][j].blue;
        }
    }
}

// -- Função que Subtrai Duas Matrizes de Pixel -- //
void subtrairMatrizPixel(pixel **matrizResul, pixel **matriz1, pixel **matriz2, int numL, int numC) {
    int i, j;

    for (i = 0; i < numL; i++) {
        for (j = 0; j < numC; j++) {
            matrizResul[i][j].red = matriz1[i][j].red - matriz2[i][j].red;
            matrizResul[i][j].green = matriz1[i][j].green - matriz2[i][j].green;
            matrizResul[i][j].blue = matriz1[i][j].blue - matriz2[i][j].blue;
        }
    }
}

// -- Função que Divide 1 Matriz em 4 SubMatrizes de Pixel -- //
void dividirMatrizPixel(pixel **quad1, pixel **quad2, pixel **quad3, pixel **quad4, pixel **matriz, int numL, int numC) {
    int i, j;
    int metL = numL/2;
    int metC = numC/2;

    // -- Primeiro Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            quad1[i][j].red = matriz[i][j].red;
            quad1[i][j].green = matriz[i][j].green;
            quad1[i][j].blue = matriz[i][j].blue;
        }
    }

    // -- Segundo Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            quad2[i][j].red = matriz[i][j + metC].red;
            quad2[i][j].green = matriz[i][j + metC].green;
            quad2[i][j].blue = matriz[i][j + metC].blue;
        }
    }

    // -- Terceiro Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            quad3[i][j].red = matriz[i + metL][j].red;
            quad3[i][j].green = matriz[i + metL][j].green;
            quad3[i][j].blue = matriz[i + metL][j].blue;
        }
    }

    // -- Quarto Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            quad4[i][j].red = matriz[i + metL][j + metC].red;
            quad4[i][j].green = matriz[i + metL][j + metC].green;
            quad4[i][j].blue = matriz[i + metL][j + metC].blue;
        }
    }
}

// -- Função que Combina 4 SubMatrizes em 1 Matriz de Pixel -- //
void combinarMatrizPixel(pixel **quad1, pixel **quad2, pixel **quad3, pixel **quad4, pixel **matriz, int numL, int numC) {
    int i, j;
    int metL = numL/2;
    int metC = numC/2;

    // -- Primeiro Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            matriz[i][j].red = quad1[i][j].red;
            matriz[i][j].green = quad1[i][j].green;
            matriz[i][j].blue = quad1[i][j].blue;
        }
    }

    // -- Segundo Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            matriz[i][j + metC].red = quad2[i][j].red;
            matriz[i][j + metC].green = quad2[i][j].green;
            matriz[i][j + metC].blue = quad2[i][j].blue;
        }
    }

    // -- Terceiro Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            matriz[i + metL][j].red = quad3[i][j].red;
            matriz[i + metL][j].green = quad3[i][j].green;
            matriz[i + metL][j].blue = quad3[i][j].blue;
        }
    }

    // -- Quarto Quadrante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            matriz[i + metL][j + metC].red = quad4[i][j].red;
            matriz[i + metL][j + metC].green = quad4[i][j].green;
            matriz[i + metL][j + metC].blue = quad4[i][j].blue;
        }
    }
}

// -- Função que Multiplica Duas Matrizes de Pixel -- //
void multiplicarMatrizPixel(pixel **matrizResul, pixel **matriz1, pixel **matriz2, int numL, int numC) {
    int metL = numL/2;
    int metC = numC/2;
    pixel **aux1, **aux2;                           // Submatrizes Auxiliares
    pixel **mA, **mB, **mC, **mD;                   // Submatrizes da Matriz 1
    pixel **mE, **mF, **mG, **mH;                   // Submatrizes da Matriz 2
    pixel **mR, **mS, **mT, **mU;                   // Submatrizes da Matriz Resultante
    pixel **p1, **p2, **p3, **p4, **p5, **p6, **p7; // Produtos do Algoritmo de Strassen

    // -- Caso Base -- //
    if (numL == 1) {
        matrizResul[0][0].red = (matriz1[0][0].red * matriz2[0][0].red);
        matrizResul[0][0].green = (matriz1[0][0].green * matriz2[0][0].green);
        matrizResul[0][0].blue = (matriz1[0][0].blue * matriz2[0][0].blue);

        return;
    }

    // -- Alocando Todas as SubMatrizes --//
    mA = criarMatrizPixel(metL, metC);
    mB = criarMatrizPixel(metL, metC);
    mC = criarMatrizPixel(metL, metC);
    mD = criarMatrizPixel(metL, metC);
    mE = criarMatrizPixel(metL, metC);
    mF = criarMatrizPixel(metL, metC);
    mG = criarMatrizPixel(metL, metC);
    mH = criarMatrizPixel(metL, metC);
    mR = criarMatrizPixel(metL, metC);
    mS = criarMatrizPixel(metL, metC);
    mT = criarMatrizPixel(metL, metC);
    mU = criarMatrizPixel(metL, metC);

    // -- Alocando SubMatrizes Auxiliares -- //
    aux1 = criarMatrizPixel(metL, metC);
    aux2 = criarMatrizPixel(metL, metC);

    // -- Dividindo as Matrizes em SubMatrizes -- //
    dividirMatrizPixel(mA, mB, mC, mD, matriz1, numL, numC);
    dividirMatrizPixel(mE, mF, mG, mH, matriz2, numL, numC);


    // -- Algoritmo de Strassen -- //

    // -- Alocando Produtos P1 até P7 -- //
    p1 = criarMatrizPixel(metL, metC);
    p2 = criarMatrizPixel(metL, metC);
    p3 = criarMatrizPixel(metL, metC);
    p4 = criarMatrizPixel(metL, metC);
    p5 = criarMatrizPixel(metL, metC);
    p6 = criarMatrizPixel(metL, metC);
    p7 = criarMatrizPixel(metL, metC);

    // -- Operações para os Produtos -- //
    // P1 = A(F - H)  //
    subtrairMatrizPixel(aux1, mF, mH, metL, metC);
    multiplicarMatrizPixel(p1, mA, aux1, metL, metC);

    //  P2 = (A + B)H  //
    somarMatrizPixel(aux1, mA, mB, metL, metC);
    multiplicarMatrizPixel(p2, aux1, mH, metL, metC);

    //  P3 = (C + D)E   //
    somarMatrizPixel(aux1, mC, mD, metL, metC);
    multiplicarMatrizPixel(p3, aux1, mE, metL, metC);

    //  P4 = D(G - E)  //
    subtrairMatrizPixel(aux1, mG, mE, metL, metC);
    multiplicarMatrizPixel(p4, mD, aux1, metL, metC);

    //  P5 = (A + D)(E + H)  //
    somarMatrizPixel(aux1, mA, mD, metL, metC);
    somarMatrizPixel(aux2, mE, mH, metL, metC);
    multiplicarMatrizPixel(p5, aux1, aux2, metL, metC);

    //  P6 = (B - D)(G + H)  //
    subtrairMatrizPixel(aux1, mB, mD, metL, metC);
    somarMatrizPixel(aux2, mG, mH, metL, metC);
    multiplicarMatrizPixel(p6, aux1, aux2, metL, metC);

    //  P7 = (A - C)(E + F)  //
    subtrairMatrizPixel(aux1, mA, mC, metL, metC);
    somarMatrizPixel(aux2, mE, mF, metL, metC);
    multiplicarMatrizPixel(p7, aux1, aux2, metL, metC);

    // -- Operações para as SubMatrizes da Matriz Resultante -- //
    // R = P5 + P4 - P2 + P6 //
    somarMatrizPixel(mR, p5, p4, metL, metC);
    subtrairMatrizPixel(mR, mR, p2, metL, metC);
    somarMatrizPixel(mR, mR, p6, metL, metC);

    // S = P1 + P2 //
    somarMatrizPixel(mS, p1, p2, metL, metC);

    // T = P3 + P4 //
    somarMatrizPixel(mT, p3, p4, metL, metC);

    // U = P1 + P5 - P3 - P7 //
    somarMatrizPixel(mU, p1, p5, metL, metC);
    subtrairMatrizPixel(mU, mU, p3, metL, metC);
    subtrairMatrizPixel(mU, mU, p7, metL, metC);

    // -- Liberando Memória das Matrizes de Produtos -- //
    liberarMatrizPixel(p1);
    liberarMatrizPixel(p2);
    liberarMatrizPixel(p3);
    liberarMatrizPixel(p4);
    liberarMatrizPixel(p5);
    liberarMatrizPixel(p6);
    liberarMatrizPixel(p7);

    // -- Liberando Memória das SubMatrizes da Matriz 1 e 2 -- //
    liberarMatrizPixel(mA);
    liberarMatrizPixel(mB);
    liberarMatrizPixel(mC);
    liberarMatrizPixel(mD);
    liberarMatrizPixel(mE);
    liberarMatrizPixel(mF);
    liberarMatrizPixel(mG);
    liberarMatrizPixel(mH);

    // -- Liberando Memória das SubMatrizes Auxiliares -- //
    liberarMatrizPixel(aux1);
    liberarMatrizPixel(aux2);

    // -- Combinando as SubMatrizes na Matriz Resultante -- //
    combinarMatrizPixel(mR, mS, mT, mU, matrizResul, numL, numC);

    // -- Liberando Memória das SubMatrizes da Matriz Resultante -- //
    liberarMatrizPixel(mR);
    liberarMatrizPixel(mS);
    liberarMatrizPixel(mT);
    liberarMatrizPixel(mU);
}

int main (void) {
    char codificacao[2];
    int altura, largura;
    int maxCor;
    pixel **matrizOriginal;
    pixel **matrizFiltro;
    pixel **matrizResultado;

    // --- Leitura dados iniciais --- //
    scanf(" %s", codificacao);
    scanf(" %d %d", &altura, &largura);
    scanf(" %d", &maxCor);
    
    printf("%s\n", codificacao);
    printf("%d %d\n", altura, largura);
    printf("%d\n", maxCor);

    // --- Lendo a Matriz Original --- //
    matrizOriginal = criarMatrizPixel(largura, altura);
    lerMatrizPixel(matrizOriginal, largura, altura);

    // --- Lendo a Matriz Filtro --- //
    matrizFiltro = criarMatrizPixel(largura, altura);
    lerMatrizPixel(matrizFiltro, largura, altura);

    // --- Multiplicando as Matrizes --- //
    matrizResultado = criarMatrizPixel(largura, altura);
    multiplicarMatrizPixel(matrizResultado, matrizOriginal, matrizFiltro, largura, altura);
    imprimirMatrizPixel(matrizResultado, largura, altura);

    // --- Liberando Memória Alocada --- //
    liberarMatrizPixel(matrizOriginal);
    liberarMatrizPixel(matrizFiltro);
    liberarMatrizPixel(matrizResultado);

    return 0;
}