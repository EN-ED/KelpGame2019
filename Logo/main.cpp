#include "Logo.hpp"


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


	SetWindowText("KelpGame2019_Logo");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(0, 0, 0);			// �w�i�F�����ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth, winHeight);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\�����\���ɂ���


	Logo m_logo = Logo();


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		m_logo.Process();
		m_logo.Draw();
	}

	// �폜
	m_logo.~Logo();
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}