#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    FILE * ptr=fopen("vending_machine1_3","r+");
    if(ptr==NULL){
        FILE * est=fopen("vending_machine1_3","w");
        fprintf(est,"0:? 0 0");
        fclose(est);
        ptr=fopen("vending_machine1_3","r+");
    }
    
    char cur_cate;
    int state=0,cur_price,cur_num,cur_aisles;
    while(1){
        fseek(ptr,0,SEEK_SET);
        fscanf(ptr,"%d:%c %d %d",&cur_aisles,&cur_cate,&cur_price,&cur_num);
        char input;
        system("cls");
        printf("*货道状态*\n假设只有1种货道，?代表无货\n");
        if(cur_aisles==0)
            printf("当前未摆放任何货物\n");
        else{
            printf("%d号货道:",cur_aisles);
            for (int i=0;i<cur_num;i++)
                putchar(cur_cate);
            printf("(%d个)  单价%d元\n",cur_num,cur_price);
        }
        char category;
        int arisles,number=0,price=0;
        switch (state){
            case 0:
            printf("输入\t1进入 摆货模式 \n\t2进入 购买模式\n\t3退出程序\n:");
            while(scanf("%d",&state)!=1
                || state>3 || state<0){
                    printf("请输入正确数值！\n:");
                    while(getchar()!='\n');
            }
            while(getchar()!='\n');
            continue;
            case 1:
            printf("*摆放货物*\n请输入货物种类(大写，或者相应的模式代码以转换模式)：");
            while(scanf("%c",&input)!=1
                ||(!isupper(input) && (input>'3' || input<='0'))){
                    printf("请输入正确数值\n:");
                    if(input!='\n') while(getchar()!='\n');
            }
            while(getchar()!='\n');
            
            if(isupper(input)){
                category=input;
                if(cur_cate!=category && cur_cate!='?'){
                    printf("一个货道只能摆放一种货物，请重新输入(按回车键继续)");
                    while(getchar()!='\n');
                    continue;
                }
                printf("请输入货物通道：");
                while(scanf("%d",&arisles)!=1 || arisles > 5 || arisles <1){
                    printf("请输入正确数据\n:");
                    if(input!='\n') while(getchar()!='\n');
                }
                while(getchar()!='\n');
                if(arisles!=cur_aisles && cur_aisles!=0){
                    printf("当前货道与已保存的货道不符，请重新输入!(按回车键继续)\n");
                    while(getchar()!='\n');
                    continue;
                }
                printf("请输入摆放数目：");
                while(scanf("%d",&number)!=1 || number==0){
                    printf("请输入正确数据\n:");
                    if(input!='\n') while(getchar()!='\n');
                }
                while(getchar()!='\n');
                if(number+cur_num>50){
                    printf("货道最多摆放50个商品，因此摆放了%d个商品\n",50-cur_num);
                    number=50-cur_num;
                }
                cur_num+=number;
                printf("请输入单价：");
                while(scanf("%d",&price)!=1 || price<=0 || price>=10){
                    printf("请输入正确数据\n:");
                    if(input!='\n') while(getchar()!='\n');
                }
                while(getchar()!='\n');
                if(price!=cur_price && cur_price!=0 ){
                    printf("检测到输入单价和已保存的商品单价不同，已修改为最后一次单价\n按回车继续");
                    while(getchar()!='\n');
                }
                cur_price=price;
                fseek(ptr,0,SEEK_SET);
                fprintf(ptr,"%d:%c %d %d",arisles,category,cur_price,cur_num);
                system("cls");
                printf("*货道状态*(假设只有1种货道，?代表无货)\n");
                if(cur_aisles==0)
                    printf("当前未摆放任何货物\n");
                else{
                    printf("%d号货道:",cur_aisles);
                    for (int i=0;i<cur_num;i++)
                        putchar(cur_cate);
                    printf("(%d个)  单价%d元\n",cur_num,cur_price);
                }
            }
            else{
                if(state)
                state=input-'0';
            }
            continue;

            case 2:
            printf("*购买货物*\n");
            if(cur_aisles==0){
                printf("当前没有货物可取\n按回车继续");
                getchar();
                state=0;
                continue;
            }
            printf("当前从%d号货道购买%c货物，输入购买数量:",cur_aisles,cur_cate);
            while(scanf("%d",&number)!=1
                || number <= 0)
            {
                printf("请输入正确数据\n:");
                if(input!='\n') while(getchar()!='\n');
            }
            while(getchar()!='\n');
            if(number > cur_num){
                printf("当前货架上摆放着%d个商品，小于您所购买的数目，最终购买%d个\n",cur_num);
                number=cur_num;
            }
            int total=cur_price*number;
            printf("总价%d元\n",total);
            while(total>0){
                printf("请投币：");
                int cions;
                while(scanf("%d",&cions)!=1
                    ||(cions!=1 &&  cions!=2 && cions!=5)){
                printf("请输入正确数值!\n请投币：");
                while(getchar()!='\n');
                }
                total-=cions;
            }
            while(getchar()!='\n');
            printf("找零%d元\n按回车继续",0-total);
            while(getchar()!='\n');
            cur_num-=number;
            if(cur_num==0){
                cur_aisles=0;
                cur_cate='?';
                cur_price=0;
                fseek(ptr,0,SEEK_SET);
                fprintf(ptr,"0:? 0 0");
            }
            else{
                fseek(ptr,0,SEEK_SET);
                fprintf(ptr,"%d:%c %d %d",cur_aisles,cur_cate,cur_price,cur_num);
            }
            continue;
            case 3:
            break;
        }
        break;
    }
    fclose(ptr);
    return 0;
}