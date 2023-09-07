#pragma once
#ifndef HEADER_H
#define HEADER_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<stack>
#include<math.h>
#include<cstdbool>

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 690;
const float SCREEN_MARGIN = 50.0f;

const sf::Vector2f sizeBtn(80, 80);

static sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML", sf::Style::Close);

#endif // !HEADER_H



