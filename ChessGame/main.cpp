 #include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<math.h>
#include <time.h>
#include<stack>
#include<algorithm>// min, max
#include<cstdbool>

using namespace sf;
using namespace std;

int size_ = 80;
Vector2f offset(50,50);
Vector2f sizeBtn(80, 80);

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 690;
const float SCREEN_MARGIN = 50.0f;

int board[8][8] =
{ -5,-4,-3,-2,-1,-3,-4,-5,
-6,-6,-6,-6,-6,-6,-6,-6,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
6, 6, 6, 6, 6, 6, 6, 6,
5, 4, 3, 2, 1, 3, 4, 5 };

int checkPos[9][9];

typedef struct QuanCo
{
    Sprite s;
    int index, cost;
    int global;
};

QuanCo f[33]; //mang luu cac quan co

class GameManager
{
public:
    GameManager(RenderWindow& window) :window(window) {}
    Vector2f positiveMove[32];//vi tri cac nuoc co the di chuyen
    int positiveCount;// so nuoc co the di chuyen
    stack<Vector2f> posS;//luu tru vi tri cac nuoc di
    stack<int> nS;//luu tru index cua quan di

    void move(int n, Vector2f oldPos, Vector2f newPos);//ham danh co
    void Undo();//ham quay lai
    void Create();
    void Play();// choi: moi thao tac o day
    void resetGlobal();
    void resetMatrix(int a[9][9]);

    void PositiveCastle(int n, int x, int y, int grid[9][9]);//tim cac nuoc co the di cua Quan Xe
    void PositiveBishop(int n, int x, int y, int grid[9][9]);
    void PositiveKnight(int n, int x, int y, int grid[9][9]);
    void PositiveKing(int n, int x, int y, int grid[9][9]);
    void PositivePawn(int n, int x, int y, int grid[9][9]);
    void toCapture(int n, int y);
    void IncreasePositive(int i, int j);//tang so nuoc co the di
    void PositiveMoving(int n);//tim cac nuoc co the di ung voi index n
    void Personal(int click, int n, sf::Vector2i pos, sf::Vector2f oldPos, sf::Vector2f newPos, int count, sf::Sound sound, bool LuotChoi);
    int checkWin();
    //AI
    int CostMove();//gia tri diem cua toan bo ban co ung voi gia tri moi quan
    //int Minimax(int depth,bool luot);// Chien luoc Minimax
    int Alpha_Beta(int depth, bool luot, int alpha, int beta);//cat tia alpha beta
    Vector2f getNextMove(bool luot);// tra ve nuoc di tot nhat theo chien luoc phia tren
    void computer(sf::Vector2f newPos, sf::Vector2f oldPos, bool LuotChoi);
private:
    sf::RenderWindow& window;
};

class Board {
public:
    Board(sf::RenderWindow &window):window(window){}
    void chessBoard();
    void drawBox(sf::Sprite sprite, sf::Texture draw_box, int x, int y);
    void drawBoxPos(int x, int y);
    void drawBoxDeath(int x,int y);
    void drawCapture(int n);
    sf::ConvexShape createRoundedRectangle(float width, float height, float radius, unsigned int cornerPoints);
private:
    sf::RenderWindow& window;
};

