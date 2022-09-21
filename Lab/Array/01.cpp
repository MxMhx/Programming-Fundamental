#include <stdio.h>
#include <string.h>

int main() {
	char input[65000];
   	int i;
   	scanf("%s",input);
   	char *token;
   	token = strtok(input, "\n");
	int str_len = strlen(token);
	while (i < str_len)
	{
		if(token[i] >= 65 && token[i] <= 90){
			printf("%c",token[i]);
		}
		i++;
	}
	return 0;
}







