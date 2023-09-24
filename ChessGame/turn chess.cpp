#include "Game.h"
Game::Game()
{
	IntGame();
}
void Game::DrawTurnPlayer()
{
	Texture t_Turn;
	Sprite s_Turn;
	Texture t_TurnBlack;
	Sprite s_TurnBlack;
	Texture t_TurnWhite;
	Sprite s_TurnWhite;
	t_Turn.loadFromFile("images/menu/turn.png");
	t_TurnBlack.loadFromFile("../Data/Image/turnblack.png");
	t_TurnWhite.loadFromFile("../Data/Image/turnwhite.png");
	s_Turn.setTexture(t_Turn);
	s_TurnBlack.setTexture(t_TurnBlack);
	s_TurnWhite.setTexture(t_TurnWhite);
	s_Turn.setPosition(880, 120);
	s_TurnBlack.setPosition(900, 200);
	s_TurnWhite.setPosition(900, 200);
	if (turnPlayer == TurnPlayer::P1Play)
	{
		windowGame.Draw(s_TurnWhite);
		windowGame.Draw(s_Turn);
	}
	else
	{
		windowGame.Draw(s_TurnBlack);
		windowGame.Draw(s_Turn);
	}
	StateMenu Game::GetStateGame()
	{
		return stateGame;
	}
	void Game::DrawChooseChangePawn()
	{
		if (changePawn == TypeIcon::ChangePawn)
		{
			if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorGame::Black)
			{
				windowGame.Draw(s_ChangePawnBlack);
			}
			else
			{
				windowGame.Draw(s_ChangePawnWhite);
			}
		}


	}
}