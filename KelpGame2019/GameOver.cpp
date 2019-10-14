#include "GameOver.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
GameOver::GameOver()
{
	mD_backGround = LoadGraph("media\\gameover.png");

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
GameOver::~GameOver()
{
	if (mD_backGround != -1) DeleteGraph(mD_backGround);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void GameOver::Draw()
{
	DrawGraph(0, 0, mD_backGround, false);		// 動画を表示

	DrawFormatString(800, 500, GetColor(255, 255, 255), "Zキーでタイトル戻るよ");			// タイトルへの移動キーを表示
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void GameOver::Process()
{
	// Zキーを押したら
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		BASICPARAM::e_nowScene = ESceneNumber::TITLE;				// TITLEのシーンへ移行する
	}
}