int GameManager::Alpha_Beta(int depth, bool luot, int alpha, int beta)
{
    if (depth == 0) {
        return CostMove();
    }
    Vector2f positiveMovetemp[32];//luu lai vi tri cac nuoc co the di
    if (luot == true) {
        int bestMove = -10000;//gia cua bestMove ban dau
        for (int j = 16; j < 32; j++)//cac quan cua nguoi choi
        {
            if (f[j].s.getPosition() == Vector2f(-100, -100)) continue;
            PositiveMoving(j);
            int coun = positiveCount;//ta khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
            positiveCount = 0;
            for (int i = 0; i < coun; i++)  positiveMovetemp[i] = positiveMove[i];
            for (int i = 0; i < coun; i++)
            {
                move(j, f[j].s.getPosition(), positiveMovetemp[i]);
                bestMove = max(bestMove, Alpha_Beta(depth - 1, !luot, alpha, beta));
                //undo
                Undo();
                alpha = max(alpha, bestMove);
                if (beta <= alpha)  return bestMove;
            }
        }
        return bestMove;
    }
    else {
        int bestMove = 10000;//gia cua bestMove ban dau
        for (int j = 0; j < 16; j++)//quan cua may
        {
            if (f[j].s.getPosition() == Vector2f(-100, -100)) continue;
            PositiveMoving(j);
            int coun = positiveCount;//ta khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
            positiveCount = 0;
            for (int i = 0; i < coun; i++)  positiveMovetemp[i] = positiveMove[i];
            for (int i = 0; i < coun; i++)
            {
                move(j, f[j].s.getPosition(), positiveMovetemp[i]);
                bestMove = min(bestMove, Alpha_Beta(depth - 1, !luot, alpha, beta));
                //undo
                Undo();
                beta = min(beta, bestMove);
                if (beta <= alpha)  return bestMove;
            }
        }
        return bestMove;
    }
}

void GameManager::IncreasePositive(int i, int j) {
    positiveMove[positiveCount] = Vector2f(i * size_, j * size_) + offset;
    positiveCount++;
}

void GameManager::toCapture(int n,int y) {
    //phong hau cho tot
    if (y == 0) {
        nS.push(100);//de ty undo xoa phong hau di
    }
    if (y == 7 ) {
        nS.push(-100);
    }
    sf::Event anotherEvent;
    bool check = true;
    int index = f[n].index;
    if (window.pollEvent(anotherEvent)) {
        if (anotherEvent.type == sf::Event::MouseButtonPressed) {
            if (anotherEvent.key.code == sf::Mouse::Left) {
                sf::Vector2i posCap = sf::Mouse::getPosition(window);
                cout << "PosCap: " << posCap.x << endl;
                int dy = (int)(posCap.x - SCREEN_MARGIN) / 80;
                int dx = (int)(posCap.y - SCREEN_MARGIN) / 80;
                cout << "dy: " << dx << endl;
                if (f[n].index == 6) {
                    if (dx == 1) index = (index / 6) * 2;
                    if (dx == 2) index = (index / 6) * 3;
                    if (dx == 3) index = (index / 6) * 4;
                    if (dx == 4) index = (index / 6) * 5;
                    check = false;
                }
                else if (index == -6) {
                    if (dx == 6) index = (index / 6) * 2;
                    if (dx == 5) index = (index / 6) * 3;
                    if (dx == 4) index = (index / 6) * 4;
                    if (dx == 3) index = (index / 6) * 5;
                    check = false;
                }
            }
        }
    }
    f[n].index = index;
    int v = 0, g;
    g = abs(f[n].index);
    if (g == 5)  v = 50;
    else if (g == 4 || g == 3)  v = 30;
    else if (g == 2)  v = 90;
    else if (g == 1)  v = 900;
    else if (g == 6)  v = 10;
    f[n].cost = f[n].index / g * v;
    if(index > 0)   f[n].s.setTextureRect({ size_ * (index - 1),size_,size_,size_ });
    else if(index < 0)  f[n].s.setTextureRect({ size_ * (index - 1),0,size_,size_ });
}

void GameManager::move(int n, Vector2f oldPos, Vector2f newPos)
{
    posS.push(oldPos);
    posS.push(newPos);
    nS.push(n);

    //di chuyen em an vao vi tri moi 
    for (int i = 0; i < 32; i++) {
        if (f[i].s.getPosition() == newPos) {
            f[i].s.setPosition(-100, -100);//di chuyen em bi an ra khoi man hinh
            posS.push(newPos);
            posS.push(Vector2f(-100, -100));
            nS.push(i);
            break;//neu ta dat f[n].s.setPosition(newPos) len truoc ma ko co break=> bi mat not con nay
        }
    }
    f[n].s.setPosition(newPos);
}

