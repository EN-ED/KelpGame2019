#include "Game.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BlurScreen g_blurScreen;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mp_backGround = nullptr;
	mp_backGround = new BackGround();

	mp_character = nullptr;
	mp_character = new Character();

	mp_chaser = nullptr;
	mp_chaser = new Chaser();

	m_endFlag = false;

	g_blurScreen.Init(200, 6, -2, 0, 0);

	m_isFirstSpeedUp = false;

	for (int i = 0; i != m_garbageNum; ++i)
	{
		mp_garbage[i] = nullptr;
		mp_garbage[i] = new Garbage(1920  + (i * 256), 1080 - 128 - 256, static_cast<Garbage::EDrawID>(i));
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	for (int i = 0; i != m_garbageNum; ++i)
	{
		if (mp_garbage[i] != nullptr) delete mp_garbage[i];
	}
	if (mp_chaser != nullptr) delete mp_chaser;
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

			for (int i = 0; i != m_garbageNum; ++i)
			{
				if (mp_garbage[i]->GetX() + 256 < 0) continue;
				mp_garbage[i]->Draw();
			}
			mp_chaser->Draw();
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

			for (int i = 0; i != m_garbageNum; ++i)
			{
				if (mp_garbage[i]->GetX() + 256 < 0) continue;
				mp_garbage[i]->Draw();
			}
			mp_chaser->Draw();
			mp_character->Draw();
		}
	}
	else
	{
		mp_backGround->Draw();
		for (int i = 0; i != m_garbageNum; ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			mp_garbage[i]->Draw();
		}
		mp_character->Draw();
		mp_chaser->Draw();
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	mp_backGround->Process();


	mp_character->Process();


	mp_chaser->Process();


	mp_chaser->SetPlyayerSpeed(mp_character->GetSpeed(), mp_character->GetDefaultMAXSpeed());


	mp_backGround->SetSpeed(mp_character->GetSpeed());


	for (int i = 0; i != m_garbageNum; ++i)
	{
		if (mp_garbage[i]->GetX() + 256 < 0) continue;
		if (mp_character->GetIsSpeedUp())
		{
			mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.5f));
			continue;
		}
		else
		{
			mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.25f));
		}
		if (/*ÎŒ²‚Ì‰E’[ ‚ª áŠQ•¨‚Ì¶’[ ‚æ‚è‘å‚«‚¢*/
			mp_character->GetAreaX() + mp_character->GetSize()		 >= mp_garbage[i]->GetX()
			/*ÎŒ²‚Ì¶’[ ‚ª áŠQ•¨‚Ì¶’[‚ÆáŠQ•¨‚Ì‘¬“x ‚æ‚è¬‚³‚¢*/
			&& mp_character->GetAreaX()								 <= mp_garbage[i]->GetX() + static_cast<int>(mp_character->GetSpeed() * 0.25f)
			/*ÎŒ²‚Ì‰º’[ ‚ª áŠQ•¨‚Ìã’[ ‚æ‚è‘å‚«‚¢*/
			&& mp_character->GetAreaY() + mp_character->GetSize()	 >= mp_garbage[i]->GetY()
			/*ÎŒ²‚Ìã’[ ‚ª áŠQ•¨‚Ì‰º’[ ‚æ‚è¬‚³‚¢*/
			&& mp_character->GetAreaY()								 <= mp_garbage[i]->GetY() + 256)
		{

			mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
		}
	}
}
