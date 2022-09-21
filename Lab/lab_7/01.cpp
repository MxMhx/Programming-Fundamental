#include <stdio.h>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <thread>

using namespace std;

void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console,&lpCursor);
}
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setcolor(int fg, int bg){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16+fg);
}
//ship
void erase_ship(int x, int y){
	gotoxy(x,y);
	setcolor(0,0);
	printf("     ");
}
void draw_ship(int x, int y) {
	gotoxy(x,y);
	setcolor(4,11);
	printf("<-0->");
}
//bullet
void erase_bullet(int x, int y){
	gotoxy(x,y);
	setcolor(0,0);
	printf(" ");
}
void draw_bullet(int x,int y) {
	gotoxy(x,y);
	setcolor(4,12);
	printf("^");
}
//star
void draw_star(int x, int y){
	gotoxy(x,y);
	setcolor(7,0);
	printf("*");
}

int main() {
	//vector<int> bullet_x;
	//vector<int> bullet_y;s
	struct bullet{
		bool state = false;
		int bullet_x;
		int bullet_y;
	}; 
	struct star{
		int star_x;
		int star_y;
	};
	star s[20];
	bullet b;
	srand(time(NULL));
	int count,score = 21;
	for(int i = 0; i < 20; i++){
		int tempx = 0;
		int tempy = 0;
		s[i].star_x = rand() % 61 + 10;
		s[i].star_y = rand() % 4 + 2;
		while(s[i].star_x == tempx){
			s[i].star_x = rand() % 61 + 10;	
		}
		while(s[i].star_y == tempy){
			s[i].star_y = rand() % 4 + 2;	
		}
		tempx = s[i].star_x;
		tempy = s[i].star_y;
	}
	bool moveleft = false , moveright = false;
	setcursor(0);
	int x = 30, y = 29;
	char ch = ' ';
	draw_ship(x,y);
	do {
		if (_kbhit()){
			ch = _getch();
			if(ch == 'a'){
				moveleft = true;
				moveright = false;	
			}
			if(ch == 'd'){
				moveleft = false;
				moveright = true;
			}
			if(ch == 's'){
				moveleft = false;
				moveright = false;
			}
			if(ch == ' '){
				if(b.state == false){
					b.bullet_x = x + 2;
					b.bullet_y = y - 1;
					b.state = true;
				}
			}
			fflush(stdin);
		}
		if(moveright){
			erase_ship(x,y);
			if (x > 114){
				draw_ship(115,y);
			} else draw_ship(++x,y);
		}
		else if(moveleft){
			erase_ship(x,y);
			if (x < 1){
				draw_ship(0,y);
			} else draw_ship(--x,y);
		}
		if(b.bullet_y > 0 && b.state == true){
			erase_bullet(b.bullet_x,b.bullet_y);
			draw_bullet(b.bullet_x,--b.bullet_y);
		} else{
			erase_bullet(b.bullet_x,b.bullet_y);
			b.state = false;
		}
		for(int i = 0; i < 20; i++){
			if(s[i].star_y == b.bullet_y && s[i].star_x == b.bullet_x){
				erase_bullet(b.bullet_x, b.bullet_y);
				b.state = false;
				thread q(Beep, 420, 300);
 				q.detach();
 				score++;
				s[i].star_x = rand() % 61 + 10;
				s[i].star_y = rand() % 4 + 2;
				for(int j = 0; j < 20; j++){
				if(s[i].star_x == s[j].star_x && s[i].star_y == s[j].star_y){
					count++;
					}
				}
				if(count != 1){
					s[i].star_x = rand() % 61 + 10;
					s[i].star_y = rand() % 4 + 2;
				}
			}
		}
		for(int i = 0; i < 20; i++){
			draw_star(s[i].star_x, s[i].star_y);
		}
		gotoxy(105,0);
		printf("score : %d",score);
		Sleep(100);
	}
	while (ch != 'x');
	return 0;
}
