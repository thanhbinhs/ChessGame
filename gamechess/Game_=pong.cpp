#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
void chessBoard() {
    sf::RenderWindow window(sf::VideoMode(1560, 1060), "Chessboard"); // Đặt kích thước cửa sổ 1560x1060
    
    const float cellSize = 120.0f; // Kích thước mỗi ô 120
    const float boardSize = cellSize * 8.0f; 
    const float margin = 50.0f;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(margin, (window.getSize().y - boardSize) / 2.0f);
    // chữ 
    sf::Font customFont;
    if (!customFont.loadFromFile("Aloevera-oVoWO.tff")) {
        cout << "false to load font";
    }
    sf::Text text;
    text.setFont(customFont); // Thiết lập font tùy chỉnh
    text.setString("Hello, SFML!"); // Đặt nội dung chữ
    text.setCharacterSize(24); // Kích thước chữ
    text.setFillColor(sf::Color::Red); // Màu chữ
    text.setPosition(100, 100); // Vị trí chữ trên cửa sổ
    window.draw(text);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //window.draw(text);
            // Xử lý các sự kiện khác ở đây, ví dụ: di chuyển các quân cờ.
        }
        window.clear(); // Xóa nội dung cửa sổ
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
                    square.setFillColor(sf::Color(64,64,64));
                }
                else {
                    square.setFillColor(sf::Color(220,220,220));
                }
                window.draw(square);
            }
        }
        window.draw(text);
        window.display(); // Hiển thị nội dung của cửa sổ

    }
}

int main() {
    chessBoard();
    return 0;
}
