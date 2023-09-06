#include "header.h"
using namespace std;

sf::RectangleShape createButton() {
	sf::RectangleShape button;
	button.setSize(sizeBtn);
	return button;
}

int a[8][8];
#include <SFML/Graphics.hpp>
#include <iostream>
void chessBoard() {
    sf::RenderWindow window(sf::VideoMode(1560, 1060), "Chessboard"); // Đặt kích thước cửa sổ 1560x1060

    const float cellSize = 120.0f; // Kích thước mỗi ô 120
    const float boardSize = cellSize * 8.0f;
    const float margin = 50.0f;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(margin, (window.getSize().y - boardSize) / 2.0f);
    // Load font chữ 
    sf::Font customFont;
    if (!customFont.loadFromFile("font_1.ttf")) {
        cout << "false to load font";
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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
                        square.setFillColor(sf::Color(64, 64, 64));
                    }
                    else {
                        square.setFillColor(sf::Color(220, 220, 220));
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
                texti.setPosition(boardPosition.x + i * cellSize + 50.f, 15.f); // Vị trí chữ trên cửa sổ
                window.draw(texti);
            }
            // Vẽ số để đánh dấu toạ độ quân cờ
            for (int ij = 0; ij < 8; ij++) {
                sf::Text textij;
                textij.setFont(customFont); // Thiết lập font tùy chỉnh
                textij.setString(std::string(1, '1' + ij)); // Đặt nội dung chữ
                textij.setCharacterSize(24); // Kích thước chữ
                textij.setFillColor(sf::Color::White); // Màu chữ
                textij.setPosition(25.f, boardPosition.y + ij * cellSize + 45.f); // Vị trí chữ trên cửa sổ
                window.draw(textij);
            }
            // Dòng kẻ tách phần setting và bàn cờ
            sf::RectangleShape line(sf::Vector2f(1060.f, 5.f));
            line.rotate(90.f);
            line.setPosition(1060.f, 0.f);
            window.draw(line);
            // Chữ edit 
            sf::Text textMenu;
            textMenu.setFont(customFont); // Thiết lập font tùy chỉnh
            textMenu.setString("Setting"); // Đặt nội dung chữ
            textMenu.setCharacterSize(100); // Kích thước chữ
            textMenu.setFillColor(sf::Color::White); // Màu chữ
            textMenu.setPosition(1135.f, 20.f); // Vị trí chữ trên cửa sổ
            window.draw(textMenu);



            window.display(); // Hiển thị nội dung của cửa sổ
        }
    }
}

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"SFML",sf::Style::Default);
	sf::Texture texture;
	texture.loadFromFile("../Data/Image/chesses.png");
	sf::Sprite sprite(texture);
	sprite.setTextureRect({ 0,0,80,80 });

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			window.clear(sf::Color::White);

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					sf::RectangleShape button = createButton();
					button.setPosition(i * sizeBtn.x, j * sizeBtn.y);
					if ((i + j) % 2 == 0)	button.setFillColor(sf::Color(248,220,180));
					else
					{
						button.setFillColor(sf::Color(184, 140, 100));
					}
					window.draw(button);
				}
			}

		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 8; j++) {
				if (i == 0) {
					if (j == 0 or j == 7)	sprite.setTextureRect({ 80 * 4,0,80,80 });
					if (j == 1 or j == 6)	sprite.setTextureRect({ 80 * 3,0,80,80 });
					if (j == 2 or j == 5)	sprite.setTextureRect({ 80 * 2,0,80,80 });
					if (j == 3)				sprite.setTextureRect({ 80,0,80,80 });
					if (j == 4)				sprite.setTextureRect({ 0,0,80,80 });
				}
				else {
					sprite.setTextureRect({ 80 * 5,0,80,80 });
				}

				sprite.setPosition(j * 80, i * 80);
				window.draw(sprite);
			}
		}

		for (int i = 6; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i == 7) {
					if (j == 0 or j == 7)	sprite.setTextureRect({ 80 * 4,80,80,80 });
					if (j == 1 or j == 6)	sprite.setTextureRect({ 80 * 3,80,80,80 });
					if (j == 2 or j == 5)	sprite.setTextureRect({ 80 * 2,80,80,80 });
					if (j == 3)				sprite.setTextureRect({ 80,80,80,80 });
					if (j == 4)				sprite.setTextureRect({ 0,80,80,80 });
				}
				else {
					sprite.setTextureRect({ 80 * 5,80,80,80 });
				}

				sprite.setPosition(j * 80, i * 80);
				window.draw(sprite);
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
			cout << pos.x << " " << pos.y << endl;

		}

		window.display();
	}


}
