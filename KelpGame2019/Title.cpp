#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::Title()
{
	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::~Title()
{
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");	// 現在タイトルだと表示


	DrawFormatString(800, 500, GetColor(255, 255, 255), "Zキーで初めてね");	// 遷移のためのキー表示
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Process()
{
	// Zキーを押したら
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		BASICPARAM::e_nowScene = ESceneNumber::GAME;		// GAMEシーンへ移行
	}
}
