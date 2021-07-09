#include "head.h"
void littleEndian() {
	endianTest temp;
	temp.a = 0x1234;
	if (temp.b == 0x12) {
		printf("The computer is BigEndian.\n");
	}
	else {
		printf("The computer is LittleEndian.\n");
	}
}