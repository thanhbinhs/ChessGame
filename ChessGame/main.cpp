#include "header.h"

using namespace std;
using namespace sf;

sf::Vector2f offset(40, 40);
Sprite f[33]; //mang lưu các quân cờ
sf::Vector2i pos;
int dx = 0;
int dy = 0;
int click = 0;
bool isMouse = true;

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
    
    const float boardSize = cellSize * 8;

    // Vị trí của bàn cờ để nó nằm bên trái và cách lề 50 pixel
    sf::Vector2f boardPosition(SCREEN_MARGIN, SCREEN_MARGIN);
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
            // Chữ edit 
            sf::Text textMenu;
            textMenu.setFont(customFont); // Thiết lập font tùy chỉnh
            textMenu.setString("Setting"); // Đặt nội dung chữ
            textMenu.setCharacterSize(60); // Kích thước chữ
            textMenu.setFillColor(sf::Color::White); // Màu chữ
            textMenu.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2, 20.f); // Vị trí chữ trên cửa sổ
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
			f[k].setPosition(sizeBtn.x * j + SCREEN_MARGIN, sizeBtn.y * i + SCREEN_MARGIN);
			k++;
		}
}



int main() {
    window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("../Data/Image/chesses.png");
	f->setTexture(texture);
	for (int i = 0; i < 32; i++) {
		f[i].setTexture(texture);
	}
	loadPosition();
	sf::Event event;
	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

            chessBoard();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    pos = sf::Mouse::getPosition(window);
                    click++;
                }
            }
            if (click == 1 and isMouse == true) {
                    dy = (pos.x - SCREEN_MARGIN) / 80;
                    dx = (pos.y - SCREEN_MARGIN) / 80;
                    cout << "Old Board: " << board[dx][dy] << endl;
                    isMouse = false;

            }
            if (click == 2) {
                sf::Vector2i pos_n = sf::Mouse::getPosition(window);
                int dy_n = (pos_n.x - SCREEN_MARGIN) / 80;
                int dx_n = (pos_n.y - SCREEN_MARGIN) / 80;
                cout << "New Board: " << board[dx_n][dy_n] << endl;

                board[dx_n][dy_n] = board[dx][dy];
                board[dx][dy] = 0;

                loadPosition();

                //reset
                isMouse = true;
                click = 0;
            }
            
		}




		for (auto i : f) window.draw(i);

		window.display();
	}
}
