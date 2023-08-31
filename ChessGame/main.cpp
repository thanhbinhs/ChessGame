#include "header.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"SFML",sf::Style::Default);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	window.display();

}