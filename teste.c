#include<stdio.h>
#include<conio.h>
#include<math.h>

int power(int);
int strassen(int *, int *, int *, int, int);

int main()
{
    int i,j,k;  //variaveis auxilares
    int n1,n2,n3; //qtd linhas e coluna das matrizes
    int n,m;

    /*Input first matrix*/
    printf("Enter the order of the 1st Matrix (rows and columns):");
    scanf("%d%d",&n1,&n2);
    int A[n1][n2];
    printf("\nNow enter the first matrix");
    for(i=0;i<n1;i++){
        printf("\nEnter the elements of the %d-th row:",i+1);
        for(j=0;j<n2;j++)
            scanf(" %d",&A[i][j]);
    }

    /*Input second matrix*/
    printf("\nEnter the no. of columns of the 2nd Matrix:");
    scanf("%d",&n3);
    int B[n2][n3];
    printf("\nNow enter the second matrix");
    for(i=0;i<n2;i++){
        printf("\nEnter the elements of the %d-th row:",i+1);
        for(j=0;j<n3;j++)
           scanf(" %d",&B[i][j]);
    }

    /*Creating square matrix of order 2^n for all and initializing all elements to 0 except prefixed*/
    if(n1>=n2 && n1>=n3)
        n=n1;
    else if(n2>=n1 && n2>=n3)
        n=n2;
    else
        n=n3;
    int o=1;
    while(n>power(o))
        o=o+1;
    m=power(o);
    int a[m][m],b[m][m],C[m][m];
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            a[i][j]=0;
            b[i][j]=0;
        }
    }
    for(i=0;i<n1;i++)
        for(j=0;j<n2;j++)
            a[i][j]=A[i][j];
    for(i=0;i<n2;i++)
        for(j=0;j<n3;j++)
            b[i][j]=B[i][j];

    /*Printing first matrix*/
    printf("\nThis is the first matrix:");
    for(i=0;i<m;i++){
        printf("\n\n\n");
        for(j=0;j<m;j++)
            printf("\t%d",a[i][j]);
    }
    /*Printing second matrix*/
    printf("\n\n\nThis is the second matrix:");
    for(i=0;i<m;i++){
        printf("\n\n\n");
        for(j=0;j<m;j++)
            printf("\t%d",b[i][j]);
    }
    /*Initializing the multiplication Matrix:*/
    for(i=0;i<m;i++)
        for(j=0;j<m;j++)
            C[i][j]=0;

    strassen(a,b,C,m,m);    //Calling the function.

    /*Printing the final matrix*/
    printf("\n\n\nThis is the final matrix:");
    for(i=0;i<m;i++){
        printf("\n\n\n");
        for(j=0;j<m;j++)
            printf("\t%d",C[i][j]);
    }
}

int power(int n){
    int i,p=1;
    for(i=1;i<=n;i++)
        p=2*p;
    return(p);
}

int strassen(int *A, int *B, int *C, int m, int n){
    if(m==2){
        int P=(*A+*(A+n+1))*(*B+*(B+n+1));  //P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])
        int Q=(*(A+n)+*(A+n+1))*(*B);       //Q=(A[1][0]+A[1][1])*B[0][0]
        int R=(*A)*(*(B+1)-*(B+n+1));       //R=A[0][0]*(B[0][1]-B[1][1])
        int S=(*(A+n+1))*(*(B+n)-*B);       //S=A[1][1]*(B[1][0]-B[0][0])
        int T=(*A+*(A+1))*(*(B+n+1));       //T=(A[0][0]+A[0][1])*B[1][1]
        int U=(*(A+n)-*A)*(*B+*(B+1));      //U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])
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