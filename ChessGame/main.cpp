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
int checkTurn = -1;

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

int checkPos[8][8];


sf::RectangleShape createButton() {
	sf::RectangleShape button;
	button.setSize(sizeBtn);
	return button;
}

void reloadPos() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            checkPos[i][j] = 0;
}

void drawBox(int x, int y) {
    sf::RectangleShape box;
    box.setFillColor(sf::Color(255, 92, 51,200));
    box.setSize(sizeBtn);
    box.setPosition(y * cellSize + SCREEN_MARGIN, x * cellSize + SCREEN_MARGIN);
    window.draw(box);
}

void drawBoxWhite(int x, int y) {
    sf::RectangleShape box;
    box.setFillColor(sf::Color(179, 179, 179,100));
    box.setSize(sizeBtn);
    box.setPosition(y * cellSize + SCREEN_MARGIN, x * cellSize + SCREEN_MARGIN);
    window.draw(box);
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
            textMenu.setPosition(SCREEN_WIDTH - (textMenu.getGlobalBounds().width) * 1.2f, 20.f); // Vị trí chữ trên cửa sổ
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

void PositiveXe(int x, int y) {
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
    for (int j = y + 1; j < 8;j++) {
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

void PositiveTuong(int x, int y) {
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

void PositiveMa(int x, int y)//xet 8 vi tri co the di
{

    if (board[x + 2][y + 1] == 0 && x + 2 < 8 && y + 1 < 8)                                 checkPos[x + 2][y + 1] = 1;
    else if (board[x][y] * board[x + 2][y + 1] < 0 && x + 2 < 8 && y + 1 < 8)               checkPos[x + 2][y + 1] = 2;
    if (board[x + 2][y - 1] && y - 1 >= 0 && x + 2 < 8)                                     checkPos[x + 2][y - 1] = 1;
    else if (board[x][y] * board[x + 2][y - 1] < 0 && y - 1 >= 0 && x + 2 < 8)              checkPos[x + 2][y - 1] = 2;
    if (board[x - 2][y + 1] == 0 && x - 2 >= 0 && y + 1 < 8)                                checkPos[x - 2][y + 1] = 1;
    else if (board[x][y] * board[x - 2][y + 1] < 0 && x - 2 >= 0 && y + 1 < 8)              checkPos[x - 2][y + 1] = 2;
    if (board[x - 2][y - 1] == 0 && x - 2 >= 0 && y - 1 >= 0)                               checkPos[x - 2][y - 1] = 1;
    else if (board[x][y] * board[x - 2][y - 1] < 0 && x - 2 >= 0 && y - 1 >= 0)             checkPos[x - 2][y - 1] = 2;
    if (board[x +1][y +2] == 0 && x +1 <8 && y +2 <8)                                       checkPos[x + 1][y + 2] = 1;
    else if (board[x][y] * board[x +1][y +2] < 0 && x +1 < 8 && y + 2 < 8)                  checkPos[x + 1][y + 2] = 2;
    if (board[x - 1][y + 2] == 0 && x - 1 >= 0 && y + 2 < 8)                                checkPos[x - 1][y + 2] = 1;
    else if (board[x][y] * board[x - 1][y + 2] < 0 && x + 1 < 8 && y + 2 < 8)               checkPos[x - 1][y + 2] = 2;
    if (board[x + 1][y - 2] == 0 && y - 2 >= 0 && x + 1 < 8)                                checkPos[x + 1][y - 2] = 1;
    else if (board[x][y] * board[x + 1][y - 2] < 0 && y - 2 >= 0 && x + 1 < 8)              checkPos[x + 1][y - 2] = 2;
    if (board[x - 1][y - 2] == 0 && x - 1 >= 0 && y - 2 >= 0)                               checkPos[x - 1][y - 2] = 1;
    else if (board[x][y] * board[x - 1][y - 2] < 0 && x - 1 >= 0 && y - 2 >= 0)             checkPos[x - 1][y - 2] = 2;
}

void PositiveVua(int x, int y)//xet 8 vi tri co the di
{   
    if (board[x + 1][y] == 0 && x + 1 < 8) checkPos[x + 1][y] = 1;
    else if (board[x + 1][y] * board[x][y] < 0 && x + 1 < 8) checkPos[x + 1][y] = 2;
    if (board[x - 1][y] == 0 && x - 1 >= 0) checkPos[x - 1][y] = 1;
    else if (board[x - 1][y] * board[x][y] < 0 && x - 1 >= 0) checkPos[x - 1][y] = 2;
    if (board[x + 1][y + 1] == 0 && x + 1 < 8 && y + 1 < 8) checkPos[x + 1][y + 1] = 1;
    else if (board[x + 1][y + 1] * board[x][y] < 0 && x + 1 < 8 && y + 1 < 8) checkPos[x + 1][y + 1] = 2;
    if (board[x - 1][y + 1] == 0 && x - 1 >= 0 && y + 1 < 8) checkPos[x - 1][y + 1] = 1;
    else if (board[x - 1][y + 1] * board[x][y] < 0 && x - 1 >= 0 && y + 1 < 8) checkPos[x - 1][y + 1] = 2;
    if (board[x][y + 1] == 0 && y + 1 < 8) checkPos[x][y + 1] = 1;
    else if (board[x][y + 1] * board[x][y] < 0 && y + 1 < 8) checkPos[x][y + 1] = 2;
    if (board[x - 1][y - 1] == 0 && x - 1 >= 0 && y - 1 >= 0) checkPos[x - 1][y - 1] = 1;
    else if (board[x - 1][y - 1] * board[x][y] < 0 && x - 1 >= 0 && y - 1 >= 0) checkPos[x - 1][y - 1] = 2;
    if (board[x + 1][y - 1] == 0 && x + 1 < 8 && y - 1 >= 0) checkPos[x + 1][y - 1] = 1;
    else if (board[x + 1][y - 1] * board[x][y] < 0 && x + 1 < 8 && y - 1 >= 0) checkPos[x + 1][y - 1] = 2;
    if (board[x][y - 1] == 0 && y - 1 >= 0) checkPos[x][y - 1] = 1;
    else if (board[x][y - 1] * board[x][y] < 0 && y - 1 >= 0) checkPos[x][y - 1] = 2;
}

void PositiveTot(int x, int y)
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

void PositiveHau(int x, int y) {
    PositiveXe(x, y);
    PositiveTuong(x, y);
}

bool falseChoose(int i,int j) {
    if (checkPos[i][j] == 0) {
        return false;
    }
    return true;
}


int main() {
    window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("../Data/Image/chesses.png");
	f->setTexture(texture);
	for (int i = 0; i < 32; i++) {
		f[i].setTexture(texture);
	}
	sf::Event event;
	loadPosition();
	while (window.isOpen()) {
        if (isMouse == true)    chessBoard();
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
                        sf::RectangleShape box;
                        box.setFillColor(sf::Color::Yellow);
                        box.setSize(sizeBtn);
                        box.setPosition(dy * cellSize + SCREEN_MARGIN, dx * cellSize + SCREEN_MARGIN);
                        window.draw(box);
                        if (board[dx][dy] == -5 || board[dx][dy] == 5) {
                            PositiveXe(dx, dy);
                        }
                        if (board[dx][dy] == -3 || board[dx][dy] == 3) {
                            PositiveTuong(dx, dy);
                        }
                        if (board[dx][dy] == -4 || board[dx][dy] == 4) {
                            PositiveMa(dx, dy);
                        }
                        if (board[dx][dy] == -2 || board[dx][dy] == 2) {
                            PositiveHau(dx, dy);
                        }
                        if (board[dx][dy] == -1 || board[dx][dy] == 1) {
                            PositiveVua(dx, dy);
                        }
                        if (board[dx][dy] == -6 || board[dx][dy] == 6) {
                            PositiveTot(dx, dy);
                        }
                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                if (checkPos[i][j] == 2) drawBox(i, j);
                                else if (checkPos[i][j] == 1)    drawBoxWhite(i, j);
                            }
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

                if (falseChoose(dx_n,dy_n)) {
                    board[dx_n][dy_n] = board[dx][dy];
                    board[dx][dy] = 0;
                    checkTurn = -checkTurn;
                }

                cout << "New Board: " << endl;
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        cout << board[i][j] << " ";
                    }
                    cout << endl;
                }

                loadPosition();
                reloadPos();
                //reset
                isMouse = true;
                click = 0;
            }
            
		}


		for (auto i : f) window.draw(i);

		window.display();
	}
}
