#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Object.h"
#include "bullet.h"
#include "Enemy.h"
#include "hp.h"
#include "Ui.h"
#include "Enemy_Bullet.h"
#include "menu.h"
#include "Player.h"
#include <vector>

void gameupdate() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SUSHIROLL");
	window.setFramerateLimit(50);

	float charecheight = 119;
	const float movementSpeed = 6;
	bool checkjump = false;
	bool check = true;
	bool checkright = true;
	bool checkleft = true;
	int countJump = 0;
	bool checktop = false;
	bool selectsword = true;
	bool fencing = false;
	bool collision = false;
	int damage = 0;
	bool pause = false;
	//setup the mouse
	sf::Mouse mouse;
	sf::Vector2i mpos(1000, 550);
	mouse.setPosition(mpos, window);
	window.setMouseCursorVisible(true);

	Hp_Player heartplayer;
	Weapon_Ui weapon;
	Enemy_Bullet enemybullet;
	animation animate;
	ActiveObject active;
	Pause pausegame;
	active.init();

	Meteor meteor;

	//bg
	GameObject bg = GameObject("images/background.png", 0, 0);

	//ground
	sf::Vector2f velocity;
	GameObject map = GameObject("images/ground.png", 0, 595);

	//charector
	float position_y = 0;
	float velocity_charecY = 0;
	sf::Vector2f velocity_charec;
	sf::Vector2f velocity_cha;
	sf::Texture charectex;
	charectex.loadFromFile("images/Sprite_sushi/spritesheet.png");
	sf::IntRect charecrect(1, 608, 81, 118);
	sf::Sprite charec(charectex, charecrect);
	charec.setPosition(600, 400);

	//Brick
	GameObject Brick[32] = { GameObject("images/manysushsi.png", 902, 530),
		GameObject("images/manysushsi.png", 902, 465),
		GameObject("images/Sprite_RiceRollSalmon.png", 1629, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 1629, 371),
		GameObject("images/Sprite_RiceRollSalmon.png", 1729, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 1972, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 1972, 371),
		GameObject("images/Sprite_RiceRollSalmon.png", 1972, 259),
		GameObject("images/Sprite_RiceRollSalmon.png", 1972, 147),
		GameObject("images/Sprite_RiceRollSalmon.png", 3816, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 3816, 372),
		GameObject("images/Sprite_RiceRollSalmon.png", 4196, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 4196, 372),
		GameObject("images/Sprite_RiceRollSalmon.png", 5280, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 5280, 371),
		GameObject("images/manysushsi.png", 6199, 530),
		GameObject("images/manysushsi.png", 6370, 530),
		GameObject("images/manysushsi.png", 6370, 465),
		GameObject("images/manysushsi.png", 6541, 530),
		GameObject("images/manysushsi.png", 6541, 465),
		GameObject("images/manysushsi.png", 6541, 400),
		GameObject("images/manysushsi.png", 7432, 530),
		GameObject("images/Sprite_RiceRollSalmon.png", 7603, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 7943, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 8640, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 8980, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 8980, 371),
		GameObject("images/Sprite_RiceRollSalmon.png", 10229, 259),
		GameObject("images/Sprite_RiceRollSalmon.png", 10469, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 10469, 371),
		GameObject("images/Sprite_RiceRollSalmon.png", 11237, 483),
		GameObject("images/Sprite_RiceRollSalmon.png", 11237, 371)
	};

	int size_Brick = sizeof(Brick) / sizeof(Brick[0]);

	//Bar
	GameObject Bar[14] = {
		GameObject("images/ground_2long.png",2732,468),
		GameObject("images/ground_2long.png",3816,312),
		GameObject("images/ground_2long.png",4800,535),
		GameObject("images/ground_2long.png",5380,371),
		GameObject("images/ground_2.png",7703,483),
		GameObject("images/ground_2.png",8400,535),
		GameObject("images/ground_2.png",8740,483),
		GameObject("images/ground_2.png",9080,371),
		GameObject("images/manysushsi.png",9560,371),
		GameObject("images/ground_2.png",9731,371),
		GameObject("images/ground_2.png",9902,371),
		GameObject("images/ground_2.png",10229,371),
		GameObject("images/ground_2.png",10569,371),
		GameObject("images/ground_2.png",10809,431)
	};
	int size_Bar = sizeof(Bar) / sizeof(Bar[0]);


	//trap
	GameObject trap[11] = {
		GameObject("images/fire_trap.png",1829,505),
		GameObject("images/fire_trap.png",1877,505),
		GameObject("images/fire_trap.png",1925,505),
		GameObject("images/fire_trap.png",9320,505),
		GameObject("images/fire_trap.png",9368,505),
		GameObject("images/fire_trap.png",9416,505),
		GameObject("images/fire_trap.png",9464,505),
		GameObject("images/fire_trap.png",9512,505),
		GameObject("images/fire_trap.png",11073,505),
		GameObject("images/fire_trap.png",11121,505),
		GameObject("images/fire_trap.png",11169,505)
	};

	int size_trap = sizeof(trap) / sizeof(trap[0]);

	//test object
	sf::RectangleShape mo(sf::Vector2f(420, 595));
	mo.setFillColor(sf::Color::Transparent);
	mo.setPosition(450, 0);
	//Collision
	sf::FloatRect nextpos;
	sf::FloatRect nextpos_y;
	sf::FloatRect nextpostop;

	//Clock
	sf::Clock clock;
	sf::Clock firerate;


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//pause game

		//space to jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (checkjump == false && countJump <= 1) {
				countJump += 1;
				velocity_charecY = -20;
			}
			checkjump = true;
		}
		else checkjump = false;

		//printf("%f , %f\n", charec.getPosition().x + charec.getGlobalBounds().width, charec.getPosition().x);
		// checkpoint 01 when add new object
		//Collision value
		sf::FloatRect playerBounds = charec.getGlobalBounds();
		sf::FloatRect Brick_Bounds[sizeof(Brick) / sizeof(Brick[0])];
		sf::FloatRect Bar_Bounds[sizeof(Bar) / sizeof(Bar[0])];

		for (int i = 0; i < size_Brick; i++) {
			Brick_Bounds[i] = Brick[i].sprite.getGlobalBounds();
		}
		for (int i = 0; i < size_Bar; i++) {
			Bar_Bounds[i] = Bar[i].sprite.getGlobalBounds();
		}

		nextpos = playerBounds;
		nextpos_y = playerBounds;
		nextpos_y.top += velocity_charecY + 1;
		nextpostop = playerBounds;
		nextpostop.top += velocity_charecY - 1;

		if (checkright) {
			nextpos.left += velocity.x + 20;
			nextpos_y.left += velocity.x - 25;
		}
		else if (checkleft) {
			nextpos.left += velocity.x - 20;
			nextpos_y.left += velocity.x + 25;
		}

		//Charec Movement
		velocity.x = 0.f;
		velocity.y = 0.f;

		//movement
		if (check) {
			//CheckScreen
			if (map.sprite.getPosition().x <= -1 || charec.getGlobalBounds().intersects(mo.getGlobalBounds())) {
				//moveLeft
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					velocity.x += movementSpeed;
					checkleft = true;
					checkright = false;
				}
			}
			//moveRight
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				velocity.x += -movementSpeed;
				checkleft = false;
				checkright = true;
			}
		}
		else {
			if (checkright) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					velocity.x += movementSpeed;
				}
			}
			else if (checkleft) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					velocity.x += -movementSpeed;
				}
			}
		}

		// checkpoint 02 when add new object
		//Collision Brick
		for (int i = 0; i < size_Brick; i++) {
			if (Brick_Bounds[i].intersects(nextpos)) {
				check = false;
				break;
			}
			else {
				check = true;
			}
		}
		if (check) {
			for (int i = 0; i < size_Bar; i++) {
				if (Bar_Bounds[i].intersects(nextpos) && !Bar_Bounds[i].intersects(nextpostop)) {
					check = false;
					break;
				}
				else check = true;
			}
		}
		// checkpoint 03 when add new object
		//Check collision top while Jump or Under Floating Object
		for (int i = 0; i < size_Bar; i++) {
			if (charec.getPosition().x >= Bar[i].sprite.getGlobalBounds().left && charec.getPosition().x <= Bar[i].sprite.getGlobalBounds().left + Bar[i].sprite.getGlobalBounds().width) {
				if (charec.getPosition().y > Bar[i].sprite.getPosition().y) {
					if (Bar_Bounds[i].intersects(nextpostop)) {
						//printf("hit %d\n", i);
						velocity_charecY = 0;
					}
					i = size_Bar;
				}
			}

			else if (charec.getPosition().x + charec.getGlobalBounds().width >= Bar[i].sprite.getGlobalBounds().left && charec.getPosition().x + charec.getGlobalBounds().width <= Bar[i].sprite.getGlobalBounds().left + Bar[i].sprite.getGlobalBounds().width) {
				if (charec.getPosition().y > Bar[i].sprite.getPosition().y) {
					if (Bar_Bounds[i].intersects(nextpostop)) {
						//printf("hit %d\n", i);
						velocity_charecY = 0;
					}
					i = size_Bar;
				}
			}
			else if (i == size_Bar - 1) {
				//printf("not under\n");
			}
		}

		//animation sprite
		animate.anima(&charecrect.left, &charecrect.top, &selectsword, &charecrect.width, &charecrect.height, &charecheight, &fencing);
		charec.setTextureRect(charecrect);

		//enemy bullet
		enemybullet.collispriteenemy(charec, fencing);
		enemybullet.setPos(charec, selectsword, checkleft, checkright);
		enemybullet.collision(charec);
		enemybullet.hitenemy(charec, &collision);
		meteor.collision(charec);
		heartplayer.damage(collision, damage, meteor.collision_sp);
		// checkpoint 04 when add new object
		//setPostion += getPositon When On top the brick
		position_y += velocity_charecY;
		if (map.sprite.getGlobalBounds().intersects(nextpos_y)) {
			position_y = map.sprite.getGlobalBounds().top - charecheight;
			countJump = 0;
		}
		else {
			for (int i = 0; i < size_Brick; i++) {
				if (Brick_Bounds[i].intersects(nextpos_y)) {
					position_y = Brick_Bounds[i].top - charecheight;
					countJump = 0;
					i = size_Brick;
				}
				else if (Bar_Bounds[i].intersects(nextpos_y) && i < size_Bar && charec.getPosition().y < Bar_Bounds[i].top) {
					position_y = Bar_Bounds[i].top - charecheight;
					countJump = 0;
					i = size_Brick;
				}
				//gravity
				else if (i == (size_Brick - 1)) {
					velocity_charecY += 1;
				}
			}
		}
		// checkpoint 05 when add new object
		//move sprite
		if (!pause) {
			if (charec.getGlobalBounds().intersects(mo.getGlobalBounds())) {
				charec.move(-velocity);
				charec.setPosition(charec.getPosition().x, position_y);
			}
			//right of box
			else if (charec.getPosition().x == mo.getGlobalBounds().left + mo.getGlobalBounds().width) {
				if (checkright) {
					enemybullet.move(velocity);
					active.move(velocity);
					meteor.move(velocity);
					for (int i = 0; i < size_Brick; i++) {
						Brick[i].sprite.move(velocity);
					}
					for (int i = 0; i < size_Bar; i++) {
						Bar[i].sprite.move(velocity);
					}
					for (int i = 0; i < size_trap; i++) {
						trap[i].sprite.move(velocity);
					}
					map.sprite.move(velocity);
					charec.setPosition(charec.getPosition().x, position_y);
				}
				else {
					charec.move(-velocity);
					charec.setPosition(charec.getPosition().x, position_y);
				}
			}
			//left of box
			else if (charec.getGlobalBounds().left + charec.getGlobalBounds().width <= mo.getPosition().x) {
				if (checkleft) {
					enemybullet.move(velocity);
					active.move(velocity);
					meteor.move(velocity);
					for (int i = 0; i < size_Brick; i++) {
						Brick[i].sprite.move(velocity);
					}
					for (int i = 0; i < size_Bar; i++) {
						Bar[i].sprite.move(velocity);
					}
					for (int i = 0; i < size_trap; i++) {
						trap[i].sprite.move(velocity);
					}
					map.sprite.move(velocity);
					charec.setPosition(charec.getPosition().x, position_y);
				}
				else {
					charec.move(-velocity);
					charec.setPosition(charec.getPosition().x, position_y);
				}
			}
			else {
				enemybullet.move(velocity);
				active.move(velocity);
				meteor.move(velocity);
				for (int i = 0; i < size_Brick; i++) {
					Brick[i].sprite.move(velocity);
				}
				for (int i = 0; i < size_Bar; i++) {
					Bar[i].sprite.move(velocity);
				}
				for (int i = 0; i < size_trap; i++) {
					trap[i].sprite.move(velocity);
				}
				map.sprite.move(velocity);
				charec.setPosition(charec.getPosition().x, position_y);
			}
			enemybullet.automove(sf::Vector2f(2, 0), charec, Brick, fencing, &damage);
			meteor.fire();
		}
		//draw
		window.clear();
		window.draw(bg.sprite);
		
		for (int i = 0; i < size_Brick; i++) {
			window.draw(Brick[i].sprite);
		}
		for (int i = 0; i < size_Bar; i++) {
			window.draw(Bar[i].sprite);
		}
		for (int i = 0; i < size_trap; i++) {
			window.draw(trap[i].sprite);
		}
		weapon.draw(window, selectsword);
		enemybullet.draw(window);
		enemybullet.draw_bullet(window);
		window.draw(map.sprite);
		heartplayer.draw(window);
		meteor.draw(window);
		window.draw(mo);
		window.draw(charec);
		active.draw(window);
		active.collision(charec, window);
		pausegame.pausegame(window, &pause, heartplayer.gamestateover());
		pausegame.gameover(window, &pause, heartplayer.gamestateover());
		window.display();
	}
}

