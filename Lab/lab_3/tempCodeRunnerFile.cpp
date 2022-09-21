#include <stdio.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;

void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
//ship
void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("     ");
}
void draw_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(4, 11);
	printf("<-0->");
}
//bullet
void erase_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
void draw_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(4, 12);
	printf("^");
}

int main() {
	vector<int> bullet_x;
	vector<int> bullet_y;
	bool moveleft = false, moveright = false;
	setcursor(0);
	int x = 30, y = 29;
	char ch = ' ';
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				moveleft = true;
				moveright = false;
			}
			if (ch == 'd') {
				moveleft = false;
				moveright = true;
			}
			if (ch == 's') {
				moveleft = false;
				moveright = false;
			}
			if (ch == ' ') {
				bullet_x.push_back(x + 2);
				bullet_y.push_back(y - 1);
			}
			fflush(stdin);
		}
		if (moveright) {
			erase_ship(x, y);
			if (x > 114) {
				draw_ship(115, y);
			}
			else draw_ship(++x, y);
		}
		else if (moveleft) {
			erase_ship(x, y);
			if (x < 1) {
				draw_ship(0, y);
			}
			else draw_ship(--x, y);
		}
		auto ix = bullet_x.begin();
		auto iy = bullet_y.begin();
		while (auto ix != bullet_x.end()) {
			erase_bullet(*ix, *iy);
			if (*iy > 0) draw_bullet(*ix, --*iy);
			++ix;
			++iy;
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}




