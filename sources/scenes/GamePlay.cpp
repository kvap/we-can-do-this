#include "GamePlay.hpp"

#include <sceneIds.hpp>
#include <iostream>

GamePlay::GamePlay() {
}

int GamePlay::run(sf::RenderWindow &window) {
	const std::string fontfile = "DejaVuSans.ttf";
	sf::Font font;
	if (!font.loadFromFile(fontfile)) {
		std::cerr << "could not load font: " << fontfile << std::endl;
		return -1;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(L"GamePlay");
	text.setCharacterSize(20);
	text.setColor(sf::Color::Green);
	
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				return -1;
			} else if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			} else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::Space:
						return FINAL_INFO_SCENE;
						break;
				}
			} else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
					case sf::Keyboard::Space:
						return FINAL_INFO_SCENE;
						break;
				}
			}
		}

		float dt = clock.getElapsedTime().asSeconds();

		clock.restart();

		window.clear();
		window.draw(text);
		window.display();
	}

	return -1;
}
