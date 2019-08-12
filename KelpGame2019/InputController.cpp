#include "InputController.hpp"



namespace ps = PadStick;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------

int PadData::m_button[4][16];

int PadData::m_stick[4][6];
int PadData::m_stickCheck[4][8];
int PadData::m_trigger[4][2];

short PadData::stickLX_DeadZoneMAX = 1000;
short PadData::stickLX_DeadZoneMIN = -1000;
short PadData::stickLY_DeadZoneMAX = 1000;
short PadData::stickLY_DeadZoneMIN = -1000;
short PadData::stickRX_DeadZoneMAX = 1000;
short PadData::stickRX_DeadZoneMIN = -1000;
short PadData::stickRY_DeadZoneMAX = 1000;
short PadData::stickRY_DeadZoneMIN = -1000;

XINPUT_STATE PadData::m_input[4];

char PadData::m_padNum = -1;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void PadData::UpDate()
{
	// �Q�[���p�b�h�̎擾�o���Ă��邩
	if (m_padNum == -1) return;


	// �Q�[���p�b�h�̌���������
	for (int padNumber = 0; padNumber < static_cast<int>(m_padNum); ++padNumber)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(padNumber + 1, &m_input[padNumber]);



		/// �{�^���֌W-----------------------------------------------------------
		{
			// �S�{�^�����͏���
			for (int j = 0; j < 16; ++j)
			{
				// ������Ă��Ȃ�������
				if (m_input[padNumber].Buttons[j] == 0)
				{
					if (m_button[padNumber][j] < 0)
					{
						m_button[padNumber][j] = 0;
					}
					else if (m_button[padNumber][j] > 0)
					{
						m_button[padNumber][j] = -1;
					}
				}
				// i�Ԃ̃L�[�R�[�h�ɑΉ�����{�^����������Ă�����
				else if (m_input[padNumber].Buttons[j] == 1)
				{
					m_button[padNumber][j]++;
				}
			}
		}
		/// ---------------------------------------------------------------------



		/// �g���K�[�֌W---------------------------------------------------------
		{
			// �g���K�[�̓��͐��l��n��
			m_trigger[padNumber][ps::LEFT_TRIGGER] = m_input[padNumber].LeftTrigger;
			m_trigger[padNumber][ps::RIGHT_TRIGGER] = m_input[padNumber].RightTrigger;
		}
		/// ---------------------------------------------------------------------



		/// �X�e�B�b�N���͊֌W---------------------------------------------------
		{
			/// �X�e�B�b�N�̃f�b�h�]�[�����l���������͐��l���擾�i�f�b�h�]�[���͎󂯕t���Ȃ��l

			// ���X�e�B�b�N���E
			if (m_input[padNumber].ThumbLX > stickLX_DeadZoneMAX || m_input[padNumber].ThumbLX < stickLX_DeadZoneMIN)
			{
				m_stick[padNumber][ps::LEFT_STICK_X] = m_input[padNumber].ThumbLX;
			}
			else
			{
				if (m_stick[padNumber][ps::LEFT_STICK_X] != 0) m_stick[padNumber][ps::LEFT_STICK_X] = 0;
			}

			// ���X�e�B�b�N�㉺
			if (m_input[padNumber].ThumbLY > stickLY_DeadZoneMAX || m_input[padNumber].ThumbLY < stickLY_DeadZoneMIN)
			{
				m_stick[padNumber][ps::LEFT_STICK_Y] = m_input[padNumber].ThumbLY;
			}
			else
			{
				if (m_stick[padNumber][ps::LEFT_STICK_Y] != 0) m_stick[padNumber][ps::LEFT_STICK_Y] = 0;
			}

			// �E�X�e�B�b�N���E
			if (m_input[padNumber].ThumbRX > stickRX_DeadZoneMAX || m_input[padNumber].ThumbRX < stickRX_DeadZoneMIN)
			{
				m_stick[padNumber][ps::RIGHT_STICK_X] = m_input[padNumber].ThumbRX;
			}
			else
			{
				if (m_stick[padNumber][ps::RIGHT_STICK_X] != 0) m_stick[padNumber][ps::RIGHT_STICK_X] = 0;
			}

			// �E�X�e�B�b�N�㉺
			if (m_input[padNumber].ThumbRY > stickRY_DeadZoneMAX || m_input[padNumber].ThumbRY < stickRY_DeadZoneMIN)
			{
				m_stick[padNumber][ps::RIGHT_STICK_Y] = m_input[padNumber].ThumbRY;
			}
			else
			{
				if (m_stick[padNumber][ps::RIGHT_STICK_Y] != 0) m_stick[padNumber][ps::RIGHT_STICK_Y] = 0;
			}
		}
		/// ---------------------------------------------------------------------



		/// �X�e�B�b�N�����|���֌W-----------------------------------------------
		{
			// ���X�e�B�b�N���E�ɉ����|���Ă�����
			if (m_input[padNumber].ThumbLX == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)]++;
			}
			// ���X�e�B�b�N�����ɉ����|���Ă�����
			else if (m_input[padNumber].ThumbLX == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)]++;
			}
			// ���X�e�B�b�N�������|����Ă��Ȃ�������
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] = -1;
				}
			}


			// ���X�e�B�b�N����ɉ����|���Ă�����
			if (m_input[padNumber].ThumbLY == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)]++;
			}
			// ���X�e�B�b�N�����ɉ����|���Ă�����
			else if (m_input[padNumber].ThumbLY == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)]++;
			}
			// ���X�e�B�b�N�������|����Ă��Ȃ�������
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] = -1;
				}
			}


			// �E�X�e�B�b�N���E�ɉ����|���Ă�����
			if (m_input[padNumber].ThumbRX == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)]++;
			}
			// �E�X�e�B�b�N�����ɉ����|���Ă�����
			else if (m_input[padNumber].ThumbRX == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)]++;
			}
			// �E�X�e�B�b�N�������|����Ă��Ȃ�������
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] = -1;
				}
			}


			// �E�X�e�B�b�N����ɉ����|���Ă�����
			if (m_input[padNumber].ThumbRY == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)]++;
			}
			// �E�X�e�B�b�N�����ɉ����|���Ă�����
			else if (m_input[padNumber].ThumbRY == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)]++;
			}
			// �E�X�e�B�b�N�������|����Ă��Ȃ�������
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] = -1;
				}
			}
		}
		/// ---------------------------------------------------------------------
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetButton(const int& t_code, const int& t_padNum)
{
	return m_button[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetTrigger(const int& t_code, const int& t_padNum)
{
	return m_trigger[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetStick(const int& t_code, const int& t_padNum)
{
	return m_stick[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftOrDown)
{
	if (t_leftOrDown)
	{
		return m_stickCheck[t_padNum][t_code - 2];
	}
	else
	{
		return m_stickCheck[t_padNum][t_code - 2 + 4];
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const bool PadData::IsCheckEnd()
{
	return
	{
		(m_button[0][XINPUT_BUTTON_START] > 1 && m_button[0][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[1][XINPUT_BUTTON_START] > 1 && m_button[1][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[2][XINPUT_BUTTON_START] > 1 && m_button[2][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[3][XINPUT_BUTTON_START] > 1 && m_button[3][XINPUT_BUTTON_BACK] > 1)
	};
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const char PadData::GetPadNum()
{
	return m_padNum;
}