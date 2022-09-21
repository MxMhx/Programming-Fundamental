#include <stdio.h>

int main() {
	int row,column;
	scanf("%d",&row);
	column = (row * 2) - 1; 
	for(int i = 1; i <= row; i++){
		for(int j = 1; j <= column; j++){
			if(j <= i || j >= (column - i) + 1)
				printf("* ");
			else
				printf("  ");
		}
		printf("\n");
	}
	for(int i = row - 1; i > 0; i--){
		for(int j = 1; j <= column; j++){
			if(j <= i || j >= (column - i) + 1)
				printf("* ");
			else
				printf("  ");
		}
		printf("\n");
	}
	return 0;
}


