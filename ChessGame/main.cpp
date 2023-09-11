#include "header.h"


using namespace std;
using namespace sf;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML", sf::Style::Close);


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

int board[8][8] =
{ -5,-4,-3,-1,-2,-3,-4,-5,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  5, 4, 3, 1, 2, 3, 4, 5 };


int board_s[8][8] = {
-5,-4,-3,-1,-2,-3,-4,-5,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  5, 4, 3, 1, 2, 3, 4, 5
};

int checkPos[9][9];

int check_king[9][9];


sf::RectangleShape createButton() {
    sf::RectangleShape button;
    button.setSize(sizeBtn);
    return button;
}

void reloadPos(int checkPos[9][9]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            checkPos[i][j] = 0;
}

void drawBox(int x, int y) {
    sf::Texture draw_box;
    draw_box.loadFromFile("../Data/Image/death.png");
    sf::Sprite sp;
    sp.setTexture(draw_box);
    sp.setPosition(y * cellSize + SCREEN_MARGIN, x * cellSize + SCREEN_MARGIN);
    window.draw(sp);
}

void drawBoxWhite(int x, int y) {
    sf::Texture draw_box;
    draw_box.loadFromFile("../Data/Image/legalMove.png");
    sf::Sprite sp;
    sp.setTexture(draw_box);
    sp.setPosition(y * cellSize + SCREEN_MARGIN, x * cellSize + SCREEN_MARGIN);
    window.draw(sp);
}

void drawBoxKing(int x, int y) {
    sf::Texture draw_box;
    draw_box.loadFromFile("../Data/Image/kingDeath.png");
    sf::Sprite sp;
    sp.setTexture(draw_box);
    sp.setPosition(y * cellSize + SCREEN_MARGIN, x * cellSize + SCREEN_MARGIN);
    window.draw(sp);
}

void drawBoxPos(int x, int y) {
    sf::RectangleShape boxPos;
    boxPos.setFillColor(sf::Color(245, 236, 66, 100));
    boxPos.setSize(sizeBtn);
    boxPos.setPosition(dy * cellSize + SCREEN_MARGIN, dx * cellSize + SCREEN_MARGIN);
    window.draw(boxPos);
}

