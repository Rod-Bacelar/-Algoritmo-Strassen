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

// -- Função para criar varias Matrizes de Pixel Continuas -- //
pixel ***criarMatrizesContinuasPixel(int numM, int numL, int numC) {
    int i, j;
    pixel ***matrizes;
    
    // -- Alocando vetor de ponteiros para o número de matrizes -- //
    matrizes = malloc (numM * sizeof(pixel**));
    if (matrizes == NULL) {
        exit(1);
    }
    
    // -- Alocando todas as linhas continuamente -- //
    matrizes[0] = malloc (numM * numL * sizeof(pixel*));
    if (matrizes[0] == NULL) {
        exit(1);
    }

    // -- Ajusta os ponteiros de martrizes para suas respectivas matrizes -- //
    for (i = 1; i < numM; i++) {
        matrizes[i] = matrizes[0] + i * numL;
    }

    // -- Alocando todas as matrizes continuamente -- //
    matrizes[0][0] = malloc (numM * numL * numC * sizeof(pixel));
    if (matrizes[0][0] == NULL) {
        exit(1);
    }

    // -- Ajusta os ponteiros de linhas para suas respectivas linhas -- //
    for (i = 0; i < numM; i++) {
        for (j = 0; j < numL; j++) {
            if (i != 0 || j != 0) {
                matrizes[i][j] = matrizes[0][0] + (j * numC) + (i * numC * numL);
            }
        }
    }

    return matrizes;
}

