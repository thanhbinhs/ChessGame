#include "GameManager.hpp"


void Game::reloadPos(int checkPos[9][9]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            checkPos[i][j] = 0;
}



void Game::PositiveCastle(int x, int y, int checkPos[9][9]) {
    for (int i = x + 1; i < 8; i++) {
        if (board[i][y] != 0) {
            if (board[i][y] * board[x][y] < 0) {
                checkPos[i][y] = 2;
            }
            break;
        }
        else {
            checkPos[i][y] = 1;
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if (board[i][y] != 0) {
            if (board[i][y] * board[x][y] < 0) {
                checkPos[i][y] = 2;
            }
            break;
        }
        else {
            checkPos[i][y] = 1;
        }
    }
    for (int j = y + 1; j < 8; j++) {
        if (board[x][j] != 0) {
            if (board[x][j] * board[x][y] < 0) {
                checkPos[x][j] = 2;
            }
            break;
        }
        else {
            checkPos[x][j] = 1;
        }
    }
    for (int j = y - 1; j >= 0; j--) {
        if (board[x][j] != 0) {
            if (board[x][j] * board[x][y] < 0) {
                checkPos[x][j] = 2;
            }
            break;
        }
        else {
            checkPos[x][j] = 1;
        }
    }

}

void Game::PositiveBishop(int x, int y, int checkPos[9][9]) {
    for (int i = x + 1, j = y + 1;
        (i < 8 && j < 8); i++, j++) {
        if (board[i][j] != 0) {
            if (board[i][j] * board[x][y] < 0) {
                checkPos[i][j] = 2;
            }
            break;
        }
        else {
            checkPos[i][j] = 1;
        }
    }
    for (int i = x + 1, j = y - 1;
        (i < 8 && j >= 0); i++, j--) {
        if (board[i][j] != 0) {
            if (board[i][j] * board[x][y] < 0)
                checkPos[i][j] = 2;
            break;
        }
        else {
            checkPos[i][j] = 1;
        }

    }
    for (int i = x - 1, j = y + 1;
        (i >= 0 && j < 8); i--, j++) {
        if (board[i][j] != 0) {
            if (board[i][j] * board[x][y] < 0)
                checkPos[i][j] = 2;
            break;
        }
        else {
            checkPos[i][j] = 1;
        }

    }
    for (int i = x - 1, j = y - 1;
        (i >= 0 && j >= 0); i--, j--) {
        if (board[i][j] != 0) {
            if (board[i][j] * board[x][y] < 0)
                checkPos[i][j] = 2;
            break;
        }
        else {
            checkPos[i][j] = 1;
        }

    }
}

void Game::PositiveKnight(int x, int y, int checkPos[9][9])//xet 8 vi tri co the di
{

    if (board[x + 2][y + 1] == 0 && x + 2 < 8 && y + 1 < 8)                                 checkPos[x + 2][y + 1] = 1;
    else if (board[x][y] * board[x + 2][y + 1] < 0 && x + 2 < 8 && y + 1 < 8)                       checkPos[x + 2][y + 1] = 2;
    if (board[x + 2][y - 1] == 0 && y - 1 >= 0 && x + 2 < 8)                                     checkPos[x + 2][y - 1] = 1;
    else if (board[x][y] * board[x + 2][y - 1] < 0 && y - 1 >= 0 && x + 2 < 8)                      checkPos[x + 2][y - 1] = 2;
    if (board[x - 2][y + 1] == 0 && x - 2 >= 0 && y + 1 < 8)                                checkPos[x - 2][y + 1] = 1;
    else if (board[x][y] * board[x - 2][y + 1] < 0 && x - 2 >= 0 && y + 1 < 8)                      checkPos[x - 2][y + 1] = 2;
    if (board[x - 2][y - 1] == 0 && x - 2 >= 0 && y - 1 >= 0)                               checkPos[x - 2][y - 1] = 1;
    else if (board[x][y] * board[x - 2][y - 1] < 0 && x - 2 >= 0 && y - 1 >= 0)                     checkPos[x - 2][y - 1] = 2;
    if (board[x + 1][y + 2] == 0 && x + 1 < 8 && y + 2 < 8)                                 checkPos[x + 1][y + 2] = 1;
    else if (board[x][y] * board[x + 1][y + 2] < 0 && x + 1 < 8 && y + 2 < 8)                       checkPos[x + 1][y + 2] = 2;
    if (board[x - 1][y + 2] == 0 && x - 1 >= 0 && y + 2 < 8)                                checkPos[x - 1][y + 2] = 1;
    else if (board[x][y] * board[x - 1][y + 2] < 0 && x - 1 >= 0 && y + 2 < 8)                      checkPos[x - 1][y + 2] = 2;
    if (board[x + 1][y - 2] == 0 && y - 2 >= 0 && x + 1 < 8)                                checkPos[x + 1][y - 2] = 1;
    else if (board[x][y] * board[x + 1][y - 2] < 0 && y - 2 >= 0 && x + 1 < 8)                      checkPos[x + 1][y - 2] = 2;
    if (board[x - 1][y - 2] == 0 && x - 1 >= 0 && y - 2 >= 0)                               checkPos[x - 1][y - 2] = 1;
    else if (board[x][y] * board[x - 1][y - 2] < 0 && x - 1 >= 0 && y - 2 >= 0)                     checkPos[x - 1][y - 2] = 2;
}

void Game::PositiveKing(int x, int y, int checkPos[9][9])//xet 8 vi tri co the di
{
    int checkColor = board[x][y];

    if (board[x + 1][y] == 0 && x + 1 < 8)                                          checkPos[x + 1][y] = 1;
    else if (board[x + 1][y] * board[x][y] < 0 && x + 1 < 8)                            checkPos[x + 1][y] = 2;
    if (board[x - 1][y] == 0 && x - 1 >= 0)                                         checkPos[x - 1][y] = 1;
    else if (board[x - 1][y] * board[x][y] < 0 && x - 1 >= 0)                           checkPos[x - 1][y] = 2;
    if (board[x + 1][y + 1] == 0 && x + 1 < 8 && y + 1 < 8)                         checkPos[x + 1][y + 1] = 1;
    else if (board[x + 1][y + 1] * board[x][y] < 0 && x + 1 < 8 && y + 1 < 8)           checkPos[x + 1][y + 1] = 2;
    if (board[x - 1][y + 1] == 0 && x - 1 >= 0 && y + 1 < 8)                        checkPos[x - 1][y + 1] = 1;
    else if (board[x - 1][y + 1] * board[x][y] < 0 && x - 1 >= 0 && y + 1 < 8)          checkPos[x - 1][y + 1] = 2;
    if (board[x][y + 1] == 0 && y + 1 < 8)                                          checkPos[x][y + 1] = 1;
    else if (board[x][y + 1] * board[x][y] < 0 && y + 1 < 8)                            checkPos[x][y + 1] = 2;
    if (board[x - 1][y - 1] == 0 && x - 1 >= 0 && y - 1 >= 0)                       checkPos[x - 1][y - 1] = 1;
    else if (board[x - 1][y - 1] * board[x][y] < 0 && x - 1 >= 0 && y - 1 >= 0)         checkPos[x - 1][y - 1] = 2;
    if (board[x + 1][y - 1] == 0 && x + 1 < 8 && y - 1 >= 0)                        checkPos[x + 1][y - 1] = 1;
    else if (board[x + 1][y - 1] * board[x][y] < 0 && x + 1 < 8 && y - 1 >= 0)          checkPos[x + 1][y - 1] = 2;
    if (board[x][y - 1] == 0 && y - 1 >= 0)                                         checkPos[x][y - 1] = 1;
    else if (board[x][y - 1] * board[x][y] < 0 && y - 1 >= 0)                           checkPos[x][y - 1] = 2;
    if (board[x][y + 3] == checkColor * 5 && board[x][y + 1] == 0 && board[x][y + 2] == 0) {
        if (checkCastlingWhite == true && checkColor == 1)  checkPos[7][6] = 1;
        if (checkCastlingBlack == true && checkColor == -1) checkPos[0][6] = 1;
    }
}

void Game::PositivePawn(int x, int y, int checkPos[9][9])
{
    int k = board[x][y] / abs(board[x][y]); // 1 hoac -1 
    if (x == 1 || x == 6) {
        if (board[x - k][y] == 0 && board[x - 2 * k][y] == 0 && x - 2 * k >= 0 && x - 2 * k < 8) {
            checkPos[x - 2 * k][y] = 1;
        }
    }
    if (board[x - k][y] == 0 && x - k >= 0 && x - k < 8) checkPos[x - k][y] = 1;
    if (board[x - k][y + 1] * board[x][y] < 0 && x - k >= 0 && x - k < 8 && y + 1 < 8) checkPos[x - k][y + 1] = 2;
    if (board[x - k][y - 1] * board[x][y] < 0 && x - k >= 0 && y - 1 < 8 && x - k >= 0) checkPos[x - k][y - 1] = 2;
}

void Game::PositiveQueen(int x, int y, int checkPos[9][9]) {
    PositiveCastle(x, y, checkPos);
    PositiveBishop(x, y, checkPos);
}

void Game::toCapture(int x, int y,int board[8][8]) {
    sf::Event anotherEvent;
    bool check = true;
    if (window.pollEvent(anotherEvent)) {
        if (anotherEvent.type == sf::Event::MouseButtonPressed) {
            if (anotherEvent.key.code == sf::Mouse::Left) {
                sf::Vector2i posCap = sf::Mouse::getPosition(window);
                cout << "PosCap: " << posCap.x << endl;
                int dy = (int)(posCap.x - SCREEN_MARGIN) / 80;
                int dx = (int)(posCap.y - SCREEN_MARGIN) / 80;
                cout << "dy: " << dx << endl;
                if (board[x][y] == 6) {
                    if (dx == 0) board[x][y] = (board[x][y] / 6) * 2;
                    if (dx == 1) board[x][y] = (board[x][y] / 6) * 3;
                    if (dx == 2) board[x][y] = (board[x][y] / 6) * 4;
                    if (dx == 3) board[x][y] = (board[x][y] / 6) * 5;
                    check = false;
                }
                else if(board[x][y] == -6 ){
                    if (dx == 7) board[x][y] = (board[x][y] / 6) * 2;
                    if (dx == 6) board[x][y] = (board[x][y] / 6) * 3;
                    if (dx == 5) board[x][y] = (board[x][y] / 6) * 4;
                    if (dx == 4) board[x][y] = (board[x][y] / 6) * 5;
                    check = false;
                }
            }
        }
    }
}

void Game::toCastling(int x, int y, int dx, int dy) {
    int checkColor = board[x][y];
    board[x][y] = 0;
    board[dx][dy] = checkColor * 1;
    board[dx][dy - 1] = checkColor * 5;
    board[dx][dy + 1] = 0;
}

bool Game::falseChoose(int i, int j) {
    if (checkPos[i][j] == 0) {
        return false;
    }
    return true;
}

void Game::checkKing(int check) {
    reloadPos(check_king);
    if (check == -1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] > 0) {
                    if (board[i][j] == 6)    PositivePawn(i, j, check_king);
                    if (board[i][j] == 5)    PositiveCastle(i, j, check_king);
                    if (board[i][j] == 4)     PositiveKnight(i, j, check_king);
                    if (board[i][j] == 3)    PositiveBishop(i, j, check_king);
                    if (board[i][j] == 2)       PositiveQueen(i, j, check_king);
                    if (board[i][j] == 1)    PositiveKing(i, j, check_king);
                }
            }
        }

    }
    else if (check == 1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] < 0) {
                    if (board[i][j] == -6)    PositivePawn(i, j, check_king);
                    if (board[i][j] == -5)    PositiveCastle(i, j, check_king);
                    if (board[i][j] == -4)     PositiveKnight(i, j, check_king);
                    if (board[i][j] == -3)    PositiveBishop(i, j, check_king);
                    if (board[i][j] == -2)       PositiveQueen(i, j, check_king);
                    if (board[i][j] == -1)    PositiveKing(i, j, check_king);
                }
            }
        }
    }

}

