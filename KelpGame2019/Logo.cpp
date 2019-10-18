#include "Logo.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	mD_dxlibLogo = LoadGraph("media\\logo\\DxLogo.jpg");
	mD_teamLogo = LoadGraph("media\\logo\\天下無双ロゴ.png");
	mD_skip = LoadGraph("media\\logo\\ASkip.png");
	mD_Re = LoadGraph("media\\logo\\re.png");
	mD_Okizari = LoadGraph("media\\logo\\okizari.png");
	mD_Pazuru = LoadGraph("media\\logo\\pazuru.png");
	mD_Escape = LoadGraph("media\\logo\\escape.png");

	m_nowLogoNumber = ELOGONOW::dxlib;
	m_logoTransTime = 0;

	m_endFlag = false;

	m_x = 1520;
	m_y = 648;
	m_addX = -16;
	m_addY = -16;
	m_turnY = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	if (mD_Escape != -1) DeleteGraph(mD_Escape);
	if (mD_Pazuru != -1) DeleteGraph(mD_Pazuru);
	if (mD_Okizari != -1) DeleteGraph(mD_Okizari);
	if (mD_Re != -1) DeleteGraph(mD_Re);
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
		switch (m_turnY)
		{
		case 1:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
			DrawGraph(0, 0, mD_Pazuru, false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;

		case 2:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
			DrawGraph(0, 0, mD_Okizari, false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;

		case 3:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
			DrawGraph(0, 0, mD_Escape, false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;

		case 4:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
			DrawGraph(0, 0, mD_Re, false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;

		default:
			break;
		}
		DrawRotaGraph(m_x, m_y, 0.25, 0, mD_teamLogo, true);
		// DrawGraph(960 - 960/*中心座標 - 横サイズの半分*/, 540 - 540/*中心座標 - 縦サイズの半分*/, mD_teamLogo, true);		// teamのロゴを表示
		// printfDx("%d\t%d\n", m_x, m_y);
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
		m_x += m_addX;
		m_y += m_addY;
		if (m_x - 128 < 0 || m_x + 128 > 1920) m_addX = -m_addX;
		if (m_y - 128 < 0 || m_y + 128 > 1080)
		{
			m_addY = -m_addY;
			m_turnY++;
		}
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
