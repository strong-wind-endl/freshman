#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//������������ļ��������ۻ�����״̬�ᱣ����vending_machine2_1��

//�����������
typedef struct {
    int category;
    int number;
    int price;
} Aisles;

//��������ʽ�Ƿ������ͬ��״̬�в�ͬ�ļ��ԭ��
int test_input(char inp[10][10],int state);

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
    
    int total_price=0;//�ñ������ڼ���۸�����
    int state=1;
    char his_inp[10][20];
    while(1){
        
        fseek(ptr,0,SEEK_SET);
        fread(vend,sizeof(Aisles),5,ptr);


        //����ۻ���״̬
        system("cls");
        printf("***********�Զ��ۻ���***********\nע:?����û�����û�л���\n");
        for (int i=0;i<5;i++){
            printf("%d�Ż���:����%c %d��,����%dԪ\n",i+1,vend[i].category,vend[i].number,vend[i].price);
        }
        switch (state)
        {
            case 1:
            printf("****�ڻ�ģʽ(����END���빺��ģʽ)****\n�ڻ�ʱ����������� ���� ���� ��Ŀ\n�����룺");
            break;
        
            case 2:
            printf("****����ģʽ��ѡ�����(����END��ʼ����)****\n����������� ���� ��Ŀ\n");
            printf("�����룺");
            break;
            
            case 3:
            printf("��ǰ��֧��%dԪ\n��Ͷ��(1 2��5Ԫ)��",total_price);
            break;

            case 4:
            state--;

            default:
            printf("δ֪����\n");
            fclose(ptr);
            return 0;
        }


        //��ȡ���룬����������д����Կո�Ϊ��־������ֿ�
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

        //��������Ƿ���END���ǵĻ�������һ��״̬
        if(strcmp("END",pro_inp[0])==0){
            if(pro_inp[1][0]==0)
                state++;
            else
                printf("��������ȷ���ݣ�\n");
            continue;
        }

        //
        else{
            switch(state){
                case 1://�ڷŻ���״̬
                if(test_input(pro_inp,state)==1){
                    int aisles=atoi(pro_inp[1]),price=atoi(pro_inp[2]),number=atoi(pro_inp[3]);
                    //���¼���if���Ǽ�����������Ƿ����
                    if(vend[aisles-1].category!=pro_inp[0][0] && vend[aisles-1].category!='?'){
                        printf("һ������ֻ�ܴ��һ�ֻ�����ʧ��\n���س�����");
                        while(getchar()!='\n');
                        continue;
                    }
                    if(vend[aisles-1].number+number>50){
                        number=50-vend[aisles-1].number;
                        printf("һ���������ڷ�50��������հڷ���%d������\n���س�������",number);
                        while(getchar()!='\n');
                    }
                    if(vend[aisles-1].price!=price && vend[aisles-1].price!=0){
                        printf("��⵽���뵥�ۺ��ѱ������Ʒ���۲�ͬ�����޸�Ϊ���һ�ε���\n���س�����");
                        while(getchar()!='\n');
                    }

                    //ͨ�����󣬽�����д���ļ�
                    vend[aisles-1].category=pro_inp[0][0];
                    vend[aisles-1].number+=number;
                    vend[aisles-1].price=price;
                    fseek(ptr,0,SEEK_SET);
                    fwrite(vend,sizeof(Aisles),5,ptr);
                }
                continue;


                case 2:
                if(test_input(pro_inp,state)==1){
                    //���¼���if���Ǽ�����������Ƿ����
                    int aisles=atoi(pro_inp[1]),number=atoi(pro_inp[2]);
                    if(vend[aisles-1].category=='?'){
                        printf("����ʧ��:�û���û�л���\n���س�������");
                        while(getchar()!='\n');
                        continue;
                    }
                    if(vend[aisles-1].category!=pro_inp[0][0]){
                        printf("����ʧ��:�û���û�и��ֻ���\n���س�������");
                        while(getchar()!='\n');
                        continue;
                    }
                    if(number>vend[aisles-1].number){
                        printf("�û�����ֻ��%d������ѹ���%d������\n���س�������",vend[aisles-1].number,vend[aisles-1].number);
                        number=vend[aisles-1].number;
                        while(getchar()!='\n');
                    }

                    //�������󣬼����ܼۣ���������д���ļ�
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



                case 3://Ͷ��ģʽ
                if(test_input(pro_inp,state)==1){
                    int coin=atoi(pro_inp[0]);
                    total_price-=coin;
                    if(total_price>0)
                        continue;
                    printf("����%dԪ\n���س����˳�����",0-total_price);
                    while(getchar()!='\n');
                }
                else
                    continue;
                break;
            }
        }
        break;
    }
    fclose(ptr);
    return 0;
}


int test_input(char inp[10][10],int state){
    int coin;
    switch(state){
        case 1://�ڻ�״̬�ļ��
        if(inp[4][0]!='\0' ||  inp[3][0]=='\0'){//��������Ŀ
            printf("������Ŀ�������ÿո�ָ�����\n���س�������");
            while(getchar()!='\n');
            return 0;
        }
        if(strlen(inp[0])!=1 || isalpha(inp[0][0])!=1){//�������������룬�ų�����"AB"����"?"�����
            printf("��������ֻ����һ����ĸ\n���س�������");
            while(getchar()!='\n');
            return 0;
        }
        int aisles=atoi(inp[1]),price=atoi(inp[2]),number=atoi(inp[3]);//��һ���������ĵ��۵��Ƿ�����Ƿ��ڷ�Χ��
        if(aisles==0 || price==0 || number==0 || aisles<=0 || aisles>5 || price<0 || price>10 || number <0){
            printf("��������ȷ����\n���س�������");
            while(getchar()!='\n');
            return 0;
        }
        break;
        case 2://����ģʽ(ѡ�����ģʽ�ļ��)
        if(inp[3][0]!='\0' || inp[2][0]=='\0'){
            printf("������Ŀ�������ÿո�ָ�����\n���س�������");
            while(getchar()!='\n');
            return 0;
        }
        if(strlen(inp[0])!=1 || isalpha(inp[0][0])!=1){
            printf("��������ֻ����һ����ĸ\n���س�������");
            while(getchar()!='\n');
            return 0;
        }
        int aisles2=atoi(inp[1]),number2=atoi(inp[2]);
        if(aisles2==0 || number2==0 || aisles2<=0 || aisles2>5 || number2<0){
            printf("��������ȷ����\n���س�������");
            while(getchar()!='\n');
            return 0;
        }
        break;
        case 3://Ͷ��״̬�ļ��
        coin=atoi(inp[0]);
        if(coin==0 || inp[1][0]!='\0'){
            printf("Ͷ�Ҵ�����������ȷ��ֵ\n���س�����");
            while(getchar()!='\n');
            return 0;
        }
        break;
    }
    return 1;
}
