#pragma once
#include "bullet.h"
#include "Enemy.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#define size_Maskboy 3
#define size_Bat 3
#define size_shooter 3

class Enemy_Bullet {
public:
	Enemy_Bullet();
	bool hit = false;
	//Enemy
	void draw(sf::RenderWindow &window) {
		/*for (int i = 0; i < size_Enemy; i++) {
			if (showenemy[i]) enemy[i].draw(window);
			hp[i].draw(window);
		}*/
		for (int i = 0; i < size_Maskboy; i++) {
			maskboy[i].draw(window);
		}
		for (int i = 0; i < size_Bat; i++) {
			bat[i].draw(window);
		}
		for (int i = 0; i < size_shooter; i++) {
			shooter[i].draw(window);
		}
	}

	void move(sf::Vector2f velocity) {
		for (int i = 0; i < size_Enemy; i++) {
			enemy[i].move(velocity);
			hp[i].move(velocity);
		}
		for (int i = 0; i < size_Maskboy; i++) {
			maskboy[i].move(velocity);
		}
		for (int i = 0; i < size_Bat; i++) {
			bat[i].move(velocity);
		}
		for (int i = 0; i < size_shooter; i++) {
			shooter[i].move(velocity);
		}
	}

	void automove(sf::Vector2f speed, sf::Sprite sprite, GameObject object[23], bool fencing, int *damage) {
		//collision object
		for (int j = 0; j < 23; j++) {
			for (int i = 0; i < size_Maskboy; i++) {
				if (sprite.getPosition().x > maskboy[i].sprite.getPosition().x - 500 && sprite.getPosition().x < maskboy[i].sprite.getPosition().x + 400) {
					if (maskboy[i].sprite.getGlobalBounds().intersects(object[j].sprite.getGlobalBounds())) {
						if (maskboy[i].sprite.getPosition().x > object[j].sprite.getPosition().x) {
							right[i] = true;
							left[i] = false;
						}
						if (maskboy[i].sprite.getPosition().x < object[j].sprite.getPosition().x) {
							left[i] = true;
							right[i] = false;
						}
						i = 2;
						j = 23;
					}
					else if (j == 22) {
						right[i] = false;
						left[i] = false;
					}
				}
			}
			for (int k = 0; k < size_shooter; k++) {
				if (sprite.getPosition().x > shooter[k].sprite.getPosition().x - 500 && sprite.getPosition().x < shooter[k].sprite.getPosition().x + 400) {
					if (shooter[k].sprite.getGlobalBounds().intersects(object[j].sprite.getGlobalBounds())) {
						if (shooter[k].sprite.getPosition().x > object[j].sprite.getPosition().x) {
							r_shoot[k] = true;
							l_shoot[k] = false;
						}
						if (shooter[k].sprite.getPosition().x < object[j].sprite.getPosition().x) {
							l_shoot[k] = true;
							r_shoot[k] = false;
						}
						k = 2;
						j = 23;
					}
					else if (j == 22) {
						l_shoot[k] = false;
						r_shoot[k] = false;
					}
				}
			}
		}
		//collision sprite and walk
		for (int i = 0; i < size_Maskboy; i++) {
			if (sprite.getPosition().x > maskboy[i].sprite.getPosition().x - 500 && sprite.getPosition().x < maskboy[i].sprite.getPosition().x + 400) {
				if (!sprite.getGlobalBounds().intersects(maskboy[i].sprite.getGlobalBounds())) {
					attack[i] = false;
					maskboy[i].spriterect.left = 0;
					if (sprite.getPosition().x < maskboy[i].sprite.getPosition().x) {
						if (!right[i]) {
							maskboy[i].spriterect.top = 112;
							maskboy[i].move(-speed);
						}
					}
					else {
						if (!left[i]) {
							maskboy[i].spriterect.top = 0;
							maskboy[i].move(speed);
						}
					}
				}
				else if(!attack[i]) {
					if (cooldown[i].getElapsedTime().asSeconds() >= 2.0f) {
						attack[i] = true;
						cooldown[i].restart();
					}
				}
			}
			//attack
			if (attack[i]) {
				if (clockmask[i].getElapsedTime().asSeconds() > 0.1f) {
					maskboy[i].spriterect.left += 145;
					if (maskboy[i].spriterect.left > 1014 || fencing) {
						attack[i] = false;
						maskboy[i].spriterect.left = 0;
					}
					if (maskboy[i].spriterect.left > 800) {
						*damage += 1;
					}
					clockmask[i].restart();
				}
			}
			maskboy[i].setup();
		}
		for (int i = 0; i < size_shooter; i++) {
			if (sprite.getPosition().x > shooter[i].sprite.getPosition().x - 500 && sprite.getPosition().x < shooter[i].sprite.getPosition().x + 400) {
				if (!sprite.getGlobalBounds().intersects(shooter[i].sprite.getGlobalBounds())) {
					attackshoot[i] = false;
					shooter[i].spriterect.left = 0;
					if (sprite.getPosition().x < shooter[i].sprite.getPosition().x) {
						if (!r_shoot[i]) {
							shooter[i].spriterect.top = 0;
						}
					}
					else {
						if (!l_shoot[i]) {
							shooter[i].spriterect.top = 70;
						}
					}
				}
				else if (!attackshoot[i]) {
					
				}
			}
			shooter[i].setup();
		}
		//fly bat
		for (int i = 0; i < size_Bat; i++) {
			if (bat[i].sprite.getPosition().y <= 100) statebat[i] = true;
			else if (bat[i].sprite.getPosition().y >= 350) statebat[i] = false;
			if (statebat[i]) {
				bat[i].move(sf::Vector2f(0, 1));
			}
			else {
				bat[i].move(sf::Vector2f(0, -1));
			}
			if (clockbat[i].getElapsedTime().asSeconds() > 0.2f) {
				bat[i].spriterect.left += 150;
				if (bat[i].spriterect.left > 1049) {
					bat[i].spriterect.left = 0;
				}
				clockbat[i].restart();
			}
			bat[i].setup();
		}
	}

