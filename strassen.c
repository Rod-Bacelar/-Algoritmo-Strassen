#include <stdio.h>
#include <stdlib.h>

typedef struct pixel {
    int red;
    int green;
    int blue;
} pixel;

void imprimeMatrizPixel(pixel **matriz, int numLinhas, int numColunas) {
    int i, j;
    
    for (i = 0; i < numLinhas; i++) {
        for (j = 0; j < numColunas; j++) {
            printf("[%d ", matriz[i][j].red);
            printf("%d ", matriz[i][j].green);
            printf("%d] ", matriz[i][j].blue);
        }
        printf("\n");
    }
}

void lerMatrizPixel(pixel **matriz, int numLinhas, int numColunas) {
    int i, j;
    
    for (i = 0; i < numLinhas; i++) {
        for (j = 0; j < numColunas; j++) {
            scanf("%d", &matriz[i][j].red);
            scanf("%d", &matriz[i][j].green);
            scanf("%d", &matriz[i][j].blue);
        }
    }
}

pixel **alocaMatrizPixel(int numLinhas, int numColunas) {
    int i;
    pixel **matriz;

// -- Alocando vetor de ponteiros para o número de linhas -- //
    matriz = malloc (numLinhas * sizeof(pixel*));

// -- Alocando toda a matriz continuamente -- //
    matriz[0] = malloc (numLinhas * numColunas * sizeof(pixel));

// -- Ajusta os ponteiros de linhas para suas respectivas linhas -- //
    for (i = 1; i < numLinhas; i++) {
        matriz[i] = matriz[0] + i * numColunas;
    }

    return matriz;
}

pixel **somaMatriz(pixel **matriz1, pixel **matriz2, int numLinhas, int numColunas) {
    int i, j;
    pixel **matrizResultado;

    matrizResultado = alocaMatrizPixel(numLinhas, numColunas);

    for (i = 0; i < numLinhas; i++) {
        for (j = 0; j < numColunas; j++) {
            matrizResultado[i][j].red = matriz1[i][j].red + matriz2[i][j].red;
            matrizResultado[i][j].green = matriz1[i][j].green + matriz2[i][j].green;
            matrizResultado[i][j].blue = matriz1[i][j].blue + matriz2[i][j].blue;
        }
    }

    return matrizResultado;
}

pixel **divideMatrizQuad(pixel **matriz, int numLinhas, int numColunas, int quadRetorno) {
    int i, j;
    int inicioL, inicioC;
    int metLin, metCol;
    pixel **matrizResultado;

    // -- Definindo os Limites dos Quadrantes -- //
    inicioL = 0;
    inicioC = 0;
    metLin = numLinhas/2;
    metCol = numColunas/2;

    matrizResultado = alocaMatrizPixel(metLin, metLin);

    if (quadRetorno == 3 || quadRetorno == 4) {
        inicioL = metLin;
    }

    if (quadRetorno == 2 || quadRetorno == 4) {
        inicioC = metCol;
    }


    for (i = 0; i < metLin; i++) {
        for (j = 0; j < metCol; j++) {
            matrizResultado[i][j].red = matriz[i + inicioL][j + inicioC].red;
            matrizResultado[i][j].green = matriz[i + inicioL][j + inicioC].green;
            matrizResultado[i][j].blue = matriz[i + inicioL][j + inicioC].blue;
        }
    }

    return matrizResultado;
}

pixel **juntaMatrizQuad(pixel **q1, pixel **q2, pixel **q3, pixel **q4, int numLinhas, int numColunas) {
    int i, j;
    int metLin, metCol;
    pixel **matrizResultado;


    matrizResultado = alocaMatrizPixel(numLinhas, numColunas);
    metLin = numLinhas/2;
    metCol = numColunas/2;

    for (i = 0; i < metLin; i++) {
        for (j = 0; j < metCol; j++) {
            matrizResultado[i][j].red = q1[i][j].red;
            matrizResultado[i][j].green = q1[i][j].green;
            matrizResultado[i][j].blue = q1[i][j].blue;
        }
    }

    for (i = 0; i < metLin; i++) {
        for (j = 0; j < metCol; j++) {
            matrizResultado[i][j + metCol].red = q2[i][j].red;
            matrizResultado[i][j + metCol].green = q2[i][j].green;
            matrizResultado[i][j + metCol].blue = q2[i][j].blue;
        }
    }

    for (i = 0; i < metLin; i++) {
        for (j = 0; j < metCol; j++) {
            matrizResultado[i + metLin][j].red = q3[i][j].red;
            matrizResultado[i + metLin][j].green = q3[i][j].green;
            matrizResultado[i + metLin][j].blue = q3[i][j].blue;
        }
    }

    for (i = 0; i < metLin; i++) {
        for (j = 0; j < metCol; j++) {
            matrizResultado[i + metLin][j + metCol].red = q4[i][j].red;
            matrizResultado[i + metLin][j + metCol].green = q4[i][j].green;
            matrizResultado[i + metLin][j + metCol].blue = q4[i][j].blue;
        }
    }

    return matrizResultado;
}

