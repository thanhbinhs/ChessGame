#pragma once
#ifndef BOARD_H
#define BOARD_H

#include"header.h"

class Board {
public:
    Board(sf::RenderWindow& window) : window(window){}
    bool loadTexture(const std::string& filename);
    void loadPosition(int board[8][8]);
    void chessBoard();
    void drawBoxPos(int x, int y,int dx, int dy);
    void drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y);
    void drawBoxDeath(int x, int y);
    void drawBoxDeathKing(int x, int y);
    void drawBoxLegalMove(int x, int y);
    void drawCapture(const std::string& filename, int x, int y);
    void drawBoard(int checkPos[9][9], int board[8][8], int check_king[9][9],  int dx, int dy);
    void showTurn(int check);
    void Quit();
    void PrintSetting();
    sf::RectangleShape createButton();
private:
    sf::RenderWindow& window;
    sf::Texture texture;
};


#endif // !BOARD_H

