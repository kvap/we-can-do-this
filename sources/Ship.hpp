#ifndef SHIP_HPP
#define SHIP_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

class Object;
#include "Object.hpp"
#include "Loggable.hpp"

enum {
	LEVEL_BG,
	LEVEL_MG,
	LEVEL_FG,
	LEVELS
};

class Ship : public Loggable {
	private:
		Object **tiles[LEVELS];
		int currentLevel;
		int width;
		int height;
		bool gravity;
	public:
		Ship();
		~Ship();
		void load(std::string filename, sf::Texture &tilemap);
		void save(std::string filename);
		void setGravity(bool value);
		bool getGravity();
		int getWidth();
		int getHeight();
		Object *getObject(int level, int x, int y);
		bool inertPlace(int x, int y); // cannot start or stop moving here
		void putObject(int x, int y, Object *object);
		int getCurrentLevel();
		void setCurrentLevel(int level);
		void draw(sf::RenderWindow &window);
};
 
#endif // SHIP_HPP
