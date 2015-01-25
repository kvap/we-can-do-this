#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

class Creature;
class Object {
	private:
		sf::Sprite sprite;
	protected:
		int oldx, oldy;
		int x, y;
		int tile;
		float timeout;
		sf::Clock clock;
	public:
		Object(int x, int y, int tile, sf::Texture &tilemap);
		virtual ~Object() {};
		void draw(sf::RenderWindow &window);
		int getTile() { return tile; };
		int getX() { return x; };
		int getY() { return y; };
		void interPos(float &x, float &y); // interpolate x, y when moving
		virtual std::string getName() { return "object"; };
		virtual void use(Creature *user) = 0;
		virtual bool usable(Creature *user) { return false; };
		virtual void move(int newx, int newy, float time);
		bool isMoving();
};

// A macro for avoiding lots of boilerplate code here.
#define INERT(KLASS, ENUM, NAME) \
	class KLASS : public Object {\
		public:\
			KLASS(int x, int y, sf::Texture &tilemap) : Object(x, y, ENUM, tilemap) {};\
			std::string getName() { return NAME; };\
			void use(Creature *user) {};\
	}

INERT(FloorJail, Tile::TILE_FLOOR_JAIL, "Jail Floor");
INERT(FloorLab, Tile::TILE_FLOOR_LAB, "Lab Floor");
INERT(FloorQuarters, Tile::TILE_FLOOR_QUARTERS, "Quarters Floor");
INERT(FloorWC, Tile::TILE_FLOOR_WC, "WC Floor");
INERT(FloorRNR, Tile::TILE_FLOOR_RNR, "RNR Floor");
INERT(FloorCorridor, Tile::TILE_FLOOR_CORRIDOR, "Corridor Floor");
INERT(FloorEngine, Tile::TILE_FLOOR_ENGINE, "Engine Floor");
INERT(FloorHospital, Tile::TILE_FLOOR_HOSPITAL, "Hospital Floor");
INERT(FloorGuard, Tile::TILE_FLOOR_GUARD, "Guard Floor");
INERT(FloorMess, Tile::TILE_FLOOR_MESS, "Mess Floor");
INERT(FloorBridge, Tile::TILE_FLOOR_BRIDGE, "Bridge Floor");

INERT(Respawn, Tile::TILE_RESPAWN, "Respawn");

INERT(Stick, Tile::TILE_STICK, "Stick");
INERT(Toilet, Tile::TILE_TOILET, "Toilet");
INERT(Multicooker, Tile::TILE_MULTICOOKER, "Multicooker");
INERT(GuardStand, Tile::TILE_GUARD_STAND, "Guard Stand");
INERT(BioChamber, Tile::TILE_BIO_CHAMBER, "Bio Chamber");
INERT(Microscope, Tile::TILE_MICROSCOPE, "Microscope");
INERT(Couch, Tile::TILE_COUCH, "Couch");
INERT(Engine, Tile::TILE_ENGINE, "Engine");
INERT(Dynamo, Tile::TILE_DYNAMO, "Dynamo");
INERT(Hatch, Tile::TILE_HATCH, "Hatch");
INERT(WallW, Tile::TILE_WALL_W, "Wall W");
INERT(WallQ, Tile::TILE_WALL_Q, "Wall Q");
INERT(WallA, Tile::TILE_WALL_A, "Wall A");
INERT(WallZ, Tile::TILE_WALL_Z, "Wall Z");
INERT(WallX, Tile::TILE_WALL_X, "Wall X");
INERT(WallC, Tile::TILE_WALL_C, "Wall C");
INERT(WallD, Tile::TILE_WALL_D, "Wall D");
INERT(WallE, Tile::TILE_WALL_E, "Wall E");
INERT(Jacuzzi, Tile::TILE_JACUZZI, "Jacuzzi");

enum {
	RACE_HUMAN,
	RACE_ROBOT,
	RACE_VEG
};

enum {
	JOB_PILOT,
	JOB_MEDIC,
	JOB_ENGINEER,
	JOB_COOK,
	JOB_GUARD
};

class Creature : public Object {
	protected:
		int job;
		int damage;
		int hunger;
		int fatigue;
	public:
		Creature(int x, int y, sf::Texture &tilemap) : Object(x, y, Tile::TILE_RESPAWN, tilemap) {
			damage = 0;
			hunger = 0;
			fatigue = 0;
		};
		virtual std::string getName() { return "Creature"; };
		virtual void use(Creature *user) {
			switch (user->getJob()) {
				case JOB_GUARD:
					damage += 10;
					break;
			}
		};
		virtual int getRace() = 0;
		int getJob() { return job; };
		void setJob(int job) { this->job = job; };
		virtual bool usable(Creature *user) { return true; };
};

class Human : public Creature {
	public:
		Human(int x, int y, sf::Texture &tilemap) : Creature(x, y, tilemap) {};
		std::string getName() { return "Human"; };
		virtual void use(Creature *user) {
			switch (user->getJob()) {
				case JOB_MEDIC:
					damage = 0;
					break;
			}
		};
		int getRace() { return RACE_HUMAN; };
		bool usable(Creature *user) { return true; };
};

class Robot : public Creature {
	public:
		Robot(int x, int y, sf::Texture &tilemap) : Creature(x, y, tilemap) {};
		std::string getName() { return "Human"; };
		virtual void use(Creature *user) {
			switch (user->getJob()) {
				case JOB_ENGINEER:
					damage = 0;
					break;
			}
		};
		int getRace() { return RACE_ROBOT; };
		bool usable(Creature *user) { return true; };
};

#endif
