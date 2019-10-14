#pragma once
#include "DxLib.h"
#include "InputKey.hpp"


class BackGround
{
private:
	int mD_backGround;
	int mD_underGround;

	int m_areaX;
	int m_speed;


public:
	BackGround();
	~BackGround();


	void Draw();

	void Process();

	void SetSpeed(const float& t_speed);
};

