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
    void ResetBox(int &a, int &b);
    //AI
    int CostMove();//gia tri diem cua toan bo ban co ung voi gia tri moi quan
    //int Minimax(int depth,bool luot);// Chien luoc Minimax
    int Alpha_Beta(int depth, bool luot, int alpha, int beta);//cat tia alpha beta
    Vector2f getNextMove(bool luot);// tra ve nuoc di tot nhat theo chien luoc phia tren
    void computer(sf::Vector2f newPos, sf::Vector2f oldPos, bool LuotChoi);
    void comCapture(sf::Vector2f newPos, int c, int n);
    void Message_Box(int check);
    int CheckEndTime(sf::Time Remainingtime1, sf::Time Remainingtime2);

private:
    sf::RenderWindow& window;
    sf::Time delay = sf::milliseconds(0);
    int x_com = 0;
    int y_com = 0;
    bool check_com = false;
    bool mess = false;

    bool check_setTime = false;
    bool checkWhite = true;
    bool checkBlack = true;

    sf::Vector2f new_;
    int capture_int;

    bool checkareaSetting = false;
    bool checkareaPvP = false;
    bool checkareaAI = false;
    bool checkareaSetTime = false;
    int cellSize = size_;

    int Menu = 0;
    int menu = 0;
    int com = 0;

    //Setime 
    
    // Clock 1 Run First
    bool FreezeTheClock2 = true;
    bool StartTime = false;

    sf::Clock clock1;
    sf::Time countdownTime1 = sf::seconds(900);
    bool Stop1 = false;
    bool ContinueremainingTime1 = true;
    bool Continue1 = false;
    sf::Time remainingTime1;
    sf::Time remainingStop1;

    // Clock2
    sf::Clock clock2;
    sf::Time countdownTime2 = sf::seconds(900);
    bool Stop2 = false;
    bool ContinueremainingTime2 = false;
    bool Continue2 = false;
    bool BurnTheClock2 = false;
    sf::Time remainingTime2;
    sf::Time remainingStop2;
    
    // Box, Print Box
    sf::Vector2i mousePositionBlackFirst;
    sf::Vector2i mousePositionBlackSecond;
    sf::Vector2i mousePositionWhiteFirst;
    sf::Vector2i mousePositionWhiteSecond;
    int x1;
    int x2;
    int x3;
    int x4;
    int y1;
    int y2;
    int y3;
    int y4;
    bool FirstClickWhite = false;
    bool SecondClickWhite = false;
    bool FirstClickBlack = false;
    bool SecondClickBlack = false;
    bool PrintBox = false;
    bool resetBox = false;
    bool resetBoxCom = false;
    bool resetBox3 = false;
    bool resetBox4 = false;
};


#endif