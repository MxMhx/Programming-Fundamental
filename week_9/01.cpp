#include <stdio.h>

int n,m;
int main() {
	int checkvector = 0; // 0 right , 1 left , 2 up , 3 down
	bool end = true, start = false;
	scanf("%d %d",&n,&m);
	//save pos to array
	int a[n][m];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	int column = m - 1;
	for(int row = n - 1; row > 0 && !start; row--){
		while(end){
			//check left
			if(a[row][column-1] == 0 && checkvector != 0 && column != 0){
				column--;
				checkvector = 1;
			}
			//check up
			else if(a[row-1][column] == 0 && checkvector != 3){
				row--;
				checkvector = 2;
			}
			//check down
			else if(a[row+1][column] == 0 && checkvector != 2){
				row++;
				checkvector = 3;
			}
			//check right
			else if(a[row][column+1] == 0 && checkvector != 1){
				column++;
				checkvector = 0;
			}else end = false;
			if(column == 0 && row == 0) start = true;
		}	
	}
	if(start) printf("YES");
	else printf("NO");
	return 0;
}
