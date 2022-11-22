#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <string.h>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define FONT "font/Minecraft.ttf"

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
	sf::RectangleShape shape;
	GameSheet(std::string, float, float, int, int, int, int);
	void setup() {
		sprite.setTextureRect(spriterect);
		float position_x = spriterect.width / 4;
		float position_y = spriterect.height / 4;
		shape.setPosition(sf::Vector2f(position_x + sprite.getPosition().x, position_y + sprite.getPosition().y));
	}

	void move(sf::Vector2f speed) {
		sprite.move(speed);
		shape.move(speed);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
		window.draw(shape);
	}
};

class FontText {
public:
	sf::Font font;
	sf::Text text;
	sf::Vector2f pos;
	FontText(std::string, std::string, float, float, sf::Color, int size);

	void settext(std::string textSource) {
		text.setString(textSource);
	}

	void setpos(sf::Vector2f pos) {
		text.setPosition(pos);
	}
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
		activate[0][0].sprite.setPosition(806, 545);
		activate[0][1].sprite.setPosition(5586, 525);
		activate[0][2].sprite.setPosition(8143, 545);

		activate[1][0].sprite.setPosition(3175,545);
		activate[1][1].sprite.setPosition(8276, 525);
		activate[1][2].sprite.setPosition(12776, 321);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				showactive[i][j] = true;
			}
		}
	}
	void collision(sf::Sprite sprite, sf::RenderWindow &window, int selectmap, int *sizeheart) {
		FontText pressE = FontText(FONT, "Press E", 600, 660, sf::Color::Color(102, 255, 132, 255), 30);
		for (int i = 0; i < size_Activate; i++) {
			if (sprite.getGlobalBounds().intersects(activate[selectmap][i].sprite.getGlobalBounds()) && showactive[selectmap][i]) {
				window.draw(pressE.text);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					if (!click) {
						showactive[selectmap][i] = false;
						wink = true;
						*sizeheart += 1;
					}
					click = true;
				}
				else {
					click = false;
				}
				if (wink) {
					effect.setPosition(activate[selectmap][i].sprite.getPosition().x - 5, activate[selectmap][i].sprite.getPosition().y - 10);
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

	void move(sf::Vector2f velocity, int selectmap) {
		for (int i = 0; i < size_Activate; i++) {
			activate[selectmap][i].sprite.move(velocity);
		}
	}

	void draw(sf::RenderWindow &window, int selectmap) {
		for (int i = 0; i < size_Activate; i++) {
			if(showactive[selectmap][i]) window.draw(activate[selectmap][i].sprite);
		}
	}

private:
	//Activate Object by press E
	GameObject activate[2][3] = { {
		GameObject("images/heart.png",806,545),
		GameObject("images/heart.png", 5586, 545),
		GameObject("images/heart.png",8143,545),
	},{
		GameObject("images/heart.png",3175,545),
		GameObject("images/heart.png", 8276, 525),
		GameObject("images/heart.png",12776,321),
	}
		
	};

	int size_Activate = sizeof(activate[0]) / sizeof(activate[0][0]);

	bool showactive[2][3] = {
		{ true , true , true },{ true , true , true }
	};

	sf::Font font;
	sf::Text text;
};

class Meteor {
public:
	bool collision_sp = false;
	int firespeed;
	int distance;
	Meteor() {
		shape.setSize(sf::Vector2f(40, 50));
		shape.setFillColor(sf::Color::Transparent);
		texture.loadFromFile("images/Meteor1-sheet.png");
		spriterect = sf::IntRect(0, 0, 160, 80);
		sprite.setTextureRect(spriterect);
		sprite.setTexture(texture);
		srand(time(NULL));
		sprite.setPosition(sf::Vector2f(1270, 200));
	};

	void fire(int velocity) {
		//increase speed
		distance += -velocity;
		if (distance < 4000) {
			firespeed = -15;
		}
		else if (distance < 10000) {
			firespeed = -18;
		}
		else {
			firespeed = -22;
		}

		shape.setPosition(sf::Vector2f(sprite.getPosition().x + 5, sprite.getPosition().y + 15));
		if (sprite.getPosition().x <= -500) {
			float height = rand() % 640;
			sprite.setPosition(sf::Vector2f(1270, height));
		}
		sprite.move(sf::Vector2f(firespeed, 0));
		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			spriterect.left += 160;
			if (spriterect.left > 320) {
				spriterect.left = 0;
			}
			clock.restart();
		}
		sprite.setTextureRect(spriterect);
	}

	void reset() {
		sprite.setPosition(sf::Vector2f(1270, 300));
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

class Fireball {
public:
	bool fire_ball_sprite = false;
	bool shoot = false;

	Fireball() {
		texture.loadFromFile("images/red_fireball-sheet.png");
		rect = sf::IntRect(0, 0, 16, 15);
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		sprite.setPosition(sf::Vector2f(400, -50));
	}

	void draw(sf::RenderWindow &window) {
		for (int i = 0; i < 2; i++) {
			if (shoot) window.draw(sprite);
		}
	}

	void fire(sf::Sprite shooter, sf::Sprite charec, bool showshooter, bool close) {
		if (showshooter) {
			if (!shoot && !close) {
				if (charec.getPosition().x < shooter.getPosition().x) {
					sprite.setPosition(sf::Vector2f(shooter.getPosition().x + 3, shooter.getPosition().y + 42));
					shoot = true;
					rect.top = 15;
					firespeed = -7;
				}
				else {
					sprite.setPosition(sf::Vector2f(shooter.getPosition().x + 46, shooter.getPosition().y + 42));
					shoot = true;
					rect.top = 0;
					firespeed = 7;
				}
				sprite.setTextureRect(rect);
			}
			if (shoot || close) {
				sprite.move(firespeed, 0);
				if (clock.getElapsedTime().asSeconds() > 0.15f) {
					rect.left += 15;
					if (rect.left > 17) {
						rect.left = 0;
					}
					clock.restart();
				}
				sprite.setTextureRect(rect);
				if (charec.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
					shoot = false;
				}
				if (sprite.getPosition().x < shooter.getPosition().x - 400 || sprite.getPosition().x > shooter.getPosition().x + 400) {
					shoot = false;
					sprite.setPosition(sf::Vector2f(sprite.getPosition().x, -50));
				}
			}
		}
		else {
			shoot = false;
		}
	}

	void collision(sf::Sprite charec) {
		fire_ball_sprite = false;
		if (charec.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
			fire_ball_sprite = true;
		}
		else if (!fire_ball_sprite) fire_ball_sprite = false;
	}

	void move(sf::Vector2f speed) {
		sprite.move(speed);
	}

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect rect;
	bool state = false;
	int firespeed;
	sf::Clock clock;
};

class TextBox {
public:
	TextBox(int size, sf::Color color, bool select, float x, float y) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = select;
		font.loadFromFile(FONT);
		textbox.setFont(font);
		textbox.setPosition(sf::Vector2f(x, y));

		if (select) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}

	void setSelected(bool select) {
		isSelected = select;
		if (!select) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length() - 1; i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	void setLimit(bool haslimit, int lim) {
		hasLimit = haslimit;
		limit = lim;
	}

	std::string getText() {
		return text.str();
	}

	void draw(sf::RenderWindow &window) {
		window.draw(textbox);
	}

	void typedOn(sf::Event input, int *screen, sf::RenderWindow &window, sf::Sprite &charec, int *scoresource) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
					if (charTyped == ENTER_KEY) {
						charec.setPosition(sf::Vector2f(600, 400));
						Enter(&text.str());
						*screen = 0;
						*scoresource = 0;
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

	void reset() {
		while (text.str().length() > 0)
		{
			deleteLastChar();
		}
	}
private:
	sf::Clock clock;
	sf::Text textbox;
	sf::Font font;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY) {
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}
	
	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}

	void Enter(std::string *namesource) {
		std::fstream  name("ScoreBoard.txt", std::ios::app);
		if (name.is_open()) {
			name << *namesource << std::endl;
			name.close();
		}
	}
};