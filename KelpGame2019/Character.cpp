#include "Character.hpp"



/// ---------------------------------------------------------------------------------------
void Character::PositionProcess()
{
	// ��������������
	if (m_nowState == ESTATE::speedUp)
	{
		// �����J�E���g������Ă��Ȃ�������
		if (m_speedUpCount < 1.0)
		{
			m_playerX += static_cast<int>(std::sinf(M_PI * m_speedUpCount) * 120.0f);
		}
	}
	// �����ő厞��������
	else if (m_nowState == ESTATE::speedMAX)
	{
		// �����ő咆�J�E���g����������ȏゾ������(�y�����ɖ߂��Ă��钆
		if (m_speedMaxWaitCount > m_speedMaxWaitMaxCount / 2 && m_speedMaxWaitCount <= m_speedMaxWaitMaxCount)
		{
			m_playerX -= static_cast<int>(std::sinf(M_PI / 5.0f) * 8.0f);
		}
		// �����ő咆�J�E���g����������ȉ���������(�y���E�ɐi��ł��钆
		else if (m_speedMaxWaitCount < /* [<]�Ȃ̂�SpeedProcess�ɍ��킹�邽�� */ m_speedMaxWaitMaxCount / 2)
		{
			m_playerX += static_cast<int>(std::sinf(M_PI / 5.0f) * 8.0f);
		}
	}
	// ��������̌�����������
	else if (m_nowState == ESTATE::speedDown)
	{
		// �ʏ펞�ɖ߂�
		if (m_speedUpCount > 0.1f)
		{
			m_playerX -= static_cast<int>(std::sinf(M_PI * m_speedUpCount) * 120.0f);
		}
	}
	// �_���[�W����������
	else if (m_nowState == ESTATE::damageHit)
	{
		m_playerX -= 2;
	}
	// �ʏ펞��������
	else if(m_nowState ==ESTATE::normal)
	{
		if (m_playerX < m_defaultX)
		{
			m_playerX++;
		}
		else if (m_playerX > m_defaultX)
		{
			m_playerX--;
		}
	}


	m_playerY = m_playerUnderY - m_playerSize;
}



/// ---------------------------------------------------------------------------------------
void Character::HitGarbageProcess()
{
	// ������Q��ID�łȂ��A��Q���ɓ������Ă��āA�������ł͂Ȃ��A�ʏ펞�ŁA�_���[�W���łȂ��A�񕜒��łȂ�������
	if (m_preHitGarbageID != m_hitGarbageID && m_isHitGarbage && !m_isNowSpeedUp && m_nowState == ESTATE::normal && !m_isDamageHit && !m_nowHeal)
	{
		m_preHitGarbageID = m_hitGarbageID;

		m_isHitGarbage = false;


		// ��Q���ɂ�菈����
		switch (m_hitGarbageObjectID)
		{
		case EHitGarbageID::doro:

			SoundProcess::Play(SoundProcess::E_SE::debuff);
			m_isDamageHit = true;
			m_smallSpeed += m_damageSmallValue;
			m_nowState = ESTATE::doroDamageHit;

			break;

		case EHitGarbageID::mizutamari:

			SoundProcess::Play(SoundProcess::E_SE::slip);
			m_isDamageHit = true;
			m_smallSpeed += m_damageSmallValue;
			m_preDamageMAXSpeed = m_nowSpeed * 0.7f;
			m_nowState = ESTATE::damageHit;

			break;

		case EHitGarbageID::sekiyu:

			SoundProcess::Play(SoundProcess::E_SE::catchTouyu);
			m_nowHeal = true;
			m_nowState = ESTATE::heal;

			break;

		default:
			break;
		}
	}


	// �_���[�W���󂯂Ă�����
	if (m_isDamageHit)
	{
		// �_���[�W�J�E���g���ő�ɂȂ��Ă��āA�����Ă��Ȃ�������
		if (++m_damageCount > m_damageMaxCount && m_isGroundFlag)
		{
			m_damageCount = 0;
			m_isDamageHit = false;
			m_nowState = ESTATE::normal;
		}
	}


	// �񕜂��Ă�����
	if (m_nowHeal)
	{
		// �傫��������
		if ((m_smallSpeed -= 0.01f) < 0.0f) m_smallSpeed = 0.0f;

		// �_���[�W�J�E���g���ő�ɂȂ��Ă��āA�����Ă��Ȃ�������
		if (++m_healCount > m_healMaxCount && m_isGroundFlag)
		{
			m_healCount = 0;
			m_nowHeal = false;
			m_nowState = ESTATE::normal;
		}
	}
}



