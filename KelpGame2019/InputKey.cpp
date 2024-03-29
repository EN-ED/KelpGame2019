#include "InputKey.hpp"



/// ---------------------------------------------------------------------------------------

int KeyData::m_key[256];
char KeyData::m_tmpKey[256];



/// ---------------------------------------------------------------------------------------
void KeyData::UpDate()
{
	// 全てのキーの入力状態を得る（押されたら１を出力し、押されていなかったら０を返す
	if (GetHitKeyStateAll(m_tmpKey) == -1) return;


	// 全キー入力処理
	for (int i = 0; i < 256; ++i)
	{
		// 押されていなかったら
		if (m_tmpKey[i] == 0)
		{
			if (m_key[i] < 0)
			{
				m_key[i] = 0;
			}
			else if (m_key[i] > 0)
			{
				m_key[i] = -1;
			}
		}
		// i番のキーコードに対応するキーが押されていたら
		else if (m_tmpKey[i] == 1)
		{
			m_key[i]++;
		}
	}
}



/// ---------------------------------------------------------------------------------------
const int KeyData::Get(const int t_keyCode)
{
	return m_key[t_keyCode];
}



/// ---------------------------------------------------------------------------------------
const bool KeyData::IsCheckEnd()
{
	return m_key[KEY_INPUT_ESCAPE] > 0;
}