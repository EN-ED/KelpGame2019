#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputKey.hpp"


class Logo : public BaseScene
{
private:
	/// ‰æ‘œ

	int m_teamLogo;		// “®‰æ‚Ì‰æ‘œ
	int m_dxlibLogo;		// dxlib‚Ì‰æ‘œ


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

