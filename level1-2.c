#include <stdio.h>

int main(){
    int price;
    printf("��������ܼۣ�");
    while(scanf("%d",&price)!=1){
        printf("��������ȷ��ֵ!\n");
        while(getchar()!='\n');
    }
    while(price>0){
        printf("��Ͷ�ң�");
        int cions;
        while(scanf("%d",&cions)!=1
            ||(cions!=1 &&  cions!=2 && cions!=5)){
            printf("��������ȷ��ֵ!\n��Ͷ�ң�");
            while(getchar()!='\n');
        }
        price-=cions;
    }
    printf("����%dԪ\n",0-price);
    return 0;
}