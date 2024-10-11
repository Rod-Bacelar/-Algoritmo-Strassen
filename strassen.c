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
            printf("%d %d %d ", matriz[i][j].red, matriz[i][j].green, matriz[i][j].blue);
        }
        printf("\n");
    }
}

// -- Função para Ler uma Entrada de Matriz de Pixel -- //
void lerMatrizPixel(pixel **matriz, int numL, int numC) {
    int i, j;
    
    for (i = 0; i < numL; i++) {
        for (j = 0; j < numC; j++) {
            scanf("%d %d %d", &matriz[i][j].red, &matriz[i][j].green, &matriz[i][j].blue);
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

    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            // -- Primeiro Quadrante -- //
            quad1[i][j].red = matriz[i][j].red;
            quad1[i][j].green = matriz[i][j].green;
            quad1[i][j].blue = matriz[i][j].blue;

            // -- Segundo Quadrante -- //
            quad2[i][j].red = matriz[i][j + metC].red;
            quad2[i][j].green = matriz[i][j + metC].green;
            quad2[i][j].blue = matriz[i][j + metC].blue;

            // -- Terceiro Quadrante -- //
            quad3[i][j].red = matriz[i + metL][j].red;
            quad3[i][j].green = matriz[i + metL][j].green;
            quad3[i][j].blue = matriz[i + metL][j].blue;

            // -- Quarto Quadrante -- //
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

    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            // -- Primeiro Quadrante -- //
            matriz[i][j].red = quad1[i][j].red;
            matriz[i][j].green = quad1[i][j].green;
            matriz[i][j].blue = quad1[i][j].blue;
        
            // -- Segundo Quadrante -- //
            matriz[i][j + metC].red = quad2[i][j].red;
            matriz[i][j + metC].green = quad2[i][j].green;
            matriz[i][j + metC].blue = quad2[i][j].blue;

            // -- Terceiro Quadrante -- //
            matriz[i + metL][j].red = quad3[i][j].red;
            matriz[i + metL][j].green = quad3[i][j].green;
            matriz[i + metL][j].blue = quad3[i][j].blue;

            // -- Quarto Quadrante -- //
            matriz[i + metL][j + metC].red = quad4[i][j].red;
            matriz[i + metL][j + metC].green = quad4[i][j].green;
            matriz[i + metL][j + metC].blue = quad4[i][j].blue;
        }
    }
}

// -- Função que Multiplica Duas Matrizes de Pixel -- //
void multiplicarMatrizPixel(pixel **matrizResul, pixel **matriz1, pixel **matriz2, int numL, int numC) {
    int i,j;
    int metL = numL/2;
    int metC = numC/2;
    pixel ***subMatrizes;
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

    // -- Alocando as subMatrizes continuamente -- //
    subMatrizes = malloc (21 * sizeof(pixel**));
    if (subMatrizes == NULL) {
        printf("Erro");
    }
    
    subMatrizes[0] = malloc (21 * metL * sizeof(pixel*));
    if (subMatrizes[0] == NULL) {
        printf("Erro 1");
    }

    for (i = 1; i < 21; i++) {
        subMatrizes[i] = subMatrizes[0] + i * metL;
    }

    subMatrizes[0][0] = malloc (21 * metL * metC * sizeof(pixel));
    if (subMatrizes[0][0] == NULL) {
        printf("Erro 2");
    }

    for (i = 0; i < 21; i++) {
        for (j = 0; j < metL; j++) {
            if (i != 0 || j != 0) {
                subMatrizes[i][j] = subMatrizes[0][0] + (j * metC) + (i * metC * metL);
            }
        }
    }

    // -- Atribuindo uma nova variável para as SubMatrizes --//
    mA = subMatrizes[0];
    mB = subMatrizes[1];
    mC = subMatrizes[2];
    mD = subMatrizes[3];
    mE = subMatrizes[4];
    mF = subMatrizes[5];
    mG = subMatrizes[6];
    mH = subMatrizes[7];
    mR = subMatrizes[8];
    mS = subMatrizes[9];
    mT = subMatrizes[10];
    mU = subMatrizes[11];

    // -- Atribuindo uma nova variável para SubMatrizes Auxiliares -- //
    aux1 = subMatrizes[12];
    aux2 = subMatrizes[13];

    // -- Atribuindo uma nova variável para P1 até P7 -- //
    p1 = subMatrizes[14];
    p2 = subMatrizes[15];
    p3 = subMatrizes[16];
    p4 = subMatrizes[17];
    p5 = subMatrizes[18];
    p6 = subMatrizes[19];
    p7 = subMatrizes[20];

    // -- Dividindo as Matrizes em SubMatrizes -- //
    dividirMatrizPixel(mA, mB, mC, mD, matriz1, numL, numC);
    dividirMatrizPixel(mE, mF, mG, mH, matriz2, numL, numC);

    if (numL > 32) {
        // -- Maior que 32 -> Algoritmo de Strassen -- //
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
    } else {
        // -- Menor que 32 -> Algoritmo Tradiconal -- //
        // -- Operações para as SubMatrizes da Matriz Resultante -- //
        // R = AE + BG //
        multiplicarMatrizPixel(aux1, mA, mE, metL, metC);
        multiplicarMatrizPixel(aux2, mB, mG, metL, metC);
        somarMatrizPixel(mR, aux1, aux2, metL, metC);

        // S = AF + BH //
        multiplicarMatrizPixel(aux1, mA, mF, metL, metC);
        multiplicarMatrizPixel(aux2, mB, mH, metL, metC);
        somarMatrizPixel(mS, aux1, aux2, metL, metC);

        // T = CE + DG //
        multiplicarMatrizPixel(aux1, mC, mE, metL, metC);
        multiplicarMatrizPixel(aux2, mD, mG, metL, metC);
        somarMatrizPixel(mT, aux1, aux2, metL, metC);

        // U = CF + DH //
        multiplicarMatrizPixel(aux1, mC, mF, metL, metC);
        multiplicarMatrizPixel(aux2, mD, mH, metL, metC);
        somarMatrizPixel(mU, aux1, aux2, metL, metC);
    }


    // -- Combinando as SubMatrizes na Matriz Resultante -- //
    combinarMatrizPixel(mR, mS, mT, mU, matrizResul, numL, numC);

    // -- Liberando Memória do Vetor de SubMatrizes -- //
    liberarMatrizPixel(subMatrizes[0]);
    free(subMatrizes);
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