#pragma once
#ifndef _BLURSCREEN_HPP
#define _BLURSCREEN_HPP
#include "DxLib.h"



/*
ブラー処理
*/
struct BlurScreen
{
private:
	int m_screen[2];									// 背面に使うスクリーン画像
	int m_current;										// 2枚のどの画像を使っているか
	int m_alpha;										// 透過値
	int m_screenWidth, m_screenHeight;					// スクリーンの各大きさ
	int m_offsetX1, m_offsetX2, m_offsetY1, offsetY2;	// ブラー処理をする方向
	int m_notBlendDraw;									// 数フレームだけブラー処理させないためのカウント変数


public:
	BlurScreen() 
	{
		m_screen[0] = 0;
		m_screen[1] = 0;
		m_current = 0;
		m_alpha = 0;
		m_screenWidth = 0;
		m_screenHeight = 0;
		m_offsetX1 = 0;
		m_offsetX2 = 0; 
		m_offsetY1 = 0; 
		offsetY2 = 0; 
		m_notBlendDraw = 0;
	}
	~BlurScreen() {}


	// 初期化
	void Init(int t_alpha, int t_offsetX1, int t_offsetY1, int t_offsetX2, int t_offsetY2);

	// ブラー処理する直前に一回だけ呼ぶ
	void ReplayInit();

	// 解放
	void Release();

	// ブラー処理をする描画の直前に置く
	void PreRenderBlurScreen();

	// ブラー処理をする描画の後に置く
	void PostRenderBlurScreen();
};

#endif // !_BLURSCREEN_HPP