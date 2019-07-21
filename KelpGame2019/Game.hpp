#pragma once
#include "BaseScene.hpp"
#include <random>


class Game : public BaseScene
{
private:
	int mD_backGroundDraw;					// 背景画像
	int mD_playerDraw;						// プレイヤー画像
	int mD_chaserDraw;						// 追いかけるもの画像
	int mD_garbageDraw;						// 障害物画像
	int mD_underGroundDraw;					// 床画像

	const int m_mostMaxY = 1080 - 128;		// プレイヤーの最大最底辺位置
	int m_playerHP;							// プレイヤーの体力
	const int m_playerMaxHP = 1024;						// プレイヤーの最大体力値
	const int m_playerHPdiv = m_playerMaxHP / 32;		// プレイヤーの体力に応じて大きさを小さくするための除算値
	const int m_playerMaxSpeed = 70;			// プレイヤーの最大速度

	int m_scrollX;

	int m_nowSpeed;							// 現在のスピード
	int m_lowNowSpeed;						// 現在のコンマ以下のスピード
	int m_speedChangeCount;					// コンマ以下のスピードの数値変換タイミング
	bool m_isSpeedChange;					// コンマ以下のスピードの数値変換タイミング

	void SpeedProcess();

	void PlayerJump();

	int m_playerX;		// プレイヤーのX座標

	const int m_playerMaxX = 180;		// プレイヤーのずらしたZ座標の最大値

	const int m_maxMomentSpeed = 30;		// プレイヤーの瞬間的に加速時の加算最大値

	const int m_playerHitHaleX = 20;		// プレイヤーがぶつかってひるんだ時のZ座標の最大値

	const int m_haleDownMaxSpeed = 20;		// プレイヤーがぶつかったときの減少最大値

	const int m_jumpMoveX = 3;				// プレイヤーのジャンプ時に少し右にずれるようにするときの最大X値

	/// ジャンプ関連--------------------------------------------

	int m_playerY;	// プレイヤーのY座標

	bool m_isGroundFlag;	// 地面に触れてるか

	bool m_isJumpFlag;	// ジャンプしているか

	bool m_isLongJump;	// 長押しジャンプか

	int m_jumpPower;	// ジャンプ力

	int m_gravityPower;	// 重力

	bool m_isFallNow;	// 落ちているかどうか

	int m_preY;	// 直前のY座標

	const int m_jumpMaxPower = 50;		// ジャンプ力の最大値

	const int m_jumpMinPower = 10;		// ジャンプ力の最小値
	/// --------------------------------------------------------


public:
	Game();
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

