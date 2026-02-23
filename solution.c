#include <stdio.h>
int main() {
	int n, b, x;
	long long s;
	scanf("%d", &n);
	scanf("%d", &x);
        s=x;
	for(int i=1; i<n; i++){
	    scanf("%d", &b);
	    s+=b;
	    if(b>x)
	    x=b;
	}
	printf("%lld",(1LL*n*x)-s);
}

