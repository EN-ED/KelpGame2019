#pragma once



class Chaser
{
private:
	int mD_chaserArray[31];
	const int m_chaserArrayNum = 31;
	int m_chaserSpeedCount;
	int m_chasrArraySpeed = 2;

	int m_chaserX;


public:
	Chaser();
	~Chaser();


	void Draw();

	void Process();
};

