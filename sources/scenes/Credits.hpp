#ifndef CREDITS_HPP
#define CREDITS_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

class Credits : public Scene {
	public:
		Credits();
		int run(sf::RenderWindow &window);
};

#endif // CREDITS_HPP
