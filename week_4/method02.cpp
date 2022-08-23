#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
	int i = 0;
	char height[39];
	char print[3];
	int num = 0,result = 0,mul,count;
	scanf("%[^\n]s",height);
	int height_len = strlen(height);
	while(i < height_len)
	{
		for(int k = 0; k<3; k++){
			mul = pow(10,2-k);
			print[k] = height[i];
			num += (height[i] - 48) * mul;
			i++;
		}
		printf("Student 1 : %d\n",num);
		result += num;
		count++;
		i++;
		num = 0;
	}
	result /= 10;
	
	printf("Average height of 10 student is %d",result);
	return 0;
}
