#include "Manager.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "InputController.hpp"
#include "SoundProcess.hpp"


/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = 1920;
	int winHeight = 1080;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText("����I�Ό�����I");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(0, 0, 0);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth, winHeight);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX
	SetWindowIconID(333);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\�����\���ɂ���

	SoundProcess::Init();

	KeyData::UpDate();

	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 20000, -20000, 20000, -20000, 20000, -20000);
	PadData::UpDate();
	
	Manager m_manager = Manager();

	
	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && !PadData::IsCheckEnd() && !m_manager.GetEnd())
	{
		KeyData::UpDate();
		PadData::UpDate();


		m_manager.Update();
	}

	// �폜
	m_manager.~Manager();
	SoundProcess::Release();
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}