#include "GameOver.hpp"
#include "DxLib.h"
#include "InputKey.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
GameOver::GameOver()
{
	mD_movieDraw = LoadGraph("media\\movieLogo.mp4");
	PlayMovieToGraph(mD_movieDraw);

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
GameOver::~GameOver()
{
	if (mD_movieDraw != -1) DeleteGraph(mD_movieDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void GameOver::Draw()
{
	DrawExtendGraph(960 - 480 - 900 * 2, 540 - 220 - 900, 960 + 480 + 900 * 2, 540 + 220 + 900, mD_movieDraw, false);		// 動画を表示

	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover");				// ゲームオーバーのシーンだと表示

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


	// 動画が終了していたら
	if (!GetMovieStateToGraph(mD_movieDraw))
	{
		SeekMovieToGraph(mD_movieDraw, 0);		// 位置を最初に戻す
		PlayMovieToGraph(mD_movieDraw);			// 動画を再生する
	}
}
