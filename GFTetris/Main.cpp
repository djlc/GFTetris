#include "DxLib.h"
#include "Parent.h"
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstacne, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#ifndef _DEBUG
	SetOutApplicationLogValidFlag(false);
#endif

	// �E�B���h�E�̏�����
	(strcmp(lpCmdLine, "-f") == 0) ? ChangeWindowMode(false) : ChangeWindowMode(true);
	SetGraphMode(640, 480, 16);
	SetWindowText("GF TETRIS");

	// DxLib ����������
	if (DxLib_Init() == -1) {
		MessageBox(
			NULL,
			"�����������Ɏ��s���܂����BDirectX���C���X�g�[������Ă��Ȃ��\��������܂��B",
			"Init Error",
			MB_OK | MB_ICONERROR
			);
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// ����������
	srand(time(0));

	// �Q�[�����[�v
	while (!ProcessMessage() && !ClearDrawScreen()) {

		// update
		Parent::getInstance()->update();

		// ����ʂ���\��ʂɕ`��
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}