void GameManager::Undo()
{
    int n = nS.top();
    nS.pop();
    Vector2f p = posS.top();//kiem tra xem co = (-100,-100) => day la con bi an
    posS.pop();
    Vector2f q = posS.top();
    posS.pop();
    if (n == 100) {
        n = nS.top();
        nS.pop();
        f[n].index = 6;
        f[n].cost = 10;
        f[n].s.setTextureRect(IntRect(5 * size_, size_, size_, size_));
    }
    if (n == -100) {
        n = nS.top();
        nS.pop();
        f[n].index = -6;
        f[n].cost = -10;
        f[n].s.setTextureRect(IntRect(5 * size_, 0, size_, size_));
    }
    f[n].s.setPosition(q);

    if (p == Vector2f(-100, -100))  Undo();// luc nay moi dy chuyen con an
}

void GameManager::Create()//gan gia tri can thiet vao danh sach Quan co
{
    positiveCount = 0;//so nuoc co the di ban dau duong nhien =0(chua chon gi ca)
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].index = n;
            f[k].s.setTextureRect(IntRect(size_ * x, size_ * y, size_, size_));
            f[k].s.setPosition(size_ * j + offset.x, size_ * i + offset.y);
            //cost
            int v = 0, g;
            g = abs(f[k].index);
            if (g == 5)  v = 50;
            else if (g == 4 || g == 3)  v = 30;
            else if (g == 2)  v = 90;
            else if (g == 1)  v = 900;
            else if (g == 6)  v = 10;
            f[k].cost = f[k].index / g * v;
            k++;
        }
    }
}

Vector2f GameManager::getNextMove(bool luot)
{
    Vector2f oldPos, newPos, oldPostemp, newPostemp;// ta can tim vi tri co minimax nho nhat de ung voi may( quan den)
    int minimaxtemp = 10000, minimax = 10000;
    int count1, n;
    Vector2f positiveMovetemp[32];

    for (int i = 0; i < 16; i++)
    {
        if (f[i].s.getPosition() == Vector2f(-100, -100)) continue;
        //////
        PositiveMoving(i);
        count1 = positiveCount;//khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
        positiveCount = 0;
        ///set///
        for (int k = 0; k < count1; k++) positiveMovetemp[k] = positiveMove[k];
        //set oldPos va newPos  tam thoi
        oldPostemp = f[i].s.getPosition();
        //newPostemp=positiveMove[0];
        for (int j = 0; j < count1; j++)
        {
            move(i, oldPostemp, positiveMovetemp[j]);
            int alpha = -9999, beta = 9999;
            int temp = Alpha_Beta(3, !luot, alpha, beta);
            if (minimaxtemp > temp) {
                newPostemp = positiveMovetemp[j];
                minimaxtemp = temp;
            }
            Undo();
        }
        if (minimax > minimaxtemp) {
            minimax = minimaxtemp;
            oldPos = oldPostemp;
            newPos = newPostemp;
            n = i;
        }
    }
    //lay cac thong tin nuoc di
    posS.push(oldPos);//luu tam o trong stack ty ra ngoai xoa di
    nS.push(n);
    return newPos;
}

void GameManager::computer(sf::Vector2f newPos,sf::Vector2f oldPos,bool LuotChoi)
{
    newPos = getNextMove(LuotChoi);
    int c = nS.top();   nS.pop();//lay dk thong tin roi xoa di
    oldPos = posS.top();  posS.pop();//vi ham move tu nhet trong stack roi
    move(c, oldPos, newPos);


}

int GameManager::CostMove()// don gian con nao bi chet thi khong tinh diem cua con day
{
    int s = 0;
    for (int i = 0; i < 32; i++)
    {
        if (f[i].s.getPosition() == Vector2f(-100, -100)) continue;//neu no da bi out-> ko tinh diem
        s += f[i].cost;
    }
    return s;
}

