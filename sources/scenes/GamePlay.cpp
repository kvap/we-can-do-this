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

	bool goup = false;
	bool godown = false;
	bool goleft = false;
	bool goright = false;

	sf::Text text;
	text.setFont(font);
	text.setString(L"GamePlay");
	text.setCharacterSize(20);
	text.setColor(sf::Color::Green);

	sf::Sprite sky(skytex);

	Human human(76, 48, tilemap, &ship);
	Creature *player = &human;

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
						goleft = true;
						break;
					case sf::Keyboard::Right:
						goright = true;
						break;
					case sf::Keyboard::Up:
						goup = true;
						break;
					case sf::Keyboard::Down:
						godown = true;
						break;
				}
			} else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						return FINAL_INFO_SCENE;
						break;
					case sf::Keyboard::Left:
						goleft = false;
						break;
					case sf::Keyboard::Right:
						goright = false;
						break;
					case sf::Keyboard::Up:
						goup = false;
						break;
					case sf::Keyboard::Down:
						godown = false;
						break;
				}
			}
		}

		int dx = 0, dy = 0;
		if (goup) dy--;
		if (godown) dy++;
		if (goleft) dx--;
		if (goright) dx++;
		if ((dx || dy) && !player->isMoving()) {
			int newx = player->getX() + dx;
			int newy = player->getY() + dy;
			Object *o = ship.getObject(LEVEL_FG, newx, newy);
			if (o) {
				goup = godown = goleft = goright = false;
				if (o->usable(player)) {
					std::cout << "use " << o->getName() << std::endl;
					o->use(player);
				} else {
					std::cout << "kick " << o->getName() << std::endl;
				}
				// use object
			} else {
				player->move(newx, newy, 0.5);
			}
		}

		float dt = clock.getElapsedTime().asSeconds();

		clock.restart();

		sf::View view = window.getView();
		float ix, iy;
		player->interPos(ix, iy);
		sky.setPosition(sf::Vector2f(ix * TILE_SIZE - (int)skytex.getSize().x / 2, iy * TILE_SIZE - (int)skytex.getSize().y / 2));
		view.setCenter(sf::Vector2f((ix + 0.5) * TILE_SIZE, (iy + 0.5) * TILE_SIZE));
		window.setView(view);

		window.clear();
		window.draw(sky);
		ship.draw(window);
		player->draw(window);
		window.draw(text);
		window.display();
	}

	return -1;
}
