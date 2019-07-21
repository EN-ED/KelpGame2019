#include "GameOver.hpp"



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
	DrawExtendGraph(960 - 480 - 900 * 2, 540 - 220 - 900, 960 + 480 + 900 * 2, 540 + 220 + 900, mD_movieDraw, false);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover");

	DrawFormatString(800, 500, GetColor(255, 255, 255), "Zキーでタイトル戻るよ");
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void GameOver::Process()
{
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		BASICPARAM::e_nowScene = ESceneNumber::TITLE;
	}


	if (!GetMovieStateToGraph(mD_movieDraw))
	{
		SeekMovieToGraph(mD_movieDraw, 0);
		PlayMovieToGraph(mD_movieDraw);
	}
}
