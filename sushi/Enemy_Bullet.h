#pragma once
#include "bullet.h"
#include "Enemy.h"
#include "Object.h"
#include "sounds.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define size_Maskboy 6
#define size_Bat 4
#define size_shooter 6
#define mapcount 2
#define bat_point 10
#define maskboy_point 5
#define shooter_point 6

class Enemy_Bullet {
public:
	Enemy_Bullet();
	bool hit = false;

	bool fireball_hit = false;
	//Enemy
	void draw(sf::RenderWindow &window, int selectmap) {
		for (int i = 0; i < size_Maskboy; i++) {
			if(showmaskboy[selectmap][i]) maskboy[selectmap][i].draw(window);
			hp_maskboy[selectmap][i].draw(window);
		}
		for (int i = 0; i < size_Bat; i++) {
			if(showbat[selectmap][i]) bat[selectmap][i].draw(window);
			hp[selectmap][i].draw(window);
		}
		for (int i = 0; i < size_shooter; i++) {
			if(showshooter[selectmap][i]) shooter[selectmap][i].draw(window);
			hp_shooter[selectmap][i].draw(window);
		}
		fireball.draw(window);
	}

	void move(sf::Vector2f velocity, int selectmap) {
		for (int i = 0; i < size_Maskboy; i++) {
			maskboy[selectmap][i].move(velocity);
			hp_maskboy[selectmap][i].move(velocity);
		}
		for (int i = 0; i < size_Bat; i++) {
			bat[selectmap][i].move(velocity);
			hp[selectmap][i].move(velocity);
		}
		for (int i = 0; i < size_shooter; i++) {
			shooter[selectmap][i].move(velocity);
			hp_shooter[selectmap][i].move(velocity);
		}
		fireball.move(velocity);
	}

