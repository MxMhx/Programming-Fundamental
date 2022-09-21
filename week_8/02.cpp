#include <stdio.h>
#include <string.h>

int main() {
	struct check{
		bool lower = false;
		bool upper = false;
		bool digit = false;
		bool sign = false;
	};
	check kob;
	kob.lower;
	check rom;
	check jo;
	char password[100];
	char k[13];
	char r[13];
	char j[13];
	int i = 0, o = 0, p = 0, count = 0;
	scanf("%[^\n]s",password); fgetc(stdin);
	for(i = 0; password[i] != '\0'; i++){
		if(password[i] == ','){
			count++;
		}
		if(count == 0){
			if(password[i] >= 'a' && password[i] <= 'z') kob.lower = true;
			if(password[i] >= 'A' && password[i] <= 'Z') kob.upper = true;
			if(password[i] >= '0' && password[i] <= '9') kob.digit = true;
			if(password[i] == '$' || password[i] == '@' || password[i] == '#') kob.sign = true;
			if(password[i] != ',') k[i] = password[i];
		} else if(count == 1){
			if(password[i] >= 'a' && password[i] <= 'z') rom.lower = true;
			if(password[i] >= 'A' && password[i] <= 'Z') rom.upper = true;
			if(password[i] >= '0' && password[i] <= '9') rom.digit = true;
			if(password[i] == '$' || password[i] == '@' || password[i] == '#') rom.sign = true;
			if(password[i] != ',') {
				r[o] = password[i];
				o++;
			}
		} else if(count == 2){
			if(password[i] >= 'a' && password[i] <= 'z') jo.lower = true;
			if(password[i] >= 'A' && password[i] <= 'Z') jo.upper = true;
			if(password[i] >= '0' && password[i] <= '9') jo.digit = true;
			if(password[i] == '$' || password[i] == '@' || password[i] == '#') jo.sign = true;
			if(password[i] != ',') {
				j[p] = password[i];
				p++;
			}
		}
	}
	char *token_k = strtok(k,"\0");
	int str_len_k = strlen(token_k);
	
	char *token_r = strtok(r,"\0");
	int str_len_r = strlen(token_r);
	
	char *token_j = strtok(j,"\0");
	int str_len_j = strlen(token_j);
	
	if(kob.lower && kob.upper && kob.digit && kob.sign && str_len_k >= 6 && str_len_k <= 12){
		printf("%s (Kob)",token_k);
	}
	else if(rom.lower && rom.upper && rom.digit && rom.sign && str_len_r >= 6 && str_len_r <= 12){
		printf("%s (Romtham)",token_r);
	}
	else if(jo.lower && jo.upper && jo.digit && jo.sign && str_len_j >= 6 && str_len_j <= 12){
		printf("%s (Jojo)",token_j);
	}
	return 0;
}
