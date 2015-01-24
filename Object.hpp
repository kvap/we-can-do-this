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
		virtual void use(Object &user) = 0;
		virtual bool usable(Object &user) { return false; };
};

class FloorJail : public Object {
	public:
		FloorJail(int x, int y, sf::Texture &tilemap) : Object(x, y, TILE_FLOOR_JAIL, tilemap) {};
		void use(Object &user) {};
};

class FloorLab : public Object {
	public:
		FloorLab(int x, int y, sf::Texture &tilemap) : Object(x, y, TILE_FLOOR_LAB, tilemap) {};
		void use(Object &user) {};
};

class FloorQuarters : public Object {
	public:
		FloorQuarters(int x, int y, sf::Texture &tilemap) : Object(x, y, TILE_FLOOR_QUARTERS, tilemap) {};
		void use(Object &user) {};
};

#endif
