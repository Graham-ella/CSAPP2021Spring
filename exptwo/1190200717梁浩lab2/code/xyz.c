#include <stdio.h>
int x  = 1190200717;
int main(int argc, char *argv[]){
     double y = 1903008.0717;
     static char z[100] = "1190200717-梁浩";
     printf("x = %d\n", x);
     printf("y = %f\n", y);
     printf("z = %s\n", z);
     printf("The address of x is :%p\n",&x);
     printf("The address of y is :%p\n",&y);
     printf("The address of z is :%p\n",&z);
}
