#pragma once
#include "DxLib.h"



/*
��Q���̖{��
*/
class Garbage
{
public:
	// ��Q���̎��
	enum class EDrawID { doro, mizutamari, sekiyu };


private:
	/// �摜-----------------------------
	int mD_garbage;


	/// �����n----------------------------
	int m_x;
	int m_y;

	EDrawID m_ID;


public:
	Garbage(const int t_x, const int t_y, const EDrawID t_ID);
	~Garbage();


	// �`��
	void Draw();

	// ����
	void Process(const int t_speed);


	const int GetX() const;
	const int GetY() const;
	const EDrawID GetID() const;
};

