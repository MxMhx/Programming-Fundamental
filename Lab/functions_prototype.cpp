#include <stdio.h>

int isPrime(int x){
	int check = 0;
	for(int i = 1;i<=x;i++){
		if(x%i == 0) check ++;
	}
	if(check == 2)
		return 1;
	else
		return 0;
}

int main() {
	int a;
	scanf("%d",&a);
	if (isPrime(a) == 1) printf("prime number");
	else printf("not prime number");
	return 0;
}




