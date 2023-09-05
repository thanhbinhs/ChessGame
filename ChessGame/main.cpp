#include "header.h"

using namespace std;

sf::RectangleShape createButton() {
	sf::RectangleShape button;
	button.setSize(sizeBtn);
	return button;
}

int a[8][8];

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"SFML",sf::Style::Default);


	sf::Texture texture;
	texture.loadFromFile("../Data/Image/chesses.png");
	sf::Sprite sprite(texture);
	sprite.setTextureRect({ 0,0,80,80 });

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			window.clear(sf::Color::White);

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					sf::RectangleShape button = createButton();
					button.setPosition(i * sizeBtn.x, j * sizeBtn.y);
					if ((i + j) % 2 == 0)	button.setFillColor(sf::Color(248,220,180));
					else
					{
						button.setFillColor(sf::Color(184, 140, 100));
					}
					window.draw(button);
				}
			}

		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 8; j++) {
				if (i == 0) {
					if (j == 0 or j == 7)	sprite.setTextureRect({ 80 * 4,0,80,80 });
					if (j == 1 or j == 6)	sprite.setTextureRect({ 80 * 3,0,80,80 });
					if (j == 2 or j == 5)	sprite.setTextureRect({ 80 * 2,0,80,80 });
					if (j == 3)				sprite.setTextureRect({ 80,0,80,80 });
					if (j == 4)				sprite.setTextureRect({ 0,0,80,80 });
				}
				else {
					sprite.setTextureRect({ 80 * 5,0,80,80 });
				}

				sprite.setPosition(j * 80, i * 80);
				window.draw(sprite);
			}
		}

		for (int i = 6; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i == 7) {
					if (j == 0 or j == 7)	sprite.setTextureRect({ 80 * 4,80,80,80 });
					if (j == 1 or j == 6)	sprite.setTextureRect({ 80 * 3,80,80,80 });
					if (j == 2 or j == 5)	sprite.setTextureRect({ 80 * 2,80,80,80 });
					if (j == 3)				sprite.setTextureRect({ 80,80,80,80 });
					if (j == 4)				sprite.setTextureRect({ 0,80,80,80 });
				}
				else {
					sprite.setTextureRect({ 80 * 5,80,80,80 });
				}

				sprite.setPosition(j * 80, i * 80);
				window.draw(sprite);
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
			cout << pos.x << " " << pos.y << endl;

		}

		window.display();
	}


}