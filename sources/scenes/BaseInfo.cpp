#include "BaseInfo.hpp"

#include <sceneIds.hpp>
#include <iostream>

float deltaX=60;
float deltaY=20;

BaseInfo::BaseInfo() {
}

int BaseInfo::run(sf::RenderWindow &window) {
	int i=1;
	const std::string fontfile = "DejaVuSans.ttf";
	sf::Font font;
	if (!font.loadFromFile(fontfile)) {
		std::cerr << "could not load font: " << fontfile << std::endl;
		return -1;
	}
	sf::Texture texture;
    if (!texture.loadFromFile("speech_bubble_r.png"))
        return -1;
    sf::Sprite sprite(texture);
	sf::Text text;
	text.setFont(font);
	text.setString(L"Что случилось?");
	text.setCharacterSize(48);
	text.setColor(sf::Color::Color(112,146,190,255));	
	text.setPosition(deltaX,deltaY);
	sprite.setPosition(100,100);
	text.setPosition(100+deltaX,100+deltaY);
	
	sf::Clock clock;
	float elapsedSeconds = 0.0f;
	while (window.isOpen()) {
		if (elapsedSeconds >= 20) {
			return GAME_PLAY_SCENE;
		}
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
						return GAME_PLAY_SCENE;
						break;
				}
			} else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
					case sf::Keyboard::Space:
						return GAME_PLAY_SCENE;
						break;
				}
			}
		}

		float dt = clock.getElapsedTime().asSeconds();
		elapsedSeconds += dt;
		clock.restart();
		if (dt>3 && i==1){
			text.setString(L"Кто здесь?");
			sprite.setPosition(130,150);
	        text.setPosition(130+deltaX,150+deltaY);
			i++;
		}
		if (dt>6 && i==2){
			text.setString(L"Я...я... кто я?");
			sprite.setPosition(80,180);
	        text.setPosition(80+deltaX,180+deltaY);
			i++;
		}
		if (dt>9 && i==3){
			text.setString(L"Я ничего не помню");
			sprite.setPosition(130,80);
	        text.setPosition(130+deltaX,80+deltaY);
			i++;
		}
		if (dt>12 && i==4){
			text.setString(L"Где мы? Что произошло?");
			sprite.setScale(1.5,1);
			sprite.setPosition(50,220);
	        text.setPosition(50+deltaX,220+deltaY);
			i++;
		}
		if (dt>15 && i==5){
			sprite.setScale(1,1);
			text.setString(L"Ничего не вижу");
			sprite.setPosition(130,250);
	        text.setPosition(130+deltaX,250+deltaY);
			i++;
		}
		if (dt>18 && i==6){
			sprite.setScale(1.5,1);
			text.setString(L"Кто-нибудь, включите свет!");
			sprite.setPosition(20,150);
	        text.setPosition(20+deltaX,150+deltaY);
			i++;
		}

		window.clear();
		window.draw(sprite);
		window.draw(text);
		window.display();
	}

	return -1;
}
