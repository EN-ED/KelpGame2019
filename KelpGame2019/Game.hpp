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


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