/// ---------------------------------------------------------------------------------------
void Character::SpeedProcess()
{
	// ��������
	if (m_nowState == ESTATE::speedUp)
	{
		m_nowSpeed += m_addSpeed;
	}
	// �ő������
	else if (m_nowState == ESTATE::speedMAX) {}
	// �ʏ펞
	else if(m_nowState == ESTATE::speedDown)
	{
		if (m_nowSpeed > m_playerMaxSpeed + 0.5f)
		{
			m_nowSpeed -= m_addSpeed;
		}
	}
	// �ʏ펞
	else if(m_nowState == ESTATE::normal)
	{
		// �ő������菬����������
		if (m_nowSpeed < m_playerMaxSpeed - 0.5f)
		{
			m_nowSpeed += m_addSpeed;
		}
		// �ő�������傫��������
		else if (m_nowSpeed > m_playerMaxSpeed + 0.5f)
		{
			m_nowSpeed -= m_addSpeed;
		}
		// ���������_�I�ɊԂɂ�����
		else
		{
			// �����ɂ�����
			if (m_nowSpeed != m_playerMaxSpeed)
			{
				m_nowSpeed = m_playerMaxSpeed;
			}
		}
	}
	// �_���[�W��
	else if (m_nowState == ESTATE::damageHit)
	{
		if (m_nowSpeed > m_preDamageMAXSpeed)
		{
			m_nowSpeed += m_damageDownSpeed;
		}
	}


	if (m_nowSpeed <= 0.0f)
	{
		m_nowSpeed = 0.0f;
	}
}



/// ---------------------------------------------------------------------------------------
void Character::SpeedUpProcess()
{
	// �����L�[��������A�����`���[�W������Ă��āA�ʏ펞��������
	if (PadData::GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, 0) == 1 && m_speedUpChargeCount == m_speedUpChargeMax && m_nowState == ESTATE::normal)
	{
		SoundProcess::Play(SoundProcess::E_SE::speedUp);
		m_isNowSpeedUp = true;
		m_nowState = ESTATE::speedUp;
		m_playerDrawAnimCount = m_runFirstPlayerAnim;
	}


	// ��������������
	if (m_nowState == ESTATE::speedUp)
	{
		m_playerDrawAnimCount = m_runFirstPlayerAnim;

		m_speedUpCount += 0.1f;


		// �����J�E���g������Ă��Ȃ�������
		if (m_speedUpCount < m_speedUpCountTime)
		{
			m_addSpeed += std::sinf(M_PI * m_speedUpCount) * 1.5f;
		}
		// �����J���g�����܂�����
		else
		{
			m_nowState = ESTATE::speedMAX;
		}
	}
	// �ő��������������
	else if (m_nowState == ESTATE::speedMAX)
	{
		// �����ő咆�J�E���g����������ȏゾ������(�y�����ɖ߂��Ă��钆
		if (++m_speedMaxWaitCount > m_speedMaxWaitMaxCount)
		{
			m_nowState = ESTATE::speedDown;
			m_isNowSpeedUp = false;
		}
	}
	// �������̌�������������
	else if (m_nowState == ESTATE::speedDown)
	{
		if (m_speedMaxWaitCount != 0) m_speedMaxWaitCount = 0;

		m_speedUpCount -= 0.1f;

		// ��������߂�
		if (m_speedUpCount > 0.0f)
		{
			m_addSpeed -= std::sinf(M_PI * m_speedUpCount) * 1.5f;
		}
		// ��������߂�����
		else
		{
			m_nowState = ESTATE::normal;
		}
	}


	// ����������
	if (m_isNowSpeedUp)
	{
		if (m_speedUpChargeCount != 0) m_speedUpChargeCount = 0;
	}
	// �������Ă��Ȃ�������
	else
	{
		if (m_speedUpChargeCount < m_speedUpChargeMax) m_speedUpChargeCount++;
	}
}