// -- Função que Multiplica Duas Matrizes de Pixel -- //
void multiplicarMatrizPixel(pixel **matrizResul, pixel **matriz1, pixel **matriz2, int numL, int numC) {
    int i, j;
    int metL = numL/2;
    int metC = numC/2;
    pixel ***subMatrizes;
    
    pixel **mA, **mD, **mE, **mH;               // Submatrizes Necessárias
    pixel **FsubH, **AaddB, **CaddD, **GsubE, **AaddD, **EaddH, **BsubD, **GaddH, **AsubC, **EaddF;
    pixel **p1, **p2, **p3, **p4, **p5, **p6, **p7; // Produtos do Algoritmo de Strassen


    // -- Caso Base -- //
    if (numL == 1) {
        matrizResul[0][0].red = (matriz1[0][0].red * matriz2[0][0].red);
        matrizResul[0][0].green = (matriz1[0][0].green * matriz2[0][0].green);
        matrizResul[0][0].blue = (matriz1[0][0].blue * matriz2[0][0].blue);

        return;
    }

    // -- Alocando Memória para as submatrizes -- //
    subMatrizes = criarMatrizesContinuasPixel(21, metL, metC);

    // -- Atribuindo submatrizes das Operações -- //
    FsubH = subMatrizes[0];
    AaddB = subMatrizes[1];
    CaddD = subMatrizes[2];
    GsubE = subMatrizes[3];
    AaddD = subMatrizes[4];
    EaddH = subMatrizes[5];
    BsubD = subMatrizes[6];
    GaddH = subMatrizes[7];
    AsubC = subMatrizes[8];
    EaddF = subMatrizes[9];

    // -- Submatrizes para respectivamente A, D, E, H e também para R, S, T, U -- //
    mA = subMatrizes[10];
    mD = subMatrizes[11];
    mE = subMatrizes[12];
    mH = subMatrizes[13];

    // -- Atribuindo uma nova variável para P1 até P7 -- //
    p1 = subMatrizes[14];
    p2 = subMatrizes[15];
    p3 = subMatrizes[16];
    p4 = subMatrizes[17];
    p5 = subMatrizes[18];
    p6 = subMatrizes[19];
    p7 = subMatrizes[20];

    // -- Calculando todas as operações de adição e de subtração -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            // F - H //
            FsubH[i][j].red = matriz2[i][j + metC].red - matriz2[i + metL][j + metC].red;
            FsubH[i][j].green = matriz2[i][j + metC].green - matriz2[i + metL][j + metC].green;
            FsubH[i][j].blue = matriz2[i][j + metC].blue - matriz2[i + metL][j + metC].blue;
            
            // A + B //
            AaddB[i][j].red = matriz1[i][j].red + matriz1[i][j + metC].red;
            AaddB[i][j].green = matriz1[i][j].green + matriz1[i][j + metC].green;
            AaddB[i][j].blue = matriz1[i][j].blue + matriz1[i][j + metC].blue;

            // C + D //
            CaddD[i][j].red = matriz1[i + metL][j].red + matriz1[i + metL][j + metC].red;
            CaddD[i][j].green = matriz1[i + metL][j].green + matriz1[i + metL][j + metC].green;
            CaddD[i][j].blue = matriz1[i + metL][j].blue + matriz1[i + metL][j + metC].blue;

            // G - E //
            GsubE[i][j].red = matriz2[i + metL][j].red - matriz2[i][j].red;
            GsubE[i][j].green = matriz2[i + metL][j].green - matriz2[i][j].green;
            GsubE[i][j].blue = matriz2[i + metL][j].blue - matriz2[i][j].blue;

            // A + D //
            AaddD[i][j].red = matriz1[i][j].red + matriz1[i + metL][j + metC].red;
            AaddD[i][j].green = matriz1[i][j].green + matriz1[i + metL][j + metC].green;
            AaddD[i][j].blue = matriz1[i][j].blue + matriz1[i + metL][j + metC].blue;

            // E + H //
            EaddH[i][j].red = matriz2[i][j].red + matriz2[i + metL][j + metC].red;
            EaddH[i][j].green = matriz2[i][j].green + matriz2[i + metL][j + metC].green;
            EaddH[i][j].blue = matriz2[i][j].blue + matriz2[i + metL][j + metC].blue;
            
            // B - D //
            BsubD[i][j].red = matriz1[i][j + metC].red - matriz1[i + metL][j + metC].red;
            BsubD[i][j].green = matriz1[i][j + metC].green - matriz1[i + metL][j + metC].green;
            BsubD[i][j].blue = matriz1[i][j + metC].blue - matriz1[i + metL][j + metC].blue;

            // G + H //
            GaddH[i][j].red = matriz2[i + metL][j].red + matriz2[i + metL][j + metC].red;
            GaddH[i][j].green = matriz2[i + metL][j].green + matriz2[i + metL][j + metC].green;
            GaddH[i][j].blue = matriz2[i + metL][j].blue + matriz2[i + metL][j + metC].blue;

            // A - C //
            AsubC[i][j].red = matriz1[i][j].red - matriz1[i + metL][j].red;
            AsubC[i][j].green = matriz1[i][j].green - matriz1[i + metL][j].green;
            AsubC[i][j].blue = matriz1[i][j].blue - matriz1[i + metL][j].blue;

            // E + F //
            EaddF[i][j].red = matriz2[i][j].red + matriz2[i][j + metC].red;
            EaddF[i][j].green = matriz2[i][j].green + matriz2[i][j + metC].green;
            EaddF[i][j].blue = matriz2[i][j].blue + matriz2[i][j + metC].blue;

            // -- Atribuindo as submatrizes necessárias para a multiplicação -- //
            // -- Submatriz A -- //
            mA[i][j].red = matriz1[i][j].red;
            mA[i][j].green = matriz1[i][j].green;
            mA[i][j].blue = matriz1[i][j].blue;

            // -- Submatriz D -- //
            mD[i][j].red = matriz1[i + metL][j + metC].red;
            mD[i][j].green = matriz1[i + metL][j + metC].green;
            mD[i][j].blue = matriz1[i + metL][j + metC].blue;

            // -- SubMatriz E -- //
            mE[i][j].red = matriz2[i][j].red;
            mE[i][j].green = matriz2[i][j].green;
            mE[i][j].blue = matriz2[i][j].blue;

            // -- Submatriz H -- //
            mH[i][j].red = matriz2[i + metL][j + metC].red;
            mH[i][j].green = matriz2[i + metL][j + metC].green;
            mH[i][j].blue = matriz2[i + metL][j + metC].blue;
        }
    }
    
    // -- Operações para os Produtos -- //
    multiplicarMatrizPixel(p1, mA, FsubH, metL, metC); // P1 = A(F - H)  //
    multiplicarMatrizPixel(p2, AaddB, mH, metL, metC); //  P2 = (A + B)H  //
    multiplicarMatrizPixel(p3, CaddD, mE, metL, metC); //  P3 = (C + D)E   //
    multiplicarMatrizPixel(p4, mD, GsubE, metL, metC); //  P4 = D(G - E)  //
    multiplicarMatrizPixel(p5, AaddD, EaddH, metL, metC); //  P5 = (A + D)(E + H)  //
    multiplicarMatrizPixel(p6, BsubD, GaddH, metL, metC); //  P6 = (B - D)(G + H)  //
    multiplicarMatrizPixel(p7, AsubC, EaddF, metL, metC); //  P7 = (A - C)(E + F)  //


    // -- Operações e Combinanção das SubMatrizes na Matriz Resultante -- //
    for (i = 0; i < metL; i++) {
        for (j = 0; j < metC; j++) {
            // R = P5 + P4 - P2 + P6 //
            matrizResul[i][j].red = p5[i][j].red + p4[i][j].red - p2[i][j].red + p6[i][j].red;
            matrizResul[i][j].green = p5[i][j].green + p4[i][j].green - p2[i][j].green + p6[i][j].green;
            matrizResul[i][j].blue = p5[i][j].blue + p4[i][j].blue - p2[i][j].blue + p6[i][j].blue;

            // S = P1 + P2 //
            matrizResul[i][j + metC].red = p1[i][j].red + p2[i][j].red;
            matrizResul[i][j + metC].green = p1[i][j].green + p2[i][j].green;
            matrizResul[i][j + metC].blue = p1[i][j].blue + p2[i][j].blue;
            
            // T = P3 + P4 //
            matrizResul[i + metL][j].red = p3[i][j].red + p4[i][j].red;
            matrizResul[i + metL][j].green = p3[i][j].green + p4[i][j].green;
            matrizResul[i + metL][j].blue = p3[i][j].blue + p4[i][j].blue;
            
            // U = P1 + P5 - P3 - P7 //
            matrizResul[i + metL][j + metC].red = p1[i][j].red + p5[i][j].red - p3[i][j].red - p7[i][j].red;
            matrizResul[i + metL][j + metC].green = p1[i][j].green + p5[i][j].green - p3[i][j].green - p7[i][j].green;
            matrizResul[i + metL][j + metC].blue = p1[i][j].blue + p5[i][j].blue - p3[i][j].blue - p7[i][j].blue;
        }
    }

    // -- Liberando Memória do Vetor de SubMatrizes -- //
    free(subMatrizes[0][0]);
    free(subMatrizes[0]);
    free(subMatrizes);
}

