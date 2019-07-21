#pragma once
#include "BaseScene.hpp"


class Logo : public BaseScene
{
private:
	/// 画像

	int mD_movieDraw;		// 動画の画像
	int mD_dxlibLogo;		// dxlibの画像


	/// シーン遷移に関する

	int m_nowLogoNumber;	// 現在のロゴ
	int m_movieZoom;		// 動画のズームタイム
	int m_logoTransTime;	// ロゴの遷移時間

public:
	Logo();
	~Logo();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

