#include "SFML/Graphics.hpp"
#include "gamewindow.h"

int main()
{
	sf::Music music;
	music.openFromFile("sounds/bgmusic1.wav");
	music.play();
	gameupdate();
	return 0;
}