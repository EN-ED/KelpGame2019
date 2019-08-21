#include "Game.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mp_backGround = nullptr;
	mp_backGround = new BackGround();

	mp_character = nullptr;
	mp_character = new Character();

	m_endFlag = false;

	BlurScreen::Init(200, 6, -2, 0, 0);

	m_isFirstSpeedUp = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mp_character != nullptr) delete mp_character;
	if (mp_backGround != nullptr) delete mp_backGround;

	BlurScreen::Release();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	if (mp_character->GetIsSpeedUp())
	{
		if (m_isFirstSpeedUp)
		{
			BlurScreen::PreRenderBlurScreen();
			mp_backGround->Draw();
			mp_character->BlurDraw();
			BlurScreen::PostRenderBlurScreen();

			mp_character->Draw();
		}
		else
		{
			m_isFirstSpeedUp = true;
			BlurScreen::ReplayInit();
			BlurScreen::PreRenderBlurScreen();
			mp_backGround->Draw();
			mp_character->BlurDraw();
			BlurScreen::PostRenderBlurScreen();

			mp_character->Draw();
		}
	}
	else
	{
		mp_backGround->Draw();


		mp_character->Draw();
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	mp_backGround->Process();


	mp_character->Process();


	mp_backGround->SetIsSpeedUp(mp_character->GetIsSpeedUp());
}
