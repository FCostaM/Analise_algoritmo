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
    /*
    int matriz[2][2] = {{1,1},{1,1}};    
    mostraMatriz(2, matriz);
    multiplicaMatrizes(2, matriz, matriz);
    */

    int n;
    FILE *arq;

    arq = fopen("matriz.txt", "r");
    if(arq == NULL)
    {
        printf("Arquivo inexistente");
        return 0;
    }

    fscanf(arq, "%d", &n);

    int matriz[n][n];

    for(int i = 0; i < n; i++)
    {
        for(int j; j < n; j++)
        {
            fscanf(arq, "%d", &matriz[i][j]);
        }
    }

    mostraMatriz(n, matriz);

    printf("%d", n);

    fclose(arq);
    
    return 0;
}


