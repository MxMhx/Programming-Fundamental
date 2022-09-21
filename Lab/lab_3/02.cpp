#include <stdio.h>

int main() {
	int sum = 0;
	for(int j = 1; j <= 10000; j++){
		for(int i = 1; i <= j - 1; i++){
			if(j%i == 0)
				sum = sum + i;
		}
		if(sum == j)
			printf("%d ",sum);
			sum = 0;
	}
	return 0;
}





