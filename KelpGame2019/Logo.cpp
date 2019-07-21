#include "Logo.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	mD_movieDraw = LoadGraph("media\\movieLogo.mp4");
	mD_dxlibLogo = LoadGraph("media\\DxLogo.jpg");

	m_nowLogoNumber = 0;
	m_movieZoom = 0;
	m_logoTransTime = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	PauseMovieToGraph(mD_movieDraw);
	DeleteGraph(mD_movieDraw);
	DeleteGraph(mD_dxlibLogo);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Draw()
{
	if (m_logoTransTime < 50)
	{
		SetDrawBright(m_logoTransTime * 5, m_logoTransTime * 5, m_logoTransTime * 5);
	}
	else if (m_logoTransTime > 250)
	{
		SetDrawBright(250 - ((m_logoTransTime - 250) * 5), 250 - ((m_logoTransTime - 250) * 5), 250 - ((m_logoTransTime - 250) * 5));
	}


	if (m_nowLogoNumber == 0)
	{
		DrawGraph(960 - 120, 540 - 120, mD_dxlibLogo, false);
	}
	else if (m_nowLogoNumber == 1)
	{
		DrawExtendGraph(960 - 480 - m_movieZoom * 2, 540 - 220 - m_movieZoom, 960 + 480 + m_movieZoom * 2, 540 + 220 + m_movieZoom, mD_movieDraw, false);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	if (m_nowLogoNumber == 0)
	{
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;
			m_nowLogoNumber = 1;
			PlayMovieToGraph(mD_movieDraw);
		}
	}
	else if (m_nowLogoNumber == 1)
	{
		if (m_logoTransTime++ >= 300)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;
		}
		else
		{
			m_movieZoom += 3;
		}
	}
}
