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
    printf("*�ڷŻ���*(����ֻ��3��ͨ��)\n����������ࡢ�������ڵ�ͨ���š����ﵥ�ۡ�����������Կո����\n\
�����������ݶ����ĸ���ȡǰ�ĸ���Ϊ������Ϣ\n");
    while(scanf("%c %d %d %d",&category,&aisles,&price,&num)!=4
        || !isupper(category) || judge(aisles,price,num)){
        printf("��������ȷ��ֵ!\n");
        while(getchar()!='\n');
    }
    fscanf(ptr,"3:%c %d %d",&cur_cate,&cur_price,&cur_num);
    if(cur_cate!=category && cur_cate!='?'){
        printf("���ʧ�ܣ�һ��ͨ��ֻ�ܰڷ�һ�ֻ���\n");
        getchar();
        fclose(ptr);
        return 0;
    }
    if(cur_price!=price && cur_price!=0)
        printf("��ӻ��ﵥ����������ﵥ�۲�ͬ�����޸�Ϊ��ǰ����\n");
    if(cur_num+num>50){
        printf("�������ڷ�50�������ǰ������Ŀ������Χ���Ѱڷ�%d������",50-cur_num);
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