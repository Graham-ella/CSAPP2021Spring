#include <stdio.h>
int main(){
    float a = 1.0;
    float b = 0;
    *((unsigned *)(&b)) = 0x1;
    printf("浮点数除以0的结果为:%f\n",a/0);
    printf("浮点数除以极小浮点数的结果为:%f\n",a/b);
}