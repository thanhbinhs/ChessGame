#include "board.hpp"


void Board::chessBoard() {
    float cellSize = size_;
    const float boardSize = cellSize * 8;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(SCREEN_MARGIN, SCREEN_MARGIN);
    // Load font chữ 
    sf::Font font;
    if (!font.loadFromFile("../Data/Font/font_1.ttf")) {
        font.loadFromFile("Data/Font/font_1.ttf");
    }


    sf::RectangleShape BoxBoard(sf::Vector2f(650, 650));
    BoxBoard.setFillColor(sf::Color::Black);
    BoxBoard.setPosition(SCREEN_MARGIN - 5.f, SCREEN_MARGIN - 5.f);
    sf::RectangleShape BoxBoard0(sf::Vector2f(650 + 60, 650 + 60));
    BoxBoard0.setFillColor(sf::Color::White);
    BoxBoard0.setPosition(SCREEN_MARGIN - 35, SCREEN_MARGIN - 35);
    sf::RectangleShape BoxBoard00(sf::Vector2f(650 + 65, 650 + 65));
    BoxBoard00.setFillColor(sf::Color::Black);
    BoxBoard00.setPosition(SCREEN_MARGIN - 37.3f, SCREEN_MARGIN - 37.3f);
    window.clear(sf::Color(100, 100, 100)); // Xóa nội dung cửa sổ
    window.draw(BoxBoard00);
    window.draw(BoxBoard0);
    window.draw(BoxBoard);

    // Vẽ bàn cờ
    sf::RectangleShape board(sf::Vector2f(640, 640));
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
                square.setFillColor(sf::Color(244, 244, 244));
            }
            else {
                square.setFillColor(sf::Color(115, 126, 131));
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
        texti.setFillColor(sf::Color::Black); // Màu chữ
        texti.setPosition(boardPosition.x + i * cellSize + SCREEN_MARGIN / 2 + 5.f, 15.f); // Vị trí chữ trên cửa sổ
        window.draw(texti);
    }
    // Vẽ số để đánh dấu toạ độ quân cờ
    for (int ij = 0; ij < 8; ij++) {
        sf::Text textij;
        textij.setFont(font); // Thiết lập font tùy chỉnh
        textij.setString(std::string(1, '1' + ij)); // Đặt nội dung chữ
        textij.setCharacterSize(24); // Kích thước chữ
        textij.setFillColor(sf::Color::Black); // Màu chữ
        textij.setPosition(SCREEN_MARGIN / 2, boardPosition.y + ij * cellSize + SCREEN_MARGIN / 2); // Vị trí chữ trên cửa sổ
        window.draw(textij);
    }


    // thong tin tren ban co.
    sf::RectangleShape BoxInInformation(sf::Vector2f(295, cellSize));
    BoxInInformation.setFillColor(sf::Color(0, 0, 0));
    BoxInInformation.setPosition(745, SCREEN_MARGIN + cellSize);
    window.draw(BoxInInformation);

    sf::Text textGameMode;
    textGameMode.setFont(font);
    textGameMode.setString("Game Mode: ");
    textGameMode.setCharacterSize(25);
    textGameMode.setFillColor(sf::Color::White);
    textGameMode.setPosition(SCREEN_WIDTH - (textGameMode.getGlobalBounds().width) * 1.2f - 100.f, SCREEN_MARGIN + cellSize + 10.f);
    window.draw(textGameMode);

    sf::Text textTurnof;
    textTurnof.setFont(font);
    textTurnof.setString("Turn: ");
    textTurnof.setCharacterSize(25);
    textTurnof.setFillColor(sf::Color::White);
    textTurnof.setPosition(SCREEN_WIDTH - (textTurnof.getGlobalBounds().width) * 1.2f - 200.f, SCREEN_MARGIN + cellSize + 10.f + 30.f);
    window.draw(textTurnof);





    // Các dòng kẻ đen và trắng 
    sf::RectangleShape line(sf::Vector2f(1060.f, 5.f));
    line.rotate(90.f);
    line.setFillColor(sf::Color::Black);
    line.setPosition(640.0f + SCREEN_MARGIN * 2 + 5.f, 0.f);
    window.draw(line);

    sf::RectangleShape lineSetting(sf::Vector2f(3.f, 295.f));
    lineSetting.rotate(90.f);
    lineSetting.setFillColor(sf::Color::White);
    lineSetting.setPosition(1040, SCREEN_MARGIN + cellSize);
    window.draw(lineSetting);

    sf::RectangleShape lineSetting0(sf::Vector2f(3.f, 295.f));
    lineSetting0.rotate(90.f);
    lineSetting0.setFillColor(sf::Color::White);
    lineSetting0.setPosition(1040, SCREEN_MARGIN + cellSize * 2.f);
    window.draw(lineSetting0);


    sf::RectangleShape lineSetting1(sf::Vector2f(3.f, 295.f));
    lineSetting1.rotate(90.f);
    lineSetting1.setFillColor(sf::Color::White);
    lineSetting1.setPosition(1040, SCREEN_MARGIN - 3.f);
    window.draw(lineSetting1);




    // setting
    sf::Texture setting;
    if (!setting.loadFromFile("../Data/Image/Setting1.png")) {
        //cout << "false load Setting1.png";
    }
    sf::Texture setting1;
    if (!setting1.loadFromFile("../Data/Image/Setting2.png")) {
        //cout << "false load Setting2.png";
    }

    // text
    sf::Text textMenu;
    textMenu.setFont(font);
    textMenu.setString("Setting");
    textMenu.setCharacterSize(60);
    textMenu.setFillColor(sf::Color::White);
    textMenu.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2f - 10.f, SCREEN_MARGIN);
    window.draw(textMenu);

    sf::Text textQuit;
    textQuit.setFont(font);
    textQuit.setString("Quit");
    textQuit.setCharacterSize(60);
    textQuit.setFillColor(sf::Color::White);
    textQuit.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2f - 10.f, SCREEN_MARGIN + cellSize * 7);
    window.draw(textQuit);

    // box
    sf::RectangleShape BoxInSetting2(sf::Vector2f(295, cellSize));
    BoxInSetting2.setFillColor(sf::Color(0, 0, 0));
    BoxInSetting2.setPosition(745, SCREEN_MARGIN);

    // image 
    sf::IntRect croppingRect(595, 560, 80, 80);
    sf::Texture Stop;
    Stop.loadFromImage(setting.copyToImage(), croppingRect);
    sf::Sprite Stopp;
    Stopp.setTexture(Stop);
    Stopp.setPosition(750 + 160, SCREEN_MARGIN + cellSize * 7 + 1);
    window.draw(Stopp);

    sf::IntRect croppingRect1(595, 560, 80, 80);
    sf::Texture Stop1;
    Stop.loadFromImage(setting1.copyToImage(), croppingRect);
    sf::Sprite Stopp1;
    Stopp1.setTexture(Stop1);
    Stopp1.setPosition(750 + 160, SCREEN_MARGIN + cellSize * 7 + 1);
    window.draw(Stopp1);

    // Lấy vị trí chuột
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


    // In Game mode;


    // In ra vị trí chuột lên cửa sổ
    //   std::cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN && mousePosition.y <= SCREEN_MARGIN + cellSize)) {
        window.draw(BoxInSetting2);
        window.draw(textMenu);
    }

    if ((mousePosition.x >= 745 + 160 && mousePosition.x <= SCREEN_WIDTH - 50) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 7 && mousePosition.y <= SCREEN_MARGIN + cellSize * 8)) {
        window.draw(Stopp);
    }
    int x = 1; int y = 1;
    sf::RectangleShape FisrtBoxBlack;
    FisrtBoxBlack.setFillColor(sf::Color(255, 153, 51));
    FisrtBoxBlack.setSize(sizeBtn);
    FisrtBoxBlack.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    //window.draw(FisrtBoxBlack);
}


