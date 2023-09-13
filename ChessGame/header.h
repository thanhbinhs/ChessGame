
#ifndef HEADER_H
#define HEADER_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<Windows.h>
#include<string>
#include<iostream>
#include<stack>
#include<math.h>
#include<cstdbool>


using namespace std;
using namespace sf;


const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 690;
const float SCREEN_MARGIN = 50.0f;

const sf::Vector2f sizeBtn(80, 80);

const sf::Vector2f offset(40, 40);

static sf::Sprite f[33];   //mang lưu các quân cờ
static sf::Vector2i pos;

static sf::Font font;


static int click = 0;
static bool isMouse = true;
static int checkTurn = -1;
static bool checkCastling[5];
static float cellSize = 80.0f;

static int board[8][8] =
{ -5,-4,-3,-2,-1,-3,-4,-5,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  5, 4, 3, 2, 1, 3, 4, 5 };


static int board_s[8][8] = {
-5,-4,-3,-2,-1,-3,-4,-5,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  5, 4, 3, 2, 1, 3, 4, 5
};

static int checkPos[9][9];

static int check_king[9][9];





enum WhiteChesses {
    VUA = 1,
    HAU,
    TUONG,
    MA,
    XE,
    TOT
};

enum BlackChesses {
    TOTDEN = -6,
    XEDEN,
    MADEN,
    TUONGDEN,
    HAUDEN,
    VUADEN
};







#endif // !HEADER_H
