#include <stdio.h>

int main() {
	int m,n,count,j = 0;
	scanf("%d",&m);
	scanf("%d",&n);
	int i = n - 1;
	while( i > 0) {
		count++;
		i -= m + 1;
	}
	if(i == 0){
		printf("ERROR");
	} else {
		i = n - 1;
		int num[count];
		while( i > 0) {
			num[j] = i;
			i -= m + 1;
			j++;
		}
		for(int k = j - 1; k >= 0; k--){
			printf("%d ",num[k]);
		}
	}
	return 0;
}
