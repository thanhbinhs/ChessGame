#pragma once
#ifndef HEADER_H
#define HEADER_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<stack>

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 690;
static sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML", sf::Style::Close);

const sf::Vector2f sizeBtn(80, 80);


#endif // !HEADER_H