void chessBoard() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    const float boardSize = cellSize * 8;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(SCREEN_MARGIN, SCREEN_MARGIN);
    // Load font chữ 
    sf::Font customFont;
    if (!customFont.loadFromFile("../Data/Font/font_1.ttf")) {
        cout << "false to load font";
    }

    window.clear(sf::Color(179, 179, 179)); // Xóa nội dung cửa sổ
    // Vẽ bàn cờ
    sf::RectangleShape board(sf::Vector2f(boardSize, boardSize));
    board.setPosition(boardPosition);
    board.setFillColor(sf::Color::White); // Màu nền của bàn cờ
    window.draw(board);
    // Vẽ các ô trắng và đen trên bàn cờ
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square(sf::Vector2f(cellSize, cellSize));
            square.setPosition(boardPosition.x + i * cellSize, boardPosition.y + j * cellSize);

            // Thay đổi màu sắc xen kẽ của các ô
            if ((i + j) % 2 == 0) {
                square.setFillColor(sf::Color(248, 220, 180));
            }
            else {
                square.setFillColor(sf::Color(184, 140, 100));
            }
            window.draw(square);
        }
    }
    // Vẽ chữ cái để đánh dấu toạ độ quân cờ
    for (int i = 0; i < 8; i++) {
        sf::Text texti;
        texti.setFont(customFont); // Thiết lập font tùy chỉnh
        texti.setString(std::string(1, 'A' + i)); // Đặt nội dung chữ
        texti.setCharacterSize(24); // Kích thước chữ
        texti.setFillColor(sf::Color::White); // Màu chữ
        texti.setPosition(boardPosition.x + i * cellSize + SCREEN_MARGIN / 2, 15.f); // Vị trí chữ trên cửa sổ
        window.draw(texti);
    }
    // Vẽ số để đánh dấu toạ độ quân cờ
    for (int ij = 0; ij < 8; ij++) {
        sf::Text textij;
        textij.setFont(customFont); // Thiết lập font tùy chỉnh
        textij.setString(std::string(1, '1' + ij)); // Đặt nội dung chữ
        textij.setCharacterSize(24); // Kích thước chữ
        textij.setFillColor(sf::Color::White); // Màu chữ
        textij.setPosition(SCREEN_MARGIN / 2, boardPosition.y + ij * cellSize + SCREEN_MARGIN / 2); // Vị trí chữ trên cửa sổ
        window.draw(textij);
    }
    // Dòng kẻ tách phần setting và bàn cờ
    sf::RectangleShape line(sf::Vector2f(1060.f, 5.f));
    line.rotate(90.f);
    line.setPosition(640.0f + SCREEN_MARGIN * 2 + 5.f, 0.f);
    window.draw(line);

    sf::Text textMenu1;
    textMenu1.setFont(customFont); // Thiết lập font tùy chỉnh
    textMenu1.setString("Setting"); // Đặt nội dung chữ
    textMenu1.setCharacterSize(60); // Kích thước chữ
    textMenu1.setFillColor(sf::Color::White); // Màu chữ
    textMenu1.setPosition(745 + 44, SCREEN_MARGIN); // Vị trí chữ trên cửa sổ
    window.draw(textMenu1);
    sf::RectangleShape BoxInSetting2(sf::Vector2f(295, cellSize));
    BoxInSetting2.setFillColor(sf::Color(248, 220, 180));
    BoxInSetting2.setPosition(745, SCREEN_MARGIN);
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN && mousePosition.y <= SCREEN_MARGIN + cellSize)) {
        window.draw(BoxInSetting2);
        window.draw(textMenu1);
    }

}

void PrintSetting() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Font customFont1;
    if (!customFont1.loadFromFile("../Data/Font/font_1.ttf")) {
        cout << "false to load font";
    }
    sf::Text textMenu;
    textMenu.setFont(customFont1); // Thiết lập font tùy chỉnh
    textMenu.setString("Setting"); // Đặt nội dung chữ
    textMenu.setCharacterSize(60); // Kích thước chữ
    textMenu.setFillColor(sf::Color::White); // Màu chữ
    textMenu.setPosition(745 + 44, SCREEN_MARGIN); // Vị trí chữ trên cửa sổ

    sf::RectangleShape BoxInSetting(sf::Vector2f(295, cellSize * 4));
    BoxInSetting.setFillColor(sf::Color::Black);
    BoxInSetting.setPosition(745, SCREEN_MARGIN);
    //window.draw(BoxInSetting);

    sf::RectangleShape BoxInSetting2(sf::Vector2f(295, cellSize));
    BoxInSetting2.setFillColor(sf::Color(248, 220, 180));
    BoxInSetting2.setPosition(745, SCREEN_MARGIN);
    //window.draw(BoxInSetting2);
    sf::RectangleShape BoxIntextPvP(sf::Vector2f(295, cellSize));
    BoxIntextPvP.setFillColor(sf::Color(248, 220, 180));
    BoxIntextPvP.setPosition(745, SCREEN_MARGIN + cellSize);

    sf::RectangleShape BoxIntextPvAI(sf::Vector2f(295, cellSize));
    BoxIntextPvAI.setFillColor(sf::Color(248, 220, 180));
    BoxIntextPvAI.setPosition(745, SCREEN_MARGIN + cellSize * 2);

    sf::RectangleShape BoxIntextQuit(sf::Vector2f(295, cellSize));
    BoxIntextQuit.setFillColor(sf::Color(248, 220, 180));
    BoxIntextQuit.setPosition(745, SCREEN_MARGIN + cellSize * 3);



    //window.draw(textMenu);
    sf::Text textPvP;
    textPvP.setFont(customFont1); // Thiết lập font tùy chỉnh
    textPvP.setString("PvP"); // Đặt nội dung chữ
    textPvP.setCharacterSize(60); // Kích thước chữ
    textPvP.setFillColor(sf::Color::White); // Màu chữ
    textPvP.setPosition(SCREEN_WIDTH - SCREEN_MARGIN * 2 - 150 + 44.5, SCREEN_MARGIN + cellSize);
    //window.draw(textPvP);
    sf::Text textPvAI;
    textPvAI.setFont(customFont1);
    textPvAI.setString("PvAI");
    textPvAI.setCharacterSize(60);
    textPvAI.setFillColor(sf::Color::White);
    textPvAI.setPosition(SCREEN_WIDTH - SCREEN_MARGIN * 2 - 150 + 36.5, SCREEN_MARGIN + cellSize * 2);
    //window.draw(textPvAI);
    sf::Text textQuit;
    textQuit.setFont(customFont1);
    textQuit.setString("Quit");
    textQuit.setCharacterSize(60);
    textQuit.setFillColor(sf::Color::White);
    textQuit.setPosition(SCREEN_WIDTH - SCREEN_MARGIN * 2 - 150 + 42.5, SCREEN_MARGIN + cellSize * 3);
    //window.draw(textQuit);

    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN && mousePosition.y <= SCREEN_MARGIN + cellSize)) {
        window.draw(BoxInSetting);
        window.draw(BoxInSetting2);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textQuit);
    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize && mousePosition.y <= SCREEN_MARGIN + cellSize * 2)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextPvP);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textQuit);
    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 2 && mousePosition.y <= SCREEN_MARGIN + cellSize * 3)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextPvAI);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textQuit);
    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 3 && mousePosition.y <= SCREEN_MARGIN + cellSize * 4)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextQuit);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textQuit);
    }



}

