#pragma once
#include "BaseScene.hpp"


class Title : public BaseScene
{
private:


public:
	Title();
	~Title();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

