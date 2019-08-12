#pragma once


class BackGround
{
private:
	int mD_backGround;
	int m_areaX;
	int m_speed;


public:
	BackGround();
	~BackGround();


	void Draw();

	void Process();
};

