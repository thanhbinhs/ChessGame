#include "board.hpp"

sf::RectangleShape Board::createButton() {
    sf::RectangleShape button;
    button.setSize(sizeBtn);
    return button;
}

bool Board::loadTexture(std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        filename.erase(filename.begin(), filename.begin() + 1);
        texture.loadFromFile(filename);
    }

    f->setTexture(texture);
    for (int i = 0; i < 32; i++) {
        f[i].setTexture(texture);
    }
    return true; // Successfully loaded the texture
}


void Board::drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y) {
    sprite.setTexture(draw_box);
    sprite.setPosition(y * cellSize + SCREEN_MARGIN, x * cellSize + SCREEN_MARGIN);
    window.draw(sprite);
}


void Board::drawBoxDeath(int x, int y) {
    sf::Texture draw_box;
    if (!draw_box.loadFromFile("../Data/Image/death.png"))
        draw_box.loadFromFile("Data/Image/death.png");
    sf::Sprite sp;
    drawBox(sp, draw_box, x, y);
}

void Board::drawBoxLegalMove(int x, int y) {
    sf::Texture draw_box;
    if(!draw_box.loadFromFile("../Data/Image/legalMove.png"))
    draw_box.loadFromFile("Data/Image/legalMove.png");

    sf::Sprite sp;
    drawBox(sp, draw_box, x, y);
}

sf::ConvexShape Board::createRoundedRectangle(float width, float height, float radius, unsigned int cornerPoints) {
    sf::ConvexShape shape;
    shape.setPointCount(4 * cornerPoints);

    float angleIncrement = 90.0f / (cornerPoints - 1);
    float currentAngle = 0.0f;

    for (unsigned int i = 0; i < 4 * cornerPoints; i += 4) {
        // Calculate the coordinates for each corner
        float x1 = width - radius + cos(currentAngle * 3.14159265f / 180) * radius;
        float y1 = height - radius + sin(currentAngle * 3.14159265f / 180) * radius;

        float x2 = radius - cos(currentAngle * 3.14159265f / 180) * radius;
        float y2 = height - radius + sin(currentAngle * 3.14159265f / 180) * radius;

        float x3 = radius - cos(currentAngle * 3.14159265f / 180) * radius;
        float y3 = radius - sin(currentAngle * 3.14159265f / 180) * radius;

        float x4 = width - radius + cos(currentAngle * 3.14159265f / 180) * radius;
        float y4 = radius - sin(currentAngle * 3.14159265f / 180) * radius;

        shape.setPoint(i, sf::Vector2f(x1, y1));
        shape.setPoint(i + 1, sf::Vector2f(x2, y2));
        shape.setPoint(i + 2, sf::Vector2f(x3, y3));
        shape.setPoint(i + 3, sf::Vector2f(x4, y4));

        currentAngle += angleIncrement;
    }

    return shape;
}

void Board::drawCapture( std::string& filename,int x,int y,int board[8][8])
{
    sf::Sprite ct[4];
    if (!texture.loadFromFile(filename)) {
        filename.erase(filename.begin(), filename.begin() + 1);
        texture.loadFromFile(filename);
    }
    ct->setTexture(texture);
    for (int i = 0; i < 4; i++) {
        ct[i].setTexture(texture);
    }
    sf::ConvexShape shape = createRoundedRectangle(cellSize, cellSize * 4, 15, 40);
    shape.setFillColor(sf::Color(230, 230, 230));
    

    if (board[x][y] == 6) {
        for (int i = 0; i < 4; i++) {
            ct[i].setTextureRect({ 80 * (i + 1),0,80,80 });
            ct[i].setPosition(cellSize * y + SCREEN_MARGIN, SCREEN_MARGIN + cellSize * (i +1));
        }
        shape.setPosition(cellSize * y + SCREEN_MARGIN, SCREEN_MARGIN + cellSize );
    }
    else if(board[x][y] == -6){
        for (int i = 3; i >= 0; i--) {
            ct[i].setTextureRect({ 80 * (i + 1),80,80,80 });
            ct[i].setPosition(cellSize * y + SCREEN_MARGIN, SCREEN_HEIGHT - ( cellSize * (i + 2)));
        }
        shape.setPosition(cellSize * y + SCREEN_MARGIN, SCREEN_HEIGHT - ( cellSize * 5));
    }

    window.draw(shape);
    for (auto i : ct)  window.draw(i);
}

void Board::drawBoxDeathKing(int x, int y) {
    sf::Texture draw_box;
    if (!draw_box.loadFromFile("../Data/Image/kingDeath.png"))
        draw_box.loadFromFile("Data/Image/kingDeath.png");

    sf::Sprite sp;
    drawBox(sp, draw_box, x, y);
}

void Board::drawBoxPos(int x, int y,int dx,int dy) {
    sf::RectangleShape boxPos;
    boxPos.setFillColor(sf::Color(245, 236, 66, 100));
    boxPos.setSize(sizeBtn);
    boxPos.setPosition(dy * cellSize + SCREEN_MARGIN, dx * cellSize + SCREEN_MARGIN);
    window.draw(boxPos);
}

