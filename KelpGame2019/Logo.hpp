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
	int mD_teamLogo;		// 動画の画像
	int mD_dxlibLogo;		// dxlibの画像
	int mD_skip;
	int mD_Re;
	int mD_Okizari;
	int mD_Pazuru;
	int mD_Escape;

	int m_x;
	int m_y;
	int m_addX;
	int m_addY;
	int m_turnY;


	/// シーン遷移に関する

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

