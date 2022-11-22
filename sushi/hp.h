#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Object.h"

class Hp_Enemy {
public:
	float width = 75;
	float width_const = 75;

	Hp_Enemy(sf::Sprite sprite) {
		float position = (sprite.getGlobalBounds().width - width_const) / 2;
		float x = sprite.getPosition().x - position;
		float y = sprite.getPosition().y - 10;

		red.setPosition(sf::Vector2f(x,y));
		red.setSize(sf::Vector2f(width_const, heigh));
		red.setFillColor(sf::Color::Red);

		black.setPosition(sf::Vector2f(x - 5, y - 5));
		black.setSize(sf::Vector2f(width_const + 10, heigh + 10));
		black.setFillColor(sf::Color::Black);
	};

	void draw(sf::RenderWindow &window) {
		if (width > 0) {
			window.draw(black);
			window.draw(red);
		}
	}

	void move(sf::Vector2f velocity) {
		red.move(velocity);
		black.move(velocity);
	}

	void damage(float damage) {
		if (damage >= width || width == 0) {
			red.setSize(sf::Vector2f(0, heigh));
			width = 0;
		}
		else {
			red.setSize(sf::Vector2f(width - damage, heigh));
		}
		width -= damage;
	}

	void setup(sf::Sprite sprite) {
		float position = (sprite.getGlobalBounds().width - width_const) / 2;
		float x = sprite.getPosition().x + position;
		float y = sprite.getPosition().y - 10;

		red.setPosition(sf::Vector2f(x, y));
		black.setPosition(sf::Vector2f(x - 5, y - 5));
	}

	void reset() {
		width = 75;
		red.setSize(sf::Vector2f(width_const, heigh));
	}

private:
	sf::RectangleShape red;
	sf::RectangleShape black;
	float heigh = 15;
};
