#pragma once




class Logo
{
private:
	/// 画像

	int m_teamLogo;		// 動画の画像
	int m_dxlibLogo;		// dxlibの画像


	/// シーン遷移に関する

	enum class ELOGONOW { dxlib, team };
	ELOGONOW m_nowLogoNumber;	// 現在のロゴ
	int m_logoTransTime;	// ロゴの遷移時間

public:
	Logo();
	~Logo();


	// 描画
	void Draw();

	// プロセス
	void Process();
};

