#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <SFML/Audio.hpp>
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

	sf::RenderWindow GAME(sf::VideoMode(1280, 720), "SUSHIROLL");
	GAME.setFramerateLimit(50);
	int screen = 0;

	GameObject bg = GameObject("images/background.png", 0, 0);

	GameObject ground[3] = {
		GameObject("images/ground_2long.png",0,480),
		GameObject("images/ground_2long.png",480,480),
		GameObject("images/ground_2long.png",960,480)
	};

	GameObject menu[3] = {
		GameObject("images/playbutton.png", 473, 254),
		GameObject("images/score.png", 473, 404),
		GameObject("images/exit.png", 473, 560)
	};

	FontText YourName(FONT, "YOUR NAME", 294, 149, sf::Color::Color(253, 101, 71, 255), 120);
	TextBox textbox(60, sf::Color::Color(0, 204, 255, 255), true, 380, 389);
	textbox.setLimit(true, 13);
	sf::RectangleShape boarderName(sf::Vector2f(709, 88));
	boarderName.setPosition(sf::Vector2f(280, 385));
	boarderName.setFillColor(sf::Color::Transparent);
	boarderName.setOutlineColor(sf::Color::White);
	boarderName.setOutlineThickness(8);

	sf::Mouse mouse;
	sf::Clock clock_MENU;

	Sounds sounds;

	//GAME

	//random map
	srand(time(NULL));
	int selectmap = 0;

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
	int point = 0;
	float pointdistance = 0;
	bool leftmouseclick = false;
	int d = 0;

	std::string Roll = "images/Sprite_RiceRollSalmon.png";
	std::string Salmon = "images/manysushsi.png";
	std::string Trap = "images/fire_trap.png";

	Hp_Player heartplayer;
	Weapon_Ui weapon;
	Enemy_Bullet enemybullet;
	animation animate;
	ActiveObject active;
	Pause pausegame;
	active.init();

	Meteor meteor;

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

	//Brick
	GameObject Brick[2][36] = { { GameObject(Salmon, 902, 530),
		GameObject(Salmon, 902, 465),
		GameObject(Roll, 1629, 483),
		GameObject(Roll, 1629, 371),
		GameObject(Roll, 1729, 483),
		GameObject(Roll, 1972, 483),
		GameObject(Roll, 1972, 371),
		GameObject(Roll, 1972, 259),
		GameObject(Roll, 1972, 147),
		GameObject(Roll, 3816, 483),
		GameObject(Roll, 3816, 372),
		GameObject(Roll, 4196, 483),
		GameObject(Roll, 4196, 372),
		GameObject(Roll, 5280, 483),
		GameObject(Roll, 5280, 371),
		GameObject(Salmon, 6199, 530),
		GameObject(Salmon, 6370, 530),
		GameObject(Salmon, 6370, 465),
		GameObject(Salmon, 6541, 530),
		GameObject(Salmon, 6541, 465),
		GameObject(Salmon, 6541, 400),
		GameObject(Salmon, 7432, 530),
		GameObject(Roll, 7603, 483),
		GameObject(Roll, 7943, 483),
		GameObject(Roll, 8640, 483),
		GameObject(Roll, 8980, 483),
		GameObject(Roll, 8980, 371),
		GameObject(Roll, 10229, 259),
		GameObject(Roll, 10469, 483),
		GameObject(Roll, 10469, 371),
		GameObject(Roll, 11237, 483),
		GameObject(Roll, 11237, 371),
		//useless
		GameObject(Roll, 11237, 800),
		GameObject(Roll, 11237, 800),
		GameObject(Roll, 11237, 800),
		GameObject(Roll, 11237, 800),
	}, {
		GameObject(Roll, 1296, 483),
		GameObject(Roll, 1396, 483),
		GameObject(Roll, 1496, 483),
		GameObject(Roll, 1884, 483),
		GameObject(Roll, 1984, 483),
		GameObject(Roll, 2084, 483),
		GameObject(Roll, 2184, 483),
		GameObject(Roll, 2184, 371),
		GameObject(Salmon, 2742, 530),
		GameObject(Salmon, 2913, 530),
		GameObject(Salmon, 2913, 465),
		GameObject(Salmon, 2913, 400),
		GameObject(Roll, 4559, 483),
		GameObject(Roll, 4969, 223),
		GameObject(Roll, 4969, 111),
		GameObject(Salmon, 5641, 530),
		GameObject(Salmon, 6179, 530),
		GameObject(Roll, 7928, 483),
		GameObject(Roll, 8803, 483),
		GameObject(Roll, 8973, 423),
		GameObject(Roll, 9313, 483),
		GameObject(Salmon, 10363, 530),
		GameObject(Salmon, 10363, 465),
		GameObject(Roll, 11419, 187),
		GameObject(Roll, 11419, 75),
		GameObject(Salmon, 11671, 530),
		GameObject(Roll, 11842, 483),
		GameObject(Roll, 11942, 483),
		GameObject(Roll, 12042, 483),
		GameObject(Salmon, 12142, 530),
		GameObject(Salmon, 12142, 530),
		GameObject(Roll, 12760, 483),
		GameObject(Roll, 12760, 371),
		GameObject(Roll, 13340, 483),
		GameObject(Roll, 13340, 371),
		GameObject(Roll, 13340, 259),
		}
	};

	int size_Brick = sizeof(Brick[0]) / sizeof(Brick[0][0]);

	//Bar
	GameObject Bar[2][16] = {
		{
		GameObject("images/ground_2long.png",2732,468),
		GameObject("images/ground_2long.png",3816,312),
		GameObject("images/ground_2long.png",4800,535),
		GameObject("images/ground_2long.png",5380,371),
		GameObject("images/ground_2.png",7703,483),
		GameObject("images/ground_2.png",8400,535),
		GameObject("images/ground_2.png",8740,483),
		GameObject("images/ground_2.png",9080,371),
		GameObject(Salmon,9560,371),
		GameObject("images/ground_2.png",9731,371),
		GameObject("images/ground_2.png",9902,371),
		GameObject("images/ground_2.png",10229,371),
		GameObject("images/ground_2.png",10569,371),
		GameObject("images/ground_2.png",10809,431),
		//useless
		GameObject("images/ground_2.png",10809,800),
		GameObject("images/ground_2.png",10809,800)
	},	{
		GameObject("images/ground_2long.png",3520,400),
		GameObject("images/ground_2long.png",4969,335),
		GameObject("images/ground_2long.png",6533,353),
		GameObject("images/ground_2long.png",7012,353),
		GameObject("images/ground_2.png",7493,353),
		GameObject("images/ground_2.png",8493,535),
		GameObject("images/ground_2.png",8733,423),
		GameObject("images/ground_2.png",9073,535),
		GameObject("images/ground_2.png",9313,423),
		GameObject("images/ground_2long.png",9553,423),
		GameObject("images/ground_2long.png",10799,299),
		GameObject("images/ground_2.png",11279,299),
		GameObject("images/ground_2long.png",12860,479),
		GameObject(Salmon,13733,368),
		GameObject(Salmon,13904,368),
		GameObject(Salmon,14075,368)
		}
	};
	int size_Bar = sizeof(Bar[0]) / sizeof(Bar[0][0]);


	//trap
	GameObject trap[2][13] = {
	{
		GameObject(Trap,1829,505),
		GameObject(Trap,1877,505),
		GameObject(Trap,1925,505),
		GameObject(Trap,9320,505),
		GameObject(Trap,9368,505),
		GameObject(Trap,9416,505),
		GameObject(Trap,9464,505),
		GameObject(Trap,9512,505),
		GameObject(Trap,11073,505),
		GameObject(Trap,11121,505),
		GameObject(Trap,11169,505),
		//useless
		GameObject(Trap,11169,800),
		GameObject(Trap,11169,800)
	},{
		GameObject(Trap,1596,505),
		GameObject(Trap,1644,505),
		GameObject(Trap,1692,505),
		GameObject(Trap,1740,505),
		GameObject(Trap,1788,505),
		GameObject(Trap,1836,505),
		GameObject(Trap,5880,505),
		GameObject(Trap,5941,505),
		GameObject(Trap,6002,505),
		GameObject(Trap,6063,505),
		GameObject(Trap,9093,445),
		GameObject(Trap,9196,445),
		GameObject(Trap,9245,445),
	}

	};

	int size_trap = sizeof(trap[0]) / sizeof(trap[0][0]);

	//test object
	sf::RectangleShape mo(sf::Vector2f(254, 895));
	mo.setFillColor(sf::Color::Transparent);
	mo.setPosition(450, -300);
	//Collision
	sf::FloatRect nextpos;
	sf::FloatRect nextpos_y;
	sf::FloatRect nextpostop;

	//Clock
	sf::Clock clock;
	sf::Clock firerate;

	Scoreboard scoreboard;

	FontText myname = FontText(FONT, "65010065 Kantinan", 5, 680, sf::Color::Black, 30);
	
	//END GAME
	while (GAME.isOpen())
	{
		sf::Event event;
		while (GAME.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				GAME.close();
			if (event.type == sf::Event::TextEntered) {
				if (screen == 4) {
					textbox.typedOn(event, &screen, GAME, charec, &point);
				}
			}
			if (screen == 2) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					screen = 0;
				}
			}
		}
		if (screen == 0) {
			charec.setPosition(sf::Vector2f(200, 362));
			charecrect.top = 1;
			charecrect.width = 81;
			if (clock_MENU.getElapsedTime().asSeconds() > 0.2f) {
				if (charecrect.left > 900) {
					charecrect.left = 1;
				}
				else charecrect.left += 170;
				charec.setTextureRect(charecrect);
				clock_MENU.restart();
			}

			//position mouse
			for (int i = 0; i < 3; i++) {
				if (menu[i].sprite.getGlobalBounds().contains(mouse.getPosition(GAME).x, mouse.getPosition(GAME).y)) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && screen == 0) {
						if (!leftmouseclick) {
							sounds.click_effect();
							screen = i + 1;
							if (screen == 1) {
								textbox.reset();
								pause = false;
								heartplayer.reset();
								//for reset all
								selectmap = 0;

								charecheight = 119;
								checkjump = false;
								check = true;
								checkright = true;
								checkleft = true;
								countJump = 0;
								checktop = false;
								selectsword = true;
								fencing = false;
								collision = false;
								damage = 0;
								pause = false;
								point = 0;
								pointdistance = 0;
								leftmouseclick = false;
								d = 0;

								active.init();
								enemybullet.init();
								//ground
								velocity = sf::Vector2f(0,0);
								map.sprite.setPosition(0, 595);

								//charector
								position_y = 0;
								velocity_charecY = 0;
								velocity_charec = sf::Vector2f(0, 0);
								velocity_cha = sf::Vector2f(0, 0);
								sf::IntRect charecrect(1, 608, 81, 118);
								sf::Sprite charec(charectex, charecrect);

								//Brick
								//01
								Brick[0][0].sprite.setPosition(902, 530);
								Brick[0][1].sprite.setPosition(902, 465);
								Brick[0][2].sprite.setPosition(1629, 483);
								Brick[0][3].sprite.setPosition(1629, 371);
								Brick[0][4].sprite.setPosition(1729, 483);
								Brick[0][5].sprite.setPosition(1972, 483);
								Brick[0][6].sprite.setPosition(1972, 371);
								Brick[0][7].sprite.setPosition(1972, 259);
								Brick[0][8].sprite.setPosition(1972, 147);
								Brick[0][9].sprite.setPosition(3816, 483);
								Brick[0][10].sprite.setPosition(3816, 372);
								Brick[0][11].sprite.setPosition(4196, 483);
								Brick[0][12].sprite.setPosition(4196, 372);
								Brick[0][13].sprite.setPosition(5280, 483);
								Brick[0][14].sprite.setPosition(5280, 371);
								Brick[0][15].sprite.setPosition(6199, 530);
								Brick[0][16].sprite.setPosition(6370, 530);
								Brick[0][17].sprite.setPosition(6370, 465);
								Brick[0][18].sprite.setPosition(6541, 530);
								Brick[0][19].sprite.setPosition(6541, 465);
								Brick[0][20].sprite.setPosition(6541, 400);
								Brick[0][21].sprite.setPosition(7432, 530);
								Brick[0][22].sprite.setPosition(7603, 483);
								Brick[0][23].sprite.setPosition(7943, 483);
								Brick[0][24].sprite.setPosition(8640, 483);
								Brick[0][25].sprite.setPosition(8980, 483);
								Brick[0][26].sprite.setPosition(8980, 371);
								Brick[0][27].sprite.setPosition(10229, 259);
								Brick[0][28].sprite.setPosition(10469, 483);
								Brick[0][29].sprite.setPosition(10469, 371);
								Brick[0][30].sprite.setPosition(11237, 483);
								Brick[0][31].sprite.setPosition(11237, 371);
								//useless
								Brick[0][32].sprite.setPosition(11237, 800);
								Brick[0][33].sprite.setPosition(11237, 800);
								Brick[0][34].sprite.setPosition(11237, 800);
								Brick[0][35].sprite.setPosition(11237, 800);
								//02
								Brick[1][0].sprite.setPosition(1296, 483);
								Brick[1][1].sprite.setPosition(1396, 483);
								Brick[1][2].sprite.setPosition(1496, 483);
								Brick[1][3].sprite.setPosition(1884, 483);
								Brick[1][4].sprite.setPosition(1984, 483);
								Brick[1][5].sprite.setPosition(2084, 483);
								Brick[1][6].sprite.setPosition(2184, 483);
								Brick[1][7].sprite.setPosition(2184, 371);
								Brick[1][8].sprite.setPosition(2742, 530);
								Brick[1][9].sprite.setPosition(2913, 530);
								Brick[1][10].sprite.setPosition(2913, 465);
								Brick[1][11].sprite.setPosition(2913, 400);
								Brick[1][12].sprite.setPosition(4559, 483);
								Brick[1][13].sprite.setPosition(4969, 223);
								Brick[1][14].sprite.setPosition(4969, 111);
								Brick[1][15].sprite.setPosition(5641, 530);
								Brick[1][16].sprite.setPosition(6179, 530);
								Brick[1][17].sprite.setPosition(7928, 483);
								Brick[1][18].sprite.setPosition(8803, 483);
								Brick[1][19].sprite.setPosition(8973, 423);
								Brick[1][20].sprite.setPosition(9313, 483);
								Brick[1][21].sprite.setPosition(10363, 530);
								Brick[1][22].sprite.setPosition(10363, 465);
								Brick[1][23].sprite.setPosition(11419, 187);
								Brick[1][24].sprite.setPosition(11419, 75);
								Brick[1][25].sprite.setPosition(11671, 530);
								Brick[1][26].sprite.setPosition(11842, 483);
								Brick[1][27].sprite.setPosition(11942, 483);
								Brick[1][28].sprite.setPosition(12042, 483);
								Brick[1][29].sprite.setPosition(12142, 530);
								Brick[1][30].sprite.setPosition(12142, 530);
								Brick[1][31].sprite.setPosition(12760, 483);
								Brick[1][32].sprite.setPosition(12760, 371);
								Brick[1][33].sprite.setPosition(13340, 483);
								Brick[1][34].sprite.setPosition(13340, 371);
								Brick[1][35].sprite.setPosition(13340, 259);

								//Bar
								//01
								Bar[0][0].sprite.setPosition(2732, 468);
								Bar[0][1].sprite.setPosition(3816,312);
								Bar[0][2].sprite.setPosition(4800,535);
								Bar[0][3].sprite.setPosition(5380,371);
								Bar[0][4].sprite.setPosition(7703,483);
								Bar[0][5].sprite.setPosition(8400,535);
								Bar[0][6].sprite.setPosition(8740,483);
								Bar[0][7].sprite.setPosition(9080,371);
								Bar[0][8].sprite.setPosition(9560,371);
								Bar[0][9].sprite.setPosition(9731,371);
								Bar[0][10].sprite.setPosition(9902,371);
								Bar[0][11].sprite.setPosition(10229,371);
								Bar[0][12].sprite.setPosition(10569,371);
								Bar[0][13].sprite.setPosition(10809,431);
								Bar[0][14].sprite.setPosition(10809,800);
								Bar[0][15].sprite.setPosition(10809, 800);
								//02
								Bar[1][0].sprite.setPosition(3520,400);
								Bar[1][1].sprite.setPosition(4969,335);
								Bar[1][2].sprite.setPosition(6533,353);
								Bar[1][3].sprite.setPosition(7012,353);
								Bar[1][4].sprite.setPosition(7493,353);
								Bar[1][5].sprite.setPosition(8493,535);
								Bar[1][6].sprite.setPosition(8733,423);
								Bar[1][7].sprite.setPosition(9073,535);
								Bar[1][8].sprite.setPosition(9313,423);
								Bar[1][9].sprite.setPosition(9553,423);
								Bar[1][10].sprite.setPosition(10799,299);
								Bar[1][11].sprite.setPosition(11279,299);
								Bar[1][12].sprite.setPosition(12860,479);
								Bar[1][13].sprite.setPosition(13733,368);
								Bar[1][14].sprite.setPosition(13904,368);
								Bar[1][15].sprite.setPosition(14075, 368);


								//trap
								//01
								trap[0][0].sprite.setPosition(1829,505);
								trap[0][1].sprite.setPosition(1877,505);
								trap[0][2].sprite.setPosition(1925,505);
								trap[0][3].sprite.setPosition(9320,505);
								trap[0][4].sprite.setPosition(9368,505);
								trap[0][5].sprite.setPosition(9416,505);
								trap[0][6].sprite.setPosition(9464,505);
								trap[0][7].sprite.setPosition(9512,505);
								trap[0][8].sprite.setPosition(11073,505);
								trap[0][9].sprite.setPosition(11121,505);
								trap[0][10].sprite.setPosition(11169,505);
								trap[0][11].sprite.setPosition(11169,800);
								trap[0][12].sprite.setPosition(11169,800);
								//02
								trap[1][0].sprite.setPosition(1596,505);
								trap[1][1].sprite.setPosition(1644,505);
								trap[1][2].sprite.setPosition(1692,505);
								trap[1][3].sprite.setPosition(1740,505);
								trap[1][4].sprite.setPosition(1788,505);
								trap[1][5].sprite.setPosition(1836,505);
								trap[1][6].sprite.setPosition(5880,505);
								trap[1][7].sprite.setPosition(5941,505);
								trap[1][8].sprite.setPosition(6002,505);
								trap[1][9].sprite.setPosition(6063,505);
								trap[1][10].sprite.setPosition(9093,445);
								trap[1][11].sprite.setPosition(9196,445);
								trap[1][12].sprite.setPosition(9245, 445);
								//test object
								mo.setPosition(450, -300);

								meteor.reset();
								////END GAME
							}
							if (screen == 3) {
								GAME.close();
							}
						}
						leftmouseclick = true;
					}
					else {
						leftmouseclick = false;
					}
				}
			}
		}
		if (screen == 1) {
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
			sf::FloatRect Brick_Bounds[sizeof(Brick[selectmap]) / sizeof(Brick[selectmap][0])];
			sf::FloatRect Bar_Bounds[sizeof(Bar[selectmap]) / sizeof(Bar[selectmap][0])];

			for (int i = 0; i < size_Brick; i++) {
				Brick_Bounds[i] = Brick[selectmap][i].sprite.getGlobalBounds();
			}
			for (int i = 0; i < size_Bar; i++) {
				Bar_Bounds[i] = Bar[selectmap][i].sprite.getGlobalBounds();
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
				if (charec.getPosition().x >= Bar[selectmap][i].sprite.getGlobalBounds().left && charec.getPosition().x <= Bar[selectmap][i].sprite.getGlobalBounds().left + Bar[selectmap][i].sprite.getGlobalBounds().width) {
					if (charec.getPosition().y > Bar[selectmap][i].sprite.getPosition().y) {
						if (Bar_Bounds[i].intersects(nextpostop)) {
							//printf("hit %d\n", i);
							velocity_charecY = 0;
						}
						i = size_Bar;
					}
				}

				else if (charec.getPosition().x + charec.getGlobalBounds().width >= Bar[selectmap][i].sprite.getGlobalBounds().left && charec.getPosition().x + charec.getGlobalBounds().width <= Bar[selectmap][i].sprite.getGlobalBounds().left + Bar[selectmap][i].sprite.getGlobalBounds().width) {
					if (charec.getPosition().y > Bar[selectmap][i].sprite.getPosition().y) {
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
			animate.anima(&charecrect.left, &charecrect.top, &selectsword, &charecrect.width, &charecrect.height, &charecheight, &fencing, checkleft, checkright);
			charec.setTextureRect(charecrect);

			//enemy bullet
			enemybullet.collispriteenemy(charec, fencing, &point, selectmap);
			enemybullet.setPos(charec, selectsword, checkleft, checkright);
			enemybullet.collision(charec, &point, selectmap);
			enemybullet.hitenemy(charec, &collision, fencing, selectmap);
			meteor.collision(charec);
			heartplayer.damage(collision, damage, meteor.collision_sp, &d, enemybullet.fireball_hit);
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
			//changemap
			if (map.sprite.getGlobalBounds().left + map.sprite.getGlobalBounds().width == 1440) {
				map.sprite.setPosition(sf::Vector2f(0, 595));
				selectmap = 1;
			}
			// checkpoint 05 when add new object
			pointdistance += -velocity.x;
			//printf("%f\n", pointdistance);
			//move sprite
			if (!pause) {
				if (charec.getGlobalBounds().intersects(mo.getGlobalBounds())) {
					charec.move(-velocity);
					charec.setPosition(charec.getPosition().x, position_y);
				}
				//right of box
				else if (charec.getPosition().x == mo.getGlobalBounds().left + mo.getGlobalBounds().width) {
					if (checkright) {
						enemybullet.move(velocity, selectmap);
						active.move(velocity, selectmap);
						meteor.move(velocity);
						for (int i = 0; i < size_Brick; i++) {
							Brick[selectmap][i].sprite.move(velocity);
						}
						for (int i = 0; i < size_Bar; i++) {
							Bar[selectmap][i].sprite.move(velocity);
						}
						for (int i = 0; i < size_trap; i++) {
							trap[selectmap][i].sprite.move(velocity);
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
						enemybullet.move(velocity, selectmap);
						active.move(velocity, selectmap);
						meteor.move(velocity);
						for (int i = 0; i < size_Brick; i++) {
							Brick[selectmap][i].sprite.move(velocity);
						}
						for (int i = 0; i < size_Bar; i++) {
							Bar[selectmap][i].sprite.move(velocity);
						}
						for (int i = 0; i < size_trap; i++) {
							trap[selectmap][i].sprite.move(velocity);
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
					enemybullet.move(velocity, selectmap);
					active.move(velocity, selectmap);
					meteor.move(velocity);
					for (int i = 0; i < size_Brick; i++) {
						Brick[selectmap][i].sprite.move(velocity);
					}
					for (int i = 0; i < size_Bar; i++) {
						Bar[selectmap][i].sprite.move(velocity);
					}
					for (int i = 0; i < size_trap; i++) {
						trap[selectmap][i].sprite.move(velocity);
					}
					map.sprite.move(velocity);
					charec.setPosition(charec.getPosition().x, position_y);
				}
				enemybullet.automove(sf::Vector2f(2, 0), charec, Brick[selectmap], fencing, &damage, selectmap);
				meteor.fire(velocity.x);
			}
		}
		
		GAME.clear();
		if (screen == 0) {
			GAME.draw(bg.sprite);
			for (int i = 0; i < 3; i++) {
				GAME.draw(ground[i].sprite);
				GAME.draw(menu[i].sprite);
			}
			GAME.draw(charec);
		}
		if (screen == 4) {
			FontText scoretxt = FontText(FONT, "score : " + std::to_string(point), 20, 20, sf::Color::Color(102, 255, 132, 255), 50);
			GAME.draw(scoretxt.text);
			GAME.draw(boarderName);
			GAME.draw(YourName.text);
			textbox.draw(GAME);
		}
		if (screen == 2) {
			scoreboard.showscore(GAME);
		}
		if (screen == 1) {
			GAME.draw(bg.sprite);
			//map01
			for (int i = 0; i < size_Brick; i++) {
				GAME.draw(Brick[selectmap][i].sprite);
			}
			for (int i = 0; i < size_Bar; i++) {
				GAME.draw(Bar[selectmap][i].sprite);
			}
			for (int i = 0; i < size_trap; i++) {
				GAME.draw(trap[selectmap][i].sprite);
			}
			GAME.draw(map.sprite);
			active.draw(GAME, selectmap);
			active.collision(charec, GAME, selectmap, &heartplayer.sizeheart);
			enemybullet.draw(GAME, selectmap);
			//end map01
			enemybullet.draw_bullet(GAME);
			heartplayer.draw(GAME, d);
			meteor.draw(GAME);
			GAME.draw(mo);
			GAME.draw(charec);
			weapon.draw(GAME, selectsword);
			pausegame.pausegame(GAME, &pause, heartplayer.gamestateover(), &screen, &leftmouseclick);
			pausegame.gameover(GAME, &pause, heartplayer.gamestateover(), &screen, &leftmouseclick, &point, pointdistance);
		}
		GAME.draw(myname.text);
		GAME.display();
	}
}