pixel **multiplicaMatriz(pixel **matriz1, pixel **matriz2, int numLinhas, int numColunas) {
    int metLin, metCol;
    pixel **matrizResultado;
    pixel **mA, **mB, **mC, **mD;
    pixel **mE, **mF, **mG, **mH;
    pixel **mR, **mS, **mT, **mU;

    
// -- Caso Base -- //
    if (numLinhas == 1) {
        //printf("\nCaso Base\n");
        matrizResultado = alocaMatrizPixel(1, 1);
        
        matrizResultado[0][0].red = (matriz1[0][0].red * matriz2[0][0].red);
        //printf("Red: %d * %d ", matriz1[0][0].red, matriz2[0][0].red);
        matrizResultado[0][0].green = (matriz1[0][0].green * matriz2[0][0].green);
        //printf(" Green: %d * %d ", matriz1[0][0].green, matriz2[0][0].green);
        matrizResultado[0][0].blue = (matriz1[0][0].blue * matriz2[0][0].blue);
        //printf(" Blue: %d * %d \n", matriz1[0][0].blue, matriz2[0][0].blue);


        return matrizResultado;
    }

// -- Divisão -- //
    //printf("Divisoes Matriz\n");
    mA = divideMatrizQuad(matriz1, numLinhas, numColunas, 1);
    mB = divideMatrizQuad(matriz1, numLinhas, numColunas, 2);
    mC = divideMatrizQuad(matriz1, numLinhas, numColunas, 3);
    mD = divideMatrizQuad(matriz1, numLinhas, numColunas, 4);

    mE = divideMatrizQuad(matriz2, numLinhas, numColunas, 1);
    mF = divideMatrizQuad(matriz2, numLinhas, numColunas, 2);
    mG = divideMatrizQuad(matriz2, numLinhas, numColunas, 3);
    mH = divideMatrizQuad(matriz2, numLinhas, numColunas, 4);
    
    metLin = numLinhas/2;
    metCol = numColunas/2;
    
    /*
    printf("A\n");
    imprimeMatrizPixel(mA, metLin, metCol);
    printf("\nB\n");
    imprimeMatrizPixel(mB, metLin, metCol);
    printf("\nC\n");
    imprimeMatrizPixel(mC, metLin, metCol);
    printf("\nD\n");
    imprimeMatrizPixel(mD, metLin, metCol);
    printf("\n\nE\n");
    imprimeMatrizPixel(mE, metLin, metCol);
    printf("\nF\n");
    imprimeMatrizPixel(mF, metLin, metCol);
    printf("\nG\n");
    imprimeMatrizPixel(mG, metLin, metCol);
    printf("\nH\n");
    imprimeMatrizPixel(mH, metLin, metCol);
    */

// -- Multiplicações -- //
    //printf("\n (A * E) + (B * G)\n");
    mR = somaMatriz(multiplicaMatriz(mA, mE, metLin, metCol), multiplicaMatriz(mB, mG, metLin, metCol), metLin, metCol);
    //printf("\n (A * F) + (B * H)\n");
    mS = somaMatriz(multiplicaMatriz(mA, mF, metLin, metCol), multiplicaMatriz(mB, mH, metLin, metCol), metLin, metCol);
    //printf("\n (C * E) + (D * G)\n");
    mT = somaMatriz(multiplicaMatriz(mC, mE, metLin, metCol), multiplicaMatriz(mD, mG, metLin, metCol), metLin, metCol);
    //printf("\n (C * F) + (D * H)\n");
    mU = somaMatriz(multiplicaMatriz(mC, mF, metLin, metCol), multiplicaMatriz(mD, mH, metLin, metCol), metLin, metCol);

    /*
    printf("\n\nR\n");
    imprimeMatrizPixel(mR, metLin, metCol);
    printf("\nS\n");
    imprimeMatrizPixel(mS, metLin, metCol);
    printf("\nT\n");
    imprimeMatrizPixel(mT, metLin, metCol);
    printf("\nU\n");
    imprimeMatrizPixel(mU, metLin, metCol);
    */
    

// -- Conquista -- //
    //printf("\nConquista\n");
    matrizResultado = juntaMatrizQuad(mR, mS, mT, mU, numLinhas, numColunas);
    //printf("\nJunta Matriz Feito\n");

    free(mA[0]);
    free(mA);
    free(mB[0]);
    free(mB);
    free(mC[0]);
    free(mC);
    free(mD[0]);
    free(mD);
    free(mE[0]);
    free(mE);
    free(mF[0]);
    free(mF);
    free(mG[0]);
    free(mG);
    free(mH[0]);
    free(mH);
    free(mR[0]);
    free(mR);
    free(mS[0]);
    free(mS);
    free(mT[0]);
    free(mT);
    free(mU[0]);
    free(mU);

    //printf("\nResultado\n");
    //imprimeMatrizPixel(matrizResultado, numLinhas, numColunas);

    return matrizResultado;
}

int main (void) {
    char codificacao[2];
    int altura, largura;
    int maxCor;
    pixel **matriz;
    pixel **mFiltro;
    pixel **matrizResultado;

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
    mFiltro = alocaMatrizPixel(largura, altura);
    lerMatrizPixel(mFiltro, largura, altura);
    imprimeMatrizPixel(mFiltro, largura, altura);

// --- Multiplicando as Matrizes --- //
    matrizResultado = multiplicaMatriz(matriz, mFiltro, largura, altura);

    printf("\nResultado Final\n");
    imprimeMatrizPixel(matrizResultado, largura, altura);

// --- Liberando Memória Alocada --- //
    free(mFiltro[0]);
    free(mFiltro);
    free(matriz[0]);
    free(matriz);

    return 0;
}