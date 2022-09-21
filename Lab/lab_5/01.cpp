#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void erase_ship(int x, int y){
	gotoxy(x,y);
	printf("      ");
}
void draw_ship(int x, int y) {
	gotoxy(x,y);
	printf("<-0-> ");
}
int main() {
	int x = 30, y = 5;
	char ch = ' ';
	draw_ship(x,y);
	do {
		if (_kbhit()){
			ch = _getch();
			if(ch == 'a'){
				if (x < 1) {
					draw_ship(0,y);
				}
				else draw_ship(--x,y);	
			}
			if(ch == 'd'){
				erase_ship(x,y);
				if (x > 113)	draw_ship(114,y);
				else draw_ship(++x,y);
			}
			if(ch == 'w'){
				erase_ship(x,y);
				if (y < 1) draw_ship(x,0);
				else draw_ship(x,--y);
			}
			if(ch == 's'){
				erase_ship(x,y);
				if (y > 28) draw_ship(x,29);
				else draw_ship(x,++y);
			}
			fflush(stdin);
		}
		Sleep(100);
	}
		while (ch != 'x');
	return 0;
}





