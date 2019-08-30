#pragma once



class Chaser
{
private:
	int mD_chaserArray[31];
	const int m_chaserArrayNum = 31;
	int m_chaserSpeedCount;
	int m_chasrArraySpeed;

	int m_chaserX;
	const int m_chaserDefaultX = 256 - 512;

	int m_chaserXAddValue;


public:
	Chaser();
	~Chaser();


	void Draw();

	void Process();


	void SetPlyayerSpeed(const float& t_playerSpeed, const float& t_defaultMAXSpeed);
};