void gamemenu() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SUSHIROLL");
	window.setFramerateLimit(50);

	GameObject bg = GameObject("images/background.png", 0, 0);

	GameObject ground[3] = {
		GameObject("images/ground_2long.png",0,480),
		GameObject("images/ground_2long.png",480,480),
		GameObject("images/ground_2long.png",960,480)
	};

	sf::RectangleShape Buttonplay;
	Buttonplay.setSize(sf::Vector2f(300, 100));
	Buttonplay.setPosition(sf::Vector2f(535, 550));
	Buttonplay.setFillColor(sf::Color::Black);

	sf::Sprite setting;
	sf::Texture settingtex;
	settingtex.loadFromFile("images/gear.png");
	setting.setTexture(settingtex);
	setting.setPosition(sf::Vector2f(1180, 10));
	setting.setScale(0.7, 0.7);

	sf::Sprite score;
	sf::Texture scoretex;
	scoretex.loadFromFile("images/high-score.png");
	score.setTexture(scoretex);
	score.setPosition(sf::Vector2f(1080, 10));
	score.setScale(0.7, 0.7);

	sf::Font font;
	font.loadFromFile("font/Minecraft.ttf");
	sf::Text play;
	play.setFont(font);
	play.setString("PLAY");
	play.setPosition(sf::Vector2f(620, 560));
	play.setScale(2,2);
	play.setFillColor(sf::Color::White);

	sf::Texture charectex;
	charectex.loadFromFile("images/Sprite_sushi/spritesheet.png");
	sf::IntRect charecrect(1, 1, 81, 118);
	sf::Sprite charec(charectex, charecrect);
	charec.setPosition(500, 362);

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			if (charecrect.left > 900) {
				charecrect.left = 1;
			}
			else charecrect.left += 170;
			charec.setTextureRect(charecrect);
			clock.restart();
		}

		window.clear();
		window.draw(bg.sprite);
		for (int i = 0; i < 3; i++) {
			window.draw(ground[i].sprite);
		}
		window.draw(charec);
		window.draw(setting);
		window.draw(score);
		window.draw(Buttonplay);
		window.draw(play);
		window.display();
	}
}