#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"


class Game : public BaseScene
{
private:
	BackGround* mp_backGround;


public:
	Game();
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

