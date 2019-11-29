#include "BackGround.hpp"



/// ---------------------------------------------------------------------------------------
BackGround::BackGround(int t_stageCorse)
{
	mD_backGround	 = -1;
	mD_underGround	 = -1;
	if (t_stageCorse == 1)
	{
		mD_backGround	 = LoadGraph("media\\stage1\\stage1_background.png");
		mD_underGround	 = LoadGraph("media\\stage1\\stage1_Ground.png");
	}
	else if (t_stageCorse == 2)
	{
		mD_backGround	 = LoadGraph("media\\stage2\\Stage2_background.png");
		mD_underGround	 = LoadGraph("media\\stage2\\sutage2_Ground.png");
	}
	else if (t_stageCorse == 3)
	{
		mD_backGround	 = LoadGraph("media\\stage3\\Stage_backGround.png");
		mD_underGround	 = LoadGraph("media\\stage3\\stage3_Ground.png");
	}

	m_areaX = 0;
	m_speed = 0;
}



/// ---------------------------------------------------------------------------------------
BackGround::~BackGround()
{
	if (mD_underGround != -1) DeleteGraph(mD_underGround);
	if (mD_backGround != -1) DeleteGraph(mD_backGround);
}



/// ---------------------------------------------------------------------------------------
void BackGround::Draw()
{
	DrawRectGraph(0, 0, m_areaX, 0, 1920, 1080, mD_backGround, false);
	DrawRectGraph(1920 - m_areaX, 0, 0, 0, m_areaX, 1080, mD_backGround, false);

	DrawRectGraph(0, 1080 - 128, m_areaX, 0, 1920, 128, mD_underGround, false);
	DrawRectGraph(1920 - m_areaX, 1080 - 128, 0, 0, m_areaX, 128, mD_underGround, false);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::Process()
{
	m_areaX += m_speed;
	if (m_areaX < 0) m_areaX = 1920;
	if (m_areaX > 1920) m_areaX = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::SetSpeed(const float t_speed)
{
	m_speed = static_cast<int>(t_speed * 0.75f);
}
