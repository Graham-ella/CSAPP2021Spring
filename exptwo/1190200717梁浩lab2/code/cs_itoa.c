#include <stdio.h>
#include <stdlib.h>
#define MAX 100
char* cs_itoa(int a);
int main()
{
    int a = -12345;
    char *result = cs_itoa(a);
    printf("结果为:%s\n",result);
}
char* cs_itoa(int a){
    char* res = (char*)malloc(MAX);
    char c_temp[MAX] = "0";
    int flag = 0;//判断是否是负数，0代表正数，1代表负数
    int count = 0;
    if(a==0){
        return "0";
    }
    if(a<0){
        a = -1*a;
        flag = 1;
        *res = '-';
    }
    while(a!=0){
        int temp = a%10;
        a /= 10;
        c_temp[count++] = temp+'0';
    }
    for(int i = flag ;i<count+flag;i++){
        *(res+i) = c_temp[count-i-1+flag];
    }
    *(res+count+flag) = '\0';
    return res;

}
