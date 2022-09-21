#include <stdio.h>

int main () {
    int a,b,i = 2,n = 1;
    printf("Enter first number : ");
    scanf("%d",&a);
    printf("Enter second number : ");
    scanf("%d",&b);
    printf("Greatest common divisor = ");
    while(i < 13){
    	if(a%i == 0 && b%i ==0){
    		n = n*i;
			a = a / i;
			b = b / i; 
		} else {
			i++;
		}
	}
	printf("%d",n); 
    return 0;
}
