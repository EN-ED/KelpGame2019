#pragma once
#include "DxLib.h"
#include <string>



/*
店下無双の本体
*/
class Chaser
{
private:
	/// 画像-----------------------------------------
	int mD_chaserArray[31];


	/// 画像の処理系---------------------------------
	const int m_chaserArrayNum = 31;

	int m_chaserSpeedCount;
	int m_chasrArraySpeed;


	/// 処理系---------------------------------------
	int m_chaserX;
	const int m_chaserDefaultX = 256 - 512;

	int m_chaserXAddValue;


public:
	Chaser();
	~Chaser();


	// 描画
	void Draw();

	// 処理
	void Process();

	// ゲーム開始時のアニメーション描画
	void FirstDraw(int t_x);

	// ゲーム開始時のアニメーション処理
	void FirstProcess();


	// プレイヤーの速度を加味してチェイサーの速度を調整する
	// @param (t_playerSpeed) プレイヤーの今のスピード
	// @param (t_defaultMAXSpeed) 通常時のプレイヤーの出せる最大スピード
	void SetPlyayerSpeed(const float t_playerSpeed, const float t_defaultMAXSpeed);

	const int GetX() const;
};

