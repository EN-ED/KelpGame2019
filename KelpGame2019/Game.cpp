#include "Game.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BlurScreen g_blurScreen;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mp_backGround = nullptr;
	mp_backGround = new BackGround();

	mp_character = nullptr;
	mp_character = new Character();

	m_endFlag = false;

	g_blurScreen.Init(200, 6, -2, 0, 0);

	m_isFirstSpeedUp = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mp_character != nullptr) delete mp_character;
	if (mp_backGround != nullptr) delete mp_backGround;

	g_blurScreen.Release();
	g_blurScreen.~BlurScreen();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	if (mp_character->GetIsSpeedUp())
	{
		if (m_isFirstSpeedUp)
		{
			g_blurScreen.PreRenderBlurScreen();
			mp_backGround->Draw();
			mp_character->BlurDraw();
			g_blurScreen.PostRenderBlurScreen();

			mp_character->Draw();
		}
		else
		{
			m_isFirstSpeedUp = true;
			g_blurScreen.ReplayInit();
			g_blurScreen.PreRenderBlurScreen();
			mp_backGround->Draw();
			mp_character->BlurDraw();
			g_blurScreen.PostRenderBlurScreen();

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


	mp_backGround->SetSpeed(mp_character->GetSpeed());
}
