#pragma once
#include "DxLib.h"



/*
ƒQ[ƒ€’†‚Ì”wŒi‚Ì–{‘Ì
*/
class BackGround
{
private:
	int mD_backGround;			// ”wŒi‰æ‘œ
	int mD_underGround;			// °‰æ‘œ
	
	int m_areaX;
	int m_speed;


public:
	BackGround(int t_stageCorse);
	~BackGround();


	void Draw();

	void Process();

	void SetSpeed(const float& t_speed);
};

