#include <stdio.h>

int main() {
	int n,m;
	int row = 0,column = 0;
	int checkvector = 0; // 0 right , 1 left , 2 up , 3 down
	bool canwalk = true;
	scanf("%d %d",&n,&m);
	//save pos to array
	int a[n][m];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	while(canwalk && column < m - 1){
		//check right
		if(a[row][column+1] == 0 && checkvector != 1){
			column++;
			checkvector = 0;
		}
		//check down
		else if(a[row+1][column] == 0 && checkvector != 2){
			row++;
			checkvector = 3;
		}
		//check up
		else if(a[row-1][column] == 0 && checkvector != 3){
			row--;
			checkvector = 2;
		}
		//check left
		else if(a[row][column-1] == 0 && checkvector != 0){
			row--;
			checkvector = 1;
		}else canwalk = false;
	}
	if(canwalk) printf("YES");
	else printf("NO");
	return 0;
}
