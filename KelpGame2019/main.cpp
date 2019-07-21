#include "InputKey.hpp"


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


	SetWindowText("KelpGame2019");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(0, 0, 0);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����
	SetEnableXAudioFlag(TRUE);					// XAudio���g�p����悤�ɂ���


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth, winHeight);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	// Effekseer������������B�����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(500) == -1)
	{
		DxLib_End();
		return -1;
	}


	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);


	Effekseer_Set2DSetting(1920, 1080);	// 2D�G�t�F�N�g�̍ő�͈͂�ݒ�


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\�����\���ɂ���

	
	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		break;
	}


	// �폜
	Effkseer_End();		// Effekseer���I������
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}