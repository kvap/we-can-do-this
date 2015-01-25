#include "Tile.hpp"

int tiles[][4] = {
	/* tiley, tilex, width, height */
	{0,  0, 1, 1}, // TILE_FLOOR_JAIL,
	{0,  1, 1, 1}, // TILE_FLOOR_LAB,
	{0,  2, 1, 1}, // TILE_FLOOR_QUARTERS,
	{0,  3, 1, 1}, // TILE_FLOOR_WC,
	{0,  4, 1, 1}, // TILE_FLOOR_RNR,
	{0,  5, 1, 1}, // TILE_FLOOR_CORRIDOR,
	{0,  6, 1, 1}, // TILE_FLOOR_ENGINE,
	{0,  7, 1, 1}, // TILE_FLOOR_HOSPITAL,
	{0,  8, 1, 1}, // TILE_FLOOR_GUARD,
	{0,  9, 1, 1}, // TILE_FLOOR_MESS,
	{0, 10, 1, 1}, // TILE_FLOOR_BRIDGE
	{1,  0, 1, 1}, // TILE_RESPAWN,
	{1,  1, 1, 1}, // TILE_STICK,
	{1,  2, 1, 1}, // TILE_TOILET,
	{1,  3, 1, 1}, // TILE_MULTICOOKER,
	{1,  4, 1, 1}, // TILE_GUARD_STAND,
	{1,  5, 1, 1}, // TILE_BIO_CHAMBER,
	{1,  6, 1, 1}, // TILE_MICROSCOPE,
	{1,  7, 1, 1}, // TILE_COUCH,
	{1,  8, 1, 1}, // TILE_ENGINE,
	{1,  9, 1, 1}, // TILE_DYNAMO,
	{1, 10, 1, 1}, // TILE_HATCH,
	{2,  1, 1, 1}, // TILE_WALL_U,
	{5,  0, 1, 1}, // TILE_WALL_UL,
	{6,  0, 1, 1}, // TILE_WALL_L,
	{7,  0, 1, 1}, // TILE_WALL_DL,
	{2,  1, 1, 1}, // TILE_WALL_D,
	{7,  1, 1, 1}, // TILE_WALL_DR,
	{6,  1, 1, 1}, // TILE_WALL_R,
	{5,  1, 1, 1}, // TILE_WALL_UR,
	{1, 12, 2, 1}, // TILE_JACUZZI
};
