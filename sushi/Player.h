#pragma once
#include "SFML/Graphics.hpp"

class animation {
public:
	sf::Clock clock;
	int topper = 608;
	bool press = false;
	bool click = false;
	bool walk = false;
	Sounds sounds;
	void anima(int *left,int *top, bool *selectsword, int *width, int *height, float *y, bool *fencing, bool checkleft, bool checkright) {
		//fencing
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && *selectsword && !*fencing) {
			if (!click) {
				sounds.fencing_effect();
				if (checkright) {
					*left = 1;
				}
				else {
					*left = 3117;
				}
				*height = 133;
				*top = 851;
				*width = 107;
				*y = 134;
				*fencing = true;
			}
			click = true;
		}
		//walk left
		else if (checkleft && !*fencing && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (!press) {
				if (*selectsword) {
					*left = 3142;
					*width = 81;
					*top = 727;
					*y = 119;
				}
				else {
					*left = 3134;
					*width = 90;
					*top = 365;
					*y = 119;
				}
			}
			if (*selectsword) {
				if (clock.getElapsedTime().asSeconds() > 0.1f) {
					if (*left < 2034) {
						*left = 3142;
					}
					*left -= 170;
					clock.restart();
				}
			}
			else {
				if (clock.getElapsedTime().asSeconds() > 0.1f) {
					if (*left < 1940) {
						*left = 3134;
					}
					*left -= 171;
					clock.restart();
				}
			}
			press = true;

		}
		//walk right
		else if (checkright && !*fencing && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (!press) {
				if (*selectsword) {
					*left = 1;
					*top = 727;
					*width = 81;
					*y = 119;
				}
				else {
					*left = 1;
					*top = 365;
					*width = 90;
					*y = 119;
				}
			}
			if (*selectsword) {
				if (clock.getElapsedTime().asSeconds() > 0.1f) {
					if (*left > 1190) {
						*left = 1;
					}
					*left += 170;
					clock.restart();
				}
			}
			else {
				if (clock.getElapsedTime().asSeconds() > 0.1f) {
					if (*left > 1197) {
						*left = 1;
					}
					*left += 171;
					clock.restart();
				}
			}
			press = true;
		}
		//switch mode
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (!press) {
				*selectsword = !*selectsword;
				if (*selectsword) {
					topper = 608;
				}
				else topper = 246;
			}
			press = true;
		}
		//idle
		else {
			if (*fencing) {
				//fencing mode
				if (checkright) {
					if (*left > 925) {
						*fencing = false;
						*top = 608;
						*left = 1;
						*width = 81;
						*height = 118;
						*y = 119;
					}
					if (clock.getElapsedTime().asSeconds() > 0.06f) {
						*left += 196;
						clock.restart();
					}
				}
				else {
					if (*left < 2154) {
						*fencing = false;
						*top = 608;
						*left = 3142;
						*width = 81;
						*height = 118;
						*y = 119;
					}
					if (clock.getElapsedTime().asSeconds() > 0.06f) {
						*left -= 197;
						clock.restart();
					}
				}
			}
			else if (checkright) {
				if (press) {
					*left = 1;
				}
				*y = 119;
				*width = 81;
				*top = topper;
				if (clock.getElapsedTime().asSeconds() > 0.15f) {
					if (*left > 1500) {
						*left = 1;
					}
					*left += 170;
					clock.restart();
				}
			}
			else {
				if (press) {
					*left = 3142;
				}
				*y = 119;
				*width = 81;
				*top = topper;
				if (clock.getElapsedTime().asSeconds() > 0.15f) {
					if (*left < 1694) {
						*left = 3142;
					}
					*left -= 170;
					clock.restart();
				}
			}
			click = false;
			press = false;
		}
	}
private:
};