#include <stdio.h>
#include <stdint.h>

int main(void) {

int dizi [2][2] = {{1,2},{3,4}};

printf("%d\t %d\n",dizi[0][0],dizi[1][1]);





//Diagonal matris oluşturma.

int matris [10][10];
int i,j;
for ( i = 0; i < 10; i++)
{
    for (j = 0; j < 10; j++)
    {
        if (i==j)
        {
            matris [i][j]=1;
        }
        else
        matris[i][j]=0;
        
    
    }
    

}

for ( i = 0; i < 10; i++)
{
    for (j = 0; j < 10; j++)
    {
        printf("%4d",matris[i][j]);
    
    }

    printf("\n");
    

}



printf("******************************************\n");

int dizil [3] [4]={ {1, 2, 5, 7} , {5, 4, 8, 6} , {7, 1, 6, 5} } ;
int dizi2 [3] [4] ={ {1, 8, 5, 7} , {1, 2, 4, 6} , {3, 7, 3, 1} } ;
int toplam [3][4];


for ( int i = 0; i < 3; i++)
{
    for ( int j=0; j < 4;j++){
        toplam[i][j]=  dizil [i] [j] + dizi2 [i] [j];
    }
}

for ( int i = 0; i < 3; i++)
{
    for (int j=0; j < 4;j++){
        printf("%4d",toplam[i][j]);
    }
    printf("\n");
}






return 0;
}