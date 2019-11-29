#include "Tutorial.hpp"



/// ---------------------------------------------------------------------------------------
void Tutorial::MainProcess()
{
	mp_backGround->Process();

	mp_character->Process();

	mp_backGround->SetSpeed(mp_character->GetSpeed());

	for (int i = 0; i != 4; ++i)
	{
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
			mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.7) >= mp_garbage[i]->GetX()
			/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
			&& mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.3) <= mp_garbage[i]->GetX() + 256
			/*石鹸の下端 が 障害物の上端 より大きい*/
			&& mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.7) >= mp_garbage[i]->GetY()
			/*石鹸の上端 が 障害物の下端 より小さい*/
			&& mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.3) <= mp_garbage[i]->GetY() + 256)
		{

			mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
		}
	}
}



/// ---------------------------------------------------------------------------------------
void Tutorial::StopProcess()
{
	if (m_stopNum == 1)
	{
		mp_character->Process();
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			m_blendValue = 255;
			m_stopNum = 2;
			m_stopFlag = false;
		}
	}
	else if (m_stopNum == 3)
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			m_blendValue = 255;
			m_stopNum = 4;
			m_stopFlag = false;
		}
	}
	else if (m_stopNum == 5)
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			m_blendValue = 255;
			m_stopNum = 6;
			m_stopFlag = false;
		}
	}
	else if (m_stopNum == 7)
	{
		mp_character->Process();
		if (PadData::GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, 0) == 1)
		{
			m_blendValue = 255;
			m_stopNum = 8;
			m_stopFlag = false;
		}
	}
}



/// ---------------------------------------------------------------------------------------
Tutorial::Tutorial()
{
	mp_character = new Character();
	mp_backGround = new BackGround(1);
	ZeroMemory(mp_garbage, sizeof(mp_garbage));
	for (int i = 0; i != 4; ++i)
	{
		if (i == 0)
		{
			mp_garbage[i] = new Garbage(1920 * 1, 1080 - 128 - 256, static_cast<Garbage::EDrawID>(0));
		}
		else if (i == 1)
		{
			mp_garbage[i] = new Garbage(1920 * 5, 1080 - 128 - 256, static_cast<Garbage::EDrawID>(1));
		}
		else if (i == 2)
		{
			mp_garbage[i] = new Garbage(1920 * 9, 1080 - 128 - 256, static_cast<Garbage::EDrawID>(2));
		}
		else if (i == 3)
		{
			mp_garbage[i] = new Garbage(1920 * 13, 1080 - 128 - 256, static_cast<Garbage::EDrawID>(0));
		}
	}

	mD_skip = LoadGraph("media\\tutorial\\ASkip.jpg");
	mD_AJump = LoadGraph("media\\tutorial\\ajump.jpg");
	mD_damage = LoadGraph("media\\tutorial\\damage.jpg");
	mD_speed = LoadGraph("media\\tutorial\\RB.jpg");
	mD_touyu = LoadGraph("media\\tutorial\\touyu.jpg");
	mD_start = LoadGraph("media\\tutorial\\start.jpg");

	m_stopNum = 0;
	m_blendValue = 255;
	m_stopFlag = false;
}



/// ---------------------------------------------------------------------------------------
Tutorial::~Tutorial()
{
	if (mD_skip != -1) DeleteGraph(mD_skip);
	if (mD_AJump != -1) DeleteGraph(mD_AJump);
	if (mD_damage != -1) DeleteGraph(mD_damage);
	if (mD_speed != -1) DeleteGraph(mD_speed);
	if (mD_touyu != -1) DeleteGraph(mD_touyu);
	if (mD_start != -1) DeleteGraph(mD_start);

	if (mp_character != nullptr) delete mp_character;
	if (mp_backGround != nullptr) delete mp_backGround;
	for (int i = 0; i != 4; ++i)
	{
		if (mp_garbage[i] != nullptr) delete mp_garbage[i];
	}
}



/// ---------------------------------------------------------------------------------------
void Tutorial::Draw()
{
	mp_backGround->Draw();
	mp_character->Draw();
	for (int i = 0; i != 4; ++i)
	{
		if (mp_garbage[i]->GetX() + 256 < 0) continue;
		mp_garbage[i]->Draw();
	}

	if (m_stopNum == 1)
	{
		DrawGraph(960 + 480 - 174, 540 - 23, mD_AJump, false);
	}
	else if (m_stopNum == 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (m_blendValue -= 5));
		DrawGraph(960 + 480 - 174, 540 - 23, mD_AJump, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (m_stopNum == 3)
	{
		DrawGraph(960 + 480 - 261, 540 - 23, mD_damage, false);
	}
	else if (m_stopNum == 4)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (m_blendValue -= 5));
		DrawGraph(960 + 480 - 261, 540 - 23, mD_damage, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (m_stopNum == 5)
	{
		DrawGraph(960 + 480 - 99, 540 - 23, mD_touyu, false);
	}
	else if (m_stopNum == 6)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (m_blendValue -= 5));
		DrawGraph(960 + 480 - 99, 540 - 23, mD_touyu, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (m_stopNum == 7)
	{
		DrawGraph(960 + 480 - 274, 540 - 23, mD_speed, false);
	}
	else if (m_stopNum == 8)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (m_blendValue -= 5));
		DrawGraph(960 + 480 - 274, 540 - 23, mD_speed, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawGraph(960 + 480 - 160, 540 - 23, mD_start, false);
	}

	DrawGraph(1920 - 171, 1080 - 45, mD_skip, false);
}



/// ---------------------------------------------------------------------------------------
void Tutorial::Process()
{
	if (m_stopFlag)
	{
		StopProcess();
	}
	else
	{
		MainProcess();
		if (mp_garbage[3]->GetX() <= -6000 && m_stopNum == 8)
		{
			m_stopNum = 9;
		}
		if (mp_garbage[3]->GetX() <= 960 && m_stopNum == 6)
		{
			m_stopNum = 7;
			m_stopFlag = true;
		}
		if (mp_garbage[2]->GetX() <= 960 && m_stopNum == 4)
		{
			m_stopNum = 5;
			m_stopFlag = true;
		}
		if (mp_garbage[1]->GetX() <= 960 && m_stopNum == 2)
		{
			m_stopNum = 3;
			m_stopFlag = true;
		}
		if (mp_garbage[0]->GetX() <= 960 && m_stopNum == 0)
		{
			m_stopNum = 1;
			m_stopFlag = true;
		}
	}


	if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1 && m_stopNum == 9)
	{
		BASICPARAM::e_nowScene = ESceneNumber::GAME;
	}

	if (PadData::GetButton(XINPUT_BUTTON_B, 0) == 1)
	{
		BASICPARAM::e_nowScene = ESceneNumber::GAME;
	}
}
