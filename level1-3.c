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
        printf("*����״̬*\n����ֻ��1�ֻ�����?�����޻�\n");
        if(cur_aisles==0)
            printf("��ǰδ�ڷ��κλ���\n");
        else{
            printf("%d�Ż���:",cur_aisles);
            for (int i=0;i<cur_num;i++)
                putchar(cur_cate);
            printf("(%d��)  ����%dԪ\n",cur_num,cur_price);
        }
        char category;
        int arisles,number=0,price=0;
        switch (state){
            case 0:
            printf("����\t1���� �ڻ�ģʽ \n\t2���� ����ģʽ\n\t3�˳�����\n:");
            while(scanf("%d",&state)!=1
                || state>3 || state<0){
                    printf("��������ȷ��ֵ��\n:");
                    while(getchar()!='\n');
            }
            while(getchar()!='\n');
            continue;
            case 1:
            printf("*�ڷŻ���*\n�������������(��д��������Ӧ��ģʽ������ת��ģʽ)��");
            while(scanf("%c",&input)!=1
                ||(!isupper(input) && (input>'3' || input<='0'))){
                    printf("��������ȷ��ֵ\n:");
                    if(input!='\n') while(getchar()!='\n');
            }
            while(getchar()!='\n');
            
            if(isupper(input)){
                category=input;
                if(cur_cate!=category && cur_cate!='?'){
                    printf("һ������ֻ�ܰڷ�һ�ֻ������������(���س�������)");
                    while(getchar()!='\n');
                    continue;
                }
                printf("���������ͨ����");
                while(scanf("%d",&arisles)!=1 || arisles > 5 || arisles <1){
                    printf("��������ȷ����\n:");
                    if(input!='\n') while(getchar()!='\n');
                }
                while(getchar()!='\n');
                if(arisles!=cur_aisles && cur_aisles!=0){
                    printf("��ǰ�������ѱ���Ļ�������������������!(���س�������)\n");
                    while(getchar()!='\n');
                    continue;
                }
                printf("������ڷ���Ŀ��");
                while(scanf("%d",&number)!=1 || number==0){
                    printf("��������ȷ����\n:");
                    if(input!='\n') while(getchar()!='\n');
                }
                while(getchar()!='\n');
                if(number+cur_num>50){
                    printf("�������ڷ�50����Ʒ����˰ڷ���%d����Ʒ\n",50-cur_num);
                    number=50-cur_num;
                }
                cur_num+=number;
                printf("�����뵥�ۣ�");
                while(scanf("%d",&price)!=1 || price<=0 || price>=10){
                    printf("��������ȷ����\n:");
                    if(input!='\n') while(getchar()!='\n');
                }
                while(getchar()!='\n');
                if(price!=cur_price && cur_price!=0 ){
                    printf("��⵽���뵥�ۺ��ѱ������Ʒ���۲�ͬ�����޸�Ϊ���һ�ε���\n���س�����");
                    while(getchar()!='\n');
                }
                cur_price=price;
                fseek(ptr,0,SEEK_SET);
                fprintf(ptr,"%d:%c %d %d",arisles,category,cur_price,cur_num);
                system("cls");
                printf("*����״̬*(����ֻ��1�ֻ�����?�����޻�)\n");
                if(cur_aisles==0)
                    printf("��ǰδ�ڷ��κλ���\n");
                else{
                    printf("%d�Ż���:",cur_aisles);
                    for (int i=0;i<cur_num;i++)
                        putchar(cur_cate);
                    printf("(%d��)  ����%dԪ\n",cur_num,cur_price);
                }
            }
            else{
                if(state)
                state=input-'0';
            }
            continue;

            case 2:
            printf("*�������*\n");
            if(cur_aisles==0){
                printf("��ǰû�л����ȡ\n���س�����");
                getchar();
                state=0;
                continue;
            }
            printf("��ǰ��%d�Ż�������%c������빺������:",cur_aisles,cur_cate);
            while(scanf("%d",&number)!=1
                || number <= 0)
            {
                printf("��������ȷ����\n:");
                if(input!='\n') while(getchar()!='\n');
            }
            while(getchar()!='\n');
            if(number > cur_num){
                printf("��ǰ�����ϰڷ���%d����Ʒ��С�������������Ŀ�����չ���%d��\n",cur_num);
                number=cur_num;
            }
            int total=cur_price*number;
            printf("�ܼ�%dԪ\n",total);
            while(total>0){
                printf("��Ͷ�ң�");
                int cions;
                while(scanf("%d",&cions)!=1
                    ||(cions!=1 &&  cions!=2 && cions!=5)){
                printf("��������ȷ��ֵ!\n��Ͷ�ң�");
                while(getchar()!='\n');
                }
                total-=cions;
            }
            while(getchar()!='\n');
            printf("����%dԪ\n���س�����",0-total);
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