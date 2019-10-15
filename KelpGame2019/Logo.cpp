#include "Logo.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	mD_dxlibLogo = LoadGraph("media\\logo\\DxLogo.jpg");
	mD_teamLogo = LoadGraph("media\\logo\\notmovie.png");
	mD_skip = LoadGraph("media\\logo\\ASkip.png");

	m_nowLogoNumber = ELOGONOW::dxlib;
	m_logoTransTime = 0;

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	if (mD_skip != -1) DeleteGraph(mD_skip);
	if (mD_teamLogo != -1) DeleteGraph(mD_teamLogo);
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
	if (m_nowLogoNumber == ELOGONOW::dxlib)
	{
		DrawGraph(960 - 120/*中心座標 - 横サイズの半分*/, 540 - 120/*中心座標 - 縦サイズの半分*/, mD_dxlibLogo, true);		// dxlibのロゴを表示
	}
	// 現在のロゴのIDが1番目だったら
	else if (m_nowLogoNumber == ELOGONOW::team)
	{
		DrawGraph(960 - 960/*中心座標 - 横サイズの半分*/, 540 - 540/*中心座標 - 縦サイズの半分*/, mD_teamLogo, true);		// teamのロゴを表示
	}

	DrawGraph(1720, 720, mD_skip, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	// 現在のロゴのIDが0番目だったら
	if (m_nowLogoNumber == ELOGONOW::dxlib)
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			m_logoTransTime = 0;				// ロゴ表示時間をリセットする
			m_nowLogoNumber = ELOGONOW::team;				// ロゴのIDを1番目にする
		}
		// ロゴ表示時間が300より大きかったら
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;				// ロゴ表示時間をリセットする
			m_nowLogoNumber = ELOGONOW::team;				// ロゴのIDを1番目にする
		}
	}
	// 現在のロゴのIDが1番目だったら
	else if (m_nowLogoNumber == ELOGONOW::team)
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;					// ロゴのIDを1番目にする
		}
		// ロゴ表示時間が300より大きかったら
		if (m_logoTransTime++ >= 300)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;					// ロゴのIDを1番目にする
		}
	}
}
