#pragma once
#include "DxLib.h"
#include "InputKey.hpp"


class Title
{
private:
	int m_backGroundColor;		// 背景色

	enum class Scene { one, two };

	Scene m_sceneChange;

	int m_sceneChangeCount;

	const int m_sceneChangeMaxCount = 20;

	int m_sceneSideDrawX;

	const int m_sceneTwoDefaultSideDrawX = 1920;


	int m_sceneOneStart;		// 最初のスタート文字

	int m_sceneOneStartBlendCount;		// 最初の文字の透過値
	bool m_isBlendDownSwitch;

	void SceneOneDraw();
	void SceneOneProcess();



	int m_sceneTwoStart;		// 2番目のスタート文字
	int m_sceneTwoEnd;			// 2番目の終了文字

	enum class TwoCursolArea { start, end };

	TwoCursolArea m_cursolArea;			// カーソルの位置

	float m_sceneTwoFontBigCount;		// 最初の文字のサイズ値
	bool m_isFontBigDownSwitch;

	void SceneTwoDraw();
	void SceneTwoProcess();


public:
	Title();
	~Title();


	// 描画
	void Draw();

	// プロセス
	void Process();
};

