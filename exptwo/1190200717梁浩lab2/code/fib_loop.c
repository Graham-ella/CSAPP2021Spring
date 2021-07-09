#include <stdio.h>
int fib_loop(int N);

int main(){
    int res = fib_loop(46);
    printf("结果为:%d\n",res);
}
int fib_loop(int N) {
	if (N < 0) {
		return -1;
	}
	else if (N == 1 || N == 2) {
		return 1;
	}else if(N==0){
        return 0;
	}
	else {
		int sum;
		int pre = 1;
		int cur = 1;
		for (int i = 3; i <= N; i++) {
			sum = pre + cur;
			pre = cur;
			cur = sum;
		}
		return cur;
	}
}