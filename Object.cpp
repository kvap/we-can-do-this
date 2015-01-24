#include "Object.hpp"
#include "Tile.hpp"

Object::Object(int x, int y, int tile, sf::Texture &tilemap) {
	this->x = x;
	this->y = y;
	sprite.setTexture(tilemap);
	int top = tiles[tile][0] * 64;
	int left = tiles[tile][1] * 64;
	int width = tiles[tile][2] * 64;
	int height = tiles[tile][3] * 64;
	sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Object::draw(sf::RenderWindow &window) {
	sprite.setPosition(x, y);
	window.draw(sprite);
}
