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

    
    
    
    return 0;
}