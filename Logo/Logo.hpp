#pragma once




class Logo
{
private:
	/// �摜

	int m_teamLogo;		// ����̉摜
	int m_dxlibLogo;		// dxlib�̉摜


	/// �V�[���J�ڂɊւ���

	enum class ELOGONOW { dxlib, team };
	ELOGONOW m_nowLogoNumber;	// ���݂̃��S
	int m_logoTransTime;	// ���S�̑J�ڎ���

public:
	Logo();
	~Logo();


	// �`��
	void Draw();

	// �v���Z�X
	void Process();
};

