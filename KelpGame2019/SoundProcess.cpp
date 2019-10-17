#include "SoundProcess.hpp"



int m_soundSE[5];
int m_soundBGM[1];
float bgmVolume;
float preVolume;
SoundProcess::E_BGM nowBGM;
SoundProcess::E_BGM nextBGM;

void SoundProcess::Init()
{
	m_soundSE[static_cast<int>(E_SE::jump)]			 = LoadSoundMem("media\\sound\\ジャンプ.wav");
	m_soundSE[static_cast<int>(E_SE::selectCancel)]	 = LoadSoundMem("media\\sound\\選択音キャンセル.wav");
	m_soundSE[static_cast<int>(E_SE::selectDo)]		 = LoadSoundMem("media\\sound\\選択音決定.wav");
	m_soundSE[static_cast<int>(E_SE::slip)]			 = LoadSoundMem("media\\sound\\滑る音.wav");
	m_soundSE[static_cast<int>(E_SE::speedUp)]		 = LoadSoundMem("media\\sound\\加速オン.wav");

	m_soundBGM[static_cast<int>(E_BGM::title)] = LoadSoundMem("media\\sound\\たいとる.wav");

	bgmVolume = 0.0f;
	preVolume = 0.0f;

	nowBGM = E_BGM::none;
	nextBGM = E_BGM::none;
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
	nextBGM = number; 
	preVolume = bgmVolume;
	bgmVolume = 0.0f;
	ChangeVolumeSoundMem(bgmVolume, m_soundBGM[static_cast<int>(nextBGM)]);
	PlaySoundMem(m_soundBGM[static_cast<int>(nextBGM)], DX_PLAYTYPE_LOOP);
}


void SoundProcess::BGMLoop(bool startTrue)
{
	if (startTrue)
	{
		if (nextBGM == E_BGM::none) return;
		if ((bgmVolume += 12.75) < 255)
		{
			ChangeVolumeSoundMem(static_cast<int>(bgmVolume >= 255 ? 255 : bgmVolume), m_soundBGM[static_cast<int>(nextBGM)]);
		}

		if (nowBGM == E_BGM::none) return;
		if ((preVolume -= 51) > 0)
		{
			ChangeVolumeSoundMem(static_cast<int>(preVolume <= 0 ? 0 : preVolume), m_soundBGM[static_cast<int>(nowBGM)]);
		}
		else
		{
			StopSoundMem(m_soundBGM[static_cast<int>(nowBGM)]);
		}
	}
	else
	{
		if ((bgmVolume -= 25.5) > 0)
		{
			ChangeVolumeSoundMem(static_cast<int>(bgmVolume <= 0 ? 0 : bgmVolume), m_soundBGM[static_cast<int>(nextBGM)]);
		}
		else
		{
			StopSoundMem(m_soundBGM[static_cast<int>(nextBGM)]);
		}
	}
}
