#include <stdio.h>
int dp_int[100]={0};
long dp_long[100]={0};
unsigned int dp_unsigned_int[100]={0};
unsigned long dp_unsigned_long[100]={0};

int fib_dg_int(int N);
long fib_dg_long(int N);
unsigned int fib_dg_unsigned_int(int N);
unsigned long fib_dg_unsigned_long(int N);

int main(){
    int res_int = fib_dg_int(47);
    printf("该项值为:%d\n",res_int);


    long res_long = fib_dg_long(47);
    printf("该项值为:%ld\n",res_long);

    unsigned int res_unsigned_int = fib_dg_unsigned_int(47);
    printf("该项值为:%u\n",res_unsigned_int);

    unsigned long res_unsigned_long = fib_dg_unsigned_long(47);
    printf("该项值为:%lu\n",res_unsigned_long);

    return 0;



}

int fib_dg_int(int N) {
	if (N == 1 || N == 2) {
		dp_int[N] = 1;
		return 1;
	}
	else if (N == 0) {
		dp_int[N] = 0;
		return 0;
	}else if(N<0){
        return -1;
	}
	else {
		if(dp_int[N]!=0){
            return dp_int[N];
		}else{
		    dp_int[N] = fib_dg_int(N-1)+fib_dg_int(N-2);
		    return dp_int[N];
		}
		//return (fib_dg(N - 1) + fib_dg(N - 2));
	}
}

long fib_dg_long(int N){
    if (N == 1 || N == 2) {
		dp_long[N] = 1;
		return 1;
	}
	else if (N == 0) {
		dp_long[N] = 0;
		return 0;
	}else if(N<0){
        return -1;
	}
	else {
		if(dp_long[N]!=0){
            return dp_long[N];
		}else{
		    dp_long[N] = fib_dg_long(N-1)+fib_dg_long(N-2);
		    return dp_int[N];
		}
		//return (fib_dg(N - 1) + fib_dg(N - 2));
	}
}

unsigned int fib_dg_unsigned_int(int N){
    if (N == 1 || N == 2) {
		dp_unsigned_int[N] = 1;
		return 1;
	}
	else if (N == 0) {
		dp_unsigned_int[N] = 0;
		return 0;
	}else if(N<0){
        return -1;
	}
	else {
		if(dp_unsigned_int[N]!=0){
            return dp_unsigned_int[N];
		}else{
		    dp_unsigned_int[N] = fib_dg_unsigned_int(N-1)+fib_dg_unsigned_int(N-2);
		    return dp_unsigned_int[N];
		}
		//return (fib_dg(N - 1) + fib_dg(N - 2));
	}
}

unsigned long  fib_dg_unsigned_long(int N) {
	if (N == 1 || N == 2) {
		dp_unsigned_long[N] = 1;
		return 1;
	}
	else if (N == 0) {
		dp_unsigned_long[N] = 0;
		return 0;
	}else if(N<0){
        return -1;
	}
	else {
		if(dp_unsigned_long[N]!=0){
            return dp_unsigned_long[N];
		}else{
		    dp_unsigned_long[N] = fib_dg_unsigned_long(N-1)+fib_dg_unsigned_long(N-2);
		    return dp_unsigned_long[N];
		}
		//return (fib_dg(N - 1) + fib_dg(N - 2));
	}
}
