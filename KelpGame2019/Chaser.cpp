#include "Chaser.hpp"



/// ---------------------------------------------------------------------------------------
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



/// ---------------------------------------------------------------------------------------
Chaser::~Chaser()
{
	for (int i = 0; i != m_chaserArrayNum; ++i)
	{
		if (mD_chaserArray[i] != -1) DeleteGraph(mD_chaserArray[i]);
	}
}



/// ---------------------------------------------------------------------------------------
void Chaser::Draw()
{
	DrawGraph(m_chaserX, 1080 - 128 - 512, mD_chaserArray[static_cast<int>(m_chaserSpeedCount / m_chasrArraySpeed)], true);
}



/// ---------------------------------------------------------------------------------------
void Chaser::Process()
{
	if (++m_chaserSpeedCount >= m_chasrArraySpeed * m_chaserArrayNum) m_chaserSpeedCount = 0;


	m_chaserX -= m_chaserXAddValue;
}



/// ---------------------------------------------------------------------------------------
void Chaser::FirstDraw(int t_x)
{
	DrawGraph(t_x, 1080 - 128 - 512, mD_chaserArray[static_cast<int>(m_chaserSpeedCount / m_chasrArraySpeed)], true);
}



/// ---------------------------------------------------------------------------------------
void Chaser::FirstProcess()
{
	if (++m_chaserSpeedCount >= m_chasrArraySpeed * m_chaserArrayNum) m_chaserSpeedCount = 0;
}



/// ---------------------------------------------------------------------------------------
void Chaser::SetPlyayerSpeed(const float t_playerSpeed, const float t_defaultMAXSpeed)
{
	if (t_playerSpeed > t_defaultMAXSpeed)
	{
		m_chaserXAddValue = static_cast<int>((t_playerSpeed - t_defaultMAXSpeed * 0.9) / (8/*この数値は見た目気分*/));
	}
	else
	{
		m_chaserXAddValue = static_cast<int>((t_playerSpeed - t_defaultMAXSpeed * 0.9) / (4/*この数値は見た目気分*/));
	}
}



/// ---------------------------------------------------------------------------------------
const int Chaser::GetX() const
{
	return m_chaserX;
}