bool Game::bool_king(int check) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == check && check_king[i][j] == 2) {
                return false;
            }
        }
    }
    return true;
}

int Game::check_win() {
    bool checkWhite = false;
    bool checkBlack = false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == -1) checkBlack = true;
            if (board[i][j] == 1)   checkWhite = true;
        }
    }
    if (!checkWhite) return 1;
    if (!checkBlack)  return -1;
    else return 0;
}

void Game::returnGame() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = board_s[i][j];
        }
    }
}

void Game::disableTurn()
{

}


void Game::messWin(int check) {
    if (check == -1)  MessageBoxA(NULL, "White is Winner", "Winner", MB_OKCANCEL | MB_ICONEXCLAMATION);
    if (check == 1)  MessageBoxA(NULL, "Black is Winner", "Winner", MB_OKCANCEL | MB_ICONEXCLAMATION);

}



void Game::Play() {
    bool checkareaSetting = false;
    bool checkareaPvP = false;
    bool checkareaPvAI = false;
    bool checkareaQuit = false;

    Board board_(window);

    board_.loadTexture("../Data/Image/chesses.png");
        // Handle texture loading failure



    //Sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../Data/Audio/moveSound.ogg"))     cout << "No Found Sound moveSound" << endl;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sf::Event event;

    sf::Text text_turn;
    int check_ = 0;

    board_.loadPosition(board);

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    pos = sf::Mouse::getPosition(window);
                    click++;
                }
            }

            bool checkSelection = false;

            // Kiểm tra xem chuột có nằm trong vùng setting không
            if ((pos.x >= 745 && pos.x <= SCREEN_WIDTH) && (pos.y >= SCREEN_MARGIN && pos.y <= SCREEN_MARGIN + cellSize)) {
                checkareaSetting = true;
                checkareaPvP = true;
                bool checkareaPvAI = false;
                cout << "1";
                click = 0;
            }
            else if ((pos.x >= 745 && pos.x <= SCREEN_WIDTH) && (pos.y >= SCREEN_MARGIN + cellSize && pos.y <= SCREEN_MARGIN + cellSize * 2) && checkareaPvP) {
                checkareaSetting = true;
                cout << "2";
                click = 0;

            }
            else if ((pos.x >= 745 && pos.x <= SCREEN_WIDTH) && (pos.y >= SCREEN_MARGIN + cellSize * 2 && pos.y <= SCREEN_MARGIN + cellSize * 3) && checkareaPvP) {
                checkareaSetting = true;
                cout << "3";
                click = 0;

            }

            else
            {
                checkareaSetting = false;
                checkareaPvP = false;
                bool checkareaPvAI = false;
            }



            if (click == 1 && isMouse == true) {
                dy = (int)(pos.x - SCREEN_MARGIN) / 80;
                dx = (int)(pos.y - SCREEN_MARGIN) / 80;
                cout << "Point:" << dx << " " << dy << endl;
                if (dy >= 0 && dy < 8) {

                    if (board[dx][dy] * checkTurn < 0) {
                        isMouse = false;
                        checkPos[dx][dy] = 3;
                        if (board[dx][dy] == -5 || board[dx][dy] == 5) {
                            PositiveCastle(dx, dy, checkPos);
                        }
                        if (board[dx][dy] == -3 || board[dx][dy] == 3) {
                            PositiveBishop(dx, dy, checkPos);
                        }
                        if (board[dx][dy] == -4 || board[dx][dy] == 4) {
                            PositiveKnight(dx, dy, checkPos);
                        }
                        if (board[dx][dy] == -2 || board[dx][dy] == 2) {
                            PositiveQueen(dx, dy, checkPos);
                        }
                        if (board[dx][dy] == -1 || board[dx][dy] == 1) {
                            PositiveKing(dx, dy, checkPos);
                        }
                        if (board[dx][dy] == -6 || board[dx][dy] == 6) {
                            PositivePawn(dx, dy, checkPos);
                        }

                    }
                    else {
                        click = 0;
                    }
                }
                else {
                    click = 0;
                }

            }
            if (click == 2) {
                sf::Vector2i pos_n = sf::Mouse::getPosition(window);
                dy_n = (int)(pos_n.x - SCREEN_MARGIN) / 80;
                dx_n = (int)(pos_n.y - SCREEN_MARGIN) / 80;
                int index = board[dx][dy];
                int index_2 = board[dx_n][dy_n];
                if (!(dx_n == dx && dy_n == dy))
                    if (falseChoose(dx_n, dy_n)) {
                        if (dx == 7 && dy == 7)    checkCastlingWhite = false;
                        if (dx == 0 && dy == 7)      checkCastlingBlack = false;
                        if (checkCastlingWhite == true && dx == 7 && dy == 4 && dx_n == 7 && dy_n == 6) {
                            toCastling(dx, dy, dx_n, dy_n);
                        }
                        else if (checkCastlingBlack == true && dx == 0 && dy == 4 && dx_n == 0 && dy_n == 6) {
                            toCastling(dx, dy, dx_n, dy_n);

                        }
                        else {
                            board[dx_n][dy_n] = board[dx][dy];
                            board[dx][dy] = 0;
                        }
                        sound.play();
                        checkKing(-checkTurn);
                        if (!bool_king(-checkTurn)) {
                            board[dx_n][dy_n] = index_2;
                            board[dx][dy] = index;
                        }
                        else {
                            checkKing(checkTurn);
                            checkTurn = -checkTurn;
                        }
                        //To Capture 
                        
                    }
                cout << "New Board: " << endl;
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        cout << board[i][j] << " ";
                    }
                    cout << endl;
                }

                board_.loadPosition(board);
                reloadPos(checkPos);

                //reset
                isMouse = true;
                click = 0;
            }

        }

        while ((board[dx_n][dy_n] == 6 && dx_n == 0) || (board[dx_n][dy_n] == -6 && dx_n == 7)) {
            board_.drawCapture("../Data/Image/chesses.png", dx_n, dy_n, board);
            toCapture(dx_n, dy_n, board);
            board_.loadPosition(board);
            window.display();
        }

        check_ = check_win();
        if (check_ == 1 || check_ == -1) {
            returnGame();
            board_.loadPosition(board);
            checkTurn = -check_;
            messWin(check_);
        }



        board_.drawBoard(checkPos, board, check_king,dx,dy);

        if (checkareaSetting) {
            board_.PrintSetting();
        }


        board_.Quit();

        window.display();
    }
}

