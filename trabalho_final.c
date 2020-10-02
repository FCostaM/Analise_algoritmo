#include <stdio.h>
#include <stdlib.h>

void multiplicaMatrizes(int n, int m1[][n],int m2[][n])
{
    int z[n][n];

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

    mostraMatriz(n, z);
}

void mostraMatriz(int n, int matriz[][n])
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


int main(void)
{
    srand(time(NULL));

    int n = 8;

    printf("numero n: %d\n", n);

    int matriz1[n][n];
    int matriz2[n][n];

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
    mostraMatriz(n, matriz1);

    printf("\nMatriz 2:\n");
    mostraMatriz(n, matriz2);

    printf("\nResultado Normal:\n");

    multiplicaMatrizes(n, matriz1, matriz2);

    printf("\nAlgoritmo 2:\n");

    int matrizResultante[n][n];

    for(int i = 0; i<n; i++) {
        for(int j=0; j<n; j++) {
            matrizResultante[i][j] = 0;
        }
    }

    printf("\n\nResultado Strassen\n\n");
    strassen(matriz1, matriz2, matrizResultante, n, n);

    mostraMatriz(n, matrizResultante);

    return 0;
}


int strassen(int *A, int *B, int *C, int m, int n){
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
