#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
	char input[65000];
   	int num,i = 0,count = 0,mul;
   	scanf("%s",input);
   	char *token;
   	token = strtok(input, "\n");
	int str_len = strlen(token);
	while (i < str_len)
	{
		//not number front
		if(token[i] >= 'A'){
			printf("%c",token[i]);
			i++;
		}
		else
		{
			//check how many num
			while(token[i] < 'A'){
				i++;
				count++;
			}
			i = i - count;
			//check how many power
			for(int k = count - 1; k >= 0; k--){
				mul = pow(10,k);
				num += (token[i] - 48) * mul;
				i++;
			}
			//printf charector a number of num
			for(int j = 1; j <= num; j++){
				printf("%c",token[i]);
			}
			i++;
			num = 0;
			count = 0;
		}
	}
	return 0;
}
