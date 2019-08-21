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


	// ï`âÊ
	void Draw() override;

	// ÉvÉçÉZÉX
	void Process() override;
};

