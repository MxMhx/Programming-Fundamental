#include <stdio.h>

void swap(int *c, int *d)
{
	int temp = *c;
	*c = *d;
	*d = temp;
}

int main() {
	int a,b;
	scanf("%d %d",&a,&b);
	swap(&a,&b);
	printf("%d %d",a,b);
	return 0;
}
