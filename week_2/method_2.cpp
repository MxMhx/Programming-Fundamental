#include <stdio.h>

int main() {
	int num;
	bool check = false;
	printf("Enter number : ");
	scanf("%d",&num);
	if(num == 2){
		printf("%d is PRIME NUMBER",num);
	}
	else if(num%2 == 0 || num <= 1){
		printf("%d is NOT PRIME NUMBER",num);
	}
	else{
		for(int i = 2; i<num; i++){
			if(num%i == 0)
				check = true;
		}
		if(check)
			printf("%d is NOT PRIME NUMBER",num);
		else
			printf("%d is PRIME NUMBER",num);
	}
    return 0;
}
