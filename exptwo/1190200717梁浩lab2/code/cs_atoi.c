#include <stdio.h>
int cs_atoi(char *s);
int main()
{
    char *s = "-1234";
    int res = cs_atoi(s);
    printf("res = %d\n",res);
}

int cs_atoi(char *s){
    int flag = 0;
    int sum = 0;
    if(*s == '-'){
        flag = 1;
    }
    for(char *p = (s+flag);*p!='\0';p++){
        sum  = 10*sum + ( *p- '0' );
    }
    return flag?(-1)*sum:sum;

}
