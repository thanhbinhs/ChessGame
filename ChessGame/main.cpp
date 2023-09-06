#include "header.h"

using namespace std;
using namespace sf;

sf::Vector2f offset(40, 40);
Sprite f[33]; //mang lưu các quân cờ

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


sf::RectangleShape createButton() {
	sf::RectangleShape button;
	button.setSize(sizeBtn);
	return button;
}

void chessBoard() {
    
    const float cellSize = 80.0f; // Kích thước mỗi ô 80
    const float boardSize = cellSize * 8.0f;
    const float margin = 50.0f;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(margin, margin);
    // Load font chữ 
    sf::Font customFont;
    if (!customFont.loadFromFile("../Data/Font/font_1.ttf")) {
        cout << "false to load font";
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
                texti.setPosition(boardPosition.x + i * cellSize + 25.f, 15.f); // Vị trí chữ trên cửa sổ
                window.draw(texti);
            }
            // Vẽ số để đánh dấu toạ độ quân cờ
            for (int ij = 0; ij < 8; ij++) {
                sf::Text textij;
                textij.setFont(customFont); // Thiết lập font tùy chỉnh
                textij.setString(std::string(1, '1' + ij)); // Đặt nội dung chữ
                textij.setCharacterSize(24); // Kích thước chữ
                textij.setFillColor(sf::Color::White); // Màu chữ
                textij.setPosition(25.f, boardPosition.y + ij * cellSize + 25.f); // Vị trí chữ trên cửa sổ
                window.draw(textij);
            }
            // Dòng kẻ tách phần setting và bàn cờ
            sf::RectangleShape line(sf::Vector2f(1060.f, 5.f));
            line.rotate(90.f);
            line.setPosition(640.0f + margin * 2 + 5.f, 0.f);
            window.draw(line);
            // Chữ edit 
            sf::Text textMenu;
            textMenu.setFont(customFont); // Thiết lập font tùy chỉnh
            textMenu.setString("Setting"); // Đặt nội dung chữ
            textMenu.setCharacterSize(60); // Kích thước chữ
            textMenu.setFillColor(sf::Color::White); // Màu chữ
            textMenu.setPosition(SCREEN_WIDTH - 250.f, 20.f); // Vị trí chữ trên cửa sổ
            window.draw(textMenu);

}

void loadPosition() {
	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 0 : 1;
			f[k].setTextureRect({ 80 * x, 80 * y, 80, 80 });
			f[k].setPosition(sizeBtn.x * j + 50, sizeBtn.y * i + 50 );
			k++;
		}
}



int main() {
	sf::Texture texture;
	texture.loadFromFile("../Data/Image/chesses.png");
	f->setTexture(texture);
	for (int i = 0; i < 32; i++) {
		f[i].setTexture(texture);
	}
	loadPosition();
	sf::Event event;
	while (window.isOpen()) {
		sf::Vector2i pos = sf::Mouse::getPosition(window) - sf::Vector2i(offset);
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			window.clear(sf::Color::White);

            chessBoard();
		}

		for (auto i : f) window.draw(i);

		window.display();
	}
}
