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
	if (++m_chaserSpeedCount >= m_chasrArraySpeed * m_chaserArrayNum) m_chaserSpeedCount = 0;


	// 石鹸君が初期位置
	if (m_playerFromDefaultAreaX == 0)
	{
		if (m_chaserX > m_chaserDefaultX)
		{
			m_chaserX--;
		}
		else if (m_chaserX < m_chaserDefaultX)
		{
			m_chaserX++;
		}
	}
	// 石鹸君が離れていく
	else if (m_playerFromDefaultAreaX < 0)
	{
		m_chaserX -= 2;
	}
	// 石鹸君が近づいていく
	else
	{
		m_chaserX += 2;
	}
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::SetPlayerFromDefaultAreaX(const int& t_playerAreaX)
{
	m_playerFromDefaultAreaX = t_playerAreaX;
}
