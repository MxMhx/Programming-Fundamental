#include <stdio.h>

int main() {
	int h1,h2,h3,h4,h5,h6,h7,h8,h9,h10;
	scanf("%d %d %d %d %d %d %d %d %d %d",&h1,&h2,&h3,&h4,&h5,&h6,&h7,&h8,&h9,&h10);
	int num = h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8 + h9 + h10;
	printf("student 1 : %d\n",h1);
	printf("student 2 : %d\n",h2);
	printf("student 3 : %d\n",h3);
	printf("student 4 : %d\n",h4);
	printf("student 5 : %d\n",h5);
	printf("student 6 : %d\n",h6);
	printf("student 7 : %d\n",h7);
	printf("student 8 : %d\n",h8);
	printf("student 9 : %d\n",h9);
	printf("student 10 : %d\n",h10);
	int result = num/10;
	printf("Average height of 10 students is %d",result);
	return 0;
}
