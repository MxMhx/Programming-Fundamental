#include <stdio.h>
#include <windows.h>
#include <time.h>
#define screen_x 80
#define screen_y 25
#define scount 80

using namespace std;

HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD characterPos = { 0,0 };
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x-1,screen_y-1 };
struct Ship{
	int X_middle=0;
	int Y_middle=0;
	
	int X_Lwing = 0;
	int X_Rwing = 0;
	int X_Rd = 0;
	int X_Ld = 0;
	
	int color = 7;
	int life = 10;
};
Ship ship;
COORD star[scount];

int setMode(){
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}
int setConsole(int x, int y){
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}
void clear_buffer(){
	for(int y = 0; y < screen_y; ++y){
		for(int x = 0; x < screen_x; ++x){
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 0;			
		}
	}
}
void fill_buffer_to_console(){
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,&windowSize);
}
void ship_to_buffer(){
	consoleBuffer[ship.X_middle + screen_x * ship.Y_middle].Char.AsciiChar ='0';
	consoleBuffer[ship.X_Lwing + screen_x * ship.Y_middle].Char.AsciiChar ='<';
	consoleBuffer[ship.X_Rwing + screen_x * ship.Y_middle].Char.AsciiChar ='>';
	consoleBuffer[ship.X_Rd + screen_x * ship.Y_middle].Char.AsciiChar ='-';
	consoleBuffer[ship.X_Ld + screen_x * ship.Y_middle].Char.AsciiChar ='-';
	
	consoleBuffer[ship.X_middle + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Lwing + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Rwing + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Rd + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Ld + screen_x * ship.Y_middle].Attributes =ship.color;
}
void init_star(){
	for(int i = 0; i < scount; i++){
		star[i].Y = rand() % 25;
		star[i].X = rand() % 80;
	}
}
void star_fall(){
	int i;
	for (i = 0; i < scount; i++) {
		if (star[i].Y >= screen_y-1) {
			star[i] = { (rand() % screen_x),1 };
		}
		else {
			star[i] = { star[i].X,star[i].Y+1 };
		}
	}
}

void fill_star_to_buffer(){
	for(int i = 0; i < scount; ++i){
		consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
		consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 15;
	}
}

void checkcol(){
	for(int i = 0;i<scount;i++){
		if(ship.X_middle == star[i].X || ship.X_Rwing == star[i].X || ship.X_Lwing == star[i].X || ship.X_Rd == star[i].X || ship.X_Ld == star[i].X){
			if(ship.Y_middle == star[i].Y){
				star[i].X = rand() % screen_x;
				star[i].Y = rand() % screen_y;
				ship.life -=1;
			}
		}
	} 
	
}
int main(){
	srand(time(NULL));
	bool play = true;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	init_star();
	while (play){
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
		for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT &&
				eventBuffer[i].Event.KeyEvent.bKeyDown == true ) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					if(eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c'){
						ship.color = rand() % 7;
					}
					//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);
					
				}
			else if (eventBuffer[i].EventType == MOUSE_EVENT) {
				int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
				int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
				if (eventBuffer[i].Event.MouseEvent.dwButtonState &
					FROM_LEFT_1ST_BUTTON_PRESSED) {
						//printf("left click\n");
						ship.color = rand() % 7;
				}
			else if (eventBuffer[i].Event.MouseEvent.dwButtonState &
						RIGHTMOST_BUTTON_PRESSED) {
							//printf("right click\n");
				}
			else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
					//printf("mouse position : (%d,%d)\n",posx, posy);
					ship.X_middle = posx;
					ship.Y_middle = posy;
				
					ship.X_Lwing = posx-2;
					ship.X_Rwing = posx+2;
					ship.X_Ld = posx-1;
					ship.X_Rd = posx+1;
				}
			}
		}
		delete[] eventBuffer;
	}
	clear_buffer();
	ship_to_buffer();
	star_fall();
	fill_star_to_buffer();
	checkcol();
	fill_buffer_to_console();
	if(ship.life < 1) play = false;
	Sleep(100);
	}
	return 0;
}





