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
		if (m_firstCharacterX > 284)
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
	mp_backGround->SetSpeed(m_firstBackGroundX);

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

			for (int i = 0; i != mp_garbage.size(); ++i)
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

			for (int i = 0; i != mp_garbage.size(); ++i)
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
		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			mp_garbage[i]->Draw();
		}
		mp_character->Draw();
		mp_chaser->Draw();
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::MainProcess()
{
	mp_backGround->Process();


	mp_character->Process();


	mp_chaser->Process();


	mp_chaser->SetPlyayerSpeed(mp_character->GetSpeed(), mp_character->GetDefaultMAXSpeed());


	mp_backGround->SetSpeed(mp_character->GetSpeed());


	for (int i = 0; i != mp_garbage.size(); ++i)
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



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameOverDraw()
{
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameOverProcess()
{
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameClearDraw()
{
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::GameClearProcess()
{
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

	while (getline(ifs, str))
	{
		// 仮置き
		std::string token;
		std::istringstream stream(str);

		// メモリ確保
		mapdata.resize(count + 1);

		while (getline(stream, token, ','))
		{
			mapdata[count].push_back(token);
		}
		// カウントアップ
		count++;
	}

	std::vector<int> m_vChipAreaX;
	std::vector<int> m_vChipAreaY;
	std::vector<int> m_vChipID;

	for (int i = 0, n = mapdata.size(); i != n; ++i)
	{
		m_vChipAreaX.push_back(std::stoi(mapdata[i][0].c_str()));
		m_vChipAreaY.push_back(std::stoi(mapdata[i][1].c_str()));
		m_vChipID.push_back(std::stoi(mapdata[i][2].c_str()));
	}

	for (int i = 0, n = m_vChipAreaX.size(); i != n; ++i)
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

	if (t_stageCorse == 1)
	{
		FileLoad("media\\stageCorse\\400000ver.csv");
	}
	else if (t_stageCorse == 2)
	{
		FileLoad("media\\stageCorse\\200000ver.csv");
	}
	else if (t_stageCorse == 3)
	{
		FileLoad("media\\stageCorse\\1000000ver.csv");
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
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	DeleteGraph(m_firstTimer[0]);
	DeleteGraph(m_firstTimer[1]);
	DeleteGraph(m_firstTimer[2]);
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
