#include <fstream>

#include "Ship.hpp"

const int levelSize = 128;

Ship::Ship() : Loggable("Ship") {
	currentLevel = LEVEL_BG;
	width = levelSize;
	height = levelSize;
	gravity = false;
	for (int l = 0; l < LEVELS; l++) {
		tiles[l] = (Object**) calloc(width * height, sizeof(Object*));
	}
}

Ship::~Ship() {
	for (int l = 0; l < LEVELS; l++) {
		free(tiles[l]);
	}
}

void Ship::setGravity(bool value) {
	gravity = value;
}

bool Ship::getGravity() {
	return gravity;
}

bool Ship::inertPlace(int x, int y) {
	if (gravity) {
		return false;
	}
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		return false;
	}
	/*
	if (tiles[LEVEL_FG][y * width + x] != NULL) {
		return false;
	}
	// */
	//*
	for (int dx = -1; dx <  2; dx++) {
		for (int dy = -1; dy < 2; dy++) {
			if ((x + dx < 0) || (x + dx >= width) || (y + dy < 0) || (y + dy >= height)) {
				continue;
			}
			if (tiles[LEVEL_FG][(y + dy) * width + x + dx] != NULL) {
				return false;
			}
		}
	}
	// */
	return true;
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
	if (object == NULL) {
		// FIXME: free the object memory
		tiles[currentLevel][width * y + x] = NULL;
		return;
	}

	if (tiles[currentLevel][width * y + x] != NULL) {
		return;
	}

	int tile = object->getTile();
	int tilewid = Tile::tiles[tile][2];
	int tilehei = Tile::tiles[tile][3];

	for (int dx = 0; dx < tilewid; dx++) {
		for (int dy = 0; dy < tilehei; dy++) {
			tiles[currentLevel][width * (y + dy) + (x + dx)] = object;
		}
	}
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
				Object *o = tiles[l][row * width + col];
				if ((o != NULL) && (o->getX() == col) && (o->getY() == row)) {
					o->draw(window);
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
					case Tile::TILE_EMPTY:
						break;
					case Tile::TILE_FLOOR_JAIL:
						putObject(col, row, new FloorJail(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_LAB:
						putObject(col, row, new FloorLab(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_QUARTERS:
						putObject(col, row, new FloorQuarters(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_WC:
						putObject(col, row, new FloorWC(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_RNR:
						putObject(col, row, new FloorRNR(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_CORRIDOR:
						putObject(col, row, new FloorCorridor(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_ENGINE:
						putObject(col, row, new FloorEngine(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_HOSPITAL:
						putObject(col, row, new FloorHospital(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_GUARD:
						putObject(col, row, new FloorGuard(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_MESS:
						putObject(col, row, new FloorMess(col, row, tilemap, this));
						break;
					case Tile::TILE_FLOOR_BRIDGE:
						putObject(col, row, new FloorBridge(col, row, tilemap, this));
						break;
					case Tile::TILE_RESPAWN:
						putObject(col, row, new Respawn(col, row, tilemap, this));
						break;
					case Tile::TILE_STICK:
						putObject(col, row, new Stick(col, row, tilemap, this));
						break;
					case Tile::TILE_TOILET:
						putObject(col, row, new Toilet(col, row, tilemap, this));
						break;
					case Tile::TILE_MULTICOOKER:
						putObject(col, row, new Multicooker(col, row, tilemap, this));
						break;
					case Tile::TILE_GUARD_STAND:
						putObject(col, row, new GuardStand(col, row, tilemap, this));
						break;
					case Tile::TILE_BIO_CHAMBER:
						putObject(col, row, new BioChamber(col, row, tilemap, this));
						break;
					case Tile::TILE_MICROSCOPE:
						putObject(col, row, new Microscope(col, row, tilemap, this));
						break;
					case Tile::TILE_COUCH:
						putObject(col, row, new Couch(col, row, tilemap, this));
						break;
					case Tile::TILE_ENGINE:
						putObject(col, row, new Engine(col, row, tilemap, this));
						break;
					case Tile::TILE_DYNAMO:
						putObject(col, row, new Dynamo(col, row, tilemap, this));
						break;
					case Tile::TILE_HATCH:
						putObject(col, row, new Hatch(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_W:
						putObject(col, row, new WallW(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_Q:
						putObject(col, row, new WallQ(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_A:
						putObject(col, row, new WallA(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_Z:
						putObject(col, row, new WallZ(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_X:
						putObject(col, row, new WallX(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_C:
						putObject(col, row, new WallC(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_D:
						putObject(col, row, new WallD(col, row, tilemap, this));
						break;
					case Tile::TILE_WALL_E:
						putObject(col, row, new WallE(col, row, tilemap, this));
						break;
					case Tile::TILE_JACUZZI:
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
				if ((o != NULL) && (o->getX() == col) && (o->getY() == row)) {
					buf[row * width + col] = o->getTile();
				} else {
					buf[row * width + col] = Tile::TILE_EMPTY;
				}
			}
		}
		outfile.write((char*)buf, width * height * sizeof(int));
	}
}
