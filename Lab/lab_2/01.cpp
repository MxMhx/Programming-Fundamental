#include <stdio.h>

int main () {
    int n,i = 2;
    printf("Enter number : ");
    scanf("%d",&n);
    printf("Factoring Result : ");
    while (i<=n)
    {
        if (n%i == 0)
        {
            n = n / i;
            if (n == 1){
            	printf("%d",i);
			} else
            printf("%d x ",i);
            }
        else {
            i++;
        }
        
    }
    
    return 0;
}
