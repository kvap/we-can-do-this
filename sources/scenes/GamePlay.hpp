#ifndef GAME_PLAY_HPP
#define GAME_PLAY_HPP

#include <Scene.hpp>
#include <SFML/Graphics.hpp>

class GamePlay : public Scene {
	public:
		GamePlay();
		int run(sf::RenderWindow &window);
};

#endif // GAME_PLAY_HPP
