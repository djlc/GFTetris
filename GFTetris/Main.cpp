#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1) {
		return -1;
	}

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
	}

	DxLib_End();

	return 0;
}