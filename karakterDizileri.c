#include <stdio.h>
#include <stdint.h>

int main(void) {

    char can[]={'c', 'a','n','a', 'n','\0'};

char dizim[]="canan";
char kullanici [100];

printf("%s\n",dizim);

printf("Lutfen bir karakter dizisi giriniz\n");
scanf ("%s", &kullanici) ;

printf("\n");
printf ("%s", kullanici);

    return 0;
}