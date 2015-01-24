#ifndef BASE_INFO_HPP
#define BASE_INFO_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

class BaseInfo : public Scene {
	public:
		BaseInfo();
		int run(sf::RenderWindow &window);
};

#endif // BASE_INFO_HPP
