#include <stdio.h>

int main() {
	int num;
	int check = 0;
	printf("Enter number : ");
	scanf("%d",&num);
	for(int i = 1;i<num;i++){
		if(num%i == 0)
			check++;
	}
	if(num == 1){
		printf("1 is NOT PRIME NUMBER");
	}
	else{
		if(check == 1)
		printf("%d is PRIME NUMBER",num);
	else
		printf("%d is NOT PRIME NUMBER",num);
	}
	
    return 0;
}
