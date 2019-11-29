#pragma once
#include "DxLib.h"


/*
ゲーム中の背景の本体
*/
class BackGround
{
private:
	/// 画像-----------------------------------
	int mD_backGround;			// 背景画像
	int mD_underGround;			// 床画像
	
	int m_areaX;				// スクロールでの座標
	int m_speed;				// スクロールの速度


public:
	/// @param (t_stageCorse) 何ステージなのか
	BackGround(int t_stageCorse);
	~BackGround();


	// 描画
	void Draw();

	// 処理
	void Process();

	// キャラクターの速度からスクロールスピードを設定
	// @param (t_speed) キャラクターの速度
	void SetSpeed(const float t_speed);
};

