#include<cstdio>
using namespace std;

/*
a ÷ b (mod mod)를 구하는 코드 
즉, (a * b^(mod-2)) % mod를 계산 
*/
int divide(int a, int b, int mod) {	
	int ret = a;						
	int gob = b;			//gob = b, b^2, b^4, b^8, ...(% mod)
	
	// time : (mod-2)의 이진수 표현에서 1이 어디에 있는지 알아내기 위한 변수
	for ( int time = mod - 2 ; time ; time = time / 2 ) {
		if ( time % 2 == 1 ) {
			ret = (long long int)ret * gob % mod;
		}
		gob = (long long int)gob * gob % mod;
	}
	return ret;
}

int main(){
	int a, b, mod;
	scanf("%d %d %d", &a, &b, &mod);
	printf("%d", divide(a, b, mod));
}
