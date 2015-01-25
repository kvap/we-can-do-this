#include "Object.hpp"
#include "Tile.hpp"

Object::Object(int x, int y, int tile, sf::Texture &tilemap) {
	this->x = x;
	this->y = y;
	this->oldx = x;
	this->oldy = y;
	this->tile = tile;
	sprite.setTexture(tilemap);
	int top = tiles[tile][0] * TILE_SIZE;
	int left = tiles[tile][1] * TILE_SIZE;
	int width = tiles[tile][2] * TILE_SIZE;
	int height = tiles[tile][3] * TILE_SIZE;
	sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Object::draw(sf::RenderWindow &window) {
	const float movetime = 1;
	float elapsed = clock.getElapsedTime().asSeconds();
	float progress = elapsed / movetime;
	if (progress > 1) {
		progress = 1;
	}
	sprite.setPosition((x * progress + oldx * (1 - progress)) * TILE_SIZE, (y * progress + oldy * (1 - progress)) * TILE_SIZE);
	window.draw(sprite);
}

void Object::move(int newx, int newy) {
	oldx = x;
	oldy = y;
	x = newx;
	y = newy;
	clock.restart();
}
