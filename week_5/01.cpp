#include <stdio.h>
#include <string.h>

int main() {
	char input[65000];
	scanf("%[^\n]s",&input);
	int i,count = 0;
	int str_len = strlen(input);
	while(i < str_len){
		if(input[i] == 'F' || input[i] == 'f'){
			if(input[i+1] == 'R' || input[i+1] == 'r'){
				if(input[i+2] == 'O' || input[i+2] == 'o'){
					if(input[i+3] == 'G' || input[i+3] == 'g'){
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