	//Bullet
	bool isFire = false;
	Bullet newbullet_r = Bullet("images/bullet_r.png");
	std::vector<Bullet> bullet_r;
	Bullet newbullet_l = Bullet("images/bullet_l.png");
	std::vector<Bullet> bullet_l;

	void setPos(sf::Sprite charec, bool check, bool checkleft, bool checkright) {
		if (check == false) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				if (isFire == false) {
					if (checkright) {
						newbullet_r.setPos(sf::Vector2f(charec.getPosition().x + 50, charec.getPosition().y + 50));
						bullet_r.push_back(newbullet_r);
					}
					else if (checkleft) {
						newbullet_l.setPos(sf::Vector2f(charec.getPosition().x, charec.getPosition().y + 50));
						bullet_l.push_back(newbullet_l);
					}
				}
				isFire = true;
			}
			else {
				isFire = false;
			}
		}
	}

	/*void fire() {
		for (int i = 0; i < bullet_r.size(); i++) {
			bullet_r[i].fire_r(15);
		}
		for (int i = 0; i < bullet_l.size(); i++) {
			bullet_l[i].fire_l(15);
		}
	}*/

	void draw_bullet(sf::RenderWindow &window) {
		for (int i = 0; i < bullet_r.size(); i++) {
			if (bullet_r[i].state) bullet_r[i].draw(window);
		}
		for (int i = 0; i < bullet_l.size(); i++) {
			if (bullet_l[i].state) bullet_l[i].draw(window);
		}
	}
	//collision bullet
	void collision(sf::Sprite charec) {
		for (int i = 0; i < bullet_r.size(); i++) {
			if (bullet_r[i].bullet.getPosition().x > 1200) bullet_r[i].state = false;
			for (int j = 0; j < size_Enemy; j++) {
				if (bullet_r[i].bullet.getGlobalBounds().intersects(enemy[j].enemy.getGlobalBounds()) && bullet_r[i].state) {
					hp[j].damage(30);
					if (hp[j].width <= 0) showenemy[j] = false;
					if(showenemy[j]) bullet_r[i].state = false;
				}
			}
			bullet_r[i].fire_r(15);
		}
		for (int i = 0; i < bullet_l.size(); i++) {
			if (bullet_l[i].bullet.getPosition().x < 0) bullet_l[i].state = false;
			for (int j = 0; j < size_Enemy; j++) {
				if (bullet_l[i].bullet.getGlobalBounds().intersects(enemy[j].enemy.getGlobalBounds()) && bullet_l[i].state) {
					hp[j].damage(30);
					if (hp[j].width <= 0) showenemy[j] = false;
					if (showenemy[j]) bullet_l[i].state = false;
				}
			}
			bullet_l[i].fire_l(15);
		}
	}
	//collision sprite and enemy for fencing
	void collispriteenemy(sf::Sprite charec, bool fencing) {
		for (int i = 0; i < size_Enemy; i++) {
			if (charec.getGlobalBounds().intersects(enemy[i].enemy.getGlobalBounds())) {
				if (fencing && !hit) {
					hp[i].damage(30);
					hit = true;
				}
				else if (!fencing) hit = false;
			}
			if (hp[i].width <= 0) showenemy[i] = false;
		}
	}

	//collision sprite and enemy for hit damage
	void hitenemy(sf::Sprite sprite, bool *collision) {
		*collision = false;
		for (int i = 0; i < size_Bat; i++) {
			if (sprite.getGlobalBounds().intersects(bat[i].sprite.getGlobalBounds())) {
				*collision = true;
			}
			else if(!*collision){
				*collision = false;
			}
		}
		for (int i = 0; i < size_Maskboy; i++) {
			if (sprite.getGlobalBounds().intersects(maskboy[i].sprite.getGlobalBounds())) {
				*collision = true;
			}
			else if (!*collision) {
				*collision = false;
			}
		}
		for (int i = 0; i < size_shooter; i++) {
			if (sprite.getGlobalBounds().intersects(shooter[i].sprite.getGlobalBounds())) {
				*collision = true;
			}
			else if (!*collision) {
				*collision = false;
			}
		}
	}
