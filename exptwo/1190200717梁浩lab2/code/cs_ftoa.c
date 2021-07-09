#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//#define min 3e-5
char* cs_ftoa(double a);
int main()
{

    double a = 123.45;
    char* result = cs_ftoa(a);
    printf("result is : %s\n",result);
    return 0;
}

char* cs_ftoa(double a){
    char* res = (char*)malloc(MAX);
    char c_zhengshu[MAX] = "0";
    char c_xiaoshu[MAX] = "0";
    int flag = 0;//判断是否是负数，0代表正数，1代表负数
    int count_zhengshu = 0;
    int count_xiaoshu = 0;
    if(a==0){
        return "0.000000";
    }
    if(a<0){
        a = -a;
        flag = 1;
        *res = '-';
    }
    int a_int = (int)a;
    while(a_int!=0){
        int temp = a_int%10;
        a_int /= 10;
        c_zhengshu[count_zhengshu++] = temp+'0';
    }
    double a_xiaoshu = a-(int)a;
    while(a_xiaoshu!=0){
        a_xiaoshu *= 10;
        int temp1 = (int)a_xiaoshu;
        c_xiaoshu[count_xiaoshu++] = temp1+'0';
        a_xiaoshu = a_xiaoshu-(int)a_xiaoshu;
    }

    for(int i = flag ;i<count_zhengshu+flag;i++){
        *(res+i) = c_zhengshu[count_zhengshu-i-1+flag];
    }
    *(res+count_zhengshu+flag) = '.';
    for(int j = 1;j<=count_xiaoshu;j++){
        *(res+j+count_zhengshu+flag) = c_xiaoshu[j-1];
    }
    *(res+count_xiaoshu+count_zhengshu+1)='\0';
    return res;



}

