#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(void) {
    
    // && --> ve
    //||--> veya
    //!--> değil
    
    int x = 25;
    int y = 20;

    printf("%d\n",x>10 && x<20); // biri yanlış sıfır döndü

    printf("%d\n",x>10 || x<20); // biri doğru olsa yeterli true döner.

    printf("%d\n",!(x>10 && x<20)); // false nin değili.

    for (int i = 0; i <= 5; i++)
    {
        printf("%d ",i);
    }


float a, b;

char op;
printf ("Lutfen operator giriniz\n");
scanf (" %c", &op) ;

printf ("Lutfen 2 adet sayi giriniz");
scanf ("%f %f", &a, &b) ;


switch (op){

case '+' :printf("%.2f + %.2f = %.2f",a, b, a+b);
break;
case '-':printf("%.2f - %.2f = %.2f",a, b, a-b);
break;
case '/':printf("%.2f / %.2f = %.2f",a, b, a/b);
break;
default: printf("Gecersiz operator\n");
}




//boolen değer tutma bunun için önce bool kütüphanesini aktif etmemiz gerekli

bool z = true;

printf("%d",z);

return 0;
    
}