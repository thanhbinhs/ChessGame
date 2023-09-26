#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<math.h>
#include<time.h>
#include<stack>
#include<algorithm>// min, max
#include<cstdbool>



using namespace sf;
using namespace std;

static int size_ = 80;
static Vector2f offset(50,50);
static Vector2f sizeBtn(80, 80);

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 690;
const float SCREEN_MARGIN = 50.0f;

static int board[8][8] =
{ -5, -4, -3, -2, -1, -3, -4, -5,
    - 6, -6, -6, -6, -6, -6, -6, -6,

0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
6,6,6,6,6,6,6,6,
5,4,3,2,1,3,4,5
};

static int checkPos[9][9];

typedef struct QuanCo
{
    Sprite s;
    int index, cost;
    int global;
};

static QuanCo f[33]; //mang luu cac quan co



#endif