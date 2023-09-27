#ifndef BOARD_HPP
#define BOARD_HPP

#include "header.h"
class Board {
public:
    Board(sf::RenderWindow &window):window(window){}
    void chessBoard();
    void PrintSetting();
    void drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y);
    void drawBoxPos(int x, int y);
    void drawBoxDeath(int x,int y);
    void drawBoxKingDeath(int x, int y);
    void drawCapture(int n);
    void SetTime();
    sf::ConvexShape createRoundedRectangle(float width, float height, float radius, unsigned int cornerPoints);
private:
    sf::RenderWindow& window;
};

#endif // !BOARD_HPP