/// ---------------------------------------------------------------------------------------
void Character::PlayerJump()
{
	// �n��ł��󒆂ł��_���[�W���󂯂Ă��Ȃ�������
	if (!m_isDamageHit && !m_isFlyDamageHit)
	{
		// �n�ʂɐG��ĂȂ�(�����Ă�
		if (!m_isGroundFlag)
		{
			m_gravityPower += m_jumpGravityEnergy;
			m_playerUnderY += m_gravityPower;

			// �n�ʂɖ��܂�����
			if (m_playerUnderY > m_mostMaxY)
			{
				m_playerUnderY = m_mostMaxY;
				m_gravityPower = 0;
				m_jumpPower = m_jumpMinPower;
				m_isGroundFlag = true;
				m_isJumpFlag = false;
			}
		}

		// �W�����v�{�^�������Ă��āA����������Ȃ�������
		if (m_isGroundFlag && PadData::GetButton(XINPUT_BUTTON_A, 0) == 1 && !m_isNowSpeedUp)
		{
			SoundProcess::Play(SoundProcess::E_SE::jump);
			m_isJumpFlag = true;
			m_isLongJump = true;
			m_isGroundFlag = false;
			m_jumpPower = m_jumpMinPower;
			m_playerDrawAnimCount = m_jumpFirstPlayerAnim;
		}

		// �W�����v���삵�Ă�����
		if (m_isJumpFlag)
		{
			// �W�����v�{�^���𗣂�����
			if (PadData::GetButton(XINPUT_BUTTON_A, 0) == -1)
			{
				m_isLongJump = false;
			}


			// �W�����v�{�^���𒷉������Ă��āA�W�����v�̏���܂ōs���Ă��Ȃ�������
			if (m_isLongJump && PadData::GetButton(XINPUT_BUTTON_A, 0) > 1 && m_jumpPower <= m_jumpMaxPower)
			{
				m_jumpPower += m_jumpAddPower;
			}


			// �グ��
			m_playerUnderY -= m_jumpPower;
		}
	}
	// �n��܂��͋󒆂Ń_���[�W���󂯂���
	else
	{
		// �n�ʂɐG��ĂȂ�(�����Ă�
		if (!m_isGroundFlag)
		{
			if (!m_isFlyDamageHit) m_isFlyDamageHit = true;
			m_playerUnderY += 16;

			// �n�ʂɖ��܂�����
			if (m_playerUnderY > m_mostMaxY)
			{
				m_isFlyDamageHit = false;
				m_playerUnderY = m_mostMaxY;
				m_gravityPower = 0;
				m_jumpPower = m_jumpMinPower;
				m_isGroundFlag = true;
				m_isJumpFlag = false;
			}
		}
	}
}



