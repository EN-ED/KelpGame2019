#include "Chaser.hpp"
#include "DxLib.h"
#include <string>



/// ------------------------------------------------------------------------------------------------------------
Chaser::Chaser()
{
	ZeroMemory(mD_chaserArray, sizeof(mD_chaserArray));
	for (int i = 0; i != m_chaserArrayNum; ++i)
	{
		std::string str = "media\\tkms_anim01\\" + std::to_string(i) + ".png";
		mD_chaserArray[i] = LoadGraph(str.c_str());
	}
	m_chaserSpeedCount = 0;
	m_chasrArraySpeed = 2;

	m_chaserX = m_chaserDefaultX;

	m_chaserXAddValue = 0;
}



/// ------------------------------------------------------------------------------------------------------------
Chaser::~Chaser()
{
	for (int i = 0; i != m_chaserArrayNum; ++i)
	{
		if (mD_chaserArray[i] != -1) DeleteGraph(mD_chaserArray[i]);
	}
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::Draw()
{
	DrawGraph(m_chaserX, 1080 - 128 - 512, mD_chaserArray[static_cast<int>(m_chaserSpeedCount / m_chasrArraySpeed)], true);
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::Process()
{
	// �A�j���[�V����
	if (++m_chaserSpeedCount >= m_chasrArraySpeed * m_chaserArrayNum) m_chaserSpeedCount = 0;


	m_chaserX -= m_chaserXAddValue;
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::SetPlyayerSpeed(const float& t_playerSpeed, const float& t_defaultMAXSpeed)
{
	if (t_playerSpeed > t_defaultMAXSpeed)
	{
		m_chaserXAddValue = static_cast<int>((t_playerSpeed - t_defaultMAXSpeed * 0.9) / 8/*���̐��l�͌����ڋC��*/);
	}
	else
	{
		m_chaserXAddValue = static_cast<int>((t_playerSpeed - t_defaultMAXSpeed * 0.9) / 4/*���̐��l�͌����ڋC��*/);
	}
}