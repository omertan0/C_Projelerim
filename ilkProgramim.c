#include <stdio.h>
#include <stdlib.h>

int main () {
    printf("Omer c\n"); // \n yeni satir ekler(assagi inmemizi saglar)
    printf("Tan\n");
    printf("mesela cift tirnak bastirmayi \"orencez\"\n");
    printf("**********************************************\n");


    int sayim1,sayim2;

    sayim1=12;
    sayim2=23;
    printf("%d %d\n",sayim1,sayim2);
    printf("*******************************************\n");

    float sayim3 = 5.65;
    double sayim4 = 6.66;
    char karakter = 'A';

    printf(" 3.Sayim: %.3f 4.Sayim: %.2lf, Karakterim: %c\n", sayim3,sayim4,karakter); //.3  noktadan sonra kac basamak gosterilecek onu belirtiyo.

    printf("**************************************************************\n");

    //Kullanicidan veri alma
    //Scanf

    int sayim5;
    printf("lutfen bir sayi giriniz: ");
    scanf("%d",&sayim5); //& isareti adres demek yani sayim5 in adresinde artik su degeri tut demek
    printf("Aldigimiz sayi: %d\n",sayim5);


    printf("**************************************************************\n");


    //Kullanıcıan 2 adet sayı ve isminin baş harfini alınız bunu ekrana bastırınız

    int ilkSayim;
    float ikinciSayim;
    char basHarf;
    printf("Lutfen karakter giriniz:\n");
    scanf(" %c",&basHarf);

    printf("Lutfen ilk sayiyi giriniz:\n");
    scanf("%d",&ilkSayim);

    printf("Lutfen ikinci sayiyi giriniz:\n");
    scanf("%f",&ikinciSayim);

    printf("ilk sayim: %d ikinci Sayim: %.2f Bas harf: %n",ilkSayim,ikinciSayim,basHarf);


    printf("***************************************************************\n");


    //Hafizada ne kadar yer tutuğunu bulmak
    //sizeof

    int can = 20;

    printf("Can degiskeni hafizada %d byte yer tutar",sizeof(can));




    return 0;
}