int main (void) {
    char codificacao[2];
    int altura, largura;
    int maxCor;
    pixel ***imagens;
    pixel **matrizOriginal;
    pixel **matrizFiltro;
    pixel **matrizResultado;

    // --- Leitura dados iniciais --- //
    scanf(" %c %c %d %d %d", &codificacao[0], &codificacao[1], &altura, &largura, &maxCor);
    
    // --- Alocando Continuamente as Imagens --- //
    imagens = criarMatrizesContinuasPixel(3, altura, largura);

    // --- Lendo a Matriz Original --- //
    matrizOriginal = imagens[0];
    lerMatrizPixel(matrizOriginal, largura, altura);

    // --- Lendo a Matriz Filtro --- //
    matrizFiltro = imagens[1];
    lerMatrizPixel(matrizFiltro, largura, altura);

    // --- Multiplicando as Matrizes --- //
    matrizResultado = imagens[2];
    multiplicarMatrizPixel(matrizResultado, matrizOriginal, matrizFiltro, largura, altura);
    
    // --- Impressão dos Dados -- //
    printf("%c%c\n%d %d\n%d\n", codificacao[0], codificacao[1], altura, largura, maxCor);
    imprimirMatrizPixel(matrizResultado, largura, altura);

    // --- Liberando Memória Alocada --- //
    free(imagens[0][0]);
    free(imagens[0]);
    free(imagens);

    return 0;
}