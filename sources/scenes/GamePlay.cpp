#include <iostream>

#include "sceneIds.hpp"
#include "GamePlay.hpp"
#include "Ship.hpp"

GamePlay::GamePlay() {
}

int GamePlay::run(sf::RenderWindow &window) {
	const std::string texfile = "tiles.png";
	sf::Texture tilemap;
	if (!tilemap.loadFromFile(texfile)) {
		std::cerr << "could not load tilemap: " << texfile << std::endl;
		return 1;
	}

	const std::string skyfile = "milky-way.jpg";
	sf::Texture skytex;
	if (!skytex.loadFromFile(skyfile)) {
		std::cerr << "could not load sky: " << skyfile << std::endl;
		return 1;
	}

	const std::string fontfile = "DejaVuSans.ttf";
	sf::Font font;
	if (!font.loadFromFile(fontfile)) {
		std::cerr << "could not load font: " << fontfile << std::endl;
		return -1;
	}

	Ship ship;
	ship.load("ship.map", tilemap);

	int dx = 0, dy = 0;

	sf::Text text;
	text.setFont(font);
	text.setString(L"GamePlay");
	text.setCharacterSize(20);
	text.setColor(sf::Color::Green);

	sf::Sprite sky(skytex);

	Human human(64, 66, tilemap);

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
					case sf::Keyboard::Left:
						dx -= 1;
						break;
					case sf::Keyboard::Right:
						dx += 1;
						break;
					case sf::Keyboard::Up:
						dy -= 1;
						break;
					case sf::Keyboard::Down:
						dy += 1;
						break;
				}
			} else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						return FINAL_INFO_SCENE;
						break;
					case sf::Keyboard::Left:
						dx += 1;
						break;
					case sf::Keyboard::Right:
						dx -= 1;
						break;
					case sf::Keyboard::Up:
						dy += 1;
						break;
					case sf::Keyboard::Down:
						dy -= 1;
						break;
				}
			}
		}

		float dt = clock.getElapsedTime().asSeconds();

		clock.restart();

		sf::View view = window.getView();
		int x = human.getX(), y = human.getY();
		sky.setPosition(sf::Vector2f(x * TILE_SIZE - (int)skytex.getSize().x / 2, y * TILE_SIZE - (int)skytex.getSize().y / 2));
		view.setCenter(sf::Vector2f((x + 0.5) * TILE_SIZE, (y + 0.5) * TILE_SIZE));
		window.setView(view);

		window.clear();
		window.draw(sky);
		ship.draw(window);
		human.draw(window);
		window.draw(text);
		window.display();
	}

	return -1;
}
