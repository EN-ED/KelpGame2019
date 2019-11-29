#pragma once
#include "DxLib.h"



/*
áŠQ•¨‚Ì–{‘Ì
*/
class Garbage
{
public:
	// áŠQ•¨‚Ìí—Ş
	enum class EDrawID { doro, mizutamari, sekiyu };


private:
	/// ‰æ‘œ-----------------------------
	int mD_garbage;


	/// ˆ—Œn----------------------------
	int m_x;
	int m_y;

	EDrawID m_ID;


public:
	Garbage(const int t_x, const int t_y, const EDrawID t_ID);
	~Garbage();


	// •`‰æ
	void Draw();

	// ˆ—
	void Process(const int t_speed);


	const int GetX() const;
	const int GetY() const;
	const EDrawID GetID() const;
};

