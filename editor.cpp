#include <iostream>
#include <SFML/Graphics.hpp>

#include "Object.hpp"

const int levelSize = 128;

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(640, 480), "We Can Do This!", sf::Style::Default, settings);

	settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	const std::string texfile = "tiles.png";
	sf::Texture tilemap;
	if (!tilemap.loadFromFile(texfile)) {
		std::cerr << "could not load tilemap: " << texfile << std::endl;
		return 1;
	}

	const std::string fontfile = "DejaVuSans.ttf";
	sf::Font font;
	if (!font.loadFromFile(fontfile)) {
		std::cerr << "could not load font: " << fontfile << std::endl;
		return 1;
	}

	int x = levelSize / 2, y = levelSize / 2;

	Object *bg[levelSize][levelSize] = {0};
	Object *mg[levelSize][levelSize] = {0};
	Object *fg[levelSize][levelSize] = {0};
	Object *(*currentLayer)[128] = bg;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setColor(sf::Color::Green);

	sf::RectangleShape cursor(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	cursor.setOutlineThickness(5);
	cursor.setOutlineColor(sf::Color(255, 255, 127, 255));
	cursor.setFillColor(sf::Color(255, 127, 127, 127));

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			} else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
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
						currentLayer = bg;
						break;
					case sf::Keyboard::Num2:
						currentLayer = mg;
						break;
					case sf::Keyboard::Num3:
						currentLayer = fg;
						break;
					case sf::Keyboard::X:
						if (currentLayer[y][x] != NULL) {
							delete currentLayer[y][x];
							currentLayer[y][x] = NULL;
						}
						break;
				}
				if (currentLayer == bg) {
					switch (event.key.code) {
						case sf::Keyboard::W:
							currentLayer[y][x] = new FloorWC(x, y, tilemap);
							break;
						case sf::Keyboard::J:
							currentLayer[y][x] = new FloorJail(x, y, tilemap);
							break;
						case sf::Keyboard::L:
							currentLayer[y][x] = new FloorLab(x, y, tilemap);
							break;
						case sf::Keyboard::Q:
							currentLayer[y][x] = new FloorQuarters(x, y, tilemap);
							break;
						case sf::Keyboard::R:
							currentLayer[y][x] = new FloorRNR(x, y, tilemap);
							break;
						case sf::Keyboard::C:
							currentLayer[y][x] = new FloorCorridor(x, y, tilemap);
							break;
						case sf::Keyboard::E:
							currentLayer[y][x] = new FloorEngine(x, y, tilemap);
							break;
						case sf::Keyboard::H:
							currentLayer[y][x] = new FloorHospital(x, y, tilemap);
							break;
						case sf::Keyboard::G:
							currentLayer[y][x] = new FloorGuard(x, y, tilemap);
							break;
						case sf::Keyboard::M:
							currentLayer[y][x] = new FloorMess(x, y, tilemap);
							break;
						case sf::Keyboard::B:
							currentLayer[y][x] = new FloorBridge(x, y, tilemap);
							break;
					}
				}
				if (currentLayer == fg) {
					switch (event.key.code) {
						case sf::Keyboard::P:
							currentLayer[y][x] = new Respawn(x, y, tilemap);
							break;
						case sf::Keyboard::S:
							currentLayer[y][x] = new Stick(x, y, tilemap);
							break;
						case sf::Keyboard::T:
							currentLayer[y][x] = new Toilet(x, y, tilemap);
							break;
						case sf::Keyboard::M:
							currentLayer[y][x] = new Multicooker(x, y, tilemap);
							break;
						case sf::Keyboard::G:
							currentLayer[y][x] = new GuardStand(x, y, tilemap);
							break;
						case sf::Keyboard::B:
							currentLayer[y][x] = new BioChamber(x, y, tilemap);
							break;
						case sf::Keyboard::Z:
							currentLayer[y][x] = new Microscope(x, y, tilemap);
							break;
						case sf::Keyboard::C:
							currentLayer[y][x] = new Couch(x, y, tilemap);
							break;
						case sf::Keyboard::E:
							currentLayer[y][x] = new Engine(x, y, tilemap);
							break;
						case sf::Keyboard::D:
							currentLayer[y][x] = new Dynamo(x, y, tilemap);
							break;
						case sf::Keyboard::H:
							currentLayer[y][x] = new Hatch(x, y, tilemap);
							break;
						case sf::Keyboard::W:
							currentLayer[y][x] = new Wall(x, y, tilemap);
							break;
						case sf::Keyboard::J:
							currentLayer[y][x] = new Jacuzzi(x, y, tilemap);
							break;
					}
				}

			}
		}
		if (x < 0) {
			x = 0;
		}
		if (x >= levelSize) {
			x = levelSize - 1;
		}
		if (y < 0) {
			y = 0;
		}
		if (y >= levelSize) {
			y = levelSize - 1;
		}

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::View view = window.getView();
		cursor.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
		view.setCenter(sf::Vector2f((x + 0.5) * TILE_SIZE, (y + 0.5) * TILE_SIZE));
		window.setView(view);

		window.clear();
		for (int row = 0; row < levelSize; row++) {
			for (int col = 0; col < levelSize; col++) {
				if (bg[row][col] != NULL) {
					bg[row][col]->draw(window);
				}
				if (currentLayer == bg) {
					continue;
				}
				if (mg[row][col] != NULL) {
					mg[row][col]->draw(window);
				}
				if (currentLayer == mg) {
					continue;
				}
				if (fg[row][col] != NULL) {
					fg[row][col]->draw(window);
				}
			}
		}
		window.draw(cursor);

		auto winsize = window.getSize();
		sf::View hud(sf::FloatRect(0, 0, winsize.x, winsize.y));
		window.setView(hud);
		std::string cellinfo = std::to_string(x) + ":" + std::to_string(y);

		if (fg[y][x] == NULL) {
			cellinfo += std::string("\nfg = NULL");
		} else {
			cellinfo += std::string("\nfg = " + fg[y][x]->getName());
		}

		if (mg[y][x] == NULL) {
			cellinfo += std::string("\nmg = NULL");
		} else {
			cellinfo += std::string("\nmg = " + mg[y][x]->getName());
		}

		if (bg[y][x] == NULL) {
			cellinfo += std::string("\nbg = NULL");
		} else {
			cellinfo += std::string("\nbg = " + bg[y][x]->getName());
		}

		if (currentLayer == bg) {
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
		} else if (currentLayer == mg) {
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
			cellinfo += std::string("\nw - wall");
			cellinfo += std::string("\nj - jacuzzi");
		}

		text.setString(cellinfo);
		window.draw(text);

		window.setView(view);
		window.display();
	}

	return 0;
}
