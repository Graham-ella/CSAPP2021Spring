#include <stdio.h>
#include <string.h>
char cstr[100] = "1190200717-梁浩";
int main()
{
    char* pstr = (char*)"1190200717-梁浩";
    printf("The address of cstr is :%p\n",cstr);
    printf("The address of pstr is :%p\n",&pstr);
    printf("pstr的内容是：%s\n",pstr);
    strcpy(cstr,"1903008.0717");
    printf("修改后cstr的内容是：%s\n",cstr);
    strcpy(pstr,"1903008.0717");

    printf("修改后pstr的内容是：%s\n",pstr);


}
