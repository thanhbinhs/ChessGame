#include"GameManager.hpp"

int main()
{
    //FreeConsole();
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Chess Game", sf::Style::Close);
    GameManager gm(window);
    gm.Play();

}

