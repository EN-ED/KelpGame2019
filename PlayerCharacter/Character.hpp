#pragma once
#include "DxLib.h"
#include "InputKey.hpp"
#include <random>


class Character
{
private:
	int mD_playerDraw;						// プレイヤー画像
	const int m_playerSize = 128;			// プレイヤーの画像サイズ

	const int m_mostMaxY = 1080 - 128;		// プレイヤーの最大最底辺位置
	const int m_defaultX = 284;				// プレイヤーの基準X座標

	const int m_playerMaxSpeed = 70;			// プレイヤーの最大速度

	float m_nowSpeed;							// 現在のスピード

	void SpeedProcess();

	void PlayerJump();

	int m_playerX;		// プレイヤーのX座標
	int m_playerY;
	int m_playerUnderY;		// プレイヤーのY座標


	/// ジャンプ関連--------------------------------------------

	bool m_isGroundFlag;	// 地面に触れてるか

	bool m_isJumpFlag;	// ジャンプしているか

	bool m_isLongJump;	// 長押しジャンプか

	int m_jumpPower;	// ジャンプ力

	int m_gravityPower;	// 重力

	const int m_jumpMaxPower = 40;		// ジャンプ力の最大値

	const int m_jumpMinPower = 10;		// ジャンプ力の最小値
	/// --------------------------------------------------------



	/// 関係ないもの
	int m_backGroundColorRed;			// 背景色赤
	int m_backGroundColorGreen;			// 背景色緑
	int m_backGroundColorBlue;			// 背景色青

	int m_backGroundSwitch;
	bool m_isBackGroundChange;




public:
	Character();
	~Character();


	// 描画
	void Draw();

	// プロセス
	void Process();
};

