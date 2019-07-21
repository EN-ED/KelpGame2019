#include "Logo.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	mD_movieDraw = LoadGraph("media\\movieLogo.mp4");
	mD_dxlibLogo = LoadGraph("media\\DxLogo.jpg");

	m_nowLogoNumber = 0;
	m_movieZoom = 0;
	m_logoTransTime = 0;

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	PauseMovieToGraph(mD_movieDraw);
	if (mD_movieDraw != -1) DeleteGraph(mD_movieDraw);
	if (mD_dxlibLogo != -1) DeleteGraph(mD_dxlibLogo);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Draw()
{
	// ロゴひょじ時間が50カウント以下だったら
	if (m_logoTransTime < 50)
	{
		SetDrawBright(m_logoTransTime * 5, m_logoTransTime * 5, m_logoTransTime * 5);		// 明るさをだんだん明るくする
	}
	// ロゴ表示時間が250カウント以上だったら
	else if (m_logoTransTime > 250)
	{
		SetDrawBright(250 - ((m_logoTransTime - 250) * 5), 250 - ((m_logoTransTime - 250) * 5), 250 - ((m_logoTransTime - 250) * 5));		// 明るさをだんだん暗くする
	}


	// 現在のロゴのIDが0番目だったら
	if (m_nowLogoNumber == 0)
	{
		DrawGraph(960 - 120, 540 - 120, mD_dxlibLogo, false);		// dxlibのロゴを表示
	}
	// 現在のロゴのIDが1番目だったら
	else if (m_nowLogoNumber == 1)
	{
		DrawExtendGraph(960 - 480 - m_movieZoom * 2, 540 - 220 - m_movieZoom, 960 + 480 + m_movieZoom * 2, 540 + 220 + m_movieZoom, mD_movieDraw, false);		// 動画を表示
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	// 現在のロゴのIDが0番目だったら
	if (m_nowLogoNumber == 0)
	{
		// Zキーが押されたら
		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			// ロゴ表示時間が150カウント以下だったら
			if (m_logoTransTime < 150)
			{
				m_logoTransTime = 150;				// ロゴ表示時間を150にする
				SetDrawBright(250, 250, 250);		// 明るさをロゴ表示の最大にする
			}
			// ロゴ表示時間が151カウント以上だったら
			else
			{
				m_logoTransTime = 300;				// ロゴ表示時間を300にする
			}
		}


		// ロゴ表示時間が300より大きかったら
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;				// ロゴ表示時間をリセットする
			m_nowLogoNumber = 1;				// ロゴのIDを1番目にする
			PlayMovieToGraph(mD_movieDraw);		// 動画を再生する
		}
	}
	// 現在のロゴのIDが1番目だったら
	else if (m_nowLogoNumber == 1)
	{
		// Zキーが押されたら
		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			// ロゴ表示時間が150カウント以下だったら
			if (m_logoTransTime < 150)
			{
				m_logoTransTime = 150;				// ロゴ表示時間を150にする
				m_movieZoom = 450;					// 動画のズーム値を450にする
				SetDrawBright(250, 250, 250);		// 明るさをロゴ表示の最大にする
			}
			// ロゴ表示時間が151カウント以上だったら
			else
			{
				BASICPARAM::e_nowScene = ESceneNumber::TITLE;		// TITLEのシーンへ移行する
			}
		}

		// ロゴ表示時間が300より大きかったら
		if (m_logoTransTime++ >= 300)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;		// TITLEのシーンへ移行する
		}
		else
		{
			m_movieZoom += 3;		// 動画のズーム値を3ずつ加算する
		}
	}
}
