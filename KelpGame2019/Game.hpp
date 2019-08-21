#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"
#include "Character.hpp"


class Game : public BaseScene
{
private:
	BackGround* mp_backGround;
	Character* mp_character;

	bool m_isFirstSpeedUp;


public:
	Game();
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

