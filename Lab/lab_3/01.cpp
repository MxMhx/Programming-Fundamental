#include <stdio.h>

int main() {
	int num,result,mod;
	scanf("%d",&num);
	while(num > 10){
		while(num%10 > 0){
			mod = num%10;
			result = result + mod;
			num = num/10;
		}
		num = result;
		result = 0;
	}
	printf("%d",num);
	
	return 0;
}




