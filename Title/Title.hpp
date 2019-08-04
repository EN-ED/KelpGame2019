#pragma once
#include "DxLib.h"
#include "InputKey.hpp"


class Title
{
private:
	int m_backGroundColor;		// 背景色

	enum class Scene { one, two };		// シーン

	Scene m_sceneChange;		// 現在のシーン

	int m_sceneChangeCount;		// シーンの移動完了までカウント

	const int m_sceneChangeMaxCount = 20;		// シーンの移動終了までのカウント値

	int m_sceneSideDrawX;			// シーン移動時の横移動値（oneとtwoを両方描画する）

	const int m_sceneTwoDefaultSideDrawX = 1920;		// シーン移動時の横最大値


	/// シーン１だけに関する

	int mD_sceneOneStart;		// 最初のスタート文字

	int m_sceneOneStartBlendCount;		// 最初の文字の透過値
	bool m_isBlendDownSwitch;			// 文字の透過値を下げるかどうか

	void SceneOneDraw();		// シーン１の描画
	void SceneOneProcess();		// シーン１のプロセス


	/// シーン２だけに関する

	int mD_sceneTwoStart;		// 2番目のスタート文字
	int mD_sceneTwoEnd;			// 2番目の終了文字

	enum class TwoCursolArea { start, end };		// カーソルの位置

	TwoCursolArea m_cursolArea;			// カーソルの位置がどこにあるか

	float m_sceneTwoFontBigCount;		// カーソルが当たっている文字のサイズ値
	bool m_isFontBigDownSwitch;			// 文字のサイズ値を下げるかどうか

	void SceneTwoDraw();			// シーン２の描画
	void SceneTwoProcess();			// シーン２のプロセス


public:
	Title();
	~Title();


	// 描画
	void Draw();

	// プロセス
	void Process();
};

