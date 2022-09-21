#include <stdio.h>

int main() {
	char str[65000],*token;
	scanf("%s",&str);
	token = str;
	
	while (*token != '\0'){
		if(*token >= 'A' && *token <= 'Z'){
			printf("%c",*token + 32);
		}
		else if(*token >= 'a' && *token <= 'z'){
			printf("%c",*token - 32);
		}
		token++;
	}
	return 0;
}





