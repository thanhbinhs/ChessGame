
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

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 690;
const float SCREEN_MARGIN = 50.0f;

const sf::Vector2f sizeBtn(80, 80);

const sf::Vector2f offset(40, 40);
static sf::Sprite f[33]; //mang lưu các quân cờ
static sf::Vector2i pos;
static int dx = 0;
static int dy = 0;
static int click = 0;
static bool isMouse = true;
static int checkTurn = -1;
static bool checkCastling[5];
static float cellSize = 80.0f;


#endif // !HEADER_H