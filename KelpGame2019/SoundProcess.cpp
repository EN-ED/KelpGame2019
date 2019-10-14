#include "SoundProcess.hpp"



int m_soundSE[5];

void SoundProcess::Init()
{
	m_soundSE[static_cast<int>(E_SE::jump)]			 = LoadSoundMem("media\\sound\\ジャンプ.wav");
	m_soundSE[static_cast<int>(E_SE::selectCancel)]	 = LoadSoundMem("media\\sound\\選択音キャンセル.wav");
	m_soundSE[static_cast<int>(E_SE::selectDo)]		 = LoadSoundMem("media\\sound\\選択音決定.wav");
	m_soundSE[static_cast<int>(E_SE::slip)]			 = LoadSoundMem("media\\sound\\滑る音.wav");
	m_soundSE[static_cast<int>(E_SE::speedUp)]		 = LoadSoundMem("media\\sound\\加速オン.wav");
}



void SoundProcess::Release()
{
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
