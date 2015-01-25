#include <iostream>
#include <SFML/Graphics.hpp>

#include "sceneIds.hpp"
#include "Editor.hpp"
#include "Object.hpp"
#include "Ship.hpp"

int Editor::run(sf::RenderWindow &window) {
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
		return 1;
	}

	Ship ship;
	ship.load("ship.map", tilemap);

	int x = ship.getWidth() / 2;
	int y = ship.getHeight() / 2;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setColor(sf::Color::Green);

	sf::RectangleShape cursor(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	cursor.setOutlineThickness(5);
	cursor.setOutlineColor(sf::Color(255, 255, 127, 255));
	cursor.setFillColor(sf::Color(255, 127, 127, 127));

	sf::Sprite sky(skytex);

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				return -1;
			} else if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			} else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						return -1;
						break;
					case sf::Keyboard::F2:
						ship.save("ship.map");
						return -1;
						break;
					case sf::Keyboard::Left:
						x--;
						break;
					case sf::Keyboard::Right:
						x++;
						break;
					case sf::Keyboard::Up:
						y--;
						break;
					case sf::Keyboard::Down:
						y++;
						break;
					case sf::Keyboard::Num1:
						ship.setCurrentLevel(LEVEL_BG);
						break;
					case sf::Keyboard::Num2:
						ship.setCurrentLevel(LEVEL_MG);
						break;
					case sf::Keyboard::Num3:
						ship.setCurrentLevel(LEVEL_FG);
						break;
					case sf::Keyboard::X:
						ship.putObject(x, y, NULL);
						break;
				}
				if (ship.getCurrentLevel() == LEVEL_BG) {
					switch (event.key.code) {
						case sf::Keyboard::W:
							ship.putObject(x, y, new FloorWC(x, y, tilemap));
							break;
						case sf::Keyboard::J:
							ship.putObject(x, y, new FloorJail(x, y, tilemap));
							break;
						case sf::Keyboard::L:
							ship.putObject(x, y, new FloorLab(x, y, tilemap));
							break;
						case sf::Keyboard::Q:
							ship.putObject(x, y, new FloorQuarters(x, y, tilemap));
							break;
						case sf::Keyboard::R:
							ship.putObject(x, y, new FloorRNR(x, y, tilemap));
							break;
						case sf::Keyboard::C:
							ship.putObject(x, y, new FloorCorridor(x, y, tilemap));
							break;
						case sf::Keyboard::E:
							ship.putObject(x, y, new FloorEngine(x, y, tilemap));
							break;
						case sf::Keyboard::H:
							ship.putObject(x, y, new FloorHospital(x, y, tilemap));
							break;
						case sf::Keyboard::G:
							ship.putObject(x, y, new FloorGuard(x, y, tilemap));
							break;
						case sf::Keyboard::M:
							ship.putObject(x, y, new FloorMess(x, y, tilemap));
							break;
						case sf::Keyboard::B:
							ship.putObject(x, y, new FloorBridge(x, y, tilemap));
							break;
					}
				}
				if (ship.getCurrentLevel() == LEVEL_FG) {
					if (event.key.shift) {
						switch (event.key.code) {
							case sf::Keyboard::W:
								ship.putObject(x, y, new WallW(x, y, tilemap));
								break;
							case sf::Keyboard::Q:
								ship.putObject(x, y, new WallQ(x, y, tilemap));
								break;
							case sf::Keyboard::A:
								ship.putObject(x, y, new WallA(x, y, tilemap));
								break;
							case sf::Keyboard::Z:
								ship.putObject(x, y, new WallZ(x, y, tilemap));
								break;
							case sf::Keyboard::X:
								ship.putObject(x, y, new WallX(x, y, tilemap));
								break;
							case sf::Keyboard::C:
								ship.putObject(x, y, new WallC(x, y, tilemap));
								break;
							case sf::Keyboard::D:
								ship.putObject(x, y, new WallD(x, y, tilemap));
								break;
							case sf::Keyboard::E:
								ship.putObject(x, y, new WallE(x, y, tilemap));
								break;
						}
					} else {
						switch (event.key.code) {
							case sf::Keyboard::P:
								ship.putObject(x, y, new Respawn(x, y, tilemap));
								break;
							case sf::Keyboard::S:
								ship.putObject(x, y, new Stick(x, y, tilemap));
								break;
							case sf::Keyboard::T:
								ship.putObject(x, y, new Toilet(x, y, tilemap));
								break;
							case sf::Keyboard::M:
								ship.putObject(x, y, new Multicooker(x, y, tilemap));
								break;
							case sf::Keyboard::G:
								ship.putObject(x, y, new GuardStand(x, y, tilemap));
								break;
							case sf::Keyboard::B:
								ship.putObject(x, y, new BioChamber(x, y, tilemap));
								break;
							case sf::Keyboard::Z:
								ship.putObject(x, y, new Microscope(x, y, tilemap));
								break;
							case sf::Keyboard::C:
								ship.putObject(x, y, new Couch(x, y, tilemap));
								break;
							case sf::Keyboard::E:
								ship.putObject(x, y, new Engine(x, y, tilemap));
								break;
							case sf::Keyboard::D:
								ship.putObject(x, y, new Dynamo(x, y, tilemap));
								break;
							case sf::Keyboard::H:
								ship.putObject(x, y, new Hatch(x, y, tilemap));
								break;
							case sf::Keyboard::J:
								ship.putObject(x, y, new Jacuzzi(x, y, tilemap));
								break;
						}
					}
				}
			}
		}
		if (x < 0) {
			x = 0;
		}
		if (x >= ship.getWidth()) {
			x = ship.getWidth() - 1;
		}
		if (y < 0) {
			y = 0;
		}
		if (y >= ship.getHeight()) {
			y = ship.getHeight() - 1;
		}

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::View view = window.getView();
		cursor.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
		sky.setPosition(sf::Vector2f(x * TILE_SIZE - skytex.getSize().x / 2, y * TILE_SIZE - skytex.getSize().y / 2));
		view.setCenter(sf::Vector2f((x + 0.5) * TILE_SIZE, (y + 0.5) * TILE_SIZE));
		window.setView(view);

		window.clear();
		window.draw(sky);
		ship.draw(window);
		window.draw(cursor);

		auto winsize = window.getSize();
		sf::View hud(sf::FloatRect(0, 0, winsize.x, winsize.y));
		window.setView(hud);
		std::string cellinfo = std::to_string(x) + ":" + std::to_string(y);

		Object *o;
		o = ship.getObject(LEVEL_FG, x, y);
		if (o == NULL) {
			cellinfo += std::string("\nfg = NULL");
		} else {
			cellinfo += std::string("\nfg = " + o->getName());
		}

		o = ship.getObject(LEVEL_MG, x, y);
		if (o == NULL) {
			cellinfo += std::string("\nmg = NULL");
		} else {
			cellinfo += std::string("\nmg = " + o->getName());
		}

		o = ship.getObject(LEVEL_BG, x, y);
		if (o == NULL) {
			cellinfo += std::string("\nbg = NULL");
		} else {
			cellinfo += std::string("\nbg = " + o->getName());
		}

		if (ship.getCurrentLevel() == LEVEL_BG) {
			cellinfo += std::string("\ncurrent bg");
			cellinfo += std::string("\nw - wc floor");
			cellinfo += std::string("\nj - jail floor");
			cellinfo += std::string("\nl - lab floor");
			cellinfo += std::string("\nq - quarters floor");
			cellinfo += std::string("\nr - rnr floor");
			cellinfo += std::string("\nc - corridor floor");
			cellinfo += std::string("\ne - engine floor");
			cellinfo += std::string("\nh - hospital floor");
			cellinfo += std::string("\ng - guard floor");
			cellinfo += std::string("\nm - mess floor");
			cellinfo += std::string("\nb - bridge floor");
		} else if (ship.getCurrentLevel() == LEVEL_MG) {
			cellinfo += std::string("\ncurrent mg");
		} else {
			cellinfo += std::string("\ncurrent fg");
			cellinfo += std::string("\np - respawn");
			cellinfo += std::string("\ns - stick");
			cellinfo += std::string("\nt - toilet");
			cellinfo += std::string("\nm - multicooker");
			cellinfo += std::string("\ng - guard stand");
			cellinfo += std::string("\nb - bio chamber");
			cellinfo += std::string("\nz - microscope");
			cellinfo += std::string("\nc - couch");
			cellinfo += std::string("\ne - engine");
			cellinfo += std::string("\nd - dynamo");
			cellinfo += std::string("\nh - hatch");
			cellinfo += std::string("\nQWE - walls");
			cellinfo += std::string("\nA D - walls");
			cellinfo += std::string("\nZXC - walls");
			cellinfo += std::string("\nj - jacuzzi");
		}

		text.setString(cellinfo);
		window.draw(text);

		window.setView(view);
		window.display();
	}

	return -1;
}
