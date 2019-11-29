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
	// 画像-------------------------------------------
	int mD_select;			// 決定ボタンの説明
	int mD_back;			// 戻るボタンの説明
	int mD_TitleLogo;		// タイトルロゴ

	int mD_backGround;		// 背景画像


	// 背景画像の処理系-------------------------------
	int m_backGroundAngle;	// 角度


	// タイトルロゴの処理系---------------------------
	int m_x, m_y;			// 座標
	double m_exRate;		// 大きさ
	double m_add;			// 大きさの加算値
	double m_angle;			// 角度


	// シーンの処理系---------------------------------
		// タイトルのシーン
	enum class Scene { one, two };

	Scene m_sceneChange;		// 現在のシーン

	int m_sceneChangeCount;						// シーンの移動完了までカウント
	const int m_sceneChangeMaxCount = 20;		// シーンの移動終了までのカウント値

	int m_sceneSideDrawX;								// シーン移動時の横移動値（oneとtwoを両方描画する）
	const int m_sceneTwoDefaultSideDrawX = 1920;		// シーン移動時の横最大値

	int m_logoBlendValue;		// ロゴの透過値


	// シーン１だけに関する画像-----------------------
	int mD_sceneOneStart;

	void SceneOneDraw();


	// シーン１だけに関する処理-----------------------
	int m_sceneOneStartBlendCount;		// 開始画像を大きくしたり小さくする数値
	bool m_isBlendDownSwitch;			// 大きくするのか小さくするのかどうか

	void SceneOneProcess();


	// シーン２だけに関する画像-----------------------
	int mD_sceneTwoStart;
	int mD_sceneTwoEnd;

	void SceneTwoDraw();


	// シーン２だけに関する処理-----------------------
		// カーソルの位置
	enum class TwoCursolArea { start, end, omakeOne, omakeTwo };
	TwoCursolArea m_cursolArea;		// カーソルはどこにいるか

	float m_sceneTwoFontBigCount;	// 選択しているカーソルを大きくしたり小さくする数値
	bool m_isFontBigDownSwitch;		// 大きくするのか小さくするのかどうか

	bool m_selectCommandLeft;	// 選択カーソルが左にあるかどうか

	void SceneTwoProcess();


	// おまけ１に関する画像---------------------------
	int mD_omakeOne;


	// おまけ１に関する処理---------------------------
	int m_omakeOneCommandNumber;		// おまけ１を出現するためのコマンドを押している数
	int m_omakeOneAbleFrame;			// おまけ１を出現させるための次のコマンドまでに押していないフレーム
	bool m_omakeOneLeft;				// おまけ１を選択しているかどうか
	bool m_omakeOneOpen;				// おまけ１を出現させたかどうか


	// おまけ２に関する画像---------------------------
	int mD_omakeTwo;


	// おまけ２に関する処理---------------------------
	int m_omakeTwoCommandNumber;		// おまけ２を出現するためのコマンドを押している数
	int m_omakeTwoAbleFrame;			// おまけ２を出現させるための次のコマンドまでに押していないフレーム
	bool m_omakeTwoLeft;				// おまけ２を選択しているかどうか
	bool m_omakeTwoOpen;				// おまけ２を出現させたかどうか


public:
	Title();
	~Title();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

