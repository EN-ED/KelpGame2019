#include "Game.hpp"
#include "DxLib.h"
#include "InputKey.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mp_backGround = nullptr;
	mp_backGround = new BackGround();

	mp_character = nullptr;
	mp_character = new Character();

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mp_character != nullptr) delete mp_character;
	if (mp_backGround != nullptr) delete mp_backGround;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	mp_backGround->Draw();


	mp_character->Draw();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	mp_backGround->Process();


	mp_character->Process();


	mp_backGround->SetIsSpeedUp(mp_character->GetIsSpeedUp());
}
