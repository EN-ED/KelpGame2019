#include "Game.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mD_backGroundDraw = LoadGraph("media\\background.png");
	mD_playerDraw = LoadGraph("media\\player.png");
	mD_chaserDraw = LoadGraph("media\\chaser.png");
	mD_garbageDraw = LoadGraph("media\\garbage.png");
	mD_underGroundDraw = LoadGraph("media\\underground.png");

	m_playerHP = m_playerMaxHP;

	m_nowSpeed = 0;
	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand(0, 9);        // [0, 9] 範囲の一様乱数
	m_lowNowSpeed = rand(mt);

	m_lowSpeedChange = false;

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mD_backGroundDraw != -1) DeleteGraph(mD_backGroundDraw);
	if (mD_playerDraw != -1) DeleteGraph(mD_playerDraw);
	if (mD_chaserDraw != -1) DeleteGraph(mD_chaserDraw);
	if (mD_garbageDraw != -1) DeleteGraph(mD_garbageDraw);
	if (mD_underGroundDraw != -1) DeleteGraph(mD_underGroundDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	DrawGraph(0, 0, mD_backGroundDraw, false);
	DrawGraph(1920, 0, mD_backGroundDraw, false);


	DrawGraph(0, m_mostMaxY, mD_underGroundDraw, false);
	DrawGraph(0, m_mostMaxY - 512, mD_chaserDraw, false);

	DrawFormatString(199, 131, GetColor(255, 255, 255), "%d.%d", m_nowSpeed, m_lowNowSpeed);
	
	DrawExtendGraph(284 + ((m_playerMaxHP - m_playerHP) / 8), (m_mostMaxY - 64) + ((m_playerMaxHP - m_playerHP) / 4)
		, 284 + 64 - ((m_playerMaxHP - m_playerHP) / 8), m_mostMaxY, mD_playerDraw, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	m_nowSpeed++;


	if ((m_lowSpeedChange = !m_lowSpeedChange))
	{
		m_playerHP--;
		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand(0, 9);        // [0, 9] 範囲の一様乱数
		m_lowNowSpeed = rand(mt);
	}


	if (m_playerHP <= 0)
	{
		BASICPARAM::e_nowScene = ESceneNumber::GAMEOVER;
	}
}
