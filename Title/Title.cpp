#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneOneDraw()
{
	// �X�^�[�g����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_sceneOneStartBlendCount);
	DrawGraph(m_sceneSideDrawX + 960 - 200, 800 - 24, m_sceneOneStart, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneOneProcess()
{
	if (m_isBlendDownSwitch)
	{
		if (m_sceneOneStartBlendCount-- < 50)
		{
			m_isBlendDownSwitch = !m_isBlendDownSwitch;
		}
	}
	else
	{
		if (m_sceneOneStartBlendCount++ > 200)
		{
			m_isBlendDownSwitch = !m_isBlendDownSwitch;
		}
	}


	if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
	{
		m_sceneChange = Scene::two;
		m_sceneTwoFontBigCount = 1.0f;

		m_sceneChangeCount = 0;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneTwoDraw()
{
	if (m_cursolArea == TwoCursolArea::start)
	{
		// �X�^�[�g����
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, m_sceneTwoFontBigCount, -0.2, m_sceneTwoStart, true);


		// �I������
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, 1.0, -0.2, m_sceneTwoEnd, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (m_cursolArea == TwoCursolArea::end)
	{
		// �X�^�[�g����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, 1.0, -0.2, m_sceneTwoStart, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// �I������
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, m_sceneTwoFontBigCount, -0.2, m_sceneTwoEnd, true);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneTwoProcess()
{
	if (m_isFontBigDownSwitch)
	{
		if ((m_sceneTwoFontBigCount -= 0.003f) < 1.0f)
		{
			m_isFontBigDownSwitch = !m_isFontBigDownSwitch;
		}
	}
	else
	{
		if ((m_sceneTwoFontBigCount += 0.005f) > 1.15f)
		{
			m_isFontBigDownSwitch = !m_isFontBigDownSwitch;
		}
	}


	if (KeyData::Get(KEY_INPUT_UP) == 1)
	{
		m_cursolArea = TwoCursolArea::start;
		m_sceneTwoFontBigCount = 1.0f;
	}
	else if (KeyData::Get(KEY_INPUT_DOWN) == 1)
	{
		m_cursolArea = TwoCursolArea::end;
		m_sceneTwoFontBigCount = 1.0f;
	}


	if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
	{
		m_sceneChange = Scene::one;
		m_sceneOneStartBlendCount = 50;

		m_sceneChangeCount = 0;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::Title()
{
	m_sceneOneStart = LoadGraph("media\\start_sceneOne.png");

	m_sceneOneStartBlendCount = 50;
	m_isBlendDownSwitch = false;

	m_sceneTwoStart = LoadGraph("media\\start_sceneTwo.png");
	m_sceneTwoEnd = LoadGraph("media\\end_sceneTwo.png");

	m_cursolArea = TwoCursolArea::start;
	m_sceneTwoFontBigCount = 1.0f;
	m_isFontBigDownSwitch = false;

	m_backGroundColor = 10;

	m_sceneChange = Scene::one;

	m_sceneChangeCount = m_sceneChangeMaxCount;

	m_sceneSideDrawX = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::~Title()
{
	if (m_sceneTwoEnd != -1) DeleteGraph(m_sceneTwoEnd);
	if (m_sceneTwoStart != -1) DeleteGraph(m_sceneTwoStart);
	if (m_sceneOneStart != -1) DeleteGraph(m_sceneOneStart);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	// �w�i
	DrawBox(0, 0, 1920, 1080, GetColor(10, m_backGroundColor, 10), true);


	SceneOneDraw();
	SceneTwoDraw();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Process()
{
	if (m_sceneChange == Scene::one)
	{
		SceneOneProcess();
		if (m_sceneChangeCount++ < m_sceneChangeMaxCount)
		{
			m_backGroundColor--;
			m_sceneSideDrawX += 1920 / m_sceneChangeMaxCount;
		}
	}
	else if (m_sceneChange == Scene::two)
	{
		SceneTwoProcess();
		if (m_sceneChangeCount++ < m_sceneChangeMaxCount)
		{
			m_backGroundColor++;
			m_sceneSideDrawX -= 1920 / m_sceneChangeMaxCount;
		}
	}
}
