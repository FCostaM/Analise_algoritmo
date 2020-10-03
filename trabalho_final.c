#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int multiplicaMatrizes(int n, long int **m1,long int **m2, long int **z)
{
    //int z[n][n];

    clock_t begin = clock();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            z[i][j] = 0;
            for(int k = 0; k < n; k++)
            {
                z[i][j] = z[i][j] + m1[i][k] * m2[k][j];
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\n\nTempo gasto normal: %f\n\n", time_spent);
    //mostraMatriz(n, z);
}

void mostraMatriz(int n, long int matriz[][n])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

long int alocaMatriz(int n, long int **matriz) {
    matriz = (int **)malloc(n*sizeof(int*));

    int j;

    for(j=0;j<n;j++) {
        matriz[j]=(int*)malloc(n*sizeof(int));
    }

    return matriz;
}


int main(void)
{
    srand(time(NULL));

    int n = 512;

    printf("numero n: %d\n", n);

    long int **matriz1;
    long int **matriz2;

    matriz1 = alocaMatriz(n, matriz1);

    matriz2 = alocaMatriz(n, matriz2);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matriz1[i][j] = rand()%10;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matriz2[i][j] = rand()%10;
        }
    }

    printf("\nMatriz 1:\n");
    //mostraMatriz(n, matriz1);

    printf("\nMatriz 2:\n");
    //mostraMatriz(n, matriz2);

    printf("\nResultado Normal:\n");

    long int **z;

    z = alocaMatriz(n, z);

    //inicia caculo de tempo
    multiplicaMatrizes(n, matriz1, matriz2, z);
    //termina calculo de tempo

    //mostraMatriz(n, z);

    printf("\nAlgoritmo 2:\n");

    long int **matrizResultante;

    matrizResultante = alocaMatriz(n, matrizResultante);

    for(int i = 0; i<n; i++) {
        for(int j=0; j<n; j++) {
            matrizResultante[i][j] = 0;
        }
    }

    printf("\n\nResultado Strassen\n\n");

    clock_t begin = clock();

    strassen(*matriz1, *matriz2, *matrizResultante, n, n);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\n\nTempo gasto strassen: %f\n\n", time_spent);

    //mostraMatriz(n, matrizResultante);

    return 0;
}


int strassen(long int *A, long int *B, long int *C, int m, int n){
    printf("\nMatriz 1:\n");
    if(m==2){
        int P=(*A+*(A+n+1))*(*B+*(B+n+1));  //P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])
        int Q=(*(A+n)+*(A+n+1))*(*B);   //Q=(A[1][0]+A[1][1])*B[0][0]
        int R=(*A)*(*(B+1)-*(B+n+1));   //R=A[0][0]*(B[0][1]-B[1][1])
        int S=(*(A+n+1))*(*(B+n)-*B);   //S=A[1][1]*(B[1][0]-B[0][0])
        int T=(*A+*(A+1))*(*(B+n+1));   //T=(A[0][0]+A[0][1])*B[1][1]
        int U=(*(A+n)-*A)*(*B+*(B+1));  //U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])
        int V=(*(A+1)-*(A+n+1))*(*(B+n)+*(B+n+1));  //V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1]);

        *C=*C+P+S-T+V;  //C[0][0]=P+S-T+V
        *(C+1)=*(C+1)+R+T;  //C[0][1]=R+T
        *(C+n)=*(C+n)+Q+S;  //C[1][0]=Q+S
        *(C+n+1)=*(C+n+1)+P+R-Q+U;  //C[1][1]=P+R-Q+U
    }
    else{
        m=m/2;
        strassen(A,B,C,m,n);
        strassen(A,B+m,C+m,m,n);
        strassen(A+m,B+m*n,C,m,n);
        strassen(A+m,B+m*(n+1),C+m,m,n);
        strassen(A+m*n,B,C+m*n,m,n);
        strassen(A+m*n,B+m,C+m*(n+1),m,n);
        strassen(A+m*(n+1),B+m*n,C+m*n,m,n);
        strassen(A+m*(n+1),B+m*(n+1),C+m*(n+1),m,n);
    }
}
