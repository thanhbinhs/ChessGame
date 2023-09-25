#include "board.hpp"


void Board::chessBoard() {

    const float boardSize = size_ * 8;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(SCREEN_MARGIN, SCREEN_MARGIN);
    // Load font chữ 
    sf::Font font;
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
            sf::RectangleShape square(sf::Vector2f(size_, size_));
            square.setPosition(boardPosition.x + i * size_, boardPosition.y + j * size_);

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
        texti.setPosition(boardPosition.x + i * size_ + SCREEN_MARGIN / 2, 15.f); // Vị trí chữ trên cửa sổ
        window.draw(texti);
    }
    // Vẽ số để đánh dấu toạ độ quân cờ
    for (int ij = 0; ij < 8; ij++) {
        sf::Text textij;
        textij.setFont(font); // Thiết lập font tùy chỉnh
        textij.setString(std::string(1, '1' + ij)); // Đặt nội dung chữ
        textij.setCharacterSize(24); // Kích thước chữ
        textij.setFillColor(sf::Color::White); // Màu chữ
        textij.setPosition(SCREEN_MARGIN / 2, boardPosition.y + ij * size_ + SCREEN_MARGIN / 2); // Vị trí chữ trên cửa sổ
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

void Board::drawBoxPos(int x, int y) {
    sf::RectangleShape boxPos;
    boxPos.setFillColor(sf::Color(245, 236, 66, 100));
    boxPos.setSize(sizeBtn);
    boxPos.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(boxPos);
}

void Board::drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y) {
    sprite.setTexture(draw_box);
    sprite.setPosition(y * size_ + SCREEN_MARGIN, x * size_ + SCREEN_MARGIN);
    window.draw(sprite);
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

void Board::drawCapture( int n )
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

    sf::Vector2f pos = f[n].s.getPosition() - offset;
    int y =(int) pos.x / size_;
    

    if (f[n].index == 6) {
        for (int i = 0; i < 4; i++) {
            ct[i].setTextureRect({ 80 * (i + 1),80,80,80 });
            ct[i].setPosition(size_ * y + SCREEN_MARGIN, SCREEN_MARGIN + size_ * (i + 1));
        }
        shape.setPosition(size_ * y + SCREEN_MARGIN, SCREEN_MARGIN + size_);
    }
    else if (f[n].index == -6) {
        for (int i = 3; i >= 0; i--) {
            ct[i].setTextureRect({ 80 * (i + 1),0,80,80 });
            ct[i].setPosition(size_ * y + SCREEN_MARGIN, SCREEN_HEIGHT - (size_ * (i + 2)));
        }
        shape.setPosition(size_ * y + SCREEN_MARGIN, SCREEN_HEIGHT - (size_ * 5));
    }

    window.draw(shape);
    for (auto i : ct)  window.draw(i);
}

