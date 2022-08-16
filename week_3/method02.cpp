#include <stdio.h>

int main() {
	int row;
	scanf("%d",&row);
	for (int i =1; i <= row; i++)  
    {  
        for (int j = 1; j <= row - i; j++)  
        {  
            printf ("  ");   
        }
        //left
        for (int l = i-1; l >= 0; l--){
        	printf("* ");
		}
		//right
		for (int m = 1; m < i; m++){
			printf("* ");
		}
        printf ("\n");  
    }
	return 0;
}