private:

	//Enemy
	Enemy enemy[2] = {
		Enemy("images/enemy.png", 3285, 484),
		Enemy("images/enemy.png", 3285, 300)
	};
	bool showenemy[2] = { true, true };

	int size_Enemy = sizeof(enemy) / sizeof(enemy[0]);

	//maskboy
	GameSheet maskboy[size_Maskboy] = {
		GameSheet("images/enemysheet.png", 3383, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 4506, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 6999, 483, 0, 0, 145, 112)
	};

	sf::Clock clockmask[size_Maskboy];
	sf::Clock cooldown[size_Maskboy];
	bool right[size_Maskboy] = { false, false };
	bool left[size_Maskboy] = { false, false };
	bool attack[size_Maskboy] = { false, false };

	//bat
	GameSheet bat[size_Bat] = {
		GameSheet("images/__Bat02_Fly_000-sheet.png", 1117, 250, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 2123, 300, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 8212, 120, 0, 0, 150, 100)
	};

	bool statebat[size_Bat] = { false, false };
	sf::Clock clockbat[size_Bat];

	//shooter
	GameSheet shooter[size_shooter] = {
		GameSheet("images/shooter.png", 1748, 412, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 5556, 302, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 10486, 302, 0, 0, 65, 70)
	};

	sf::Clock clockshooter[size_shooter];
	sf::Clock cooldownshooter[size_shooter];
	bool r_shoot[size_shooter] = { false,false };
	bool l_shoot[size_shooter] = { false,false };
	bool attackshoot[size_shooter] = { false,false };

	//Hp
	Hp_Enemy hp[2] = {
		Hp_Enemy(enemy[0].enemy.getPosition().x, enemy[0].enemy.getPosition().y),
		Hp_Enemy(enemy[1].enemy.getPosition().x, enemy[1].enemy.getPosition().y)
	};
};