#include "Chaser.hpp"
#include "DxLib.h"
#include "InputKey.hpp"



/// ------------------------------------------------------------------------------------------------------------
Chaser::Chaser()
{
	mD_chaser = LoadGraph("media\\chaser.png");
	mD_backGround = LoadGraph("media\\background.png");
	mD_underGround = LoadGraph("media\\underground.png");
	mD_player = LoadGraph("media\\player.png");

	m_scrollX = 0;
	m_playerX = 284;

	mD_screen = MakeScreen(1920, 1080);
	m_zoom = 0;
	m_chaserX = -80;
}



/// ------------------------------------------------------------------------------------------------------------
Chaser::~Chaser()
{
	if (mD_player != -1) DeleteGraph(mD_player);
	if (mD_underGround != -1) DeleteGraph(mD_underGround);
	if (mD_backGround != -1) DeleteGraph(mD_backGround);
	if (mD_chaser != -1) DeleteGraph(mD_chaser);
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::Draw()
{
	SetDrawScreen(mD_screen);
	DrawRectGraph(0, 0, m_scrollX, 0, 1920, 1080, mD_backGround, false);
	DrawRectGraph(1920 - m_scrollX, 0, 0, 0, m_scrollX, 1080, mD_backGround, false);
	DrawRectGraph(0, 1080 - 128, m_scrollX, 0, 1920, 128, mD_underGround, false);
	DrawRectGraph(1920 - m_scrollX, 1080 - 128, 0, 0, m_scrollX, 128, mD_underGround, false);

	DrawGraph(m_chaserX, 1080 - 128 - 512, mD_chaser, true);

	DrawGraph(m_playerX, 1080 - 128 - 192, mD_player, true);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawExtendGraph(0, 0 - m_zoom, 1920 + static_cast<int>((1920 / 1080) * m_zoom), 1080, mD_screen, false);
}



/// ------------------------------------------------------------------------------------------------------------
void Chaser::Process()
{
	if (++m_scrollX >= 1920) m_scrollX = 0;


	if (KeyData::Get(KEY_INPUT_LEFT) > 0)
	{
		m_playerX--;
		if (m_playerX < 284) m_chaserX++;
		if (m_playerX < 284) m_zoom++;
	}
	if (KeyData::Get(KEY_INPUT_RIGHT) > 0)
	{
		m_playerX++;
		if (m_chaserX > -80) m_chaserX--;
		if (m_zoom > 0) m_zoom--;
	}
}
