#include "Game.hpp"
#include "DxLib.h"
#include "InputKey.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mp_backGround = nullptr;
	mp_backGround = new BackGround();

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mp_backGround != nullptr) delete mp_backGround;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	mp_backGround->Draw();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	mp_backGround->Process();
}
