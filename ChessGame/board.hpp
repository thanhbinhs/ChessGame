#ifndef BOARD_HPP
#define BOARD_HPP

#include "header.h"
class Board {
public:
    Board(sf::RenderWindow& window) :window(window) {}
    void chessBoard();
    void PrintSetting();
    void drawFirstBoxBlack(int x3, int y3);
    void drawSecondBoxBlack(int x4, int y4);
    void drawFirstBoxWhite(int x1, int y1);
    void drawSecondBoxWhite(int x2, int y2);
    void drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y);
    void drawBoxPos(int x, int y);
    void drawBoxCom(int x, int y);
    void drawBoxDeath(int x, int y);
    void drawBoxKingDeath(int x, int y);
    void drawCapture(int x, int n);
    void SetTime(bool checkTurn,sf::Time remainingTime1, sf::Time remainingTime2, bool FreezeTheClock2);
    void PrintPvP(bool checkTurn);
    void PvAi(bool checkTurn);
    sf::ConvexShape createRoundedRectangle(float width, float height, float radius, unsigned int cornerPoints);
private:
    sf::RenderWindow& window;
};

#endif // !BOARD_HPP