/// ---------------------------------------------------------------------------------------
Character::Character()
{
	/// �摜------------------------------------------------
	ZeroMemory(mD_playerArray, sizeof(mD_playerArray));
	ZeroMemory(mD_playerDirtArray, sizeof(mD_playerDirtArray));
	ZeroMemory(mD_playerWaterArray, sizeof(mD_playerWaterArray));
	ZeroMemory(mD_playerSpeedArray, sizeof(mD_playerSpeedArray));
	int dirtDrawHandle = LoadGraph("media\\grad\\Doro.jpg");
	int waterDrawHandle = LoadGraph("media\\grad\\mizutamari.jpg");
	for (int i = 0; i != m_playerDrawNum; ++i)
	{
		std::string str = "media\\anim_blink\\" + std::to_string(i) + ".png";
		mD_playerArray[i] = LoadGraph(str.c_str());
		mD_playerDirtArray[i] = LoadGraph(str.c_str());
		GraphFilter(mD_playerDirtArray[i], DX_GRAPH_FILTER_GRADIENT_MAP, dirtDrawHandle, FALSE);
		mD_playerWaterArray[i] = LoadGraph(str.c_str());
		GraphFilter(mD_playerWaterArray[i], DX_GRAPH_FILTER_GRADIENT_MAP, waterDrawHandle, FALSE);
		mD_playerSpeedArray[i] = LoadGraph(str.c_str());
		GraphFilter(mD_playerSpeedArray[i], DX_GRAPH_FILTER_LEVEL, 60, 210, 180, 120, 255);
	}
	DeleteGraph(dirtDrawHandle);
	DeleteGraph(waterDrawHandle);

	mD_speedUpDescription = LoadGraph("media\\RBspeedUp.png");

	mD_jumpDescription = LoadGraph("media\\Ajump.png");

	for (int i = 0; i != 10; ++i)
	{
		std::string str = "media\\num\\";
		str.append(std::to_string(i));
		str.append(".png");
		mD_speedNumber[i] = LoadGraph(str.c_str());
	}
	mD_speedComma = LoadGraph("media\\num\\comma.png");


	/// �摜�̏����n----------------------------------------
	m_playerDrawAnimCount = 0;


	/// ���W�̏����n----------------------------------------
	m_playerX = m_defaultX;
	m_playerY = m_playerUnderY - m_playerSize;
	m_prePlayerX = m_playerX;
	m_prePlayerY = m_playerY;

	m_nowState = ESTATE::normal;


	/// ���R�k�������n-----------------------------------------
	m_smallCount = 0;

	m_smallSpeed = 0;


	/// �_���[�W�����n------------------------------------------
	m_damageCount = 0;
	m_isDamageHit = false;

	m_preDamageMAXSpeed = 0.0f;


	/// ��Q�������n-------------------------------------------
	m_isHitGarbage = false;
	m_hitGarbageID = -1;
	m_preHitGarbageID = m_hitGarbageID;
	m_hitGarbageObjectID = EHitGarbageID::none;


	/// �񕜏����n--------------------------------------------
	m_healCount = 0;
	m_nowHeal = false;


	/// �X�s�[�h�����n-----------------------------------------
	m_nowSpeed = 70.0f;

	m_nowSpeedThirdDigit = 0;
	m_nowSpeedSecondDigit = 0;
	m_nowSpeedFirstDigit = 0;
	m_nowSpeedDecimalPoint = 0;


	/// �X�s�[�h�̉��������n------------------------------------
	m_isNowSpeedUp = false;

	m_speedUpChargeCount = 0;

	m_addSpeed = 1.0f;
	m_speedUpCount = 0;
	m_speedMaxWaitCount = 0;


	/// �W�����v�����n------------------------------------------
	m_playerUnderY = m_mostMaxY;

	m_isGroundFlag = true;
	m_isJumpFlag = false;
	m_isLongJump = false;

	m_jumpPower = m_jumpMinPower;
	m_gravityPower = 0;

	m_isFlyDamageHit = false;

}



/// ---------------------------------------------------------------------------------------
Character::~Character()
{
	if (mD_jumpDescription != -1) DeleteGraph(mD_jumpDescription);
	if (mD_speedUpDescription != -1) DeleteGraph(mD_speedUpDescription);
	if (mD_speedComma != -1) DeleteGraph(mD_speedComma);
	for (int i = 0; i != 10; ++i)
	{
		if (mD_speedNumber[i] != -1) DeleteGraph(mD_speedNumber[i]);
	}
	for (int i = 0; i != m_playerDrawNum; ++i)
	{
		if (mD_playerArray[i] != -1) DeleteGraph(mD_playerArray[i]);
		if (mD_playerDirtArray[i] != -1) DeleteGraph(mD_playerDirtArray[i]);
		if (mD_playerWaterArray[i] != -1) DeleteGraph(mD_playerWaterArray[i]);
		if (mD_playerSpeedArray[i] != -1) DeleteGraph(mD_playerSpeedArray[i]);
	}
}