void Board::PrintSetting() {

    float cellSize = size_;
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
    textMenu.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2f - 10.f, SCREEN_MARGIN); // Vị trí chữ trên cửa sổ

    sf::RectangleShape BoxInSetting(sf::Vector2f(295, cellSize * 4));
    BoxInSetting.setFillColor(sf::Color::Black);
    BoxInSetting.setPosition(745, SCREEN_MARGIN);
    //window.draw(BoxInSetting);

    sf::RectangleShape BoxInSetting2(sf::Vector2f(295, cellSize));
    BoxInSetting2.setFillColor(sf::Color(115, 126, 131));
    BoxInSetting2.setPosition(745, SCREEN_MARGIN);
    //window.draw(BoxInSetting2);
    sf::RectangleShape BoxIntextPvP(sf::Vector2f(295, cellSize));
    BoxIntextPvP.setFillColor(sf::Color(115, 126, 131));
    BoxIntextPvP.setPosition(745, SCREEN_MARGIN + cellSize);

    sf::RectangleShape BoxIntextPvAI(sf::Vector2f(295, cellSize));
    BoxIntextPvAI.setFillColor(sf::Color(115, 126, 131));
    BoxIntextPvAI.setPosition(745, SCREEN_MARGIN + cellSize * 2);

    sf::RectangleShape BoxInSetTime(sf::Vector2f(295, cellSize));
    BoxInSetTime.setFillColor(sf::Color(115, 126, 131));
    BoxInSetTime.setPosition(745, SCREEN_MARGIN + cellSize * 3);
    // Text Set time
    sf::Text textSetTime;
    textSetTime.setFont(customFont1); // Thiết lập font tùy chỉnh
    textSetTime.setString("Set Time"); // Đặt nội dung chữ
    textSetTime.setCharacterSize(60); // Kích thước chữ
    textSetTime.setFillColor(sf::Color::White); // Màu chữ
    textSetTime.setPosition(SCREEN_WIDTH - SCREEN_MARGIN * 2 - 150 - 20, SCREEN_MARGIN + cellSize * 3);
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
        window.draw(textSetTime);
    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize && mousePosition.y <= SCREEN_MARGIN + cellSize * 2)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextPvP);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textSetTime);

    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 2 && mousePosition.y <= SCREEN_MARGIN + cellSize * 3)) {
        window.draw(BoxInSetting);
        window.draw(BoxIntextPvAI);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textSetTime);
    }
    if ((mousePosition.x >= 745 && mousePosition.x <= SCREEN_WIDTH) && (mousePosition.y >= SCREEN_MARGIN + cellSize * 3 && mousePosition.y <= SCREEN_MARGIN + cellSize * 4)) {
        window.draw(BoxInSetting);
        window.draw(BoxInSetTime);
        window.draw(textMenu);
        window.draw(textPvP);
        window.draw(textPvAI);
        window.draw(textSetTime);
    }


}

