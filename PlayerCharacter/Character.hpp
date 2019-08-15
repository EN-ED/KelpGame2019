#pragma once


class Character
{
private:
	const int m_playerDrawNum = 20;
	int mD_playerArray[20];

	const int m_playerDrawAnimSpeed = 6;
	int m_playerDrawAnimCount;

	const int m_playerSize = 192;			// プレイヤーの画像サイズ

	const int m_mostMaxY = 1080 - 128;		// プレイヤーの最大最底辺位置
	const int m_defaultX = 284;				// プレイヤーの基準X座標


	void PositionProcess();
	

	/// ダメージ関連--------------------------------------------

	int m_damageCount;						// ダメージを受けた演出のカウント

	const int m_damageMaxCount = 16;		// ダメージを受けた演出のカウントの最大

	int mD_playerDamageDraw;				// ダメージ演出用の画像

	bool m_isDamageHit;						// ダメージを受けたかどうか

	void DamageProcess();
	/// --------------------------------------------------------


	/// スピード関連-------------------------------------------

	const int m_playerMaxSpeed = 70;			// プレイヤーの最大速度

	float m_nowSpeed;							// 現在のスピード

	float m_addSpeed;							// 加算するスピード値

	const float m_jumpDownSpeed = -1.25f;		// ジャンプ中に減少する数値

	int m_isSpeedUp;				// 加速するかどうか
	float m_speedUpCount;				// 加速が完了するまでの時間

	int m_speedMaxWaitCount;		// 加速最大値の時に持続する時間

	const int m_speedMaxWaitMaxCount = 40;		// 加速最大値の時に持続する時間の最大(2で割り切れないと少しずれる

	int m_playerX;		// プレイヤーのX座標
	int m_playerY;		// プレイヤーのY座標

	void SpeedProcess();
	/// --------------------------------------------------------


	/// ジャンプ関連--------------------------------------------

	int m_playerUnderY;		// プレイヤーの足元のY座標

	bool m_isGroundFlag;	// 地面に触れてるか

	bool m_isJumpFlag;	// ジャンプしているか

	bool m_isLongJump;	// 長押しジャンプか

	int m_jumpPower;	// ジャンプ力

	int m_gravityPower;	// 重力

	const int m_jumpMaxPower = 40;		// ジャンプ力の最大値

	const int m_jumpMinPower = 10;		// ジャンプ力の最小値

	void PlayerJump();
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

