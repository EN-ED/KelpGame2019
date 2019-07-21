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
	const int m_playerMaxHP = 256;

	int m_nowSpeed;							// 現在のスピード
	int m_lowNowSpeed;						// 現在のコンマ以下のスピード
	bool m_lowSpeedChange;					// コンマ以下のスピードの数値変換タイミング


public:
	Game();
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

