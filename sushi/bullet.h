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


//class Bullet_main {
//public:
//	Bullet_main();
//	bool isFire = false;
//	Bullet newbullet_r = Bullet("images/bullet_r.png");
//	std::vector<Bullet> bullet_r;
//
//	int numbullet() {
//		return bullet_r.size();
//	}
//	void setPos(sf::Sprite charec) {
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//			if (isFire == false) {
//				newbullet_r.setPos(sf::Vector2f(charec.getPosition().x + 75, charec.getPosition().y + 50));
//				bullet_r.push_back(newbullet_r);
//			}
//			isFire = true;
//		}
//		else isFire = false;
//	}
//
//	void fire() {
//		for (int i = 0; i < bullet_r.size(); i++) {
//			bullet_r[i].fire_r(15);
//		}
//	}
//	void draw(sf::RenderWindow &window) {
//		for (int i = 0; i < bullet_r.size(); i++) {
//			if(bullet_r[i].state) bullet_r[i].draw(window);
//		}
//	}
//};
//class Bullet_main {
//public:
//	Bullet_main();
//
//	//Bullet
//	bool isFire = false;
//	std::vector<Bullet> bullet_r;
//	std::vector<Bullet> bullet_l;
//	std::vector<Bullet> bullet_u;
//	std::vector<Bullet> bullet_d;
//	Bullet newBullet_r();
//	Bullet newBullet_l();
//	Bullet newBullet_u();
//	Bullet newBullet_d();
//
//	sf::Clock firerate;
//
//	void fire_bullet(sf::Vector2f mousepos, sf::Sprite charec) {
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//			if (isFire == false && firerate.getElapsedTime().asSeconds() > 0.5f) {
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//					bullet_u.push_back(newBullet_u());
//				}
//				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//					bullet_d.push_back(newBullet_d());
//				}
//				else if (mousepos.x < charec.getPosition().x) {
//					bullet_l.push_back(newBullet_l());
//				}
//				else {
//					//newBullet_r().setPos(sf::Vector2f(50,50));
//					bullet_r.push_back(newBullet_r());
//					printf("%f\n", newBullet_r().bullet.getPosition().x);
//				}
//				firerate.restart();
//			}
//			isFire = true;
//		}
//		else isFire = false;
//	}
//	void draw(sf::RenderWindow &window) {
//		for (int i = 0; i < bullet_r.size(); i++) {
//			if (bullet_r[i].state) bullet_r[i].draw(window);
//		}
//	}
//private:
//};