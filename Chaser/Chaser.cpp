#include "Chaser.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include <string>



/// ------------------------------------------------------------------------------------------------------------
Chaser::Chaser()
{
	for (int i = 0; i != m_chaserArrayNum; ++i)
	{
		std::string str = "media\\tkms_anim01\\" + std::to_string(i) + ".png";
		mD_chaserArray[i] = LoadGraph(str.c_str());
	}
	m_chaserSpeedCount = 0;
	m_chasrArraySpeed = 2;

	mD_backGround = LoadGraph("media\\background.png");
	mD_underGround = LoadGraph("media\\underground.png");
	mD_player = LoadGraph("media\\player.png");

	m_scrollX = 0;
	m_playerX = 284;

	mD_screen = MakeScreen(1920, 1080);
	m_zoom = 0;
	m_chaserX = 120 - 512;
}



/// ------------------------------------------------------------------------------------------------------------
Chaser::~Chaser()
{
	if (mD_player != -1) DeleteGraph(mD_player);
	if (mD_underGround != -1) DeleteGraph(mD_underGround);
	if (mD_backGround != -1) DeleteGraph(mD_backGround);
	for (int i = 0; i != m_chaserArrayNum; ++i)
	{
		if (mD_chaserArray[i] != -1) DeleteGraph(mD_chaserArray[i]);
	}
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::Draw()
{
	SetDrawScreen(mD_screen);
	DrawRectGraph(0, 0, m_scrollX, 0, 1920, 1080, mD_backGround, false);
	DrawRectGraph(1920 - m_scrollX, 0, 0, 0, m_scrollX, 1080, mD_backGround, false);
	DrawRectGraph(0, 1080 - 128, m_scrollX, 0, 1920, 128, mD_underGround, false);
	DrawRectGraph(1920 - m_scrollX, 1080 - 128, 0, 0, m_scrollX, 128, mD_underGround, false);

	DrawGraph(m_chaserX, 1080 - 128 - 512, mD_chaserArray[static_cast<int>(m_chaserSpeedCount / m_chasrArraySpeed)], true);

	DrawGraph(m_playerX, 1080 - 128 - 192, mD_player, true);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawExtendGraph(0, 0 - m_zoom, 1920 + static_cast<int>((1920 / 1080) * m_zoom), 1080, mD_screen, false);
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::Process()
{
	if (++m_chaserSpeedCount >= m_chasrArraySpeed * m_chaserArrayNum) m_chaserSpeedCount = 0;
	if (m_playerX < 220) m_chasrArraySpeed = 1;
	else m_chasrArraySpeed = 2;

	if (++m_scrollX >= 1920) m_scrollX = 0;


	if (KeyData::Get(KEY_INPUT_LEFT) > 0)
	{
		m_playerX--;
		if (m_playerX < 284) m_chaserX += 2;
		if (m_playerX < 284) m_zoom++;
	}
	if (KeyData::Get(KEY_INPUT_RIGHT) > 0)
	{
		m_playerX++;
		if (m_chaserX > 120 - 512) m_chaserX -= 2;;
		if (m_zoom > 0) m_zoom--;
	}
}
