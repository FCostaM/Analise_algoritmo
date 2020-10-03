#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 128     //Tamanho da matriz
#define T 10        

//Aloca a memória da matriz
int *criaMatriz(int *mat)
{
    mat = malloc (N * N * sizeof (int*)) ;

    return mat;
}

//Inicializa a matriz com valores aleatórios
void iniciaMatriz(int *mat)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat[(i * N) + j] = rand()%T;
        }
    }
}

//Inicializa a matriz com valor zero
void iniciaMatrizZero(int *mat)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat[(i * N) + j] = 0;
        }
    }
}

//Imprime na tela a matriz
void mostraMatriz(int *matriz)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d ", *((matriz + i * N) + j));
        }
        printf("\n");
    }
}

//Multiplicação básica de matrizes
//Algoritmo restirado do roteiro do projeto
int multiplicaMatrizes(int *m1, int *m2)
{
    int *z = criaMatriz(z);

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            z[(i * N) + j] = 0;
            for(int k = 0; k < N; k++)
            {
                z[(i * N) + j] = z[(i * N) + j] + m1[(i * N) + k] * m2[(k * N) + j];
            }
        }
    }

    return z;
}

//Multiplicação de matrizes usando o algoritmo de Strassen
int MultiplicaStrassen(int *A, int *B, int *C, int m, int n)
{
    if(m == 2)
    {
        //p1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1])
        int p1 = (*A + *(A + n + 1)) * (*B + *(B + n + 1));

        //p2 = (A[1][0]+A[1][1])*B[0][0]
        int p2 = (*(A + n) + *(A + n + 1)) * (*B);

        //p3 = A[0][0] * (B[0][1] - B[1][1])
        int p3 = (*A) * (*(B + 1) - *(B + n + 1));  

        //p4 = A[1][1] * (B[1][0] - B[0][0])
        int p4 = (*(A + n + 1)) * (*(B + n) - *B);

        //p5 = (A[0][0] + A[0][1]) * B[1][1]
        int p5 = (*A + *(A + 1)) * (*(B + n + 1));

        //p6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1])
        int p6 = (*(A + n) - *A) * (*B + *(B + 1));
        
        //p7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
        int p7 = (*(A + 1)-*(A + n + 1)) * (*(B + n) + *(B + n + 1));  

        *C       = *C + p1 + p4 - p5 + p7;              //C[0][0]
        *(C+1)   = *(C + 1) + p3 + p5;                  //C[0][1]
        *(C+n)   = *(C + n) + p2 + p4;                  //C[1][0]
        *(C+n+1) = *(C + n + 1) + p1 + p3 - p2 + p6;    //C[1][1]
    }
    else
    {
        m = m/2;
        MultiplicaStrassen(A          ,B          ,C          ,m,n);
        MultiplicaStrassen(A          ,B+m        ,C+m        ,m,n);
        MultiplicaStrassen(A+m        ,B+m*n      ,C          ,m,n);
        MultiplicaStrassen(A+m        ,B+m*(n+1)  ,C+m        ,m,n);
        MultiplicaStrassen(A+m*n      ,B          ,C+m*n      ,m,n);
        MultiplicaStrassen(A+m*n      ,B+m        ,C+m*(n+1)  ,m,n);
        MultiplicaStrassen(A+m*(n+1)  ,B+m*n      ,C+m*n      ,m,n);
        MultiplicaStrassen(A+m*(n+1)  ,B+m*(n+1)  ,C+m*(n+1)  ,m,n);
    }
}

int main()
{
    srand(time(NULL));

    printf("\n\nMatriz 1\n\n");

    //Cria e inicializa a matriz A
    int *mat1 = criaMatriz(mat1);
    iniciaMatriz(mat1);
    mostraMatriz(mat1);

    printf("\n\nMatriz 2\n\n");

    //Cria e inicializa a matriz A
    int *mat2 = criaMatriz(mat2);
    iniciaMatriz(mat2);
    mostraMatriz(mat2);

    printf("\n\nAlgoritmo 1\n\n");

    //Medição de tempo do algoritmo 1
    clock_t comecoNormal = clock();
    int *result_normal = multiplicaMatrizes(mat1, mat2);
    clock_t finalNormal = clock();

    mostraMatriz(result_normal);

    //Tempo gasto para execução do algoritmo 1
    double tempoGastoNormal = (double)(finalNormal - comecoNormal) / CLOCKS_PER_SEC;
    printf("\nTempo gasto Algoritmo 1: %f segundos\n\n", tempoGastoNormal);

    int *result_strassen = criaMatriz(result_strassen);
    iniciaMatrizZero(result_strassen);

    printf("\nAlgoritmo Strassen\n\n");

    //Medição de tempo do algoritmo de Strassen
    clock_t comecoStrassen = clock();
    MultiplicaStrassen(mat1, mat2, result_strassen, N, N);
    clock_t finalStrassen = clock();

    mostraMatriz(result_strassen);

    //Tempo gasto para execução do algoritmo de Strassen
    double tempoGastoStrassen = (double)(finalStrassen - comecoStrassen) / CLOCKS_PER_SEC;
    printf("\nTempo gasto Algoritmo Strassen: %f segundos\n\n", tempoGastoStrassen);

    //Libera a memória das matrizes
    free(mat1);
    free(mat2);
    free(result_normal);
    free(result_strassen);

    return 0;
}
