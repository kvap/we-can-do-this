#include <iostream>
#include <SFML/Graphics.hpp>

#include "Object.hpp"

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
	sf::Texture texture;
	if (!texture.loadFromFile(texfile)) {
		std::cerr << "could not load texture: " << texfile << std::endl;
		return 1;
	}

	const std::string fontfile = "DejaVuSans.ttf";
	sf::Font font;
	if (!font.loadFromFile(fontfile)) {
		std::cerr << "could not load font: " << fontfile << std::endl;
		return 1;
	}

	float x = 0, y = 0;
	bool goleft = false;
	bool goright = false;
	bool goup = false;
	bool godown = false;

	Object *o = new FloorQuarters(0, 0, texture);

	sf::Text text;
	text.setFont(font);
	text.setString(L"привет мир");
	text.setCharacterSize(20);
	text.setColor(sf::Color::Green);

	sf::Clock clock;
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
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

		float dt = clock.getElapsedTime().asSeconds();
		const float speed = 100;
		if (goleft) {
			x -= dt * speed;
		}
		if (goright) {
			x += dt * speed;
		}
		if (goup) {
			y -= dt * speed;
		}
		if (godown) {
			y += dt * speed;
		}

		sf::View view = window.getView();
		view.setCenter(sf::Vector2f(x, y));
		window.setView(view);

		clock.restart();

		window.clear();
		o->draw(window);
		window.draw(text);

		window.display();
	}

	return 0;
}
