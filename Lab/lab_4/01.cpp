#include <string.h>
#include <stdio.h>
#include <math.h>

int main () {
 	char input[65000];
   	int num,i;
   	scanf("%s",input);
   	char *token;
   	token = strtok(input, "\n");
	int str_len = strlen(token);
	while(i < str_len){
		if(token[i] > 'A'){
			printf("%c",token[i]);
			i++;
		}
		else{
			num = token[i] - 48;
			for(int j = 1; j <= num; j++){
				printf("%c",token[i+1]);
			}
			i += 2;
		}
	}	
   	return 0;
}
// 10-99
/*int main () {
   	char input[65000];
   	int num,i,count;
   	scanf("%s",input);
   	char *token;
   	token = strtok(input, "\n");
	int str_len = strlen(token);
	while(i < str_len){
		if(token[i] >= 'A'){
			printf("%c",token[i]);
			i++;
		}
		else{
			
			if(token[i+1] > 'A'){
				num = token[i] - 48;
				for(int j = 1; j <= num; j++){
					printf("%c",token[i+1]);
				}
				i += 2;
			}
			else
			{			
				num = token[i+1] - 48;
				num += (token[i] - 48) * 10;
				for(int k = 1; k <= num; k++){
					printf("%c",token[i+2]);
				}
				i += 3;
			}
		}	
	}
   	return 0;
}*/
