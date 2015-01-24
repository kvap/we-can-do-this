#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

class Editor: public Scene {
	public:
		Editor() {};
		int run(sf::RenderWindow &window);
};

#endif // EDITOR_HPP
