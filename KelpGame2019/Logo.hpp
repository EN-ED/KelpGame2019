#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"


class Logo : public BaseScene
{
private:
	/// ‰æ‘œ

	int mD_teamLogo;		// “®‰æ‚Ì‰æ‘œ
	int mD_dxlibLogo;		// dxlib‚Ì‰æ‘œ
	int mD_skip;


	/// ƒV[ƒ“‘JˆÚ‚ÉŠÖ‚·‚é

	enum class ELOGONOW { dxlib, team };
	ELOGONOW m_nowLogoNumber;	// Œ»İ‚ÌƒƒS
	int m_logoTransTime;	// ƒƒS‚Ì‘JˆÚŠÔ

public:
	Logo();
	~Logo();


	// •`‰æ
	void Draw() override;

	// ƒvƒƒZƒX
	void Process() override;
};