void GameManager::PositivePawn(int n, int x, int y, int grid[9][9])
{
    int k = grid[x][y] / abs(grid[x][y]);// 1 hoac -1
    if ((y == 1 || y == 6) && grid[x][y - k] == 0 && grid[x][y - 2 * k] == 0 && y - 2 * k >= 0 && y - 2 * k < 8) IncreasePositive(x, y - 2 * k);
    if (grid[x][y - k] == 0 && y - k >= 0 && y - k < 8)            IncreasePositive(x, y - k);
    if (grid[x + 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 8 && x + 1 < 8) {
        IncreasePositive(x + 1, y - k);
        checkPos[y - k][x + 1] = 1;
    }
    if (grid[x - 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 8 && x - 1 >= 0) {
        IncreasePositive(x - 1, y - k);
        checkPos[y - k][x - 1] = 1;
    }
}

void GameManager::PositiveKing(int n, int x, int y, int grid[9][9])//xet 8 vi tri co the di cua vua
{
    if (grid[x + 1][y] == 0 && x + 1 < 8)     IncreasePositive(x + 1, y);
    else if (grid[x][y] * grid[x + 1][y] < 0 && x + 1 < 8) {
        IncreasePositive(x + 1, y);
        checkPos[y][x + 1] = 1;
    }
    if (grid[x - 1][y] == 0 && x - 1 >= 0)     IncreasePositive(x - 1, y);
    else if (grid[x][y] * grid[x - 1][y] < 0 && x - 1 >= 0) {
        IncreasePositive(x - 1, y);
        checkPos[y][x - 1] = 1;
    }
    if (grid[x + 1][y + 1] == 0 && x + 1 < 8 && y + 1 < 8)  IncreasePositive(x + 1, y + 1);
    else if (grid[x][y] * grid[x + 1][y + 1] < 0 && x + 1 < 8 && y + 1 < 8) {
        IncreasePositive(x + 1, y + 1);
        checkPos[y + 1][x + 1] = 1;
    }
    if (grid[x - 1][y + 1] == 0 && x - 1 >= 0 && y + 1 < 8)  IncreasePositive(x - 1, y + 1);
    else if (grid[x][y] * grid[x - 1][y + 1] < 0 && x - 1 >= 0 && y + 1 < 8) {
        IncreasePositive(x - 1, y + 1);
        checkPos[x - 1][y + 1] = 1;
    }
    if (grid[x][y + 1] == 0 && y + 1 < 8)     IncreasePositive(x, y + 1);
    else if (grid[x][y] * grid[x][y + 1] < 0 && y + 1 < 8) {
        IncreasePositive(x, y + 1);
        checkPos[y + 1][x] = 1;
    }
    if (grid[x - 1][y - 1] == 0 && x - 1 >= 0 && y - 1 >= 0) IncreasePositive(x - 1, y - 1);
    else if (grid[x][y] * grid[x - 1][y - 1] < 0 && x - 1 >= 0 && y - 1 >= 0) {
        IncreasePositive(x - 1, y - 1);
        checkPos[y - 1][x - 1] = 1;
    }
    if (grid[x + 1][y - 1] == 0 && y - 1 >= 0 && x + 1 < 8)  IncreasePositive(x + 1, y - 1);
    else if (grid[x][y] * grid[x + 1][y - 1] < 0 && y - 1 >= 0 && x + 1 < 8) {
        IncreasePositive(x + 1, y - 1);
        checkPos[y - 1][x + 1] = 1;
    }
    if (grid[x][y - 1] == 0 && y - 1 >= 0)     IncreasePositive(x, y - 1);
    else if (grid[x][y] * grid[x][y - 1] < 0 && y - 1 >= 0) {
        IncreasePositive(x, y - 1);
        checkPos[y - 1][x] = 1;
    }
}

void GameManager::PositiveKnight(int n, int x, int y, int grid[9][9])//xet 8 vi tri co the di cua ma
{
    if (grid[x + 2][y + 1] == 0 && x + 2 < 8 && y + 1 < 8)  IncreasePositive(x + 2, y + 1);
    else if (grid[x][y] * grid[x + 2][y + 1] < 0 && x + 2 < 8 && y + 1 < 8) {
        IncreasePositive(x + 2, y + 1);
        checkPos[y + 1][x + 2] = 1;
    }
    if (grid[x + 2][y - 1] == 0 && y - 1 >= 0 && x + 2 < 8)  IncreasePositive(x + 2, y - 1);
    else if (grid[x][y] * grid[x + 2][y - 1] < 0 && y - 1 >= 0 && x + 2 < 8) {
        IncreasePositive(x + 2, y - 1);
        checkPos[y - 1][x + 2] = 1;
    }

    if (grid[x - 2][y + 1] == 0 && x - 2 >= 0 && y + 1 < 8)  IncreasePositive(x - 2, y + 1);
    else if (grid[x][y] * grid[x - 2][y + 1] < 0 && x - 2 >= 0 && y + 1 < 8) {
        IncreasePositive(x - 2, y + 1);
        checkPos[y + 1][x - 2] = 1;
    }
    if (grid[x - 2][y - 1] == 0 && x - 2 >= 0 && y - 1 >= 0) IncreasePositive(x - 2, y - 1);
    else if (grid[x][y] * grid[x - 2][y - 1] < 0 && x - 2 >= 0 && y - 1 >= 0) {
        IncreasePositive(x - 2, y - 1);
        checkPos[y - 1][x - 2] = 1;
    }
    if (grid[x + 1][y + 2] == 0 && x + 1 < 8 && y + 2 < 8)  IncreasePositive(x + 1, y + 2);
    else if (grid[x][y] * grid[x + 1][y + 2] < 0 && x + 1 < 8 && y + 2 < 8) {
        IncreasePositive(x + 1, y + 2);
        checkPos[y + 2][x + 1] = 1;
    }
    if (grid[x - 1][y + 2] == 0 && x - 1 >= 0 && y + 2 < 8)  IncreasePositive(x - 1, y + 2);
    else if (grid[x][y] * grid[x - 1][y + 2] < 0 && x - 1 >= 0 && y + 2 < 8) {
        IncreasePositive(x - 1, y + 2);
        checkPos[y + 2][x - 1] = 1;
    }
    if (grid[x + 1][y - 2] == 0 && y - 2 >= 0 && x + 1 < 8)  IncreasePositive(x + 1, y - 2);
    else if (grid[x][y] * grid[x + 1][y - 2] < 0 && y - 2 >= 0 && x + 1 < 8) {
        IncreasePositive(x + 1, y - 2);
        checkPos[y - 2][x + 1] = 1;
    }
    if (grid[x - 1][y - 2] == 0 && x - 1 >= 0 && y - 2 >= 0) IncreasePositive(x - 1, y - 2);
    else if (grid[x][y] * grid[x - 1][y - 2] < 0 && x - 1 >= 0 && y - 2 >= 0) {
        IncreasePositive(x - 1, y - 2);
        checkPos[y - 2][x - 1] = 1;
    }
}

void GameManager::PositiveBishop(int n, int x, int y, int grid[9][9])//tu vi tri (x,y) xet ra 4 huong cheo
{
    for (int i = x + 1, j = y + 1; (i < 8 && j < 8); i++, j++)
    {
        if (grid[i][j] != 0) {
            if (grid[i][j] * grid[x][y] < 0) {
                IncreasePositive(i, j);
                checkPos[j][i] = 1;
            }
            break;
        }
        IncreasePositive(i, j);
    }
    for (int i = x + 1, j = y - 1; (i < 8 && j >= 0); i++, j--)
    {
        if (grid[i][j] != 0) {
            if (grid[i][j] * grid[x][y] < 0) {
                IncreasePositive(i, j);
                checkPos[j][i] = 1;
            }
            break;
        }
        IncreasePositive(i, j);
    }
    for (int i = x - 1, j = y + 1; (i >= 0 && j < 8); i--, j++)
    {
        if (grid[i][j] != 0) {
            if (grid[i][j] * grid[x][y] < 0) {
                IncreasePositive(i, j);
                checkPos[j][i] = 1;
            }
            break;
        }
        IncreasePositive(i, j);
    }
    for (int i = x - 1, j = y - 1; (i >= 0 && j >= 0); i--, j--)
    {
        if (grid[i][j] != 0) {
            if (grid[i][j] * grid[x][y] < 0) {
                IncreasePositive(i, j);
                checkPos[j][i] = 1;
            }
            break;
        }
        IncreasePositive(i, j);
    }
}

void GameManager::PositiveCastle(int n, int x, int y, int grid[9][9])//tu vi tri (x,y) xet ra 4 huong ngang
{
    for (int i = x + 1; i < 8; i++)
    {
        if (grid[i][y] != 0) {
            if (grid[i][y] * grid[x][y] < 0) {
                IncreasePositive(i, y);
                checkPos[y][i] = 1;
            }
            break;
        }
        IncreasePositive(i, y);
    }
    for (int i = x - 1; i >= 0; i--)
    {
        if (grid[i][y] != 0) {
            if (grid[i][y] * grid[x][y] < 0) {
                IncreasePositive(i, y);
                checkPos[y][i] = 1;
            }
            break;
        }
        IncreasePositive(i, y);
    }
    for (int j = y + 1; j < 8; j++)
    {
        if (grid[x][j] != 0) {
            if (grid[x][j] * grid[x][y] < 0) {
                IncreasePositive(x, j);
                checkPos[j][x] = 1;
            }
            break;
        }
        IncreasePositive(x, j);
    }
    for (int j = y - 1; j >= 0; j--)
    {
        if (grid[x][j] != 0) {
            if (grid[x][j] * grid[x][y] < 0) {
                IncreasePositive(x, j);
                checkPos[j][x] = 1;
            }
            break;
        }
        IncreasePositive(x, j);
    }
}

void GameManager::PositiveMoving(int n)
{
    Vector2f pos = f[n].s.getPosition() - offset;
    int x = pos.x / size_;
    int y = pos.y / size_;

    int grid[9][9];//mang luoi(8x8) luu lai cac vi tri ban co:
    Vector2i vtri;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = 0;// neu khong co quan co nao o O nay thi =0
    for (int j = 0; j < 32; j++)
    {
        vtri = Vector2i(f[j].s.getPosition() - offset);
        grid[vtri.x / size_][vtri.y / size_] = f[j].index;// neu co = index cua quan co
    }

    if (abs(f[n].index) == 5)  PositiveCastle(n, x, y, grid);//xe
    else if (abs(f[n].index) == 4)  PositiveKnight(n, x, y, grid);//ma
    else if (abs(f[n].index) == 3)  PositiveBishop(n, x, y, grid);//tuong 
    else if (abs(f[n].index) == 2)//hau: hop lai cac nuoc cua ca xe va tuong
    {
        PositiveCastle(n, x, y, grid);
        PositiveBishop(n, x, y, grid);
    }
    else if (abs(f[n].index) == 1)  PositiveKing(n, x, y, grid);//vua
    else   PositivePawn(n, x, y, grid); //tot
}

void GameManager::Personal(int click, int n, sf::Vector2i pos, sf::Vector2f oldPos,sf::Vector2f newPos, int count,sf::Sound sound, bool LuotChoi)
{
    if (click == 1) {
        bool isMove = false;
        for (int i = 0; i < 16; i++)
        {
            if (f[i].s.getGlobalBounds().contains(pos.x + offset.x, pos.y + offset.y))
            {
                isMove = true;
                n = i;
                f[n].global = 1;
                oldPos = f[n].s.getPosition();
            }
        }
        if (!isMove)  click = 0;
        else {
            PositiveMoving(n); count = positiveCount; positiveCount = 0;
        }
    }
    if (click == 2)
    {
        f[n].s.setColor(Color::White);
        int x = pos.x / size_;   int y = pos.y / size_;
        newPos = Vector2f(x * size_, y * size_) + offset;
        //chi di chuyen trong vung positiveMove
        for (int i = 0; i < count; i++)
        {
            if (positiveMove[i] == newPos) {
                move(n, oldPos, newPos);
                sound.play();
                LuotChoi = !LuotChoi;
            }
        }
        //reset
        count = 0;
        click = 0;

    }
}

int GameManager::checkWin()
{   
    int checkP = false;
    int checkB = false;

    sf::Vector2f lose(-100, -100);

    for (int i = 0; i < 32; i++) {
        if (f[i].index == 1 && f[i].s.getPosition() != lose) checkP = true;
        if (f[i].index == -1 && f[i].s.getPosition() != lose)    checkB = true;
    }
    if (checkP == false && checkB == true) return -1;
    if (checkB == false && checkP == true) return 1;
    return 0;
}

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

    for (int i = 0; i < 32; i++) {
        sf::Vector2f pos = f[i].s.getPosition() - offset;
        int y = pos.x / size_;
        int x = pos.y / size_;
        if (f[i].global == 1)    drawBoxPos(x, y);
    }
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

void GameManager::resetGlobal() {
    for (int i = 0; i < 32; i++) {
        f[i].global = 0;
    }
}

void GameManager::resetMatrix(int a[9][9])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            a[i][j] = 0;
        }
    }
}


