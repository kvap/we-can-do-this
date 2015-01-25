#include <fstream>

#include "Ship.hpp"

const int levelSize = 128;

Ship::Ship() : Loggable("Ship") {
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

void Ship::load(std::string filename, sf::Texture &tilemap) {
	Log("loading");

	std::ifstream infile;
	infile.open(filename, std::ios::in | std::ios::binary);

	if (!infile.is_open()) {
		return;
	}

	int buf[width * height];

	for (int l = 0; l < LEVELS; l++) {
		infile.read((char*)buf, width * height * sizeof(int));

		setCurrentLevel(l);
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				switch (buf[row * width + col]) {
					case TILE_EMPTY:
						break;
					case TILE_FLOOR_JAIL:
						putObject(col, row, new FloorJail(col, row, tilemap, this));
						break;
					case TILE_FLOOR_LAB:
						putObject(col, row, new FloorLab(col, row, tilemap, this));
						break;
					case TILE_FLOOR_QUARTERS:
						putObject(col, row, new FloorQuarters(col, row, tilemap, this));
						break;
					case TILE_FLOOR_WC:
						putObject(col, row, new FloorWC(col, row, tilemap, this));
						break;
					case TILE_FLOOR_RNR:
						putObject(col, row, new FloorRNR(col, row, tilemap, this));
						break;
					case TILE_FLOOR_CORRIDOR:
						putObject(col, row, new FloorCorridor(col, row, tilemap, this));
						break;
					case TILE_FLOOR_ENGINE:
						putObject(col, row, new FloorEngine(col, row, tilemap, this));
						break;
					case TILE_FLOOR_HOSPITAL:
						putObject(col, row, new FloorHospital(col, row, tilemap, this));
						break;
					case TILE_FLOOR_GUARD:
						putObject(col, row, new FloorGuard(col, row, tilemap, this));
						break;
					case TILE_FLOOR_MESS:
						putObject(col, row, new FloorMess(col, row, tilemap, this));
						break;
					case TILE_FLOOR_BRIDGE:
						putObject(col, row, new FloorBridge(col, row, tilemap, this));
						break;
					case TILE_RESPAWN:
						putObject(col, row, new Respawn(col, row, tilemap, this));
						break;
					case TILE_STICK:
						putObject(col, row, new Stick(col, row, tilemap, this));
						break;
					case TILE_TOILET:
						putObject(col, row, new Toilet(col, row, tilemap, this));
						break;
					case TILE_MULTICOOKER:
						putObject(col, row, new Multicooker(col, row, tilemap, this));
						break;
					case TILE_GUARD_STAND:
						putObject(col, row, new GuardStand(col, row, tilemap, this));
						break;
					case TILE_BIO_CHAMBER:
						putObject(col, row, new BioChamber(col, row, tilemap, this));
						break;
					case TILE_MICROSCOPE:
						putObject(col, row, new Microscope(col, row, tilemap, this));
						break;
					case TILE_COUCH:
						putObject(col, row, new Couch(col, row, tilemap, this));
						break;
					case TILE_ENGINE:
						putObject(col, row, new Engine(col, row, tilemap, this));
						break;
					case TILE_DYNAMO:
						putObject(col, row, new Dynamo(col, row, tilemap, this));
						break;
					case TILE_HATCH:
						putObject(col, row, new Hatch(col, row, tilemap, this));
						break;
					case TILE_WALL_W:
						putObject(col, row, new WallW(col, row, tilemap, this));
						break;
					case TILE_WALL_Q:
						putObject(col, row, new WallQ(col, row, tilemap, this));
						break;
					case TILE_WALL_A:
						putObject(col, row, new WallA(col, row, tilemap, this));
						break;
					case TILE_WALL_Z:
						putObject(col, row, new WallZ(col, row, tilemap, this));
						break;
					case TILE_WALL_X:
						putObject(col, row, new WallX(col, row, tilemap, this));
						break;
					case TILE_WALL_C:
						putObject(col, row, new WallC(col, row, tilemap, this));
						break;
					case TILE_WALL_D:
						putObject(col, row, new WallD(col, row, tilemap, this));
						break;
					case TILE_WALL_E:
						putObject(col, row, new WallE(col, row, tilemap, this));
						break;
					case TILE_JACUZZI:
						putObject(col, row, new Jacuzzi(col, row, tilemap, this));
						break;
				}
			}
		}
	}
	Log("loaded");
}

void Ship::save(std::string filename) {
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::binary);

	int buf[width * height];

	for (int l = 0; l < LEVELS; l++) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				Object *o = getObject(l, col, row);
				if (o != NULL) {
					buf[row * width + col] = o->getTile();
				} else {
					buf[row * width + col] = TILE_EMPTY;
				}
			}
		}
		outfile.write((char*)buf, width * height * sizeof(int));
	}
}
