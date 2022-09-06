#include<stdio.h>
int main() {
	int count;
	int readtext;
	FILE *f;
	f = fopen("D:/Programming_Fundamental.html","r");
	while ((readtext = fgetc(f)) != EOF) {
		if (readtext == '<') {
			readtext = fgetc(f);
			if (readtext == 'a') {
				count++;
			}
		}
	}
	fclose(f);
	printf("Amount of link : %d",count);
	return 0;
}
