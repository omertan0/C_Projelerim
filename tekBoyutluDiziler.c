#include <stdio.h>
#include <stdint.h>

int main(void) {
    
    int dizi[10]; 
    int i;

    for ( i = 0; i < 10; i++)
    {
        dizi[i]=2*i;
    }
    for ( i = 0; i < 10; i++)
    {
        printf("%d\n",dizi[i]);
        
    }

    //Sayı dizilerini kullanıcıdan alıp onra bastırma
    

    int dizi_2 [3];

    printf("dizi elemanlarini giriniz");

    for (int i = 0; i < sizeof(dizi_2)/sizeof(dizi_2[0]); i++) // sizeof(dizi_2)/sizeof(dizi_2[0]--> burada dizinin kaç toplam boyutunu 1 elemamnın boyutuna bölerek dizi sayısını hesaplıyoz.
    {
        scanf("%d",&dizi_2[i]);
    }

    for (int i = 0; i < sizeof(dizi_2)/sizeof(dizi_2[0]); i++)
    {
        printf("%d\t",dizi_2[i]);
    }
    
    

    
    
    
    return 0;
}