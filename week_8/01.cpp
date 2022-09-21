#include <stdio.h>
#include <string.h>

bool check(char a[20], int len){
	bool lower;
	bool upper;
	bool num;
	bool sign;
	bool longmai;
	if(len >= 6 && len <= 12){
		for(int i = 0; i < len; i++){
		if(a[i] >= 'a' && a[i] <= 'z'){
			lower = true;
		}
		if(a[i] >= 'A' && a[i] <= 'Z'){
			upper = true;
		}
		if(a[i] >= '0' && a[i] <= '9'){
			num = true;
		}
		if(a[i] == '$' || a[i] == '#' || a[i] == '@'){
			sign = true;
		}
	}
	}
	if(lower && upper && num && sign){
		return true;
	}else return false;	
}

int main() {
	char password[100];
	char k[13];
	char r[13];
	char j[13];
	int i = 0, o = 0, p = 0, count = 0;
	scanf("%[^\n]s",password); fgetc(stdin);
	for(i = 0; password[i] != '\0'; i++){
		if(password[i] != ',' && count == 0){
			k[i] = password[i];
		} else {
			if(count == 0){
				++i;
				count = 1;
			}
			if(password[i] != ',' && count == 1){
				r[o] = password[i];
				o++;
			} else {
				if(count == 1){
					++i;
					count = 2;
				}
				if(password[i] != '\0' && count == 2){
					j[p] = password[i];
					p++;
				}
			}
		}
	}
	char * kob = strtok(k,"\0");
	char * rom = strtok(r,"\0");
	char * jo = strtok(j,"\0");
	int len_k = strlen(kob);
	int len_r = strlen(rom);
	int len_j = strlen(jo);
	if(check(kob,len_k)){
		printf("%s (Kob)",kob);
	}else if(check(rom,len_r)){
		printf("%s (Romtham)",rom);
	}else if(check(jo,len_j)){
		printf("%s (Jojo)",jo);
	}
	return 0;
}
