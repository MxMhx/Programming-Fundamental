#pragma once
#include <SFML/Graphics.hpp>
#include "hp.h"
#include <vector>
#include "bullet.h"

class Enemy {
public:
	sf::Sprite enemy;

	Enemy(std::string textureSource, float x, float y) {
		textureenemy.loadFromFile(textureSource);
		enemy.setTexture(textureenemy);
		enemy.setPosition(sf::Vector2f(x, y));
	}

	void move(sf::Vector2f speed) {
		enemy.move(speed);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(enemy);
	}
private:
	sf::Texture textureenemy;
};