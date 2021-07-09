#include "head.h"

int main() {
	
	printf("helloWin函数运行结果:");
	helloWin();
	putchar('\n');

	printf("showByte函数运行结果:\n");
	showByte();
	putchar('\n');

	printf("vector_print函数运行结果:\n");
	vector_print();
	printf("main函数的地址为:%p\n", main);
	printf("printf函数的地址为:%p\n", printf);
	putchar('\n');
	
	printf("littleEndian函数运行结果:\n");
	littleEndian();
	putchar('\n');

	printf("WordSize函数运行结果:\n");
	WordSize();
	putchar('\n');
	


}