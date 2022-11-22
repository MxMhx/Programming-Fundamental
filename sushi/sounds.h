#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Sounds {
public:
	void click_effect() {
		buffer.loadFromFile("sounds/click.wav");
		sound.setBuffer(buffer);
		sound.play();
	}

	void fire_effect() {
		buffer.loadFromFile("sounds/gunshot_2.wav");
		sound.setBuffer(buffer);
		sound.play();
	}

	void fencing_effect() {
		buffer.loadFromFile("sounds/fencing.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};