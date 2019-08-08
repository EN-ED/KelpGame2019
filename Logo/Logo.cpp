#include "Logo.hpp"
#include "DxLib.h"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	m_dxlibLogo = LoadGraph("media\\DxLogo.jpg");
	m_teamLogo = LoadGraph("media\\notmovie.png");

	m_nowLogoNumber = ELOGONOW::dxlib;
	m_logoTransTime = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	if (m_teamLogo != -1) DeleteGraph(m_teamLogo);
	if (m_dxlibLogo != -1) DeleteGraph(m_dxlibLogo);
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
		DrawGraph(960 - 120/*中心座標 - 横サイズの半分*/, 540 - 120/*中心座標 - 縦サイズの半分*/, m_dxlibLogo, true);		// dxlibのロゴを表示
	}
	// 現在のロゴのIDが1番目だったら
	else if (m_nowLogoNumber == ELOGONOW::team)
	{
		DrawGraph(960 - 960/*中心座標 - 横サイズの半分*/, 540 - 540/*中心座標 - 縦サイズの半分*/, m_teamLogo, true);		// teamのロゴを表示
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	// 現在のロゴのIDが0番目だったら
	if (m_nowLogoNumber == ELOGONOW::dxlib)
	{
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
		// ロゴ表示時間が300より大きかったら
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;				// ロゴ表示時間をリセットする
			m_nowLogoNumber = ELOGONOW::dxlib;				// ロゴのIDを1番目にする
		}
	}
}
