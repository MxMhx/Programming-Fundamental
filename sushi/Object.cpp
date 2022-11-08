#include "Object.h"

GameObject::GameObject(std::string textureSource, float x, float y) {
	texture.loadFromFile(textureSource);
	pos = sf::Vector2f(x, y);
	sprite.setTexture(texture);
	sprite.setPosition(pos);
}

GameSheet::GameSheet(std::string textureSource, float posx, float posy, int x, int y, int width, int height) {
	texture.loadFromFile(textureSource);
	pos = sf::Vector2f(posx, posy);
	spriterect.left = x;
	spriterect.top = y;
	spriterect.width = width;
	spriterect.height = height;
	sprite.setTextureRect(spriterect);
	sprite.setTexture(texture);
	sprite.setPosition(pos);
}

FontText::FontText(std::string fontSource, std::string textSource, float x, float y, sf::Color color) {
	pos = sf::Vector2f(x, y);
	font.loadFromFile(fontSource);
	text.setFont(font);
	text.setString(textSource);
	text.setScale(1.2, 1.2);
	text.setFillColor(color);
	text.setPosition(pos);
}