void loadPosition() {
    int k = 0;
    int k_index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != 0)    k_index++;
        }
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 0 : 1;
            f[k].setTextureRect({ 80 * x, 80 * y, 80, 80 });
            f[k].setPosition(sizeBtn.x * j + SCREEN_MARGIN, sizeBtn.y * i + SCREEN_MARGIN);
            k++;
        }
    for (int i = k_index; i <= k; i++) {
        f[i].setPosition(-100, -100);
    }
}

void PositiveCastle(int x, int y, int checkPos[9][9]) {
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

void PositiveBishop(int x, int y, int checkPos[9][9]) {
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

void PositiveKnight(int x, int y, int checkPos[9][9])//xet 8 vi tri co the di
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

void PositiveKing(int x, int y, int checkPos[9][9])//xet 8 vi tri co the di
{
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
}

void PositivePawn(int x, int y, int checkPos[9][9])
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

void PositiveQueen(int x, int y, int checkPos[9][9]) {
    PositiveCastle(x, y, checkPos);
    PositiveBishop(x, y, checkPos);
}

void toCapture(int x, int y) {
    board[x][y] = (board[x][y] / 6) * 2;
}

void toCastling(int x, int y) {

}

bool falseChoose(int i, int j) {
    if (checkPos[i][j] == 0) {
        return false;
    }
    return true;
}

void checkKing(int check) {
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

int check_win() {
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

void returnGame() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = board_s[i][j];
        }
    }
}


void messWin(int check) {
    if (check == -1)  MessageBoxA(NULL, "White is Winner", "Winner", MB_OKCANCEL | MB_ICONEXCLAMATION);
    if (check == 1)  MessageBoxA(NULL, "Black is Winner", "Winner", MB_OKCANCEL | MB_ICONEXCLAMATION);

}

void showTurn(int check) {
    sf::Texture text_png;
    sf::Sprite chess_png;

    if (check == -1) {
        text_png.loadFromFile("../Data/Image/white_chess_rmbg.png");
        chess_png.setTexture(text_png);
        chess_png.setPosition(SCREEN_WIDTH - (chess_png.getGlobalBounds().width) * 1.2f, 200.f);
    }
    if (check == 1) {
        text_png.loadFromFile("../Data/Image/black_chess_rmbg.png");
        chess_png.setTexture(text_png);
        chess_png.setPosition(SCREEN_WIDTH - (chess_png.getGlobalBounds().width) * 1.5f, 200.f);
    }
    window.draw(chess_png);
}

int main() {
    bool checkareaSetting = false;
    bool checkareaPvP = false;
    bool checkareaPvAI = false;
    bool checkareaQuit = false;


    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("../Data/Image/chesses.png");
    f->setTexture(texture);
    for (int i = 0; i < 32; i++) {
        f[i].setTexture(texture);
    }

    //Sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../Data/Audio/moveSound.ogg"))     cout << "No Found Sound moveSound" << endl;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sf::Event event;

    sf::Text text_turn;
    int check_ = 0;

    loadPosition();

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



            if (click == 1 && isMouse == true) {
                dy = (pos.x - SCREEN_MARGIN) / 80;
                dx = (pos.y - SCREEN_MARGIN) / 80;

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
            if (click == 2) {
                sf::Vector2i pos_n = sf::Mouse::getPosition(window);
                int dy_n = (pos_n.x - SCREEN_MARGIN) / 80;
                int dx_n = (pos_n.y - SCREEN_MARGIN) / 80;
                if (!(dx_n == dx && dy_n == dy))
                    if (falseChoose(dx_n, dy_n)) {
                        board[dx_n][dy_n] = board[dx][dy];
                        board[dx][dy] = 0;
                        sound.play();

                        checkKing(checkTurn);

                        checkTurn = -checkTurn;

                        //To Capture 
                        if ((board[dx_n][dy_n] == 6 && dx_n == 0) || (board[dx_n][dy_n] == -6 && dx_n == 7)) {
                            toCapture(dx_n, dy_n);
                        }



                    }

                cout << "New Board: " << endl;
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        cout << board[i][j] << " ";
                    }
                    cout << endl;
                }

                loadPosition();
                reloadPos(checkPos);

                //reset
                isMouse = true;
                click = 0;
            }
            // check setting
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Kiểm tra xem chuột có nằm trong vùng setting không
                if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN && mousePosition.y <= SCREEN_MARGIN + cellSize)) {
                    checkareaSetting = true;
                    checkareaPvP = true;
                    bool checkareaPvAI = false;
                    bool checkareaQuit = false;
                    cout << "1";
                }
                else if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize && mousePosition.y <= SCREEN_MARGIN + cellSize * 2) && checkareaPvP) {
                    checkareaSetting = true;
                    cout << "2";
                }
                else if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 2 && mousePosition.y <= SCREEN_MARGIN + cellSize * 3) && checkareaPvP) {
                    checkareaSetting = true;
                    cout << "3";
                }
                else if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 3 && mousePosition.y <= SCREEN_MARGIN + cellSize * 4) && checkareaPvP) {
                    checkareaSetting = true;
                    cout << "4";
                }
                else
                {
                    checkareaSetting = false;
                    checkareaPvP = false;
                    bool checkareaPvAI = false;
                    bool checkareaQuit = false;
                }
            }

        }

        check_ = check_win();
        if (check_ == 1 || check_ == -1) {
            returnGame();
            loadPosition();
            checkTurn = -check_;
            messWin(check_);
        }

        window.clear(sf::Color(179, 179, 179));
        chessBoard();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (checkPos[i][j] == 2) drawBox(i, j);
                else if (checkPos[i][j] == 1)    drawBoxWhite(i, j);
                else if (checkPos[i][j] == 3)     drawBoxPos(i, j);
                if ((board[i][j] == -1 || board[i][j] == 1) && check_king[i][j] == 2) {
                    drawBoxKing(i, j);
                }
            }
        }

        showTurn(checkTurn);

        for (auto i : f) window.draw(i);
        // Vẽ setting
        if (checkareaSetting) {
            PrintSetting();
        }

        window.display();
    }
}