#pragma once



class Chaser
{
private:
	int mD_chaser;
	int mD_backGround;
	int mD_underGround;
	int mD_player;

	int m_scrollX;
	int m_playerX;


public:
	Chaser();
	~Chaser();


	void Draw();

	void Process();
};