void Board::drawBoxPos(int x, int y) {
    sf::RectangleShape boxPos;
    boxPos.setFillColor(sf::Color(245, 236, 66, 100));
    boxPos.setSize(sizeBtn);
    boxPos.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    //window.draw(boxPos);
}

void Board::drawBoxCom(int x, int y)
{
    sf::RectangleShape boxPos;
    boxPos.setFillColor(sf::Color(253, 2, 45, 100));
    boxPos.setSize(sizeBtn);
    boxPos.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(boxPos);
}

void Board::drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y) {
    sprite.setTexture(draw_box);
    sprite.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(sprite);
}

void Board::drawFirstBoxBlack(int x, int y) {
    sf::RectangleShape FisrtBoxBlack;
    FisrtBoxBlack.setFillColor(sf::Color(255, 229, 204));
    FisrtBoxBlack.setSize(sizeBtn);
    FisrtBoxBlack.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(FisrtBoxBlack);
}
void Board::drawSecondBoxBlack(int x, int y) {
    sf::RectangleShape SecondBoxBlack;
    SecondBoxBlack.setFillColor(sf::Color(255, 153, 51));
    SecondBoxBlack.setSize(sizeBtn);
    SecondBoxBlack.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(SecondBoxBlack);
}
void Board::drawFirstBoxWhite(int x1, int y1) {
    sf::RectangleShape FisrtBoxWhite;
    FisrtBoxWhite.setFillColor(sf::Color(204, 229, 255));
    FisrtBoxWhite.setSize(sizeBtn);
    FisrtBoxWhite.setPosition(y1 * size_ + SCREEN_MARGIN, x1 * size_ + SCREEN_MARGIN);
    window.draw(FisrtBoxWhite);
}
void Board::drawSecondBoxWhite(int x, int y) {
    sf::RectangleShape SecondBoxWhite;
    SecondBoxWhite.setFillColor(sf::Color(51, 153, 255));
    SecondBoxWhite.setSize(sizeBtn);
    SecondBoxWhite.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(SecondBoxWhite);
}

