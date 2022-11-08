#pragma once
#include "SFML/Graphics.hpp"
#include "Object.h"
#include "Enemy_Bullet.h"
#include "Object.h"
#define heartsize 5

class Hp_Player {
public:
	int d = 0;
	bool temp = false;
	bool temp2 = false;
	int tempp = 0;

	void damage(bool collision, int damage, bool collision_sp) {
		if (temp != collision) {
			if (clock.getElapsedTime().asSeconds() > 1.5f) {
				sizeheart--;
				if (d < heartsize) {
					d++;
				}
				clock.restart();
			}
			temp = collision;
		}
		if (temp2 != collision_sp) {
			if (clock.getElapsedTime().asSeconds() > 1.5f) {
				sizeheart--;
				if (d < heartsize) {
					d++;
				}
				clock.restart();
			}
			temp2 = collision_sp;
		}
		if (d < heartsize) {
			if (tempp != damage) {
				d++;
				sizeheart--;
			}
		}
		tempp = damage;
	}

	bool gamestateover() {
		if (sizeheart <= 0) {
			return 1;
		}
		else return 0;
	}

	void draw(sf::RenderWindow &window) {
		for (int i = 0; i < sizeheart; i++) {
			window.draw(heart[i].sprite);
		}
		for (int i = 0; i < d; i++) {
			window.draw(empty[i].sprite);
		}
	}
private:
	GameObject heart[heartsize] = {
			GameObject("images/heart.png", 10, 10),
			GameObject("images/heart.png", 60, 10),
			GameObject("images/heart.png", 110, 10),
			GameObject("images/heart.png", 160, 10),
			GameObject("images/heart.png", 210, 10)
	};

	GameObject empty[heartsize] = {
			GameObject("images/heart_null.png", 210, 10),
			GameObject("images/heart_null.png", 160, 10),
			GameObject("images/heart_null.png", 110, 10),
			GameObject("images/heart_null.png", 60, 10),
			GameObject("images/heart_null.png", 10, 10)
	};

	sf::Clock clock;

	int sizeheart = heartsize;
};

class Weapon_Ui {
public:
	bool selectsword = true;
	bool press;
	Weapon_Ui() {
		rec.setSize(sf::Vector2f(200, 200));
		rec.setPosition(sf::Vector2f(1050, 20));
		rec.setFillColor(sf::Color::Color(210, 210, 210, 180));

		swordtex.loadFromFile("images/sword.png");
		sword.setTexture(swordtex);
		sword.setPosition(1090, 60);

		guntex.loadFromFile("images/gun.png");
		gun.setTexture(guntex);
		gun.setPosition(1090, 60);
	}

	void draw(sf::RenderWindow &window, bool selectsword) {
		window.draw(rec);
		if(selectsword) window.draw(sword);
		else window.draw(gun);
	}
private:
	sf::RectangleShape rec;
	sf::Texture guntex;
	sf::Texture swordtex;
	sf::Sprite gun;
	sf::Sprite sword;
};

class Pause {
public:
	FontText fonttext = FontText("font/Minecraft.ttf", "PAUSE", 600, 310, sf::Color::White);
	FontText overtext = FontText("font/Minecraft.ttf", "GAME OVER", 600, 310, sf::Color::Red);
	Pause() {
		shape.setSize(sf::Vector2f(1300, 720));
		shape.setPosition(sf::Vector2f(0, 0));
		shape.setFillColor(sf::Color::Color(20, 20, 20, 180));
	}
	void pausegame(sf::RenderWindow &window, bool *pause, bool stategame) {
		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				*pause = !*pause;
				clock.restart();
			}
		}
		if (*pause && !stategame) {
			window.draw(shape);
			window.draw(fonttext.text);
		}
	}

	void gameover(sf::RenderWindow &window, bool *pause, bool stategame) {
		if (stategame) {
			*pause = true;
			window.draw(shape);
			window.draw(overtext.text);
		}
	}
private:
	sf::RectangleShape shape;
	sf::Clock clock;
};