/// ---------------------------------------------------------------------------------------
void Character::Draw()
{
	/// ���x--------------------------------------------------------------------
	if (m_nowSpeedThirdDigit != 0)
	{
		DrawGraph(199, 131, mD_speedNumber[m_nowSpeedThirdDigit], true);
		DrawGraph(199 + 121, 131, mD_speedNumber[m_nowSpeedSecondDigit], true);
		DrawGraph(199 + 242, 131, mD_speedNumber[m_nowSpeedFirstDigit], true);
		DrawGraph(199 + 363, 131 + 114, mD_speedComma, true);
		DrawGraph(199 + 378, 131, mD_speedNumber[m_nowSpeedDecimalPoint], true);
	}
	else if (m_nowSpeedSecondDigit != 0)
	{
		DrawGraph(199, 131, mD_speedNumber[m_nowSpeedSecondDigit], true);
		DrawGraph(199 + 121, 131, mD_speedNumber[m_nowSpeedFirstDigit], true);
		DrawGraph(199 + 242, 131 + 114, mD_speedComma, true);
		DrawGraph(199 + 257, 131, mD_speedNumber[m_nowSpeedDecimalPoint], true);
	}
	else if (m_nowSpeedFirstDigit != 0)
	{
		DrawGraph(199, 131, mD_speedNumber[m_nowSpeedFirstDigit], true);
		DrawGraph(199 + 121, 131 + 114, mD_speedComma, true);
		DrawGraph(199 + 136, 131, mD_speedNumber[m_nowSpeedDecimalPoint], true);
	}
	else
	{
		DrawGraph(199, 131, mD_speedNumber[0], true);
		DrawGraph(199 + 121, 131 + 114, mD_speedComma, true);
		DrawGraph(199 + 136, 131, mD_speedNumber[m_nowSpeedDecimalPoint], true);
	}


	/// �v���C���[---------------------------------------------------------------
	if (m_nowState == ESTATE::damageHit)
	{
		if (m_damageCount % 5 != 0)
		{
			DrawRotaGraph(m_playerX, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
				, 1.0 - static_cast<double>(m_smallSpeed), 0, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);

			int speedGraph = DerivationGraph(0, 0, static_cast<int>(192 * m_speedUpChargeCount / 420), 192, mD_playerSpeedArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)]);
			DrawRotaGraph(
				m_playerX - static_cast<int>((96 - (96 * m_speedUpChargeCount / 420)) * (1.0 - static_cast<double>(m_smallSpeed)))
				, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
				, 1.0 - static_cast<double>(m_smallSpeed), 0, speedGraph, true);

			int diviGraph = DerivationGraph(0, static_cast<int>(6.4 * m_damageCount), 192, 192 - static_cast<int>(6.4 * m_damageCount), mD_playerWaterArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)]);
			DrawRotaGraph(m_playerX
				, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed) + static_cast<int>((3.2 * m_damageCount) * (1.0 - static_cast<double>(m_smallSpeed)))
				, 1.0 - static_cast<double>(m_smallSpeed), 0, diviGraph, true);
		}
	}
	else if (m_nowState == ESTATE::doroDamageHit)
	{
		if (m_damageCount % 5 != 0)
		{
			DrawRotaGraph(m_playerX, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
				, 1.0 - static_cast<double>(m_smallSpeed), 0, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);

			int speedGraph = DerivationGraph(0, 0, static_cast<int>(192 * m_speedUpChargeCount / 420), 192, mD_playerSpeedArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)]);
			DrawRotaGraph(
				m_playerX - static_cast<int>((96 - (96 * m_speedUpChargeCount / 420)) * (1.0 - static_cast<double>(m_smallSpeed)))
				, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
				, 1.0 - static_cast<double>(m_smallSpeed), 0, speedGraph, true);

			int diviGraph = DerivationGraph(0, static_cast<int>(6.4 * m_damageCount), 192, 192 - static_cast<int>(6.4 * m_damageCount), mD_playerDirtArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)]);
			DrawRotaGraph(m_playerX
				, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed) + static_cast<int>((3.2 * m_damageCount) * (1.0 - static_cast<double>(m_smallSpeed)))
				, 1.0 - static_cast<double>(m_smallSpeed), 0, diviGraph, true);
		}
	}
	else
	{
		DrawRotaGraph(m_playerX, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
			, 1.0 - static_cast<double>(m_smallSpeed), 0, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);

		int speedGraph = DerivationGraph(0, 0, static_cast<int>(192 * m_speedUpChargeCount / 420), 192, mD_playerSpeedArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)]);
		DrawRotaGraph(
			m_playerX - static_cast<int>((96 - (96 * m_speedUpChargeCount / 420)) * (1.0 - static_cast<double>(m_smallSpeed)))
			, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
			, 1.0 - static_cast<double>(m_smallSpeed), 0, speedGraph, true);
	}


	/// UI-------------------------------------------------------------
	DrawGraph(300, 1080 - 128, mD_jumpDescription, true);
	if (m_speedUpChargeCount == m_speedUpChargeMax)
	{
		DrawGraph(300 + 360, 1080 - 128, mD_speedUpDescription, true);
	}
}



/// ---------------------------------------------------------------------------------------
void Character::BlurDraw()
{
	DrawRotaGraph(m_playerX, m_playerY + static_cast<int>(m_playerSize * 0.5) + static_cast<int>(m_playerSize * 0.5 * m_smallSpeed)
		, 1.0 - static_cast<double>(m_smallSpeed), 0, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);
}