void Board::drawBoxDeath(int x, int y)
{
    sf::Texture draw_box;
    if (!draw_box.loadFromFile("../Data/Image/death.png"))
        draw_box.loadFromFile("Data/Image/death.png");

    sf::Sprite sp;
    drawBox(sp, draw_box, x, y);
}

void Board::drawBoxKingDeath(int x, int y)
{
    sf::Texture draw_box;
    if (!draw_box.loadFromFile("../Data/Image/kingDeath.png"))
        draw_box.loadFromFile("Data/Image/kingDeath.png");

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

void Board::drawCapture(int x, int index)
{
    sf::Sprite ct[4];
    sf::Texture texture;
    texture.loadFromFile("../Data/Image/chesses.png");
    ct->setTexture(texture);
    for (int i = 0; i < 4; i++) {
        ct[i].setTexture(texture);
    }
    sf::ConvexShape shape = createRoundedRectangle(size_, size_ * 4, 15, 40);
    shape.setFillColor(sf::Color(230, 230, 230));

    float y = (x - SCREEN_MARGIN) / size_;

    //cout << y<<" " <<index << endl;

    if (index == 6) {
        for (int i = 0; i < 4; i++) {
            ct[i].setTextureRect({ 80 * (i + 1),0,80,80 });
            ct[i].setPosition(size_ * y + SCREEN_MARGIN, SCREEN_MARGIN + size_ * (i + 1));
        }
        shape.setPosition(size_ * y + SCREEN_MARGIN, SCREEN_MARGIN + size_);
    }
    else if (index == -6) {
        for (int i = 3; i >= 0; i--) {
            ct[i].setTextureRect({ 80 * (i + 1),80,80,80 });
            ct[i].setPosition(size_ * y + SCREEN_MARGIN, SCREEN_HEIGHT - (size_ * (i + 2.f)));
        }
        shape.setPosition(size_ * y + SCREEN_MARGIN, SCREEN_HEIGHT - (size_ * 5.f));
    }

    window.draw(shape);
    for (auto i : ct)  window.draw(i);
}


void Board::SetTime(bool checkTurn,sf::Time remainingTime1,sf::Time remainingTime2,bool FreezeTheClock2)
{
    sf::Font font;
    if (!font.loadFromFile("../Data/Font/font_1.ttf")) {
        font.loadFromFile("Data/Font/font_1.ttf");
    }
    int cellSize = size_;

    sf::RectangleShape Background(sf::Vector2f(295, cellSize * 2.f));
    Background.setFillColor(sf::Color(100, 100, 100));
    Background.setPosition(745, SCREEN_MARGIN + cellSize);
    window.draw(Background);

    sf::Text textClockB;
    textClockB.setFont(font);
    //textClockB.setString("2334");
    textClockB.setCharacterSize(40);
    textClockB.setFillColor(sf::Color::White);
    textClockB.setPosition(745 + 25 + 95, SCREEN_MARGIN + cellSize * 3.f + 15);
    window.draw(textClockB);

    sf::Text textClockW;
    textClockW.setFont(font);
    //textClockW.setString("2334");
    textClockW.setCharacterSize(40);
    textClockW.setFillColor(sf::Color::White);
    textClockW.setPosition(745 + 25 + 95, SCREEN_MARGIN + cellSize *2.f + 15);
    window.draw(textClockW);

    sf::RectangleShape lineSetting123(sf::Vector2f(5.f, 295.f));
    lineSetting123.rotate(90.f);
    lineSetting123.setFillColor(sf::Color::Black);
    lineSetting123.setPosition(1040, SCREEN_MARGIN + cellSize);
    window.draw(lineSetting123);

    sf::RectangleShape lineSetting1234(sf::Vector2f(5.f, 295.f));
    lineSetting1234.rotate(90.f);
    lineSetting1234.setFillColor(sf::Color::Black);
    lineSetting1234.setPosition(1040, SCREEN_MARGIN + cellSize * 3);
    window.draw(lineSetting1234);

    sf::RectangleShape lineSetting12(sf::Vector2f(5.f, 295.f));
    lineSetting12.rotate(90.f);
    lineSetting12.setFillColor(sf::Color::Black);
    lineSetting12.setPosition(1040, SCREEN_MARGIN - 3.f);
    window.draw(lineSetting12);

    // line doc
    sf::RectangleShape lineSetTime(sf::Vector2f(cellSize * 2.f, 5.f));
    lineSetTime.rotate(90.f);
    lineSetTime.setFillColor(sf::Color::Black);
    lineSetTime.setPosition(640.0f + SCREEN_MARGIN * 2 + 100, SCREEN_MARGIN + cellSize * 2);
    window.draw(lineSetTime);

    sf::RectangleShape lineSetting11(sf::Vector2f(5.f, 295.f));
    lineSetting11.rotate(90.f);
    lineSetting11.setFillColor(sf::Color::Black);
    lineSetting11.setPosition(1040, SCREEN_MARGIN - 3.f + cellSize * 2);
    window.draw(lineSetting11);

    sf::RectangleShape lineSetting22(sf::Vector2f(5.f, 295.f));
    lineSetting22.rotate(90.f);
    lineSetting22.setFillColor(sf::Color::Black);
    lineSetting22.setPosition(1040, SCREEN_MARGIN - 3.f + cellSize * 4);
    window.draw(lineSetting22);

    sf::Text textTime;
    textTime.setFont(font);
    textTime.setString("Time");
    textTime.setCharacterSize(60);
    textTime.setFillColor(sf::Color::White);
    textTime.setPosition(SCREEN_WIDTH - (textTime.getGlobalBounds().width) * 1.2f - 50.f, SCREEN_MARGIN + cellSize);
    window.draw(textTime);

    sf::Text textW;
    textW.setFont(font);
    textW.setString("W");
    textW.setCharacterSize(60);
    textW.setFillColor(sf::Color::White);
    textW.setPosition(SCREEN_WIDTH - (textW.getGlobalBounds().width) * 1.2f - 215.f, SCREEN_MARGIN + cellSize * 3.f);
    window.draw(textW);

    sf::Text textB;
    textB.setFont(font);
    textB.setString("B");
    textB.setCharacterSize(60);
    textB.setFillColor(sf::Color::Black);
    textB.setPosition(SCREEN_WIDTH - (textW.getGlobalBounds().width) * 1.2f - 205.f, SCREEN_MARGIN + cellSize * 2.f);
    window.draw(textB);

    // information
    sf::RectangleShape BoxInInformation(sf::Vector2f(295, cellSize));
    BoxInInformation.setFillColor(sf::Color(0, 0, 0));
    BoxInInformation.setPosition(745, SCREEN_MARGIN + cellSize * 4.f);
    window.draw(BoxInInformation);

    sf::Text textGameMode;
    textGameMode.setFont(font);
    textGameMode.setString("Game Mode:");
    textGameMode.setCharacterSize(25);
    textGameMode.setFillColor(sf::Color::White);
    textGameMode.setPosition(SCREEN_WIDTH - (textGameMode.getGlobalBounds().width) * 1.2f - 110.f, SCREEN_MARGIN + cellSize * 4.f + 10.f);
    window.draw(textGameMode);

    sf::Text textTurnof;
    textTurnof.setFont(font);
    textTurnof.setString("Turn: ");
    textTurnof.setCharacterSize(25);
    textTurnof.setFillColor(sf::Color::White);
    textTurnof.setPosition(SCREEN_WIDTH - (textTurnof.getGlobalBounds().width) * 1.2f - 200.f, SCREEN_MARGIN + cellSize * 4.f + 10.f + 30.f);
    window.draw(textTurnof);

    sf::Text textGameMode1;
    textGameMode1.setFont(font);
    textGameMode1.setString("Set Time");
    textGameMode1.setCharacterSize(25);
    textGameMode1.setFillColor(sf::Color::White);
    textGameMode1.setPosition(SCREEN_WIDTH - (textGameMode1.getGlobalBounds().width) * 1.2f, SCREEN_MARGIN + cellSize * 4.f + 10.f);
    window.draw(textGameMode1);

    if (checkTurn == false) {
        // In turn Black
        sf::Text textTurnBlack;
        textTurnBlack.setFont(font);
        textTurnBlack.setString("Black");
        textTurnBlack.setCharacterSize(25);
        textTurnBlack.setFillColor(sf::Color::White);
        textTurnBlack.setPosition(SCREEN_WIDTH - (textTurnBlack.getGlobalBounds().width) * 1.2f - 130.f, SCREEN_MARGIN + cellSize * 4.f + 40.f);
        window.draw(textTurnBlack);
    }


    if (checkTurn == true) {
        // In turn White
        sf::Text textTurnWhite;
        textTurnWhite.setFont(font);
        textTurnWhite.setString("White");
        textTurnWhite.setCharacterSize(25);
        textTurnWhite.setFillColor(sf::Color::White);
        textTurnWhite.setPosition(SCREEN_WIDTH - (textTurnWhite.getGlobalBounds().width) * 1.2f - 130.f, SCREEN_MARGIN + cellSize * 4.f + 40.f);
        window.draw(textTurnWhite);
    }

    

    // Chuyển thời gian còn lại thành chuỗi để hiển thị
    // Clock 1
    int minutes1 = static_cast<int>(remainingTime1.asSeconds()) / 60;
    int seconds1 = static_cast<int>(remainingTime1.asSeconds()) % 60;
    int milliseconds1 = static_cast<int>(remainingTime1.asMilliseconds()) % 1000;
    std::string countdownString1 = std::to_string(minutes1) + ":" + (seconds1 < 10 ? "0" : "") + std::to_string(seconds1) + "." + std::to_string(milliseconds1);
    // Clock 2
    int minutes2= static_cast<int>(remainingTime2.asSeconds()) / 60;
    int seconds2 = static_cast<int>(remainingTime2.asSeconds()) % 60;
    int milliseconds2 = static_cast<int>(remainingTime2.asMilliseconds()) % 1000;
    std::string countdownString2 = std::to_string(minutes2) + ":" + (seconds2 < 10 ? "0" : "") + std::to_string(seconds2) + "." + std::to_string(milliseconds2);

    // Cập nhật văn bản đồng hồ đếm ngược
  

    textClockW.setString(countdownString1);
    textClockB.setString(countdownString2);
    window.draw(textClockW);
    window.draw(textClockB);
    if (FreezeTheClock2 ) {
        sf::RectangleShape BackgroundInClockBlack(sf::Vector2f(295, cellSize - 5.f));
        BackgroundInClockBlack.setFillColor(sf::Color(100, 100, 100));
        BackgroundInClockBlack.setPosition(640.0f + SCREEN_MARGIN * 2 + 100, SCREEN_MARGIN + cellSize * 2.f + 5.f);
        window.draw(BackgroundInClockBlack);

        sf::Text textClockFreeze;
        textClockFreeze.setFont(font);
        textClockFreeze.setString("15:00.000");
        textClockFreeze.setCharacterSize(40);
        textClockFreeze.setFillColor(sf::Color::White);
        textClockFreeze.setPosition(745 + 25 + 95, SCREEN_MARGIN + cellSize * 2.f + 15);
        window.draw(textClockFreeze);
    }
    sf::Time t1 = sf::seconds(0.1f);
    if (remainingTime1 <= t1)
    {
        sf::RectangleShape BackgroundInClockBlack(sf::Vector2f(295, cellSize - 5.f));
        BackgroundInClockBlack.setFillColor(sf::Color(100, 100, 100));
        BackgroundInClockBlack.setPosition(640.0f + SCREEN_MARGIN * 2 + 100, SCREEN_MARGIN + cellSize * 2.f + 5.f);
        window.draw(BackgroundInClockBlack);
        sf::Text textClockFreeze;
        textClockFreeze.setFont(font);
        textClockFreeze.setString("00:00.00");
        textClockFreeze.setCharacterSize(40);
        textClockFreeze.setFillColor(sf::Color::Red);
        textClockFreeze.setPosition(745 + 25 + 95, SCREEN_MARGIN + cellSize * 2.f + 15);
        window.draw(textClockFreeze);

    }
    else if (remainingTime2 <= t1)
    {
        sf::RectangleShape BackgroundInClockBlack(sf::Vector2f(295, cellSize - 5.f));
        BackgroundInClockBlack.setFillColor(sf::Color(100, 100, 100));
        BackgroundInClockBlack.setPosition(640.0f + SCREEN_MARGIN * 2 + 100, SCREEN_MARGIN + cellSize * 3.f + 5.f);
        window.draw(BackgroundInClockBlack);
        sf::Text textClockFreeze;
        textClockFreeze.setFont(font);
        textClockFreeze.setString("00:00.00");
        textClockFreeze.setCharacterSize(40);
        textClockFreeze.setFillColor(sf::Color::Red);
        textClockFreeze.setPosition(745 + 25 + 95, SCREEN_MARGIN + cellSize * 3.f + 15);
        window.draw(textClockFreeze);
    }




}
void Board::PrintPvP(bool  checkTurn)
{
    sf::Font font;
    if (!font.loadFromFile("../Data/Font/font_1.ttf")) {
        font.loadFromFile("Data/Font/font_1.ttf");
    }
    int cellSize = size_;

    if (checkTurn == false) {
        // In turn Black
        sf::Text textTurnBlack;
        textTurnBlack.setFont(font);
        textTurnBlack.setString("Black");
        textTurnBlack.setCharacterSize(25);
        textTurnBlack.setFillColor(sf::Color::White);
        textTurnBlack.setPosition(SCREEN_WIDTH - (textTurnBlack.getGlobalBounds().width) * 1.2f - 130.f, SCREEN_MARGIN + cellSize + 40.f);
        window.draw(textTurnBlack);
    }

    if (checkTurn == true) {
        // In turn White
        sf::Text textTurnWhite;
        textTurnWhite.setFont(font);
        textTurnWhite.setString("White");
        textTurnWhite.setCharacterSize(25);
        textTurnWhite.setFillColor(sf::Color::White);
        textTurnWhite.setPosition(SCREEN_WIDTH - (textTurnWhite.getGlobalBounds().width) * 1.2f - 130.f, SCREEN_MARGIN + cellSize + 40.f);
        window.draw(textTurnWhite);
    }

    sf::RectangleShape Background(sf::Vector2f(100, 50));
    Background.setFillColor(sf::Color(0, 0, 0));
    Background.setPosition(745 + 200, SCREEN_MARGIN + cellSize + 5.f);
    window.draw(Background);

    sf::Text textGameMode2;
    textGameMode2.setFont(font);
    textGameMode2.setString("PvP");
    textGameMode2.setCharacterSize(25);
    textGameMode2.setFillColor(sf::Color::White);
    textGameMode2.setPosition(SCREEN_WIDTH - (textGameMode2.getGlobalBounds().width) * 1.2f - 50.f, SCREEN_MARGIN + cellSize + 10.f);
    window.draw(textGameMode2);
}


void Board::PvAi(bool checkTurn) {
    int cellSize = size_;
    sf::Font font;
    if (!font.loadFromFile("../Data/Font/font_1.ttf")) {
        font.loadFromFile("Data/Font/font_1.ttf");
    }

    if (checkTurn == true) {
        // in turn People
        sf::Text textTurnPeople;
        textTurnPeople.setFont(font);
        textTurnPeople.setString("People");
        textTurnPeople.setCharacterSize(25);
        textTurnPeople.setFillColor(sf::Color::White);
        textTurnPeople.setPosition(SCREEN_WIDTH - (textTurnPeople.getGlobalBounds().width) * 1.2f - 110.f, SCREEN_MARGIN + cellSize + 40.f);
        window.draw(textTurnPeople);
    }

    if (checkTurn == false) {
        // in turn Bot(AI)
        sf::Text textTurnBot;
        textTurnBot.setFont(font);
        textTurnBot.setString("Bot");
        textTurnBot.setCharacterSize(25);
        textTurnBot.setFillColor(sf::Color::White);
        textTurnBot.setPosition(SCREEN_WIDTH - (textTurnBot.getGlobalBounds().width) * 1.2f - 155.f, SCREEN_MARGIN + cellSize + 40.f);
        window.draw(textTurnBot);
    }

    sf::Text textGameMode1;
    textGameMode1.setFont(font);
    textGameMode1.setString("PvAI");
    textGameMode1.setCharacterSize(25);
    textGameMode1.setFillColor(sf::Color::White);
    textGameMode1.setPosition(SCREEN_WIDTH - (textGameMode1.getGlobalBounds().width) * 1.2f - 50.f, SCREEN_MARGIN + cellSize + 10.f);
    window.draw(textGameMode1);

}
