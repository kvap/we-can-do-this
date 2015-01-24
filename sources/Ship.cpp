#include "Ship.hpp"

const int levelSize = 128;

Ship::Ship() {
	currentLevel = LEVEL_BG;
	width = levelSize;
	height = levelSize;
	for (int l = 0; l < LEVELS; l++) {
		tiles[l] = (Object**) calloc(width * height, sizeof(Object*));
	}
}

Ship::~Ship() {
	for (int l = 0; l < LEVELS; l++) {
		free(tiles[l]);
	}
}

int Ship::getWidth() {
	return width;
}

int Ship::getHeight() {
	return height;
}

Object *Ship::getObject(int level, int x, int y) {
	return tiles[level][width * y + x];
}

void Ship::putObject(int x, int y, Object *object) {
	if (tiles[currentLevel][width * y + x] != NULL) {
		delete tiles[currentLevel][width * y + x];
	}
	tiles[currentLevel][width * y + x] = object;
}

void Ship::setCurrentLevel(int level) {
	currentLevel = level;
}

int Ship::getCurrentLevel() {
	return currentLevel;
}

void Ship::draw(sf::RenderWindow &window) {
	for (int l = 0; l <= currentLevel; l++) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				if (tiles[l][row * width + col] != NULL) {
					tiles[l][row * width + col]->draw(window);
				}
			}
		}
	}
}
