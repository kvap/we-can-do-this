#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>

class Scene {
	public:
		Scene();
		virtual int run(sf::RenderWindow &window) = 0;
};

#endif // SCENE_HPP
