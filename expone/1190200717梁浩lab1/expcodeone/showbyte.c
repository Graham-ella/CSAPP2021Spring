#include "head.h"
void show_bytes(byte_pointer num, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%.2x", num[i]);
	}
}

void showByte() {
	char c;
	FILE* fp;
	int flag = 0;
	int back = 16;
	if ((fp = fopen("./hellowin.c", "r")) == NULL) {
		printf("Cannot open file, press any key to exit!");
		exit(1);
	}
	while (!flag) {	
		for (int i = 0; i < 16; i++) {
			if ((c = fgetc(fp)) != EOF) {
				putchar(c);
			}
			/*
			else if (c == '\n') {
				c = ' ';
				putchar(c);
			}
			*/
			else {
				flag = 1;
				back = i + 1;
				//back = i;
				break;
			}
		}

		putchar('\n');
		fseek(fp, -back, SEEK_CUR);
		for (int j = 0; j < 16; j++) {
			if ((c = fgetc(fp)) != EOF) {
				show_bytes(&c, sizeof(char));
				putchar(' ');
			}
			else {
				flag = 1;
				break;
			}
		}
		putchar('\n');

	}
}


