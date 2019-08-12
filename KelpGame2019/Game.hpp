#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"
#include "Character.hpp"


class Game : public BaseScene
{
private:
	BackGround* mp_backGround;
	Character* mp_character;


public:
	Game();
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

