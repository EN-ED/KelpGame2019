#pragma once


struct BlurScreen
{
private:
	static int m_screen[2];
	static int m_current;
	static int m_alpha;
	static int m_screenWidth, m_screenHeight;
	static int m_offsetX1, m_offsetX2, m_offsetY1, offsetY2;
	static int m_notBlendDraw;


public:
	static void Init(int alpha, int offsetX1, int offsetY1, int offsetX2, int offsetY2);
	static void ReplayInit();
	static void Release();

	static void PreRenderBlurScreen();

	static void PostRenderBlurScreen();
};