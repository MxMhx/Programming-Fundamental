#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Object.h"

class Hp_Enemy {
public:
	float width = 100;

	Hp_Enemy(float x, float y) {
		red.setPosition(sf::Vector2f(x,y));
		red.setSize(sf::Vector2f(width, heigh));
		red.setFillColor(sf::Color::Red);

		black.setPosition(sf::Vector2f(x - 5, y - 5));
		black.setSize(sf::Vector2f(width + 10, heigh + 10));
		black.setFillColor(sf::Color::Black);

		shadow.setPosition(sf::Vector2f(x, y + 15));
		shadow.setSize(sf::Vector2f(width, heigh - 15));
		shadow.setFillColor(sf::Color::Color(100, 0, 0, 255));
	};

	void draw(sf::RenderWindow &window) {
		if (width > 0) {
			window.draw(black);
			window.draw(red);
			window.draw(shadow);
		}
	}

	void move(sf::Vector2f velocity) {
		red.move(velocity);
		black.move(velocity);
		shadow.move(velocity);
	}

	void damage(float damage) {
		if (damage >= width || width == 0) {
			red.setSize(sf::Vector2f(0, heigh));
			shadow.setSize(sf::Vector2f(0, heigh - 15));
			width = 0;
		}
		else {
			red.setSize(sf::Vector2f(width - damage, heigh));
			shadow.setSize(sf::Vector2f(width - damage, heigh - 15));
		}
		width -= damage;
	}

private:
	sf::RectangleShape red;
	sf::RectangleShape black;
	sf::RectangleShape shadow;
	float heigh = 20;
};
