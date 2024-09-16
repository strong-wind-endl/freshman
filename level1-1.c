#include <stdio.h>
#include <ctype.h>

int judge(int aisles,int price,int number){
    if( aisles==3 && price >0 && price<10 && number>0 && number<=50)
        return 0;
    return 1;
}


int main(){
    FILE * ptr=fopen("vending_machine1_1","r+");
    if(ptr==NULL){
        FILE * est=fopen("vending_machine1_1","w");
        fprintf(est,"3:? 0 0");
        fclose(est);
        ptr=fopen("vending_machine1_1","r+");
    }
    fseek(ptr,0,SEEK_SET);
    char cur_cate;
    int cur_num,cur_price;
    char category;
    int num,price,aisles;
    printf("*摆放货物*(假设只有3号通道)\n输入货物种类、货物所在的通道号、货物单价、货物个数，以空格隔开\n\
如果输入的数据多于四个，取前四个作为输入信息\n");
    while(scanf("%c %d %d %d",&category,&aisles,&price,&num)!=4
        || !isupper(category) || judge(aisles,price,num)){
        printf("请输入正确数值!\n");
        while(getchar()!='\n');
    }
    fscanf(ptr,"3:%c %d %d",&cur_cate,&cur_price,&cur_num);
    if(cur_cate!=category && cur_cate!='?'){
        printf("添加失败：一个通道只能摆放一种货物\n");
        getchar();
        fclose(ptr);
        return 0;
    }
    if(cur_price!=price && cur_price!=0)
        printf("添加货物单价与货道货物单价不同，已修改为当前单价\n");
    if(cur_num+num>50){
        printf("货道最多摆放50个货物，当前货物数目超出范围，已摆放%d个货物",50-cur_num);
        num=50-cur_num;
    }
    else{
        num+=cur_num;
    }
    printf("3:");
    for (int i=0;i<num;i++)
        putchar(category);
    printf(" %d",price);
    fseek(ptr,0,SEEK_SET);
    fprintf(ptr,"3:%c %d %d",category,price,num);
    return 0;
}