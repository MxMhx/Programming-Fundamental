#include <stdio.h>
#include <string.h>
int lowertoupper(char x){
	if(x >= 'a' && x <= 'z'){
		return x - 32;
	}
	else return x;
}

int main() {
	int i,count = 0,check;
	char input[65000];
	scanf("%[^\n]",&input);
	int str_len = strlen(input);
	while(i < str_len){
		if(lowertoupper(input[i]) == 'F'){
		if(lowertoupper(input[i+1]) == 'R'){
			if(lowertoupper(input[i+2]) == 'O'){
				if(lowertoupper(input[i+3]) == 'G'){
					count += 1;
					i += 3;
				}
			}
		}
	}
	i++;
	}
	printf("%d",count);
	return 0;
}
