#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
    
    
    char dizi []= "Aralik";
    

    // 1. Strlen--> Dizi uzunluğunu verir
    printf("Dizimizin uzunlugu: %d\n",strlen(dizi));
    printf("Dizimizin uzunlugu: %d",sizeof(dizi));  //\0 ı aldığı için 7 oldu.
    
    
    
    return 0;
}