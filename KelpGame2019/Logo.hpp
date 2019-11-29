#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"



/*
ロゴのシーンの大本
*/
class Logo : public BaseScene
{
private:
	// 画像-----------------------------------
	int mD_dxlibLogo;		// dxlibの画像
	int mD_skip;			// スキップ画像

	// チームロゴ関係-------------------------
	int mD_teamLogo;
	int mD_Re;				
	int mD_Okizari;
	int mD_Pazuru;
	int mD_Escape;


	// ロゴの動き-----------------------------
	int m_x;
	int m_y;
	int m_addX;
	int m_addY;
	int m_turnY;

	
	// シーンの処理関係-----------------------
	enum class ELOGONOW { dxlib, team };
	ELOGONOW m_nowLogoNumber;	// 現在のロゴ
	int m_logoTransTime;	// ロゴの遷移時間


public:
	Logo();
	~Logo();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

