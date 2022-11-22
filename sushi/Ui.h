#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Object.h"
#include "Enemy_Bullet.h"
#include "Object.h"
#define heartsize 5

class Hp_Player {
public:
	bool temp = false;
	bool temp2 = false;
	bool temp3 = false;
	int tempp = 0;

	int sizeheart = heartsize;

	void damage(bool collision, int damage, bool collision_sp, int *d, bool firehit) {
		if (temp != collision) {
			if (clock.getElapsedTime().asSeconds() > 1.5f && collision) {
				sizeheart--;
				if (*d < heartsize) {
					*d++;
				}
				clock.restart();
			}
			temp = collision;
		}
		//collision meteor
		if (temp2 != collision_sp) {
			if (clock.getElapsedTime().asSeconds() > 1.5f && collision_sp) {
				sizeheart--;
				if (*d < heartsize) {
					*d++;
				}
				clock.restart();
			}
			temp2 = collision_sp;
		}
		if (temp3 != firehit) {
			if (clock.getElapsedTime().asSeconds() > 1.5f && firehit) {
				sizeheart--;
				if (*d < heartsize) {
					*d++;
				}
				clock.restart();
			}
			temp3 = firehit;
		}
		if (*d < heartsize) {
			if (tempp != damage) {
				*d++;
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

	void draw(sf::RenderWindow &window, int d) {
		for (int i = 0; i < sizeheart; i++) {
			window.draw(heart[i].sprite);
		}
		for (int i = 0; i < d; i++) {
			window.draw(empty[i].sprite);
		}
	}

	void reset() {
		sizeheart = heartsize;
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

	ActiveObject active;
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
	FontText fonttext = FontText(FONT, "PAUSE", 370, 120, sf::Color::White, 150);
	FontText overtext = FontText(FONT, "GAME OVER", 214, 175, sf::Color::Red, 150);
	Pause() {
		shape.setSize(sf::Vector2f(1300, 720));
		shape.setPosition(sf::Vector2f(0, 0));
		shape.setFillColor(sf::Color::Color(20, 20, 20, 180));
	}
	//pause game
	void pausegame(sf::RenderWindow &window, bool *pause, bool stategame, int *screen, bool *leftmouseclick) {
		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				*pause = true;
				clock.restart();
			}
		}
		if (*pause && !stategame) {
			window.draw(shape);
			window.draw(fonttext.text);
			window.draw(resume.sprite);
			window.draw(mainmenu.sprite);

			if (resume.sprite.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (!*leftmouseclick) {
						*screen = 1;
						*pause = false;
					}
					*leftmouseclick = true;
				}
				else {
					*leftmouseclick = false; 
				}
			}
			if (mainmenu.sprite.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (!*leftmouseclick) {
						*screen = 0;
						*pause = false;
					}
					*leftmouseclick = true;
				}
				else {
					*leftmouseclick = false;
				}
			}

			
		}
	}
	//gameover
	void gameover(sf::RenderWindow &window, bool *pause, bool stategame, int *screen, bool *leftmouseclick, int *scoresource, int scorescreen) {
		if (stategame) {
			*pause = true;
			//input score borad
			std::fstream  score("ScoreBoard.txt", std::ios::app);
			if (score.is_open()) {
				*scoresource += scorescreen / 100;
				score << *scoresource << std::endl;
				score.close();
			}
			*screen = 4;
		}
	}
private:
	sf::RectangleShape shape;
	sf::Clock clock;
	sf::Mouse mouse;
	GameObject resume = GameObject("images/resume.png", 473, 350);
	GameObject mainmenu = GameObject("images/mainmenu.png", 473, 510);
};

class Scoreboard {
public:
	void showscore(sf::RenderWindow &window) {
		GameObject jumpgun = GameObject("images/Sprite_sushi/jump - gun.png", 260, 55);
		GameObject jumpsword = GameObject("images/Sprite_sushi/jump - sword.png", 940, 55);
		FontText head = FontText(FONT, "top 5 scoreboard sushi", 370, 86, sf::Color::Cyan, 40);

		window.draw(jumpgun.sprite);
		window.draw(jumpsword.sprite);
		window.draw(head.text);
		infile.open("ScoreBoard.txt");

		int pointss;
		std::string name;
		std::string textString;
		std::string pointString;

		while (std::getline(infile, pointString))
		{
			std::getline(infile, name);
			pointss = std::stoi(pointString);
			Point.push_back(pointss);
			Name.push_back(name);

			countline++;
			name = "";
			pointString = "";
			pointss = 0;
		}
		
		for (int i = 0; i < countline; i++) {
			for (int j = 0; j < countline; j++) {
				if (Point[i] > Point[j]) {
					int temp = Point[i];
					Point[i] = Point[j];
					Point[j] = temp;

					std::string txt = Name[i];
					Name[i] = Name[j];
					Name[j] = txt;
				}
			}
		}

		for (int i = 0; i < countline; i++) {
			if (i <= 4) {
				std::string point_string = std::to_string(Point[i]);
				FontText txt = FontText(FONT, Name[i], 372, 174 + (60 * i), sf::Color::White, 40);
				window.draw(txt.text);
				FontText txt_t = FontText(FONT, point_string, 819, 174 + (60 * i), sf::Color::White, 40);
				window.draw(txt_t.text);
			}
		}

		countline = 0;
		Point.clear();
		Name.clear();
		infile.close();
	}
private:
	std::ifstream infile;
	std::vector<int> Point;
	std::vector<std::string> Name;
	int countline = 0;
};