void GameManager::Play()
{

    Board bgame(window);
    Texture t1, t2, t3;
    t1.loadFromFile("../Data/Image/chesses.png");
    t3.loadFromFile("../Data/Image/legalMove.png");

    for (int i = 0; i < 32; i++) f[i].s.setTexture(t1);
    Sprite sPositive(t3);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../Data/Audio/moveSound.ogg")) {
        buffer.loadFromFile("Data/Audio/moveSound.ogg");
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    Create();//khoi tao

    bool LuotChoi = true;//luot choi : = true=> nguoi ... =false => may
    Vector2f oldPos, newPos;// luu vi tri click lan1 va lan2
    int n = 0, click = 0, count = 0;
    Vector2i pos;//vitri chuot khi click
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            ////move back//////
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::BackSpace)
                {
                    Undo();
                }
            /////click///////
            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                {
                    pos = Mouse::getPosition(window) - Vector2i(offset);
                    click++;
                }
        }

        if (LuotChoi == true)
        {
            if (click == 1) {
                bool isMove = false;

                for (int i = 16; i < 32; i++)
                {
                    if (f[i].s.getGlobalBounds().contains(pos.x + offset.x, pos.y + offset.y))
                    {
                        isMove = true;
                        n = i;
                        f[n].global = 1;
                        oldPos = f[n].s.getPosition();
                    }
                }
                if (!isMove)  click = 0;
                else {
                    PositiveMoving(n); count = positiveCount; positiveCount = 0;
                }
            }
            if (click == 2)
            {
                f[n].s.setColor(Color::White);
                int x = pos.x / size_;   int y = pos.y / size_;
                newPos = Vector2f(x * size_, y * size_) + offset;
                //chi di chuyen trong vung positiveMove
                for (int i = 0; i < count; i++)
                {
                    if (positiveMove[i] == newPos) {
                        move(n, oldPos, newPos);
                        sound.play();
                        int y = int((newPos - offset).y / size_);
                        //cout << "y new: " << y <<" "<<f[n].index<< endl;
                        while ((y == 0 && f[n].index == 6) || (y == 7 && f[n].index == -6)) {
                            bgame.drawCapture(n);
                            toCapture(n, y);
                            window.display();
                        }

                        LuotChoi = !LuotChoi;
                    }
                }
                //reset
                count = 0;
                click = 0;

            }
        }
        else  //computer moving
        {
            computer(newPos, oldPos, LuotChoi);
            sound.play();
            LuotChoi = !LuotChoi;
            //reset
            click = 0;
            //Personal(click,n,pos,oldPos,newPos,count,sound,LuotChoi);
        }

        if (click == 0) {
            resetGlobal();
            resetMatrix(checkPos);
        }

        if (checkWin() == 1) {
            cout << "You Win" << endl;
            Create();
        }
        else if (checkWin() == -1) {
            cout << "You Lose" << endl;
            Create();
        }

        ////// draw  ///////
        bgame.chessBoard();
        for (int i = 0; i < count; i++) {
            sPositive.setPosition(positiveMove[i]);
            window.draw(sPositive);
        }
        if (click == 1) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (checkPos[i][j] == 1)   bgame.drawBoxDeath(i, j);
                }
            }
        }
        for (int i = 0; i < 32; i++) {
            window.draw(f[i].s);
        }
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Chess! Alpha Beta Pruning");
    GameManager gm(window);
    gm.Play();

}
