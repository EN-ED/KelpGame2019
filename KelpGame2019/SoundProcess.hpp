#pragma once
#ifndef _SOUNDPROCESS_HPP
#define _SOUNDPROCESS_HPP
#include "DxLib.h"


namespace SoundProcess
{
	enum class E_SE
	{
		jump, speedUp, slip, selectCancel, selectDo, none
	};

	enum class E_BGM
	{
		title, none
	};


	void Init();

	void Release();

	void Play(E_SE number);

	void Play(E_BGM number);

	void BGMLoop(bool startTrue);
}


#endif // !_SOUNDPROCESS_HPP