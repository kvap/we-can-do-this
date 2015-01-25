#include "Object.hpp"
#include "Tile.hpp"

Object::Object(int x, int y, int tile, sf::Texture &tilemap, Ship* ship) {
	this->x = x;
	this->y = y;
	this->oldx = x;
	this->oldy = y;
	this->tile = tile;
	timeout = 0;
	sprite.setTexture(tilemap);
	int top = Tile::tiles[tile][0] * TILE_SIZE;
	int left = Tile::tiles[tile][1] * TILE_SIZE;
	int width = Tile::tiles[tile][2] * TILE_SIZE;
	int height = Tile::tiles[tile][3] * TILE_SIZE;
	sprite.setTextureRect(sf::IntRect(left, top, width, height));
	this->ship = ship;
}
float interpolate(float a, float progress, float b) {
	return a * (1 - progress) + b * progress;
}

void Object::interPos(float &ix, float &iy) {
	float elapsed = clock.getElapsedTime().asSeconds();
	float progress = elapsed / timeout;
	if (progress > 1) {
		progress = 1;
	}
	ix = interpolate(oldx, progress, x);
	iy = interpolate(oldy, progress, y);
}

void Object::draw(sf::RenderWindow &window) {
	float ix, iy;
	interPos(ix, iy);
	sprite.setPosition(ix * TILE_SIZE, iy * TILE_SIZE);
	window.draw(sprite);
}

void Object::move(int newx, int newy, float time) {
	oldx = x;
	oldy = y;
	x = newx;
	y = newy;
	timeout = time;
	clock.restart();
}

bool Object::isMoving() {
	return clock.getElapsedTime().asSeconds() < timeout;
}
