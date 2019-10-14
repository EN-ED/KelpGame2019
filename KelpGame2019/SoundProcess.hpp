#pragma once
#ifndef _SOUNDPROCESS_HPP
#define _SOUNDPROCESS_HPP
#include "DxLib.h"


namespace SoundProcess
{
	enum class E_SE
	{
		jump, speedUp, slip, selectCancel, selectDo
	};


	void Init();

	void Release();

	void Play(E_SE number);
}


#endif // !_SOUNDPROCESS_HPP