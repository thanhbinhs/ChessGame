#include "Menu.h"
#include "GameManager.hpp"

using namespace std;
using namespace sf;


int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML", sf::Style::Close);
    window.setFramerateLimit(60);

    Menu menu;
    Game game(window);
    if (menu.returnMenu() == 1) game.Play();

}