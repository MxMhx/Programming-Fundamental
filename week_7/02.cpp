#include <stdio.h>

int main() {
	int m,n;
	scanf("%d",&m);
	scanf("%d",&n);
	int i = n - 1;
	while( i > 0) {
		i -= m + 1;
	}
	if(i == 0){
		printf("ERROR");
	} else {
		while(i < n-1){
			i += m+1;
			printf("%d ",i);
		}
	}
	return 0;
}
