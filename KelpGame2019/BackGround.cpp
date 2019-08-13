#include "BackGround.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BackGround::BackGround()
{
	mD_backGround = LoadGraph("media\\background.png");
	mD_underGround = LoadGraph("media\\underground.png");

	BlurScreen::Init(200, 6, -2, 0, 0);

	m_areaX = 0;

	m_speed = 10;

	m_isSpeedUp = false;

	m_isFirstSpeedUp = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BackGround::~BackGround()
{
	if (mD_underGround != -1) DeleteGraph(mD_underGround);
	if (mD_backGround != -1) DeleteGraph(mD_backGround);

	BlurScreen::Release();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::Draw()
{
	if (m_isSpeedUp)
	{
		if (!m_isFirstSpeedUp)
		{
			BlurScreen::PreRenderBlurScreen();
			DrawRectGraph(0, 0, m_areaX, 0, 1920, 1080, mD_backGround, false);
			DrawRectGraph(1920 - m_areaX, 0, 0, 0, m_areaX, 1080, mD_backGround, false);

			DrawRectGraph(0, 1080 - 128, m_areaX, 0, 1920, 128, mD_underGround, false);
			DrawRectGraph(1920 - m_areaX, 1080 - 128, 0, 0, m_areaX, 128, mD_underGround, false);
			BlurScreen::PostRenderBlurScreen();
		}
		else
		{
			m_isFirstSpeedUp = false;


			BlurScreen::ReplayInit();
			BlurScreen::PreRenderBlurScreen();
			DrawRectGraph(0, 0, m_areaX, 0, 1920, 1080, mD_backGround, false);
			DrawRectGraph(1920 - m_areaX, 0, 0, 0, m_areaX, 1080, mD_backGround, false);

			DrawRectGraph(0, 1080 - 128, m_areaX, 0, 1920, 128, mD_underGround, false);
			DrawRectGraph(1920 - m_areaX, 1080 - 128, 0, 0, m_areaX, 128, mD_underGround, false);
			BlurScreen::PostRenderBlurScreen();
		}
	}
	else
	{
		DrawRectGraph(0, 0, m_areaX, 0, 1920, 1080, mD_backGround, false);
		DrawRectGraph(1920 - m_areaX, 0, 0, 0, m_areaX, 1080, mD_backGround, false);

		DrawRectGraph(0, 1080 - 128, m_areaX, 0, 1920, 128, mD_underGround, false);
		DrawRectGraph(1920 - m_areaX, 1080 - 128, 0, 0, m_areaX, 128, mD_underGround, false);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::Process()
{
	if (m_isSpeedUp)
	{
		if (m_speed < 70)
		{
			m_speed += 4;
		}
	}
	else
	{
		if (m_speed < 10)
		{
			m_speed++;
		}
		else if (m_speed > 10)
		{
			m_speed -= 2;
		}
	}
	m_areaX += m_speed;
	if (m_areaX > 1920) m_areaX = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::SetIsSpeedUp(const bool& t_isSpeedUp)
{
	if (!m_isSpeedUp)
	{
		m_isFirstSpeedUp = true;
	}

	m_isSpeedUp = t_isSpeedUp;
}
