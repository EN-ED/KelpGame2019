#pragma once
#include "BaseScene.hpp"


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

