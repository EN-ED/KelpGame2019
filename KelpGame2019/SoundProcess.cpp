#include "SoundProcess.hpp"



int m_soundSE[9];
int m_soundBGM[3];
float bgmVolume;
float preVolume;
SoundProcess::E_BGM preBGM;
SoundProcess::E_BGM nowBGM;

void SoundProcess::Init()
{
	m_soundSE[static_cast<int>(E_SE::jump)]			 = LoadSoundMem("media\\sound\\ジャンプ.wav");
	m_soundSE[static_cast<int>(E_SE::selectCancel)]	 = LoadSoundMem("media\\sound\\選択音キャンセル.wav");
	m_soundSE[static_cast<int>(E_SE::selectDo)]		 = LoadSoundMem("media\\sound\\選択音決定.wav");
	m_soundSE[static_cast<int>(E_SE::slip)]			 = LoadSoundMem("media\\sound\\滑る音.wav");
	m_soundSE[static_cast<int>(E_SE::speedUp)]		 = LoadSoundMem("media\\sound\\加速オン.wav");
	m_soundSE[static_cast<int>(E_SE::gameClear)]	 = LoadSoundMem("media\\sound\\ゲームクリアー.wav");
	m_soundSE[static_cast<int>(E_SE::gameOver)]		 = LoadSoundMem("media\\sound\\ゲームオーバー.wav");
	m_soundSE[static_cast<int>(E_SE::debuff)]		 = LoadSoundMem("media\\sound\\デバフ音.wav");
	m_soundSE[static_cast<int>(E_SE::catchTouyu)]	 = LoadSoundMem("media\\sound\\油取得できた時の音.wav");

	m_soundBGM[static_cast<int>(E_BGM::title)]		 = LoadSoundMem("media\\sound\\たいとる.wav");
	m_soundBGM[static_cast<int>(E_BGM::main)]		 = LoadSoundMem("media\\sound\\めいん.wav");
	m_soundBGM[static_cast<int>(E_BGM::mainLoop)]	 = LoadSoundMem("media\\sound\\めいんるーぷできる.wav");

	bgmVolume = 0.0f;
	preVolume = 0.0f;

	nowBGM = E_BGM::none;
	preBGM = E_BGM::none;
}



void SoundProcess::Release()
{
	for (int i = 0; i != 1; ++i)
	{
		if (m_soundBGM[i] != -1)
		{
			StopSoundMem(m_soundBGM[i]);
			DeleteSoundMem(m_soundBGM[i]);
		}
	}

	for (int i = 0; i != 5; ++i)
	{
		if (m_soundSE[i] != -1)
		{
			DeleteSoundMem(m_soundSE[i]);
		}
	}
}



void SoundProcess::Play(E_SE number)
{
	PlaySoundMem(m_soundSE[static_cast<int>(number)], DX_PLAYTYPE_BACK);
}


void SoundProcess::Play(E_BGM number)
{
	if (nowBGM != E_BGM::none)
	{
		preBGM = nowBGM;
		preVolume = bgmVolume;
	}
	nowBGM = number; 
	bgmVolume = 0.0f;
	ChangeVolumeSoundMem(bgmVolume, m_soundBGM[static_cast<int>(nowBGM)]);
	PlaySoundMem(m_soundBGM[static_cast<int>(nowBGM)], DX_PLAYTYPE_LOOP);
}


void SoundProcess::BGMLoop()
{
	if (nowBGM != E_BGM::none)
	{
		if ((bgmVolume += 12.75) < 255)
		{
			ChangeVolumeSoundMem(static_cast<int>(bgmVolume >= 255 ? 255 : bgmVolume), m_soundBGM[static_cast<int>(nowBGM)]);
		}
	}


	if (preBGM == E_BGM::none) return;
	if ((preVolume -= 51) > 0)
	{
		ChangeVolumeSoundMem(static_cast<int>(preVolume <= 0 ? 0 : preVolume), m_soundBGM[static_cast<int>(preBGM)]);
	}
	else
	{
		StopSoundMem(m_soundBGM[static_cast<int>(preBGM)]);
	}
}
