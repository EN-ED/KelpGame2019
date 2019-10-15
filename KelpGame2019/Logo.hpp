#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"


class Logo : public BaseScene
{
private:
	/// 画像

	int mD_teamLogo;		// 動画の画像
	int mD_dxlibLogo;		// dxlibの画像
	int mD_skip;


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

