#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(void) {

    //ceil floor sqrt pow abs

    printf("%.2f\n",ceil(1.2)); //üste yuvarla
    printf("%.2f\n",floor(1.8)); //alta yuvarla
    printf("%.2f\n",sqrt(81)); //karekök
    printf("%.2f\n",pow(2,4)); //üs alma
    printf("%d\n",abs(-4)); //Mutlak değer alma fakat sadece tamsayılarınkini alrı


    //Casting 

    float sayı = (float)9/4; //burada casting yaptık çünkü int bir sayıyı int sayıya bölünce sonuç int oluyodu.
    printf("%f",sayı);
    
    
    
    
    
    
    
    return 0;
}