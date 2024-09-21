#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct {
    int category;
    int number;
    int price;
} Aisles;
typedef struct{
    char category;
    int aisles;
    int number;
} Buy;

int test_input(char inp[10][10],int state){
    switch(state){
        case 1:
        if(inp[4][0]!='\0' ||  inp[3][0]=='\0'){
            printf("参数数目错误，请用空格分隔参数\n按回车键继续");
            while(getchar()!='\n');
            return 0;
        }
        if(strlen(inp[0])!=1 || isalpha(inp[0][0])!=1){
            printf("货物种类只能是一个字母\n按回车键继续");
            while(getchar()!='\n');
            return 0;
        }
        int aisles=atoi(inp[1]),price=atoi(inp[2]),number=atoi(inp[3]);
        if(aisles==0 || price==0 || number==0 || aisles<=0 || aisles>5 || price<0 || price>10 || number <0){
            printf("请输入正确数据\n按回车键继续");
            while(getchar()!='\n');
            return 0;
        }
        break;
        case 2:
        if(inp[3][0]!='\0' || inp[2][0]=='\0'){
            printf("参数数目错误，请用空格分隔参数\n按回车键继续");
            while(getchar()!='\n');
            return 0;
        }
        if(strlen(inp[0])!=1 || isalpha(inp[0][0])!=1){
            printf("货物种类只能是一个字母\n按回车键继续");
            while(getchar()!='\n');
            return 0;
        }
        int aisles2=atoi(inp[1]),number2=atoi(inp[2]);
        if(aisles2==0 || number2==0 || aisles2<=0 || aisles2>5 || number2<0){
            printf("请输入正确数据\n按回车键继续");
            while(getchar()!='\n');
            return 0;
        }
        break;
    }
    return 1;
}


int main(){
    Aisles vend[5]={
        {'?',0,0},{'?',0,0},{'?',0,0},{'?',0,0},{'?',0,0}
    };
    FILE * ptr=fopen("vending_machine2_1","rb+");
    if(ptr==NULL){
        FILE * est=fopen("vending_machine2_1","wb");
        fwrite(vend,sizeof(Aisles),5,est);
        fclose(est);
        ptr=fopen("vending_machine2_1","rb+");
    }
    
    int total_price=0;
    int state=1;
    char his_inp[10][20];
    int k=0;
    while(1){
        
        fseek(ptr,0,SEEK_SET);
        fread(vend,sizeof(Aisles),5,ptr);
        system("cls");
        printf("***********自动售货机***********\n注:?代表该货道上没有货物\n");
        for (int i=0;i<5;i++){
            printf("%d号货道:货物%c %d个,单价%d元\n",i+1,vend[i].category,vend[i].number,vend[i].price);
        }

        switch (state)
        {
            case 1:
            printf("****摆货模式(输入END进入购买模式)****\n摆货时输入货物种类 货道 单价 数目\n请输入：");
            break;
        
            case 2:
            printf("****购买模式：选择货物(输入END开始购买)****\n输入货物种类 货道 数目\n");
            printf("请输入：");
            break;
            
            case 3:
            printf("当前待支付%d元\n请投币(1 2或5元)：",total_price);
            break;

            case 4:
            fclose(ptr);
            return 0;

            default:
            printf("未知错误\n");
            fclose(ptr);
            return 0;
        }
        char input[100];
        gets(input);
        char * temp=input;
        while(*temp!='\0'){
            *temp = toupper(*temp);
            temp++;
        }
        char pro_inp[10][10]={{0}};
        char * word=(char *)malloc(4);
        word=strtok(input," ");
        for (int i=0;
            word!=NULL;
            word=strtok(NULL," "))
            strncpy(pro_inp[i++],word,10);
        free(word);
        if(strcmp("END",pro_inp[0])==0){
            if(pro_inp[1][0]==0)
                state++;
            else
                printf("请输入正确数据！\n");
            continue;
        }
        else{
            switch(state){
                case 1:
                if(test_input(pro_inp,state)==1){
                    int aisles=atoi(pro_inp[1]),price=atoi(pro_inp[2]),number=atoi(pro_inp[3]);
                    if(vend[aisles-1].category!=pro_inp[0][0] && vend[aisles-1].category!='?'){
                        printf("一个货道只能存放一种货物，存放失败\n按回车继续");
                        while(getchar()!='\n');
                        continue;
                    }
                    if(vend[aisles-1].number+number>50){
                        number=50-vend[aisles-1].number;
                        printf("一个货道最多摆放50个货物，最终摆放了%d个货物\n按回车键继续",number);
                        while(getchar()!='\n');
                    }
                    if(vend[aisles-1].price!=price && vend[aisles-1].price!=0){
                        printf("检测到输入单价和已保存的商品单价不同，已修改为最后一次单价\n按回车继续");
                        while(getchar()!='\n');
                    }
                    vend[aisles-1].category=pro_inp[0][0];
                    vend[aisles-1].number+=number;
                    vend[aisles-1].price=price;
                    fseek(ptr,0,SEEK_SET);
                    fwrite(vend,sizeof(Aisles),5,ptr);
                }
                continue;
                case 2:
                if(test_input(pro_inp,state)==1){
                    int aisles=atoi(pro_inp[1]),number=atoi(pro_inp[2]);
                    if(vend[aisles-1].category=='?'){
                        printf("购买失败:该货道没有货物\n按回车键继续");
                        while(getchar()!='\n');
                        continue;
                    }
                    if(vend[aisles-1].category!=pro_inp[0][0]){
                        printf("购买失败:该货道没有该种货物\n按回车键继续");
                        while(getchar()!='\n');
                        continue;
                    }
                    if(number>vend[aisles-1].number){
                        printf("该货道上只有%d个货物，已购买%d个货物\n按回车键继续",vend[aisles-1].number,vend[aisles-1].number);
                        number=vend[aisles-1].number;
                        while(getchar()!='\n');
                    }
                    total_price+=number*vend[aisles-1].price;
                    vend[aisles-1].number-=number;
                    if(vend[aisles-1].number==0){
                        vend[aisles-1].category='?';
                        vend[aisles-1].price=0;
                    }
                    fseek(ptr,0,SEEK_SET);
                    fwrite(vend,sizeof(Aisles),5,ptr);
                }
                continue;
                case 3:
                if(test_input(pro_inp,state)==1){
                    int coin=atoi(pro_inp[0]);
                    total_price-=coin;
                    if(total_price>0)
                        continue;
                    printf("找零%d元\n按回车键退出程序",0-total_price);
                    while(getchar()!='\n');
                }
                break;
            }
        }
        break;
    }
    fclose(ptr);
    return 0;
}