void Board::loadPosition(int board[8][8]) {
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
        f[i].setTextureRect({ 0,0,0,0 });
    }
}

void Board::chessBoard() {

    const float boardSize = cellSize * 8;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(SCREEN_MARGIN, SCREEN_MARGIN);
    // Load font chữ 
    if (!font.loadFromFile("../Data/Font/font_1.ttf")) {
        font.loadFromFile("Data/Font/font_1.ttf");
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
        texti.setFont(font); // Thiết lập font tùy chỉnh
        texti.setString(std::string(1, 'A' + i)); // Đặt nội dung chữ
        texti.setCharacterSize(24); // Kích thước chữ
        texti.setFillColor(sf::Color::White); // Màu chữ
        texti.setPosition(boardPosition.x + i * cellSize + SCREEN_MARGIN / 2, 15.f); // Vị trí chữ trên cửa sổ
        window.draw(texti);
    }
    // Vẽ số để đánh dấu toạ độ quân cờ
    for (int ij = 0; ij < 8; ij++) {
        sf::Text textij;
        textij.setFont(font); // Thiết lập font tùy chỉnh
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
    // Chữ edit 
    sf::Text textMenu;
    textMenu.setFont(font); // Thiết lập font tùy chỉnh
    textMenu.setString("Setting"); // Đặt nội dung chữ
    textMenu.setCharacterSize(60); // Kích thước chữ
    textMenu.setFillColor(sf::Color::White); // Màu chữ
    textMenu.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2f, SCREEN_MARGIN); // Vị trí chữ trên cửa sổ
    window.draw(textMenu);

}


//Draw Turn Image
void Board::showTurn(int check) {
    sf::Texture text_png;
    sf::Sprite chess_png;

    if (check == -1) {
        if (!text_png.loadFromFile("../Data/Image/white_chess_rmbg.png"))
            text_png.loadFromFile("Data/Image/white_chess_rmbg.png");
        chess_png.setTexture(text_png);
        chess_png.setPosition(SCREEN_WIDTH - (chess_png.getGlobalBounds().width) * 1.2f, 200.f);
    }
    if (check == 1) {
        if (!text_png.loadFromFile("../Data/Image/black_chess_rmbg.png"))
            text_png.loadFromFile("Data/Image/black_chess_rmbg.png");
        chess_png.setTexture(text_png);
        chess_png.setPosition(SCREEN_WIDTH - (chess_png.getGlobalBounds().width) * 1.5f, 200.f);
    }
    window.draw(chess_png);
}

void Board::drawBoard(int checkPos[9][9],int board[8][8],int check_king[9][9],int dx,int dy) {
    window.clear(sf::Color(179, 179, 179));
    chessBoard();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (checkPos[i][j] == 2) drawBoxDeath(i, j);
            else if (checkPos[i][j] == 1)    drawBoxLegalMove(i, j);
            else if (checkPos[i][j] == 3)     drawBoxPos(i, j,dx,dy);
            if ((board[i][j] == -1 || board[i][j] == 1) && check_king[i][j] == 2) {
                drawBoxDeathKing(i, j);
            }
        }
    }

    showTurn(checkTurn);

    for (auto i : f) window.draw(i);

}

void Board::Quit() {
    sf::Text textQuit;
    textQuit.setFont(font);
    textQuit.setString("Quit");
    textQuit.setCharacterSize(60);
    textQuit.setFillColor(sf::Color::White);
    textQuit.setPosition(SCREEN_WIDTH - SCREEN_MARGIN * 2 - 150 + 42.5, SCREEN_HEIGHT - cellSize);
    window.draw(textQuit);
}

void Board::PrintSetting() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Font customFont1;
    if (!customFont1.loadFromFile("../Data/Font/font_1.ttf")) {
        customFont1.loadFromFile("Data/Font/font_1.ttf");
    }
    sf::Text textMenu;
    textMenu.setFont(customFont1); // Thiết lập font tùy chỉnh
    textMenu.setString("Setting"); // Đặt nội dung chữ
    textMenu.setCharacterSize(60); // Kích thước chữ
    textMenu.setFillColor(sf::Color::White); // Màu chữ
    textMenu.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2f, SCREEN_MARGIN); // Vị trí chữ trên cửa sổ

    sf::RectangleShape BoxInSetting(sf::Vector2f(295, cellSize * 3));
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

    //window.draw(textQuit);

    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN && mousePosition.y <= SCREEN_MARGIN + cellSize)) {
        window.draw(BoxInSetting);
        window.draw(BoxInSetting2);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);

    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize && mousePosition.y <= SCREEN_MARGIN + cellSize * 2)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextPvP);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);

    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 2 && mousePosition.y <= SCREEN_MARGIN + cellSize * 3)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextPvAI);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);

    }


}


