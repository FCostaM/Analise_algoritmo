#include <stdio.h>
#include <stdlib.h>

#define N 4
#define number 10

int *criaMatriz(int *mat)
{
    mat = malloc (N * N * sizeof (int*)) ;

    return mat;
}

void iniciaMatriz(int *mat)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat[(i * N) + j] = rand()%number;
        }
    }
}

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
                //z[i][j] = z[i][j] + m1[i][k] * m2[k][j];
                z[(i * N) + j] = z[(i * N) + j] + m1[(i * N) + k] * m2[(k * N) + j];
            }
        }
    }

    return z;
}

int strassen(int *A, int *B, int *C, int m, int n)
{
    if(m == 2)
    {
        int P = (*A + *(A + n + 1)) * (*B + *(B + n + 1));  //P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])
        int Q = (*(A+n)+*(A+n+1))*(*B);   //Q=(A[1][0]+A[1][1])*B[0][0]
        int R = (*A)*(*(B+1)-*(B+n+1));   //R=A[0][0]*(B[0][1]-B[1][1])
        int S = (*(A+n+1))*(*(B+n)-*B);   //S=A[1][1]*(B[1][0]-B[0][0])
        int T = (*A+*(A+1))*(*(B+n+1));   //T=(A[0][0]+A[0][1])*B[1][1]
        int U = (*(A+n)-*A)*(*B+*(B+1));  //U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])
        int V = (*(A+1)-*(A+n+1))*(*(B+n)+*(B+n+1));  //V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1]);

        *C      =*C + P + S - T + V;                //C[0][0] = P + S - T + V
        *(C+1)  =*(C + 1) + R + T;                  //C[0][1] = R + T
        *(C+n)  =*(C + n) + Q + S;                  //C[1][0] = Q + S
        *(C+n+1)=*(C + n + 1) + P + R - Q + U;      //C[1][1] = P + R - Q + U
    }
    else
    {
        m = m/2;
        strassen(A          ,B          ,C          ,m,n);
        strassen(A          ,B+m        ,C+m        ,m,n);
        strassen(A+m        ,B+m*n      ,C          ,m,n);
        strassen(A+m        ,B+m*(n+1)  ,C+m        ,m,n);
        strassen(A+m*n      ,B          ,C+m*n      ,m,n);
        strassen(A+m*n      ,B+m        ,C+m*(n+1)  ,m,n);
        strassen(A+m*(n+1)  ,B+m*n      ,C+m*n      ,m,n);
        strassen(A+m*(n+1)  ,B+m*(n+1)  ,C+m*(n+1)  ,m,n);
    }
}

int main() 
{ 
    srand(time(NULL));

    printf("\nMatriz 1\n");
    
    int *mat1 = criaMatriz(mat1);
    iniciaMatriz(mat1);
    mostraMatriz(mat1);

    printf("\nMatriz 2\n");

    int *mat2 = criaMatriz(mat2);
    iniciaMatriz(mat2);
    mostraMatriz(mat2);

    printf("\nAlgoritmo 1\n");

    int *z = multiplicaMatrizes(mat1, mat2);
    mostraMatriz(z);

    int *result = criaMatriz(result);
    iniciaMatrizZero(result);

    printf("\nStrassen\n");
    strassen(mat1, mat2, result, N, N);
    mostraMatriz(result);

    printf("\ndeu bom\n");

    free(mat1);
    free(mat2);
    free(z);
    free(result);

    return 0; 
}