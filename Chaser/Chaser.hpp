#pragma once



class Chaser
{
private:
	int mD_chaserArray[31];
	const int m_chaserArrayNum = 31;
	int m_chaserSpeedCount;
	int m_chasrArraySpeed = 2;

	int mD_backGround;
	int mD_underGround;
	int mD_player;

	int mD_screen;
	int m_zoom;

	int m_chaserX;

	int m_scrollX;
	int m_playerX;


public:
	Chaser();
	~Chaser();


	void Draw();

	void Process();
};

