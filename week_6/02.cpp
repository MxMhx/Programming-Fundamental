#include<stdio.h>
#include <string.h>
int main() {
	int i = 0;
	int count = 0;
	int readtext;
	char str[100000];
	FILE *f;
	f = fopen("D:/Programming_Fundamental.html","r");
	while ((readtext = fgetc(f)) != EOF){
		str[i] = readtext + 0;
		i++;
	}
	fclose(f);
	i = 0;
	while (str[i] != '\0') {
		if (str[i] == '<') {
			if (str[i+1] == 'a'){
				count++;
			}
		}
		i++;
	}
	printf("Amount of Tag : %d",count);
	return 0;
}
