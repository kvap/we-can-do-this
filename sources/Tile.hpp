#ifndef TILE_HPP
#define TILE_HPP

#define TILE_SIZE 64

namespace Tile {

enum {
	TILE_FLOOR_JAIL,
	TILE_FLOOR_LAB,
	TILE_FLOOR_QUARTERS,
	TILE_FLOOR_WC,
	TILE_FLOOR_RNR,
	TILE_FLOOR_CORRIDOR,
	TILE_FLOOR_ENGINE,
	TILE_FLOOR_HOSPITAL,
	TILE_FLOOR_GUARD,
	TILE_FLOOR_MESS,
	TILE_FLOOR_BRIDGE,
	TILE_RESPAWN,
	TILE_STICK,
	TILE_TOILET,
	TILE_MULTICOOKER,
	TILE_GUARD_STAND,
	TILE_BIO_CHAMBER,
	TILE_MICROSCOPE,
	TILE_COUCH,
	TILE_ENGINE,
	TILE_DYNAMO,
	TILE_HATCH,
	TILE_WALL_W,
	TILE_WALL_Q,
	TILE_WALL_A,
	TILE_WALL_Z,
	TILE_WALL_X,
	TILE_WALL_C,
	TILE_WALL_D,
	TILE_WALL_E,
	TILE_JACUZZI,
	TILE_HATCH_OPEN,
	TILE_EMPTY = -1
};

extern int tiles[][4];

}

#endif
