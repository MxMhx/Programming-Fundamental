#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
	GameObject(std::string, float, float);
};

class GameSheet {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::IntRect spriterect;
	GameSheet(std::string, float, float, int, int, int, int);
	void setup() {
		sprite.setTextureRect(spriterect);
	}

	void move(sf::Vector2f speed) {
		sprite.move(speed);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
	}
};

class FontText {
public:
	sf::Font font;
	sf::Text text;
	sf::Vector2f pos;
	FontText(std::string, std::string, float, float, sf::Color);
};
class ActiveObject { 
public:
	sf::Clock clock;
	sf::Texture textureeffect;
	sf::Sprite effect;
	sf::IntRect effectrect;
	bool click = false;
	bool wink = false;

	void init() {
		textureeffect.loadFromFile("images/wink.png");
		effectrect.height = 77;
		effectrect.width = 77;
		effectrect.top = 1;
		effectrect.left = 1;
		effect.setTexture(textureeffect);
		effect.setTextureRect(effectrect);
	}
	void collision(sf::Sprite sprite, sf::RenderWindow &window) {
		FontText pressE = FontText("font/Minecraft.ttf", "Press E", 600, 660, sf::Color::White);
		for (int i = 0; i < size_Activate; i++) {
			if (sprite.getGlobalBounds().intersects(activate[i].sprite.getGlobalBounds())) {
				window.draw(pressE.text);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					if (!click) {
						printf("press E\n");
						wink = true;
					}
					click = true;
				}
				else {
					click = false;
				}
				if (wink) {
					effect.setPosition(activate[i].sprite.getPosition().x - 5, activate[i].sprite.getPosition().y - 10);
					if (effectrect.left > 317) {
						wink = false;
						effectrect.left = 1;
					}
					if (clock.getElapsedTime().asSeconds() > 0.05f) {
						effectrect.left += 77;
						clock.restart();
					}
					effect.setTextureRect(effectrect);
					window.draw(effect);
				}
				break;
			}
		}
	}

	void move(sf::Vector2f velocity) {
		for (int i = 0; i < size_Activate; i++) {
			activate[i].sprite.move(velocity);
		}
	}

	void draw(sf::RenderWindow &window) {
		for (int i = 0; i < size_Activate; i++) {
			window.draw(activate[i].sprite);
		}
	}
private:
	//Activate Object by press E
	GameObject activate[3] = {
		GameObject("images/bento.png",806,545),
		GameObject("images/lever.png", 5586, 525),
		GameObject("images/bento.png",8143,545),
	};

	int size_Activate = sizeof(activate) / sizeof(activate[0]);

	sf::Font font;
	sf::Text text;
};

class Meteor {
public:
	bool collision_sp = false;
	Meteor() {
		shape.setSize(sf::Vector2f(70, 80));
		shape.setFillColor(sf::Color::Transparent);
		texture.loadFromFile("images/Meteor1-sheet.png");
		spriterect = sf::IntRect(0, 0, 160, 80);
		sprite.setTextureRect(spriterect);
		sprite.setTexture(texture);
		srand(time(NULL));
		sprite.setPosition(sf::Vector2f(1270, 200));
	};

	void fire() {
		shape.setPosition(sf::Vector2f(sprite.getPosition()));
		if (sprite.getPosition().x <= -500) {
			float height = rand() % 640;
			sprite.setPosition(sf::Vector2f(1270, height));
		}
		sprite.move(sf::Vector2f(-5, 0));
		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			spriterect.left += 160;
			if (spriterect.left > 320) {
				spriterect.left = 0;
			}
			clock.restart();
		}
		sprite.setTextureRect(spriterect);
	}

	void collision(sf::Sprite sprite) {
		collision_sp = false;
		if (sprite.getGlobalBounds().intersects(shape.getGlobalBounds())) {
			collision_sp = true;
		}
		else if (!collision_sp) collision_sp = false;
	}
	void move(sf::Vector2f speed) {
		sprite.move(speed);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
		window.draw(shape);
	}
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::IntRect spriterect;
	sf::Clock clock;
	sf::RectangleShape shape;
};