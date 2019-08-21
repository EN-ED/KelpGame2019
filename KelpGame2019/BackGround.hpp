#pragma once


class BackGround
{
private:
	int mD_backGround;
	int mD_underGround;
	int m_areaX;
	int m_speed;

	bool m_isSpeedUp;


public:
	BackGround();
	~BackGround();


	void Draw();

	void Process();

	void SetIsSpeedUp(const bool& t_isSpeedUp);
};

