#include <stdio.h>
int utf8len(char* s);

int main()
{
    char *s = "1190200717梁浩";
    int res = utf8len(s);
    printf("The length of %s is : %d\n",s,res);
}

int utf8len(char* s){
    int result = 0;
    char *p = s;
    while(*p!='\0'){
        if((*p & 0x80) == 0 ){
            p++;
            result++;
        }else if((*p & 0xE0) == 0xC0){
            p+=2;
            result++;
        }else if((*p & 0xF0) == 0xE0){
            p+=3;
            result++;
        }else if((*p & 0xF8) == 0xF0){
            p+=4;
            result++;
        }else{
            printf("编码错误！");
            return -1;
        }


    }
    return result;
}