	void automove(sf::Vector2f speed, sf::Sprite sprite, GameObject object[36], bool fencing, int *damage, int selectmap) {
		//collision object
		for (int j = 0; j < 36; j++) {
			for (int i = 0; i < size_Maskboy; i++) {
				if (sprite.getPosition().x > maskboy[selectmap][i].sprite.getPosition().x - 500 && sprite.getPosition().x < maskboy[selectmap][i].sprite.getPosition().x + 400) {
					if (maskboy[selectmap][i].sprite.getGlobalBounds().intersects(object[6].sprite.getGlobalBounds())) {
						if (maskboy[selectmap][i].sprite.getPosition().x > object[j].sprite.getPosition().x) {
							right[selectmap][i] = true;
							left[selectmap][i] = false;
						}
						if (maskboy[selectmap][i].sprite.getPosition().x < object[j].sprite.getPosition().x) {
							left[selectmap][i] = true;
							right[selectmap][i] = false;
						}
						i = size_Maskboy;
						j = 36;
					}
					if (maskboy[selectmap][i].sprite.getGlobalBounds().intersects(object[j].sprite.getGlobalBounds())) {
						if (maskboy[selectmap][i].sprite.getPosition().x > object[j].sprite.getPosition().x) {
							right[selectmap][i] = true;
							left[selectmap][i] = false;
						}
						if (maskboy[selectmap][i].sprite.getPosition().x < object[j].sprite.getPosition().x) {
							left[selectmap][i] = true;
							right[selectmap][i] = false;
						}
						i = size_Maskboy;
						j = 36;
					}
					else if (j == 35) {
						right[selectmap][i] = false;
						left[selectmap][i] = false;
					}
				}
			}
			for (int k = 0; k < size_shooter; k++) {
				if (sprite.getPosition().x > shooter[selectmap][k].sprite.getPosition().x - 500 && sprite.getPosition().x < shooter[selectmap][k].sprite.getPosition().x + 400) {
					if (shooter[selectmap][k].sprite.getGlobalBounds().intersects(object[j].sprite.getGlobalBounds())) {
						if (shooter[selectmap][k].sprite.getPosition().x > object[j].sprite.getPosition().x) {
							r_shoot[selectmap][k] = true;
							l_shoot[selectmap][k] = false;
						}
						if (shooter[selectmap][k].sprite.getPosition().x < object[j].sprite.getPosition().x) {
							l_shoot[selectmap][k] = true;
							r_shoot[selectmap][k] = false;
						}
						k = size_shooter;
						j = 36;
					}
					else if (j == 35) {
						l_shoot[selectmap][k] = false;
						r_shoot[selectmap][k] = false;
					}
				}
			}
		}
		//collision sprite and walk
		for (int i = 0; i < size_Maskboy; i++) {
			if (sprite.getPosition().x > maskboy[selectmap][i].sprite.getPosition().x - 500 && sprite.getPosition().x < maskboy[selectmap][i].sprite.getPosition().x + 400) {
				if (!sprite.getGlobalBounds().intersects(maskboy[selectmap][i].sprite.getGlobalBounds())) {
					//printf("not hit\n");
					attack[selectmap][i] = false;
					maskboy[selectmap][i].spriterect.left = 0;
					if (sprite.getPosition().x > maskboy[selectmap][i].sprite.getPosition().x + 2) {
						if (!left[selectmap][i]) {
							maskboy[selectmap][i].spriterect.top = 0;
							maskboy[selectmap][i].move(speed);
						}
					}
					else if(sprite.getPosition().x < maskboy[selectmap][i].sprite.getPosition().x - 2){
						if (!right[selectmap][i]) {
							maskboy[selectmap][i].spriterect.top = 112;
							maskboy[selectmap][i].move(-speed);
						}
					}
				}
				else if(!attack[selectmap][i]) {
					if (cooldown[selectmap][i].getElapsedTime().asSeconds() >= 2.0f) {
						attack[selectmap][i] = true;
						cooldown[selectmap][i].restart();
					}
				}
				else {
					//printf("hit\n");
				}
			}
			//attack
			if (attack[selectmap][i] && showmaskboy[selectmap][i]) {
				if (clockmask[selectmap][i].getElapsedTime().asSeconds() > 0.07f) {
					maskboy[selectmap][i].spriterect.left += 145;
					if (maskboy[selectmap][i].spriterect.left > 1014 || fencing) {
						attack[selectmap][i] = false;
						maskboy[selectmap][i].spriterect.left = 0;
					}
					if (maskboy[selectmap][i].spriterect.left > 800) {
						*damage += 1;
					}
					clockmask[selectmap][i].restart();
				}
			}
			maskboy[selectmap][i].setup();
			hp_maskboy[selectmap][i].setup(maskboy[selectmap][i].sprite);
		}
		//shooter
		for (int i = 0; i < size_shooter; i++) {
			if (sprite.getPosition().x > shooter[selectmap][i].sprite.getPosition().x - 500 && sprite.getPosition().x < shooter[selectmap][i].sprite.getPosition().x + 400) {
				if (!sprite.getGlobalBounds().intersects(shooter[selectmap][i].sprite.getGlobalBounds())) {
					shooter[selectmap][i].spriterect.left = 0;
					if (sprite.getPosition().x < shooter[selectmap][i].sprite.getPosition().x) {
						//if (!r_shoot[selectmap][i]) {
						shooter[selectmap][i].spriterect.top = 0;
						shooter[selectmap][i].setup();
						//}
					}
					else {
						//if (!l_shoot[selectmap][i]) {
						shooter[selectmap][i].spriterect.top = 70;
						shooter[selectmap][i].setup();
						//}
					}
					fireball.fire(shooter[selectmap][i].sprite, sprite, showshooter[selectmap][i], false);
					fireball.collision(sprite);

					fireball_hit = false;
					if (fireball.fire_ball_sprite) {
						fireball_hit = true;
					}
					else if (!fireball_hit) fireball_hit = false;
				}
				i = size_shooter;
			}
			else if(i == size_shooter - 1) {
				fireball.fire(shooter[selectmap][i].sprite, sprite, showshooter[selectmap][i], true);
			}
			hp_shooter[selectmap][i].setup(shooter[selectmap][i].sprite);
		}
		//fly bat
		for (int i = 0; i < size_Bat; i++) {
			if (bat[selectmap][i].sprite.getPosition().y <= 100) statebat[selectmap][i] = true;
			else if (bat[selectmap][i].sprite.getPosition().y >= 350) statebat[selectmap][i] = false;
			if (statebat[selectmap][i]) {
				bat[selectmap][i].move(sf::Vector2f(0, 1));
			}
			else {
				bat[selectmap][i].move(sf::Vector2f(0, -1));
			}
			if (clockbat[selectmap][i].getElapsedTime().asSeconds() > 0.2f) {
				bat[selectmap][i].spriterect.left += 150;
				if (bat[selectmap][i].spriterect.left > 1049) {
					bat[selectmap][i].spriterect.left = 0;
				}
				clockbat[selectmap][i].restart();
			}
			bat[selectmap][i].setup();
			hp[selectmap][i].setup(bat[selectmap][i].sprite);
		}
	}

