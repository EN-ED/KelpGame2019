#pragma once


class BackGround
{
private:
	int mD_backGround;
	int m_areaX;
	int m_speed;

	int mD_underGround;


public:
	BackGround();
	~BackGround();


	void Draw();

	void Process();
};

