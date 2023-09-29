#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include"header.h"
#include "board.hpp"

class GameManager
{
public:
    GameManager(RenderWindow& window) :window(window) {}
    Vector2f positiveMove[32];//vi tri cac nuoc co the di chuyen
    int positiveCount;// so nuoc co the di chuyen
    stack<Vector2f> posS;//luu tru vi tri cac nuoc di
    stack<int> nS;//luu tru index cua quan di
    void move(int n, Vector2f oldPos, Vector2f newPos);//ham danh co
    void Undo();//ham quay lai
    void Create();
    void Play();// choi: moi thao tac o day
    void resetGlobal();
    void resetMatrix(int a[9][9]);

    void PositiveCastle(int n, int x, int y, int grid[9][9]);//tim cac nuoc co the di cua Quan Xe
    void PositiveBishop(int n, int x, int y, int grid[9][9]);
    void PositiveKnight(int n, int x, int y, int grid[9][9]);
    void PositiveKing(int n, int x, int y, int grid[9][9]);
    void PositivePawn(int n, int x, int y, int grid[9][9]);
    void toCapture(int n, int y);
    void IncreasePositive(int i, int j);//tang so nuoc co the di
    void PositiveMoving(int n);//tim cac nuoc co the di ung voi index n
    void Personal(int click, int n, sf::Vector2i pos, sf::Vector2f oldPos, sf::Vector2f newPos, int count, sf::Sound sound, bool LuotChoi);
    int checkWin();
    //AI
    int CostMove();//gia tri diem cua toan bo ban co ung voi gia tri moi quan
    //int Minimax(int depth,bool luot);// Chien luoc Minimax
    int Alpha_Beta(int depth, bool luot, int alpha, int beta);//cat tia alpha beta
    Vector2f getNextMove(bool luot);// tra ve nuoc di tot nhat theo chien luoc phia tren
    void computer(sf::Vector2f newPos, sf::Vector2f oldPos, bool LuotChoi);

    void MessageBoxCom(int check);

private:
    sf::RenderWindow& window;
    sf::Time delay = sf::milliseconds(500);
    int x_com = 0;
    int y_com = 0;
    bool check_com = false;
    bool mess = false;
<<<<<<< HEAD
    bool check_setTime = false;
=======
    bool checkWhite = true;
    bool checkBlack = true;
>>>>>>> c8f3211cd6a7ebdf79e377bd26db922f9d159a4c
};


#endif