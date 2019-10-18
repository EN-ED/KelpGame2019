#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneOneDraw()
{
	// スタート文字
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_sceneOneStartBlendCount);
	DrawGraph(m_sceneSideDrawX + 960 - 200, 800 - 24, mD_sceneOneStart, true);
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

	m_exRate += m_add;
	if (m_exRate < 0.2 || m_exRate > 0.65) m_add = -m_add;


	if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		SoundProcess::Play(SoundProcess::E_SE::selectDo);
		m_sceneTwoFontBigCount = 1.0f;
		m_sceneChangeCount = 0;
		m_x = 960 + 480;
		m_y = -120;
		m_exRate = 0.45;
		m_add = 1;
		m_angle = 0;
		m_sceneChange = Scene::two;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneTwoDraw()
{
	if (m_cursolArea == TwoCursolArea::start)
	{
		// スタート文字
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, m_sceneTwoFontBigCount, -0.2, mD_sceneTwoStart, true);


		// 終了文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, 1.0, -0.2, mD_sceneTwoEnd, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (m_cursolArea == TwoCursolArea::end)
	{
		// スタート文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, 1.0, -0.2, mD_sceneTwoStart, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// 終了文字
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, m_sceneTwoFontBigCount, -0.2, mD_sceneTwoEnd, true);
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


	if (PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, false) == 1)
	{
		m_cursolArea = TwoCursolArea::start;
		m_sceneTwoFontBigCount = 1.0f;
	}
	else if (PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, true) == 1)
	{
		m_cursolArea = TwoCursolArea::end;
		m_sceneTwoFontBigCount = 1.0f;
	}


	if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		SoundProcess::Play(SoundProcess::E_SE::selectDo);
		if (m_cursolArea == TwoCursolArea::start)
		{
			BASICPARAM::e_nowScene = ESceneNumber::GAME;
		}
		else if (m_cursolArea == TwoCursolArea::end)
		{
			m_endFlag = true;
		}
	}


	if (PadData::GetButton(XINPUT_BUTTON_B, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		SoundProcess::Play(SoundProcess::E_SE::selectCancel);
		m_sceneOneStartBlendCount = 50;
		m_sceneChangeCount = 0;
		m_x = 960;
		m_y = -120;
		m_exRate = 0.65;
		m_add = -0.01;
		m_angle = 0;
		m_sceneChange = Scene::one;
	}


	DrawGraph(1720, 720 + 24, mD_back, true);

	m_angle += m_add;
	if (m_angle < -12 || m_angle > 12) m_add = -m_add;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::Title()
{
	mD_select = LoadGraph("media\\title\\Aselect.png");
	mD_back = LoadGraph("media\\title\\BBack.png");

	mD_sceneOneStart = LoadGraph("media\\title\\start_sceneOne.png");

	m_sceneOneStartBlendCount = 50;
	m_isBlendDownSwitch = false;

	mD_sceneTwoStart = LoadGraph("media\\title\\start_sceneTwo.png");
	mD_sceneTwoEnd = LoadGraph("media\\title\\end_sceneTwo.png");

	m_cursolArea = TwoCursolArea::start;
	m_sceneTwoFontBigCount = 1.0f;
	m_isFontBigDownSwitch = false;

	m_backGroundColor = 10;

	m_sceneChange = Scene::one;

	m_sceneChangeCount = m_sceneChangeMaxCount;

	m_sceneSideDrawX = 0;

	m_endFlag = false;

	mD_TitleLogo = LoadGraph("media\\title\\石鹸君ロゴ.png");

	m_x = 960;
	m_y = -120;
	m_exRate = 0.65;
	m_add = -0.01;
	m_angle = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::~Title()
{
	if (mD_sceneTwoEnd != -1) DeleteGraph(mD_sceneTwoEnd);
	if (mD_sceneTwoStart != -1) DeleteGraph(mD_sceneTwoStart);
	if (mD_sceneOneStart != -1) DeleteGraph(mD_sceneOneStart);
	if (mD_back != -1) DeleteGraph(mD_back);
	if (mD_select != -1) DeleteGraph(mD_select);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	// 背景
	DrawBox(0, 0, 1920, 1080, GetColor(10, m_backGroundColor, 10), true);

	DrawRotaGraph(m_x, m_y + 516, m_exRate, 3.14 / 180 * m_angle, mD_TitleLogo, true);

	if (m_sceneChange == Scene::one)
	{
		SceneOneDraw();
	}
	else if (m_sceneChange == Scene::two)
	{
		SceneTwoDraw();
	}

	DrawGraph(1720, 720, mD_select, true);
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
