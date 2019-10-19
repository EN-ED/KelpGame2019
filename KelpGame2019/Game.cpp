#include "Game.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BlurScreen g_blurScreen;



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
		// ����艓���ɍs������
		if (mp_garbage[i]->GetX() + 256 < 0) continue;


		// �Ό��N���������Ă�����
		if (mp_character->GetIsSpeedUp())
		{
			mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
			continue;
		}
		// �Ό��N���������Ă��Ȃ�������
		else
		{
			mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.8f));
		}


		// ���ɐΌ��N�ɑ΂��ď�Q�����������Ă���t���[������������
		if (mp_character->GetNowDamage() || mp_character->GetNowHeal()) continue;

		// �����蔻��
		if (/*�Ό��̉E�[���1/4���炷 �� ��Q���̍��[ ���傫��*/
			mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.75) >= mp_garbage[i]->GetX()
			/*�Ό��̍��[ �� ��Q���̍��[�Ə�Q���̑��x ��菬����*/
			&& mp_character->GetAreaX() + static_cast<int>(mp_character->GetSize() * 0.25) <= mp_garbage[i]->GetX() + 256
			/*�Ό��̉��[ �� ��Q���̏�[ ���傫��*/
			&& mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.75) >= mp_garbage[i]->GetY()
			/*�Ό��̏�[ �� ��Q���̉��[ ��菬����*/
			&& mp_character->GetAreaY() + static_cast<int>(mp_character->GetSize() * 0.25) <= mp_garbage[i]->GetY() + 256)
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
void Game::TutorialDraw()
{
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::TutorialProcess()
{
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::FileLoad(std::string t_mapStr)
{
	std::ifstream ifs;
	std::vector<std::vector<std::string>> mapdata;
	ifs.open(t_mapStr);
	// �}�b�v�f�[�^�ǂݍ��ݎ��s
	if (ifs.fail())
	{
		std::cerr << "LoadError" << std::endl;
	}

	// ���u��
	std::string str;
	int count = 0;

	while (getline(ifs, str))
	{
		// ���u��
		std::string token;
		std::istringstream stream(str);

		// �������m��
		mapdata.resize(count + 1);

		while (getline(stream, token, ','))
		{
			mapdata[count].push_back(token);
		}
		// �J�E���g�A�b�v
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

	m_nowMove = NowMove::main;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
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
	case NowMove::tutorial:
		TutorialDraw();
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
	case NowMove::tutorial:
		TutorialProcess();
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
