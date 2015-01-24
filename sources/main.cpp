#include <iostream>
#include <SFML/Graphics.hpp>

#include <vector>
#include "scenes.hpp"

int main(int argc, char* argv[]) {
	int activeScene = INTRO_SCENE;
	std::vector<Scene*> scenes;

	scenes.push_back(new Intro());
	scenes.push_back(new BaseInfo());
	scenes.push_back(new GamePlay());
	scenes.push_back(new FinalInfo());
	scenes.push_back(new Credits());

	sf::ContextSettings settings;
	settings.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(640, 480), "We Can Do This!", sf::Style::Default, settings);

	settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	while (activeScene >= 0) {
		activeScene = scenes[activeScene]->run(window);
	}

	window.close();
	return 0;
}
