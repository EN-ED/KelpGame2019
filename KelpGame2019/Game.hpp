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


	// •`‰æ
	void Draw() override;

	// ƒvƒƒZƒX
	void Process() override;
};

