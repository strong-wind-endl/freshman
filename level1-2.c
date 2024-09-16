#include <stdio.h>

int main(){
    int price;
    printf("输入货物总价：");
    while(scanf("%d",&price)!=1){
        printf("请输入正确数值!\n");
        while(getchar()!='\n');
    }
    while(price>0){
        printf("请投币：");
        int cions;
        while(scanf("%d",&cions)!=1
            ||(cions!=1 &&  cions!=2 && cions!=5)){
            printf("请输入正确数值!\n请投币：");
            while(getchar()!='\n');
        }
        price-=cions;
    }
    printf("找零%d元\n",0-price);
    return 0;
}