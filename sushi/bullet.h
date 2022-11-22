#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>

class Bullet {
public:
	sf::Sprite bullet;

	bool state = true;

	Bullet(std::string textureSource) {
		textureBullet.loadFromFile(textureSource);
		bullet.setTexture(textureBullet);
		bullet.setScale(0.07, 0.07);
	}
	void fire_r(float speed) {
		bullet.move(speed, 0);
	}
	void fire_l(float speed) {
		bullet.move(-speed, 0);
	}
	void fire_u(float speed) {
		bullet.move(0, -speed);
	}
	void fire_d(float speed) {
		bullet.move(0, speed);
	}

	sf::FloatRect getBounds() {
		return bullet.getGlobalBounds();
	}

	void setPos(sf::Vector2f newpos) {
		bullet.setPosition(newpos);
	}
	void draw(sf::RenderWindow &window) {
		window.draw(bullet);
	}
private:
	sf::Texture textureBullet;
};