#include "Object.hpp"
#include "Tile.hpp"

Object::Object(int x, int y, int tile, sf::Texture &tilemap) {
	this->x = x;
	this->y = y;
	this->tile = tile;
	sprite.setTexture(tilemap);
	int top = tiles[tile][0] * TILE_SIZE;
	int left = tiles[tile][1] * TILE_SIZE;
	int width = tiles[tile][2] * TILE_SIZE;
	int height = tiles[tile][3] * TILE_SIZE;
	sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Object::draw(sf::RenderWindow &window) {
	sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
	window.draw(sprite);
}
