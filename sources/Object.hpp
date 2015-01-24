#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

class Object {
	private:
		sf::Sprite sprite;
	protected:
		int x, y;
	public:
		Object(int x, int y, int tile, sf::Texture &tilemap);
		void draw(sf::RenderWindow &window);
		virtual std::string getName() { return "object"; };
		virtual void use(Object &user) = 0;
		virtual bool usable(Object &user) { return false; };
};

// A macro for avoiding lots of boilerplate code here.
#define INERT(KLASS, ENUM, NAME) \
	class KLASS : public Object {\
		public:\
			KLASS(int x, int y, sf::Texture &tilemap) : Object(x, y, ENUM, tilemap) {};\
			std::string getName() { return NAME; };\
			void use(Object &user) {};\
	}

INERT(FloorJail, TILE_FLOOR_JAIL, "Jail Floor");
INERT(FloorLab, TILE_FLOOR_LAB, "Lab Floor");
INERT(FloorQuarters, TILE_FLOOR_QUARTERS, "Quarters Floor");
INERT(FloorWC, TILE_FLOOR_WC, "WC Floor");
INERT(FloorRNR, TILE_FLOOR_RNR, "RNR Floor");
INERT(FloorCorridor, TILE_FLOOR_CORRIDOR, "Corridor Floor");
INERT(FloorEngine, TILE_FLOOR_ENGINE, "Engine Floor");
INERT(FloorHospital, TILE_FLOOR_HOSPITAL, "Hospital Floor");
INERT(FloorGuard, TILE_FLOOR_GUARD, "Guard Floor");
INERT(FloorMess, TILE_FLOOR_MESS, "Mess Floor");
INERT(FloorBridge, TILE_FLOOR_BRIDGE, "Bridge Floor");
INERT(Respawn, TILE_RESPAWN, "Respawn");
INERT(Stick, TILE_STICK, "Stick");
INERT(Toilet, TILE_TOILET, "Toilet");
INERT(Multicooker, TILE_MULTICOOKER, "Multicooker");
INERT(GuardStand, TILE_GUARD_STAND, "Guard Stand");
INERT(BioChamber, TILE_BIO_CHAMBER, "Bio Chamber");
INERT(Microscope, TILE_MICROSCOPE, "Microscope");
INERT(Couch, TILE_COUCH, "Couch");
INERT(Engine, TILE_ENGINE, "Engine");
INERT(Dynamo, TILE_DYNAMO, "Dynamo");
INERT(Hatch, TILE_HATCH, "Hatch");
INERT(Wall, TILE_WALL, "Wall");
INERT(Jacuzzi, TILE_JACUZZI, "Jacuzzi");

#endif
