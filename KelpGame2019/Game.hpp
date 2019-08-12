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


	// •`‰æ
	void Draw() override;

	// ƒvƒƒZƒX
	void Process() override;
};