	//Bullet
	bool isFire = false;
	Bullet newbullet_r = Bullet("images/bullet_r.png");
	std::vector<Bullet> bullet_r;
	Bullet newbullet_l = Bullet("images/bullet_l.png");
	std::vector<Bullet> bullet_l;

	//Fire sounds
	Sounds sounds;
	void setPos(sf::Sprite charec, bool check, bool checkleft, bool checkright) {
		if (check == false) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				if (isFire == false) {
					sounds.fire_effect();
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

	void draw_bullet(sf::RenderWindow &window) {
		for (int i = 0; i < bullet_r.size(); i++) {
			if (bullet_r[i].state) bullet_r[i].draw(window);
		}
		for (int i = 0; i < bullet_l.size(); i++) {
			if (bullet_l[i].state) bullet_l[i].draw(window);
		}
	}
	//collision bullet
	void collision(sf::Sprite charec, int *point, int selectmap) {
		//bullet right
		for (int i = 0; i < bullet_r.size(); i++) {
			//bullet out range
			if (bullet_r[i].bullet.getPosition().x > 1200) bullet_r[i].state = false;
			//collision bullet and enemy
			for (int j = 0; j < size_Bat; j++) {
				if (bullet_r[i].bullet.getGlobalBounds().intersects(bat[selectmap][j].sprite.getGlobalBounds()) && bullet_r[i].state) {
					//hp damage
					hp[selectmap][j].damage(30);
					//state enemy
					if (hp[selectmap][j].width <= 0 && showbat[selectmap][j]) {
						showbat[selectmap][j] = false;
						*point += bat_point;
					}
					//state bullet
					if(showbat[selectmap][j]) bullet_r[i].state = false;
				}
			}
			for (int j = 0; j < size_Maskboy; j++) {
				if (bullet_r[i].bullet.getGlobalBounds().intersects(maskboy[selectmap][j].sprite.getGlobalBounds()) && bullet_r[i].state) {
					hp_maskboy[selectmap][j].damage(30);
					if (hp_maskboy[selectmap][j].width <= 0 && showmaskboy[selectmap][j]) {
						showmaskboy[selectmap][j] = false;
						*point += maskboy_point;
					}
					if (showmaskboy[selectmap][j]) bullet_r[i].state = false;
				}
			}
			for (int j = 0; j < size_shooter; j++) {
				if (bullet_r[i].bullet.getGlobalBounds().intersects(shooter[selectmap][j].sprite.getGlobalBounds()) && bullet_r[i].state) {
					hp_shooter[selectmap][j].damage(30);
					if (hp_shooter[selectmap][j].width <= 0 && showshooter[selectmap][j]) {
						showshooter[selectmap][j] = false;
						*point += shooter_point;
					}
					if (showshooter[selectmap][j]) bullet_r[i].state = false;
				}
			}
			//fire
			bullet_r[i].fire_r(15);
		}
		//bullet left
		for (int i = 0; i < bullet_l.size(); i++) {
			if (bullet_l[i].bullet.getPosition().x < 0) bullet_l[i].state = false;
			for (int j = 0; j < size_Bat; j++) {
				if (bullet_l[i].bullet.getGlobalBounds().intersects(bat[selectmap][j].sprite.getGlobalBounds()) && bullet_l[i].state) {
					hp[selectmap][j].damage(30);
					if (hp[selectmap][j].width <= 0 && showbat[selectmap][j]) {
						showbat[selectmap][j] = false;
						*point += bat_point;
					}
					if (showbat[selectmap][j]) bullet_l[i].state = false;
				}
			}
			for (int j = 0; j < size_Maskboy; j++) {
				if (bullet_l[i].bullet.getGlobalBounds().intersects(maskboy[selectmap][j].sprite.getGlobalBounds()) && bullet_l[i].state) {
					hp_maskboy[selectmap][j].damage(30);
					if (hp_maskboy[selectmap][j].width <= 0 && showmaskboy[selectmap][j]) {
						showmaskboy[selectmap][j] = false;
						*point += maskboy_point;
					}
					if (showmaskboy[selectmap][j]) bullet_l[i].state = false;
				}
			}
			for (int j = 0; j < size_shooter; j++) {
				if (bullet_l[i].bullet.getGlobalBounds().intersects(shooter[selectmap][j].sprite.getGlobalBounds()) && bullet_l[i].state) {
					hp_shooter[selectmap][j].damage(30);
					if (hp_shooter[selectmap][j].width <= 0 && showshooter[selectmap][j]) {
						showshooter[selectmap][j] = false;
						*point += shooter_point;
					}
					if (showshooter[selectmap][j]) bullet_l[i].state = false;
				}
			}
			bullet_l[i].fire_l(15);
		}
	}

	//collision sprite and enemy for fencing
	void collispriteenemy(sf::Sprite charec, bool fencing, int *point, int selectmap) {
		for (int i = 0; i < size_Bat; i++) {
			if (charec.getGlobalBounds().intersects(bat[selectmap][i].sprite.getGlobalBounds())) {
				if (fencing && !hit) {
					if (charec.getTextureRect().left == 2329 || charec.getTextureRect().left == 785) {
						hp[selectmap][i].damage(20);
						hit = true;
					}
				}
				else if (!fencing) hit = false;
			}
			if (hp[selectmap][i].width <= 0 && showbat[selectmap][i]) {
				*point += 10;
				showbat[selectmap][i] = false;
			}
		}
		for (int i = 0; i < size_Maskboy; i++) {
			if (charec.getGlobalBounds().intersects(maskboy[selectmap][i].sprite.getGlobalBounds())) {
				if (fencing && !hit) {
					if (charec.getTextureRect().left == 2329 || charec.getTextureRect().left == 785) {
						hp_maskboy[selectmap][i].damage(20);
						hit = true;
					}
				}
				else if (!fencing) hit = false;
			}
			if (hp_maskboy[selectmap][i].width <= 0 && showmaskboy[selectmap][i]) {
				*point += 5;
				showmaskboy[selectmap][i] = false;
			}
		}
		for (int i = 0; i < size_shooter; i++) {
			if (charec.getGlobalBounds().intersects(shooter[selectmap][i].sprite.getGlobalBounds())) {
				if (fencing && !hit) {
					if (charec.getTextureRect().left == 2329 || charec.getTextureRect().left == 785) {
						hp_shooter[selectmap][i].damage(20);
						hit = true;
					}
				}
				else if (!fencing) hit = false;
			}
			if (hp_shooter[selectmap][i].width <= 0 && showshooter[selectmap][i]) {
				*point += 6;
				showshooter[selectmap][i] = false;
			}
		}
	}

	//collision sprite and enemy for hit damage
	void hitenemy(sf::Sprite sprite, bool *collision, bool fencing, int selectmap) {
		*collision = false;
		for (int i = 0; i < size_Bat; i++) {
			if (sprite.getGlobalBounds().intersects(bat[selectmap][i].shape.getGlobalBounds()) && showbat[selectmap][i] && !fencing) {
				*collision = true;
			}
			else if(!*collision){
				*collision = false;
			}
		}
		for (int i = 0; i < size_Maskboy; i++) {
			if (sprite.getGlobalBounds().intersects(maskboy[selectmap][i].shape.getGlobalBounds()) && showmaskboy[selectmap][i] && !fencing) {
				*collision = true;
			}
			else if (!*collision) {
				*collision = false;
			}
		}
		for (int i = 0; i < size_shooter; i++) {
			if (sprite.getGlobalBounds().intersects(shooter[selectmap][i].shape.getGlobalBounds()) && showshooter[selectmap][i] && !fencing) {
				*collision = true;
			}
			else if (!*collision) {
				*collision = false;
			}
		}
	}

	void init() {
		//maskboy 01
		maskboy[0][0].sprite.setPosition(3383, 483),
		maskboy[0][1].sprite.setPosition(4506, 483);
		maskboy[0][2].sprite.setPosition(6999, 483);
		//useless
		maskboy[0][3].sprite.setPosition(6999, 800);
		maskboy[0][4].sprite.setPosition(6999, 800);
		maskboy[0][5].sprite.setPosition(6999, 800);
		//maskboy 02
		maskboy[1][0].sprite.setPosition(2432, 483);
		maskboy[1][1].sprite.setPosition(5076, 483);
		maskboy[1][2].sprite.setPosition(6738, 483);
		maskboy[1][3].sprite.setPosition(7450, 483);
		maskboy[1][4].sprite.setPosition(10878, 483);
		maskboy[1][5].sprite.setPosition(13045, 368);
		for (int i = 0; i < mapcount; i++) {
			for (int j = 0; j < size_Maskboy; j++) {
				showmaskboy[i][j] = true;
				hp_maskboy[i][j].reset();
			}
		}

		//bat 01
		bat[0][0].sprite.setPosition(1117, 250);
		bat[0][1].sprite.setPosition(2123, 300);
		bat[0][2].sprite.setPosition(8212, 120);
		//useless
		bat[0][3].sprite.setPosition(50000, 800);
		//bat 02
		bat[1][0].sprite.setPosition(3296, 206);
		bat[1][1].sprite.setPosition(5494, 187);
		bat[1][2].sprite.setPosition(8104, 329);
		bat[1][3].sprite.setPosition(11655, 134);
		for (int i = 0; i < mapcount; i++) {
			for (int j = 0; j < size_Bat; j++) {
				showbat[i][j] = true;
				hp[i][j].reset();
			}
		}

		//shooter 01
		shooter[0][0].sprite.setPosition(1748, 412);
		shooter[0][1].sprite.setPosition(5556, 302);
		shooter[0][2].sprite.setPosition(10486, 302);
		//useless
		shooter[0][3].sprite.setPosition(10486, 800);
		shooter[0][4].sprite.setPosition(10486, 800);
		shooter[0][5].sprite.setPosition(10486, 800);
		//shooter 02
		shooter[1][0].sprite.setPosition(2052, 415);
		shooter[1][1].sprite.setPosition(4577, 415);
		shooter[1][2].sprite.setPosition(6233, 461);
		shooter[1][3].sprite.setPosition(7317, 285);
		shooter[1][4].sprite.setPosition(9331, 355);
		shooter[1][5].sprite.setPosition(11039, 231);
		for (int i = 0; i < mapcount; i++) {
			for (int j = 0; j < size_shooter; j++) {
				showshooter[i][j] = true;
				hp_shooter[i][j].reset();
			}
		}
	}
private:
	//maskboy
	GameSheet maskboy[mapcount][size_Maskboy] = {
	{
		GameSheet("images/enemysheet.png", 3383, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 4506, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 6999, 483, 0, 0, 145, 112),
		//useless
		GameSheet("images/enemysheet.png", 6999, 800, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 6999, 800, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 6999, 800, 0, 0, 145, 112)
		},
	{
		GameSheet("images/enemysheet.png", 2432, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 5076, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 6738, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 7450, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 10878, 483, 0, 0, 145, 112),
		GameSheet("images/enemysheet.png", 13045, 368, 0, 0, 145, 112)
		}
	};

	sf::Clock clockmask[mapcount][size_Maskboy];
	sf::Clock cooldown[mapcount][size_Maskboy];
	bool right[mapcount][size_Maskboy];
	bool left[mapcount][size_Maskboy];
	bool attack[mapcount][size_Maskboy];
	bool showmaskboy[mapcount][size_Maskboy] = { {true, true , true, true, true, true}, {true, true , true, true, true, true} };

	Hp_Enemy hp_maskboy[mapcount][size_Maskboy] = {
	{
		Hp_Enemy(maskboy[0][0].sprite),
		Hp_Enemy(maskboy[0][1].sprite),
		Hp_Enemy(maskboy[0][2].sprite),
		//useless
		Hp_Enemy(maskboy[0][3].sprite),
		Hp_Enemy(maskboy[0][4].sprite),
		Hp_Enemy(maskboy[0][5].sprite)
	},{
		Hp_Enemy(maskboy[1][0].sprite),
		Hp_Enemy(maskboy[1][1].sprite),
		Hp_Enemy(maskboy[1][2].sprite),
		Hp_Enemy(maskboy[1][3].sprite),
		Hp_Enemy(maskboy[1][4].sprite),
		Hp_Enemy(maskboy[1][5].sprite),
	}
	};

	//bat
	GameSheet bat[mapcount][size_Bat] = {
	{
		GameSheet("images/__Bat02_Fly_000-sheet.png", 1117, 250, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 2123, 300, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 8212, 120, 0, 0, 150, 100),
		//useless
		GameSheet("images/__Bat02_Fly_000-sheet.png", 50000, 800, 0, 0, 150, 100)
	},{
		GameSheet("images/__Bat02_Fly_000-sheet.png", 3296, 206, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 5494, 187, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 8104, 329, 0, 0, 150, 100),
		GameSheet("images/__Bat02_Fly_000-sheet.png", 11655, 134, 0, 0, 150, 100),
	}
	};

	bool statebat[mapcount][size_Bat];
	bool showbat[mapcount][size_Bat] = { {true, true, true, true}, {true, true, true, true} };
	sf::Clock clockbat[mapcount][size_Bat];

	//Hp
	Hp_Enemy hp[mapcount][size_Bat] = {
	{
		Hp_Enemy(bat[0][0].sprite),
		Hp_Enemy(bat[0][1].sprite),
		Hp_Enemy(bat[0][2].sprite),
		Hp_Enemy(bat[0][3].sprite)
	},{
		Hp_Enemy(bat[1][0].sprite),
		Hp_Enemy(bat[1][1].sprite),
		Hp_Enemy(bat[1][2].sprite),
		Hp_Enemy(bat[1][3].sprite)
	}
	};

	//shooter
	GameSheet shooter[mapcount][size_shooter] = {
	{
		GameSheet("images/shooter.png", 1748, 412, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 5556, 302, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 10486, 302, 0, 0, 65, 70),
		//useless
		GameSheet("images/shooter.png", 10486, 800, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 10486, 800, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 10486, 800, 0, 0, 65, 70)
	},{
		GameSheet("images/shooter.png", 2052, 415, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 4577, 415, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 6233, 461, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 7317, 285, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 9331, 355, 0, 0, 65, 70),
		GameSheet("images/shooter.png", 11039, 231, 0, 0, 65, 70)
	}
	};

	sf::Clock clockshooter[mapcount][size_shooter];
	sf::Clock cooldownshooter[mapcount][size_shooter];
	bool r_shoot[mapcount][size_shooter];
	bool l_shoot[mapcount][size_shooter];
	bool attackshoot[mapcount][size_shooter];
	bool showshooter[mapcount][size_shooter] = { {true, true , true, true, true, true}, {true, true , true, true, true, true} };

	Hp_Enemy hp_shooter[mapcount][size_shooter] = { {
		Hp_Enemy(shooter[0][0].sprite),
		Hp_Enemy(shooter[0][1].sprite),
		Hp_Enemy(shooter[0][2].sprite),
		//useless
		Hp_Enemy(shooter[0][3].sprite),
		Hp_Enemy(shooter[0][4].sprite),
		Hp_Enemy(shooter[0][5].sprite),
	},{
		Hp_Enemy(shooter[1][0].sprite),
		Hp_Enemy(shooter[1][1].sprite),
		Hp_Enemy(shooter[1][2].sprite),
		Hp_Enemy(shooter[1][3].sprite),
		Hp_Enemy(shooter[1][4].sprite),
		Hp_Enemy(shooter[1][5].sprite)
	}
	};

	Fireball fireball;
};