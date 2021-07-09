#include <stdio.h>
typedef unsigned char *byte_pointer;
float change(unsigned u);
void show_byte(byte_pointer start, size_t len);


typedef union{
    float f;
    unsigned u;
}unsigned_float;

int main(){

    unsigned temp_a = 0x00000000;//+0
    float a = change(temp_a);
    printf("%f\n",a);
    printf("16进制结果为:");
    show_byte(&a,sizeof(a));
    printf("\n");


    unsigned temp_b = 0x80000000;//-0
    float b = change(temp_b);
    printf("%f\n",b);
    printf("16进制结果为:");
    show_byte(&b,sizeof(b));
    printf("\n");


    unsigned temp_c = 0x00000001;//最小浮点正数
    float c = change(temp_c);
    printf("%f\n",c);
    printf("16进制结果为:");
    show_byte(&c,sizeof(c));
    printf("\n");


    unsigned temp_d = 0x7F7FFFFF;//最大浮点正数
    float d = change(temp_d);
    printf("%f\n",d);
    printf("16进制结果为:");
    show_byte(&d,sizeof(d));
    printf("\n");



    unsigned temp_e = 0x00800000;//最小正的规格化浮点数
    float e = change(temp_e);
    printf("%f\n",e);
    printf("16进制结果为:");
    show_byte(&e,sizeof(e));
    printf("\n");

    unsigned temp_f = 0x7F800000;//正无穷大
    float f = change(temp_f);
    printf("%f\n",f);
    printf("16进制结果为:");
    show_byte(&f,sizeof(f));
    printf("\n");

    unsigned temp_g = 0x7F800001;//NAN 0111 1111 1000 0000 0000 0000 0000 0001
    float g = change(temp_g);
    printf("%f\n",g);
    printf("16进制结果为:");
    show_byte((byte_pointer)&g,sizeof(g));
    printf("\n");





}

float change(unsigned u){
    unsigned_float arg;
    arg.u = u;
    return arg.f;
}

void show_byte(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%.2x ", start[i]);
    }
}

