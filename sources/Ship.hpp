#ifndef SHIP_HPP
#define SHIP_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

#include "Object.hpp"

enum {
	LEVEL_BG,
	LEVEL_MG,
	LEVEL_FG,
	LEVELS
};

class Ship {
	private:
		Object **tiles[LEVELS];
		int currentLevel;
		int width;
		int height;
	public:
		Ship();
		~Ship();
		int getWidth();
		int getHeight();
		Object *getObject(int level, int x, int y);
		void putObject(int x, int y, Object *object);
		int getCurrentLevel();
		void setCurrentLevel(int level);
		void draw(sf::RenderWindow &window);
};
 
#endif // SHIP_HPP
