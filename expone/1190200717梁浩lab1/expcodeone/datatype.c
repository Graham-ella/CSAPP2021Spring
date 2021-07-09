#include "head.h"


//��ӡÿ�������ı�����������ֵ��������ַ��������Ӧ16���Ƶ��ڴ���ֽ�

short short_num = 717;
int int_num =   1190200717;
long long_num = 1903008071;


float f_num = 123456.123456f;
double d_num = 1190200717.1903008;

char char_num = 'L';

char* point_char = &char_num;

endianTest union_num;

Demo struct_test = {17,'H'};

enum DAY

{

	mon = 1, tue=2, wed=3

}day;

void vector_print() {
	
	printf("short_num = %d , ������ַΪ:%p , ��Ӧ16����Ϊ:", short_num, &short_num);
	show_bytes(&short_num, sizeof(short));
	printf("\n");

	printf("char_num = %c , ������ַΪ:%p , ��Ӧ16����Ϊ:", char_num, &char_num);
	show_bytes(&char_num, sizeof(char));
	printf("\n");

	printf("int_num = %d , ������ַΪ:%p , ��Ӧ16����Ϊ:", int_num, &int_num);
	show_bytes(&int_num, sizeof(int));
	printf("\n");

	printf("long_num = %ld , ������ַΪ:%p , ��Ӧ16����Ϊ:", long_num, &long_num);
	show_bytes(&long_num, sizeof(long));
	printf("\n");

	printf("f_num = %f , ������ַΪ:%p , ��Ӧ16����Ϊ:", f_num, &f_num);
	show_bytes(&f_num, sizeof(float));
	printf("\n");

	printf("d_num = %lf, ������ַΪ:%p , ��Ӧ16����Ϊ:", d_num, &d_num);
	show_bytes(&d_num, sizeof(long));
	printf("\n");

	printf("point_char = %c, ������ַΪ:%p , ��Ӧ16����Ϊ:", *point_char, &point_char);
	show_bytes(&point_char, sizeof(char*));
	printf("\n");

	
	
	union_num.a = 43;
	printf("union_num.a = %d, ������ַΪ:%p , ��Ӧ16����Ϊ:", union_num.a, &union_num.a);
	show_bytes(&union_num.a, sizeof(union_num.a));
	printf("\n");
	printf("union_num.b = %c, ������ַΪ:%p , ��Ӧ16����Ϊ:", union_num.b, &union_num.b);
	show_bytes(&union_num.b, sizeof(union_num.b));
	printf("\n");

	printf("struct_test.x = %d, ������ַΪ:%p , ��Ӧ16����Ϊ:", struct_test.x, &struct_test.x);
	show_bytes(&struct_test.x, sizeof(struct_test.x));
	printf("\n");
	printf("struct_test.y = %c, ������ַΪ:%p , ��Ӧ16����Ϊ:", struct_test.y, &struct_test.y);
	show_bytes(&struct_test.y, sizeof(struct_test.y));
	printf("\n");

	day = mon;
	printf("day_mon = %d, ������ַΪ:%p , ��Ӧ16����Ϊ:", day, &day);
	show_bytes(&day, sizeof(day));
	printf("\n");
	day = tue;
	printf("day_tue = %d, ������ַΪ:%p , ��Ӧ16����Ϊ:", day, &day);
	show_bytes(&day, sizeof(day));
	printf("\n");
	day = wed;
	printf("day_wed = %d, ������ַΪ:%p , ��Ӧ16����Ϊ:", day, &day);
	show_bytes(&day, sizeof(day));
	printf("\n");
	


	

}



