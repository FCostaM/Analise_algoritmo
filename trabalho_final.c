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

    int n = 4;

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

    printf("\nResultado:\n");

    multiplicaMatrizes(n, matriz1, matriz2);

    return 0;
}