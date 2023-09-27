
﻿#include"header.h"
#include"GameManager.hpp"

int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Chess! Alpha Beta Pruning");
    GameManager gm(window);
    gm.Play();

}

