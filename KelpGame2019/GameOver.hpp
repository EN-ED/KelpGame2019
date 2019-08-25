#pragma once
#include "BaseScene.hpp"


class GameOver : public BaseScene
{
private:
	/// ‰æ‘œ

	int mD_backGround;		// “®‰æ‚Ì‰æ‘œ

public:
	GameOver();
	~GameOver();


	// •`‰æ
	void Draw() override;

	// ƒvƒƒZƒX
	void Process() override;
};

