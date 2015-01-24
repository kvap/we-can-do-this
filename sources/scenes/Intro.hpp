#ifndef INTRO_HPP
#define INTRO_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

class Intro: public Scene {
	public:
		Intro();
		int run(sf::RenderWindow &window);
};

#endif // INTRO_HPP
