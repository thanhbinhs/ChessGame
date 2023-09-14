#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include"header.h"
#include"board.hpp"


class Game {
public:
    Game(sf::RenderWindow& window) : window(window){}
    void PositiveCastle(int x, int y, int checkPos[9][9]);
    void PositiveKnight(int x, int y, int checkPos[9][9]);
    void PositiveBishop(int x, int y, int checkPos[9][9]);
    void PositiveKing(int x, int y, int checkPos[9][9]);
    void PositiveQueen(int x, int y, int checkPos[9][9]);
    void PositivePawn(int x, int y, int checkPos[9][9]);
    void checkKing(int check);
    void reloadPos(int checkPos[9][9]);
    void toCapture(int x, int y,int board[8][8]);
    void toCastling(int x, int y, int dx, int dy);
    bool falseChoose(int i, int j);
    void returnGame();
    void disableTurn();
    int check_win();
    void checkSetting();
    bool bool_king(int check);
    void messWin(int check);
    void Play();
private:
    sf::RenderWindow& window;
    int dx = 0;
    int dy = 0;
    int dy_n = 0;
    int dx_n = 0;
    bool checkCastlingWhite = true;
    bool checkCastlingBlack = true;
    sf::Sprite f[33];


    bool checkareaSetting = false;
};


#endif // !GAME_MANAGER_H


