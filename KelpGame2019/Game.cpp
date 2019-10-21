#include "Game.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BlurScreen g_blurScreen;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::FirstDraw()
{
	mp_backGround->Draw();

	mp_character->FirstDraw(m_firstCharacterX, 1080 - 128 - 192, m_firstCharacterTurn);

	mp_chaser->FirstDraw(m_firstchaserX);

	if (m_firstFrameCount < 490 && m_firstFrameCount> 450)
	{
		DrawGraph(1920 / 2 - 64, 1080 / 2 - 64, m_firstTimer[0], true);
	}
	else if (m_firstFrameCount <= 450 && m_firstFrameCount > 390)
	{
		DrawGraph(1920 / 2 - 64, 1080 / 2 - 64, m_firstTimer[1], true);
	}
	else if (m_firstFrameCount <= 390 && m_firstFrameCount > 330)
	{
		DrawGraph(1920 / 2 - 64, 1080 / 2 - 64, m_firstTimer[2], true);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::FirstProcess()
{
	m_firstFrameCount++;
	if (m_firstFrameCount == 60)
	{
		m_firstCharacterTurn = false;
	}
	else if (m_firstFrameCount == 120)
	{
		m_firstCharacterTurn = true;
	}
	else if (m_firstFrameCount >= 180 && m_firstFrameCount < 210)
	{
		if (m_firstCharacterX < 1920)
		{
			m_firstCharacterX += 100;
		}
		m_firstBackGroundX = -100;
	}
	else if (m_firstFrameCount > 220 && m_firstFrameCount < 250)
	{
		m_firstchaserX += 10;
		m_firstBackGroundX = 40;
		m_firstCharacterTurn = false;
	}
	else if(m_firstFrameCount > 250 && m_firstFrameCount < 500)
	{
		if (m_firstCharacterX > 284 - 10)
		{
			m_firstCharacterX -= 10;
		}
		if (m_firstBackGroundX < 70)
		{
			m_firstBackGroundX++;
		}
		if (m_firstchaserX < 256 - 512)
		{
			m_firstchaserX++;
		}
		else
		{
			m_firstchaserX--;
		}
	}
	else if(m_firstFrameCount >= 500)
	{
		m_nowMove = NowMove::main;
	}


	mp_backGround->Process();
	mp_backGround->SetSpeed(static_cast<float>(m_firstBackGroundX));

	mp_chaser->FirstProcess();

	mp_character->FirstProcess();


	if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
	{
		m_nowMove = NowMove::main;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::MainDraw()
{
	if (mp_character->GetIsSpeedUp())
	{
		if (m_isFirstSpeedUp)
		{
			g_blurScreen.PreRenderBlurScreen();
			mp_backGround->Draw();
			mp_character->BlurDraw();
			g_blurScreen.PostRenderBlurScreen();

			for (size_t i = 0, n = mp_garbage.size(); i != n; ++i)
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

			for (size_t i = 0, n = mp_garbage.size(); i != n; ++i)
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
		for (size_t i = 0, n = mp_garbage.size(); i != n; ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			mp_garbage[i]->Draw();
		}
		mp_character->Draw();
		mp_chaser->Draw();
	}


	DrawBox(160, 19, 1920 - 160, 25, GetColor(255, 255, 255), true);
	DrawCircle(160 + static_cast<int>(1620 * (m_nowLoad / m_maxLoad)), 22, 5, GetColor(0, 0, 0));
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::MainProcess()
{
	if (m_nowLoad >= m_maxLoad)
	{
		m_nowMove = NowMove::gameclear;
	}
	if (mp_character->GetSize() <= 0 || mp_chaser->GetX() + 512 > mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.3))
	{
		m_nowMove = NowMove::gameover;
	}


	mp_backGround->Process();


	mp_character->Process();
	m_nowLoad += mp_character->GetSpeed();


	mp_chaser->Process();


	mp_chaser->SetPlyayerSpeed(mp_character->GetSpeed(), mp_character->GetDefaultMAXSpeed());


	mp_backGround->SetSpeed(mp_character->GetSpeed());


	for (size_t i = 0, n = mp_garbage.size(); i != n; ++i)
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

		int xA = mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.25);
		int xB = xA + static_cast<int>(mp_character->GetSize() * 0.5);
		int yA = mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.25);
		int yB = yA + static_cast<int>(mp_character->GetSize() * 0.5);
		// 当たり判定
		// 右端が障害物の左端に当たってすぎる
		if (xB >= mp_garbage[i]->GetX())
		{
			// 上端が障害物の下端よりも上にいる 左端が障害物の右端よりも左にいる
			if (yA <= mp_garbage[i]->GetY() + 256 && xA <= mp_garbage[i]->GetX() + 256)
			{
				mp_character->HitGarbageNow(static_cast<int>(i), static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
			}

			// 下端が障害物の上端に当たって過ぎる 左端が障害物の右端よりも中にいる
			if (yB >= mp_garbage[i]->GetY() && xA <= mp_garbage[i]->GetX() + 256)
			{
				if (yA <= mp_garbage[i]->GetY() + 256)
				{
					mp_character->HitGarbageNow(static_cast<int>(i), static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
				}
			}
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameOverDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast<int>(m_overFrame / 2));
	mp_backGround->Draw();
	for (size_t i = 0, n = mp_garbage.size(); i != n; ++i)
	{
		if (mp_garbage[i]->GetX() + 256 < 0) continue;
		mp_garbage[i]->Draw();
	}
	mp_character->Draw();
	mp_chaser->Draw();
	DrawBox(160, 19, 1920 - 160, 25, GetColor(255, 255, 255), true);
	DrawCircle(160 + static_cast<int>(1620 * (m_nowLoad / m_maxLoad)), 22, 5, GetColor(0, 0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_overFrame);
	DrawGraph(1920 / 2 - 491 / 2, 1080 / 2 - 132 - 60, mD_gameOver, false);

	if (m_overGameReset)
	{
		DrawBox(1920 / 2 - 362 - 60, 1080 / 2, 1920 / 2 - 60, 1080 / 2 + 133, GetColor(0, 255, 0), true);
	}
	DrawGraph(1920 / 2 - 362 - 60, 1080 / 2, mD_overReset, true);

	if (!m_overGameReset)
	{
		DrawBox(1920 / 2 + 60, 1080 / 2, 1920 / 2 + 60 + 326, 1080 / 2 + 135, GetColor(0, 0, 255), true);
	}
	DrawGraph(1920 / 2 + 60, 1080 / 2, mD_overTitle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameOverProcess()
{
	if (m_overFrame >= 255)
	{
		if (PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, true) == 1)
		{
			m_overGameReset = true;
		}

		if (PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, false) == 1)
		{
			m_overGameReset = false;
		}

		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			if (m_overGameReset)
			{
				BASICPARAM::e_nowScene = ESceneNumber::GAMERETURN;
			}
			else
			{
				BASICPARAM::e_nowScene = ESceneNumber::TITLE;
			}
		}
	}
	else
	{
		m_overFrame += 5;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameClearDraw()
{
	mp_backGround->Draw();
	mp_character->Draw();
	DrawBox(160, 19, 1920 - 160, 25, GetColor(255, 255, 255), true);
	DrawCircle(160 + static_cast<int>(1620 * (m_nowLoad / m_maxLoad)), 22, 5, GetColor(0, 0, 0));


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_clearFrame);
	DrawGraph(1920 / 2 - 1045 / 2, 1080 / 2 - 130, mD_gameClear, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_clearFrame);
	DrawGraph(1920 / 2 - 1700 / 2, 1080 / 2, mD_clearOmake, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameClearProcess()
{
	if (m_clearFrame < 255)
	{
		m_clearFrame++;
	}
	else
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;
		}
	}


	mp_backGround->Process();


	mp_character->FirstProcess();


	mp_backGround->SetSpeed(mp_character->GetSpeed());
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::FileLoad(std::string t_mapStr)
{
	std::ifstream ifs;
	std::vector<std::vector<std::string>> mapdata;
	ifs.open(t_mapStr);
	// マップデータ読み込み失敗
	if (ifs.fail())
	{
		std::cerr << "LoadError" << std::endl;
	}

	// 仮置き
	std::string str;
	int count = 0;
	int arrayCount = 0;

	while (getline(ifs, str))
	{
		// 仮置き
		std::string token;
		std::istringstream stream(str);

		// メモリ確保
		mapdata.resize(++count);
		arrayCount = count - 1;

		while (getline(stream, token, ','))
		{
			mapdata[arrayCount].push_back(token);
		}
	}

	std::vector<int> m_vChipAreaX;
	std::vector<int> m_vChipAreaY;
	std::vector<int> m_vChipID;

	for (size_t i = 0, n = mapdata.size(); i != n; ++i)
	{
		m_vChipAreaX.push_back(std::stoi(mapdata[i][0].c_str()));
		m_vChipAreaY.push_back(std::stoi(mapdata[i][1].c_str()));
		m_vChipID.push_back(std::stoi(mapdata[i][2].c_str()));
	}

	for (size_t i = 0, n = m_vChipAreaX.size(); i != n; ++i)
	{
		switch (m_vChipID.at(i))
		{
		case 0:
			mp_garbage.push_back(new Garbage(m_vChipAreaX.at(i), m_vChipAreaY.at(i), Garbage::EDrawID::doro));
			break;
		case 1:
			mp_garbage.push_back(new Garbage(m_vChipAreaX.at(i), m_vChipAreaY.at(i), Garbage::EDrawID::mizutamari));
			break;
		case 2:
			mp_garbage.push_back(new Garbage(m_vChipAreaX.at(i), m_vChipAreaY.at(i), Garbage::EDrawID::sekiyu));
			break;
		default:
			break;
		}
	}

	std::vector<int>().swap(m_vChipAreaX);
	std::vector<int>().swap(m_vChipAreaY);
	std::vector<int>().swap(m_vChipID);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game(int t_stageCorse)
{
	mp_backGround = nullptr;
	mp_backGround = new BackGround(t_stageCorse);

	mp_character = nullptr;
	mp_character = new Character();

	mp_chaser = nullptr;
	mp_chaser = new Chaser();

	m_endFlag = false;

	g_blurScreen.Init(200, 6, -2, 0, 0);

	m_isFirstSpeedUp = false;


	std::vector<Garbage*>().swap(mp_garbage);

	m_maxLoad = -1;
	if (t_stageCorse == 1)
	{
		FileLoad("media\\stageCorse\\400000ver.csv");
		m_maxLoad = 400000;
	}
	else if (t_stageCorse == 2)
	{
		FileLoad("media\\stageCorse\\200000ver.csv");
		m_maxLoad = 200000;
	}
	else if (t_stageCorse == 3)
	{
		FileLoad("media\\stageCorse\\1000000ver.csv");
		m_maxLoad = 1000000;
	}

	m_nowMove = NowMove::start;

	m_firstCharacterX = 1920 / 2 - 192 / 2;
	m_firstCharacterTurn = true;
	m_firstFrameCount = 0;
	m_firstBackGroundX = 0;
	m_firstchaserX = -512;

	m_firstTimer[0] = LoadGraph("media\\num\\1.png");
	m_firstTimer[1] = LoadGraph("media\\num\\2.png");
	m_firstTimer[2] = LoadGraph("media\\num\\3.png");

	mD_gameClear = LoadGraph("media\\clear\\clear.jpg");
	if (t_stageCorse == 1)
	{
		mD_clearOmake = LoadGraph("media\\clear\\one.jpg");
	}
	else if (t_stageCorse == 2)
	{
		mD_clearOmake = LoadGraph("media\\clear\\two.jpg");
	}
	m_clearFrame = 0;

	mD_gameOver = LoadGraph("media\\over\\sekkennkunnga.jpg");
	mD_overReset = LoadGraph("media\\over\\reset.png");
	mD_overTitle = LoadGraph("media\\over\\down.png");

	m_overGameReset = false;

	m_overFrame = 0;

	m_nowLoad = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mD_gameOver != -1) DeleteGraph(mD_gameOver);
	if (mD_overReset != -1) DeleteGraph(mD_overReset);
	if (mD_overTitle != -1) DeleteGraph(mD_overTitle);
	if (mD_gameClear != -1) DeleteGraph(mD_gameClear);
	if (mD_clearOmake != -1) DeleteGraph(mD_clearOmake);
	if (m_firstTimer[0] != -1) DeleteGraph(m_firstTimer[0]);
	if (m_firstTimer[1] != -1) DeleteGraph(m_firstTimer[1]);
	if (m_firstTimer[2] != -1) DeleteGraph(m_firstTimer[2]);
	for (int i = 0; i != mp_garbage.size(); ++i)
	{
		if (mp_garbage[i] != nullptr) delete mp_garbage[i];
	}
	std::vector<Garbage*>().swap(mp_garbage);
	if (mp_chaser != nullptr) delete mp_chaser;
	if (mp_character != nullptr) delete mp_character;
	if (mp_backGround != nullptr) delete mp_backGround;

	g_blurScreen.Release();
	g_blurScreen.~BlurScreen();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	switch (m_nowMove)
	{
	case NowMove::start:
		FirstDraw();
		break;

	case NowMove::main:
		MainDraw();
		break;

	case NowMove::gameover:
		GameOverDraw();
		break;

	case NowMove::gameclear:
		GameClearDraw();
		break;

	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	switch (m_nowMove)
	{
	case NowMove::start:
		FirstProcess();
		break;

	case NowMove::main:
		MainProcess();
		break;

	case NowMove::gameover:
		GameOverProcess();
		break;

	case NowMove::gameclear:
		GameClearProcess();
		break;

	default:
		break;
	}
}
