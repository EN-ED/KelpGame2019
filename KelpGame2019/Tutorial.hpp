#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"
#include "Character.hpp"
#include "BackGround.hpp"
#include "Garbage.hpp"



/*
ゲーム開始前のチュートリアルのシーンの大本
*/
class Tutorial : public BaseScene
{
private:
	/// クラスポインタ-----------------------
	Character* mp_character;
	BackGround* mp_backGround;
	Garbage* mp_garbage[4];


	/// 画像---------------------------------
	int mD_skip;
	int mD_AJump;
	int mD_damage;
	int mD_speed;
	int mD_touyu;
	int mD_start;


	/// 処理系-------------------------------
	int m_blendValue;

	int m_stopNum;
	bool m_stopFlag;

	void MainProcess();
	void StopProcess();


public:
	Tutorial();
	~Tutorial();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

