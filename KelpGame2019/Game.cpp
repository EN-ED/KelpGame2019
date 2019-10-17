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
		// 左より遠くに行ったら
		if (mp_garbage[i]->GetX() + 256 < 0) continue;

		
		// 石鹸君が加速していたら
		if (mp_character->GetIsSpeedUp())
		{
			mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
			continue;
		}
		// 石鹸君が加速していなかったら
		else
		{
			mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.8f));
		}


		// 既に石鹸君に対して障害物が当たっているフレーム中だったら
		if (mp_character->GetNowDamage() || mp_character->GetNowHeal()) continue;

		// 当たり判定
		if (/*石鹸の右端より1/4減らす が 障害物の左端 より大きい*/
			mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.75)		 >= mp_garbage[i]->GetX()
			/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
			&& mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.25)	 <= mp_garbage[i]->GetX() + 256
			/*石鹸の下端 が 障害物の上端 より大きい*/
			&& mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.75)	 >= mp_garbage[i]->GetY()
			/*石鹸の上端 が 障害物の下端 より小さい*/
			&& mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.25)	 <= mp_garbage[i]->GetY() + 256)
		{

			mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
		}
	}
}
