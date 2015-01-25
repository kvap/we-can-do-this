#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <algorithm> 
#include <SFML/Graphics.hpp>

#include "Ship.hpp"
#include "Tile.hpp"

class Ship;
class Creature;
class Object {
	private:
		sf::Sprite sprite;
		Ship *ship;
	protected:
		int oldx, oldy;
		int x, y;
		int tile;
		float timeout;
		sf::Clock clock;
	public:
		Object(int x, int y, int tile, sf::Texture &tilemap, Ship* ship);
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
			KLASS(int x, int y, sf::Texture &tilemap, Ship* ship)\
				: Object(x, y, ENUM, tilemap, ship) {};\
			std::string getName() { return NAME; };\
			void use(Creature *user) {};\
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
INERT(Microscope, TILE_MICROSCOPE, "Microscope");
INERT(Couch, TILE_COUCH, "Couch");
INERT(Engine, TILE_ENGINE, "Engine");
INERT(Dynamo, TILE_DYNAMO, "Dynamo");
INERT(WallW, TILE_WALL_W, "Wall W");
INERT(WallQ, TILE_WALL_Q, "Wall Q");
INERT(WallA, TILE_WALL_A, "Wall A");
INERT(WallZ, TILE_WALL_Z, "Wall Z");
INERT(WallX, TILE_WALL_X, "Wall X");
INERT(WallC, TILE_WALL_C, "Wall C");
INERT(WallD, TILE_WALL_D, "Wall D");
INERT(WallE, TILE_WALL_E, "Wall E");
INERT(Jacuzzi, TILE_JACUZZI, "Jacuzzi");

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
		Creature(int x, int y, sf::Texture &tilemap, Ship* ship)
				: Object(x, y, TILE_RESPAWN, tilemap, ship) {
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
		void heal(int h) { damage = std::max(damage - h, 0); };
		virtual bool usable(Creature *user) { return true; };
};

class Human : public Creature {
	public:
		Human(int x, int y, sf::Texture &tilemap, Ship* ship)
			: Creature(x, y, tilemap, ship) {};
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
		Robot(int x, int y, sf::Texture &tilemap, Ship* ship)
			: Creature(x, y, tilemap, ship) {};
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

class BioChamber : public Object {
	public:
		BioChamber(int x, int y, sf::Texture &tilemap, Ship* ship)
			: Object(x, y, TILE_BIO_CHAMBER, tilemap, ship) { };

		std::string getName() { return "Bio Chamber"; };
		void use(Creature *user) {
			switch (user->getRace()) {
				case RACE_VEG:
				case RACE_HUMAN:
					user->heal(10);
					break;
				case RACE_ROBOT:
					user->heal(-10);
			}
		}
};

class Hatch : public Object {
	public:
		Hatch(int x, int y, sf::Texture &tilemap, Ship* ship)
			: Object(x, y, TILE_HATCH, tilemap, ship) { };

		std::string getName() { return "Hatch"; };
		void use(Creature *user) {
			ship.setCurrentLevel(LEVEL_MG);
			ship.putObject(x, y, new HatchOpen(x, y, tilemap, ship));
			ship.setCurrentLevel(LEVEL_FG);
			ship.putObject(x, y, NULL);
		}
};

class HatchOpen : public Object {
	public:
		HatchOpen(int x, int y, sf::Texture &tilemap, Ship* ship)
			: Object(x, y, TILE_HATCH_OPEN, tilemap, ship) { };

		std::string getName() { return "Hatch open"; };
		void use(Creature *user) {
			ship.setCurrentLevel(LEVEL_FG);
			ship.putObject(x, y, new Hatch(x, y, tilemap, ship));
			ship.setCurrentLevel(LEVEL_MG);
			ship.putObject(x, y, NULL);
		}
};

#endif
