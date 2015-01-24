#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/OpenGL.hpp>

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(640, 480), "We Can Do This!", sf::Style::Default, settings);

	settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	const std::string texfile = "Tux.png";
	sf::Texture texture;
	if (!texture.loadFromFile(texfile)) {
		std::cerr << "could not load texture: " << texfile << std::endl;
		return 1;
	}
	texture.setSmooth(true);

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

	sf::Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setPosition(sf::Vector2f(100, 200));

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
				// adjust the viewport when the window is resized
				//glViewport(0, 0, event.size.width, event.size.height);
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
		window.draw(sprite);
		window.draw(text);

		/*
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(0.5, 0.5, 0.0);
		glRotatef(angle * 180 / M_PI, 0, 0, 1);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		sf::Texture::bind(&texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2f(-0.25, -0.25);
			glTexCoord2f(1, 1); glVertex2f( 0.25, -0.25);
			glTexCoord2f(1, 0); glVertex2f( 0.25,  0.25);
			glTexCoord2f(0, 0); glVertex2f(-0.25,  0.25);
		glEnd();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		sf::Texture::bind(NULL);
		glPopMatrix();
		*/

		window.display();
	}

	return 0;
}