/// ---------------------------------------------------------------------------------------
void Character::Process()
{
	/// ���W------------------------------------------
	m_prePlayerX = m_playerX;
	m_prePlayerY = m_playerY;


	/// �A�j���[�V�����R�}----------------------------
	if (++m_playerDrawAnimCount >= m_playerDrawAnimSpeed * m_playerDrawNum) m_playerDrawAnimCount = 0;


	/// �k��------------------------------------------
	if (++m_smallCount > m_smallCountTime)
	{
		m_smallSpeed += m_smallValue;
		m_smallCount = 0;
	}


	SpeedProcess();

	SpeedUpProcess();

	PlayerJump();

	HitGarbageProcess();

	PositionProcess();


	/// ���x��`�悷�邽�߂�-----------------------------
	int temp = static_cast<int>(m_nowSpeed * 10);
	if (temp > 1000)
	{
		m_nowSpeedThirdDigit = temp / 1000;
		m_nowSpeedSecondDigit = temp / 100 - (m_nowSpeedThirdDigit * 10);
		m_nowSpeedFirstDigit = temp / 10 - (m_nowSpeedThirdDigit * 100) - (m_nowSpeedSecondDigit * 10);
		m_nowSpeedDecimalPoint = temp - (m_nowSpeedThirdDigit * 1000) - (m_nowSpeedSecondDigit * 100) - (m_nowSpeedFirstDigit * 10);
	}
	else if (temp > 100)
	{
		m_nowSpeedThirdDigit = 0;
		m_nowSpeedSecondDigit = temp / 100;
		m_nowSpeedFirstDigit = temp / 10 - (m_nowSpeedSecondDigit * 10);
		m_nowSpeedDecimalPoint = temp - (m_nowSpeedSecondDigit * 100) - (m_nowSpeedFirstDigit * 10);
	}
	else if (temp > 10)
	{
		m_nowSpeedThirdDigit = 0;
		m_nowSpeedSecondDigit = 0;
		m_nowSpeedFirstDigit = temp / 10;
		m_nowSpeedDecimalPoint = temp - (m_nowSpeedFirstDigit * 10);
	}
	else
	{
		m_nowSpeedThirdDigit = 0;
		m_nowSpeedSecondDigit = 0;
		m_nowSpeedFirstDigit = 0;
		m_nowSpeedDecimalPoint = temp;
	}
}



/// ---------------------------------------------------------------------------------------
void Character::FirstDraw(int t_x, int t_y, bool t_turn)
{
	if (t_turn)
	{
		DrawTurnGraph(t_x, t_y, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);
	}
	else
	{
		DrawGraph(t_x, t_y, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);
	}
}



/// ---------------------------------------------------------------------------------------
void Character::FirstProcess()
{
	if (++m_playerDrawAnimCount >= m_playerDrawAnimSpeed * m_playerDrawNum) m_playerDrawAnimCount = 0;
}



/// ---------------------------------------------------------------------------------------
const bool Character::GetIsSpeedUp() const
{
	if (m_nowState == ESTATE::speedUp || m_nowState == ESTATE::speedMAX || m_nowState == ESTATE::speedDown)
	{
		return true;
	}
	else
	{
		return false;
	}
}



/// ---------------------------------------------------------------------------------------
const float Character::GetSpeed() const
{
	return m_nowSpeed;
}



/// ---------------------------------------------------------------------------------------
const float Character::GetDefaultMAXSpeed() const
{
	return m_playerMaxSpeed;
}



/// ---------------------------------------------------------------------------------------
void Character::HitGarbageNow(const int t_garbageID, const EHitGarbageID t_garbageObjectID)
{
	m_hitGarbageObjectID = t_garbageObjectID;
	m_isHitGarbage = true;
	m_hitGarbageID = t_garbageID;
}



/// ---------------------------------------------------------------------------------------
const int Character::GetAreaX() const
{
	return m_playerX;
}



/// ---------------------------------------------------------------------------------------
const int Character::GetAreaY() const
{
	return m_playerY;
}



/// ---------------------------------------------------------------------------------------
const int Character::GetSize() const
{
	return static_cast<int>(192 * (1.0 - static_cast<double>(m_smallSpeed)));
}



/// ---------------------------------------------------------------------------------------
const bool Character::GetNowDamage() const
{
	return m_isDamageHit;
}



/// ---------------------------------------------------------------------------------------
const bool Character::GetNowHeal() const
{
	return m_nowHeal;
}



/// ---------------------------------------------------------------------------------------
const float Character::GetSmallSpeed() const
{
	return m_smallSpeed;
}
