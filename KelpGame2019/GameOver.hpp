#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputKey.hpp"


class GameOver : public BaseScene
{
private:
	/// �摜

	int mD_backGround;		// ����̉摜

public:
	GameOver();
	~GameOver();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

