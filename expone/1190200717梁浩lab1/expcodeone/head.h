#include <stdio.h>
#include <string.h>
#include <limits.h>


#pragma warning(disable:4996)

typedef unsigned char* byte_pointer;

typedef union{
	int a;
	char b;
}endianTest;

typedef struct demo {
	int x;
	char y;
}Demo;



void helloWin();
void show_bytes(byte_pointer num, size_t len);
void showByte();
void vector_print();
void littleEndian();
void WordSize();

extern short short_num;
extern int int_num;
extern long long_num;
extern char char_num;
extern float f_num;
extern double d_num;
extern char* point_char;


