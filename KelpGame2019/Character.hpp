#pragma once
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "SoundProcess.hpp"
#include "InputController.hpp"



/*
石鹸君（主人公）
*/
class Character
{
public:
	// どの障害物に当たったか判定するための列挙
	enum class EHitGarbageID { doro, mizutamari, sekiyu, none };


private:
	/// 画像------------------------------------------------
	int mD_playerArray[20];				// 通常の石鹸君
	int mD_playerDirtArray[20];			// 泥に浸かった石鹸君
	int mD_playerWaterArray[20];			// 水に浸かった石鹸君
	int mD_playerSpeedArray[20];		// 加速している石鹸君

	int mD_speedUpDescription;			// 加速できることを教える画像

	int mD_jumpDescription;				// ジャンプボタンを教える画像

	int mD_speedNumber[10];				// 速度の画像
	int mD_speedComma;					// 速度のコンマ画像



	/// 画像の処理系----------------------------------------
	const int m_playerDrawNum = 20;				// 画像のコマ数
	const int m_playerDrawAnimSpeed = 6;		// 画像のコマを送る速度の最大
	int m_playerDrawAnimCount;					// 画像のコマを送る速度のカウント

	const int m_runFirstPlayerAnim = m_playerDrawAnimSpeed * 13;	// 急加速したときの石鹸君のフレームコマ

	const int m_jumpFirstPlayerAnim = m_playerDrawAnimSpeed * 8;	// ジャンプしたときの石鹸君のフレームコマ



	/// 座標の処理系----------------------------------------
	const int m_playerSize = 192;			// プレイヤーの画像サイズ
	const int m_mostMaxY = 1080 - 128;		// プレイヤーの最大最底辺位置
	const int m_defaultX = 284;				// プレイヤーの基準X座標

	int m_playerX, m_playerY;		// 石鹸君の座標
	int m_prePlayerX, m_prePlayerY;	// 石鹸君の直前座標

		// 石鹸君の状態を示す列挙
	enum class ESTATE{ normal, speedUp, speedMAX, speedDown, damageHit, heal, doroDamageHit };
	ESTATE m_nowState;				// 現在の状態
	
		// 座標処理
	void PositionProcess();



	/// 自然縮小処理系-----------------------------------------
	int m_smallCount;					// 時間経過で石鹸君が小さくなるカウント
	const int m_smallCountTime = 30;	// 小さくなるタイミング

	float m_smallSpeed;					// 石鹸君の縮小している数値
	const float m_smallValue = 0.005f;	// 縮小する数値



	/// ダメージ処理系------------------------------------------
	int m_damageCount;						// ダメージを受けた演出のカウント
	const int m_damageMaxCount = 30;		// ダメージを受けた演出のカウントの最大

	bool m_isDamageHit;						// ダメージを受けたかどうか

	float m_preDamageMAXSpeed;				// ダメージによる減速の最大値
	const float m_damageDownSpeed = -1.25f;	// ダメージによる減速の加算値

	const float m_damageSmallValue = 0.05f;	// ダメージによる縮小する数値

		// ダメージ処理
	void HitGarbageProcess();



	/// 障害物処理系-------------------------------------------
	bool m_isHitGarbage;					// 障害物に当たったかどうか

		/// 同じ障害物IDに対して何度も当たらないようにするための変数群
	int m_hitGarbageID;						// 配置されている障害物IDのうちどれにあたったか
	int m_preHitGarbageID;					// 直前に当たった障害物IDはどれか

	EHitGarbageID m_hitGarbageObjectID;		// どの障害物に当たったか



	/// 回復処理系--------------------------------------------
	int m_healCount;						// ダメージを受けた演出のカウント
	const int m_healMaxCount = 15;		// ダメージを受けた演出のカウントの最大

	bool m_nowHeal;							// 回復障害物（灯油）に当たったかどうか



	/// スピード処理系-----------------------------------------
	float m_nowSpeed;						// 現在のスピード
	const float m_playerMaxSpeed = 70;		// プレイヤーの最大速度

	int m_nowSpeedThirdDigit;		// 現在の速度の三桁目の数字
	int m_nowSpeedSecondDigit;		// 現在の速度の二桁目の数字
	int m_nowSpeedFirstDigit;		// 現在の速度の二桁目の数字
	int m_nowSpeedDecimalPoint;		// 現在の速度の小数点の数字

		// スピード処理
	void SpeedProcess();



	/// スピードの加速処理系------------------------------------
	bool m_isNowSpeedUp;				// 加速中かどうか

	int m_speedUpChargeCount;			// 加速可能までの時間
	const int m_speedUpChargeMax = 420;	// 加速可能までの最大時間

	float m_addSpeed;						// 加算中に加算されるスピード値
	float m_speedUpCount;					// 加速が最大になるまでの時間
	const float m_speedUpCountTime = 1.0f;	// 加速が最大時になるまでの必要時間
	int m_speedMaxWaitCount;				// 加速最大値の時に持続する時間
	const int m_speedMaxWaitMaxCount = 40;	// 加速最大値の時に持続する時間の最大(2で割り切れないと少しずれる

		// スピード加速処理
	void SpeedUpProcess();



	/// ジャンプ処理系------------------------------------------
	int m_playerUnderY;		// プレイヤーの足元のY座標
	
	bool m_isGroundFlag;	// 地面に触れてるか
	bool m_isJumpFlag;		// ジャンプしているか
	bool m_isLongJump;		// 長押しジャンプか

	int m_jumpPower;		// ジャンプ力
	int m_gravityPower;		// 重力

	const int m_jumpMaxPower = 120;		// ジャンプ力の最大値
	const int m_jumpMinPower = 24;		// ジャンプ力の最小値

	const int m_jumpAddPower = 16;		// ジャンプ中の上昇値
	const int m_jumpGravityEnergy = 8;	// ジャンプ中の減少値

	bool m_isFlyDamageHit;		// ジャンプ中にダメージを受けたかどうか

		// ジャンプ処理
	void PlayerJump();



public:
	Character();
	~Character();


	// 描画
	void Draw();

	// ブラー処理描画
	void BlurDraw();

	// 処理
	void Process();


	// ゲーム開始時のアニメーションの描画
	void FirstDraw(int t_x, int t_y, bool t_turn);

	// ゲーム開始時のアニメーションの処理
	void FirstProcess();


	// 障害物が当たった
	void HitGarbageNow(const int t_garbageID, const EHitGarbageID t_garbageObjectID);


	const bool GetIsSpeedUp() const;

	const float GetSpeed() const;
	
	const float GetDefaultMAXSpeed() const;

	const int GetAreaX() const;
	
	const int GetAreaY() const;
	
	const float GetSize() const;
	
	const bool GetNowDamage() const;
	
	const bool GetNowHeal() const;
	
	const float GetSmallSpeed() const;
};

