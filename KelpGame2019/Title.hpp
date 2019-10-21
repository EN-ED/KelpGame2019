#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"
#include "SoundProcess.hpp"



/*
タイトルのシーンの大本
*/
class Title : public BaseScene
{
private:
	int m_backGroundColor;		// 背景色

	enum class Scene { one, two };		// シーン

	Scene m_sceneChange;		// 現在のシーン

	int m_sceneChangeCount;		// シーンの移動完了までカウント

	const int m_sceneChangeMaxCount = 20;		// シーンの移動終了までのカウント値

	int m_sceneSideDrawX;			// シーン移動時の横移動値（oneとtwoを両方描画する）

	const int m_sceneTwoDefaultSideDrawX = 1920;		// シーン移動時の横最大値

	int mD_select;

	int mD_back;

	int mD_TitleLogo;

	int m_x;
	int m_y;
	double m_exRate;
	double m_add;
	double m_angle;

	int mD_backGround;
	int m_backGroundAngle;


	/// シーン１だけに関する

	int mD_sceneOneStart;		// 最初のスタート文字

	int m_sceneOneStartBlendCount;		// 最初の文字の透過値
	bool m_isBlendDownSwitch;			// 文字の透過値を下げるかどうか

	void SceneOneDraw();		// シーン１の描画
	void SceneOneProcess();		// シーン１のプロセス


	/// シーン２だけに関する

	int mD_sceneTwoStart;		// 2番目のスタート文字
	int mD_sceneTwoEnd;			// 2番目の終了文字

	enum class TwoCursolArea { start, end, omakeOne, omakeTwo };		// カーソルの位置

	TwoCursolArea m_cursolArea;			// カーソルの位置がどこにあるか

	float m_sceneTwoFontBigCount;		// カーソルが当たっている文字のサイズ値
	bool m_isFontBigDownSwitch;			// 文字のサイズ値を下げるかどうか

	void SceneTwoDraw();			// シーン２の描画
	void SceneTwoProcess();			// シーン２のプロセス


	/// おまけ１
	int m_omakeOneCommandNumber;
	int m_omakeOneAbleFrame;
	bool m_omakeOneLeft;
	bool m_omakeOneOpen;
	int mD_omakeOne;


	/// おまけ２
	int m_omakeTwoCommandNumber;
	int m_omakeTwoAbleFrame;
	bool m_omakeTwoLeft;
	bool m_omakeTwoOpen;
	int mD_omakeTwo;

	int m_logoBlendValue;
	bool m_selectCommandLeft;


public:
	Title();
	~Title();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

