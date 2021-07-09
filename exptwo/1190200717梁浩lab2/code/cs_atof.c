#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double cs_atof(char *s);

int main()
{
    char *s = "12345.102234";
    double result = cs_atof(s);
    printf("result = %f\n",result);
}

double cs_atof(char *s){
    double res = 0;
    int flag = 0;//判断字符串是否带负号，flag = 0 代表 正
    int point = 0;//代表有没有读到小数点了, 0代表没读到
    if(*s=='-'){
        flag = 1;
    }
    char *p = (s+flag);
    for(;*p!='\0'&& !point;p++){
        if(*p == '.'){
            point = 1;
        }else{
            res = 10*res + *p-'0';
        }
    }

     for(;*p!='\0';p++,point++){
        double temp = *p-'0';
        for(int i =1;i<=point;i++){
            temp/=10;
        }
        res += temp;
    }

    return flag?(-1)*res:res;
}
