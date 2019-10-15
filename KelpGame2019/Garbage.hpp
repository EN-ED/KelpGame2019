#pragma once
#include "DxLib.h"



class Garbage
{
public:
	enum class EDrawID { doro, mizutamari, sekiyu };



private:
	int m_x;
	int m_y;

	int mD_garbage;


	EDrawID m_ID;



public:
	Garbage(const int& t_x, const int& t_y, EDrawID t_ID);
	~Garbage();


	void Draw();

	void Process(const int& t_speed);

	const int& GetX() const;
	const int& GetY() const;
	const EDrawID& GetID() const;
};

