#pragma once
#include "WindowGame.h"
#include "EventInput.h"
#include "Connector.h"
#include <fstream>
using namespace sf;
enum class TypeIcon
{
	ChangePawn,
	NoChangePawn,
};
class Game 
{
private:
	EventInputGame eventInputGame;
	bool DrawSpriteInGame;
	sf::Texture t_ChangePawnBlack;
	sf::Sprite s_ChangePawnBlack;
	sf::Texture t_ChangePawnWhite;
	sf::Sprite s_ChangePawnWhite;
	string movesBlack;
	string movesWhite;
public:
	Game();
	void SelectionMovePlace();
	WindowGame* GetWindowGame();
	void DrawTurnPlayer();// ve luot nguoi choi
	StateMenu GetStateGame();// lay trang thai game
};