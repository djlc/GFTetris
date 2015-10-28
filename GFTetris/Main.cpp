#include "DxLib.h"
#include "Parent.h"
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstacne, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#ifndef _DEBUG
	SetOutApplicationLogValidFlag(false);
#endif

	// ウィンドウの初期化
	(strcmp(lpCmdLine, "-f") == 0) ? ChangeWindowMode(false) : ChangeWindowMode(true);
	SetGraphMode(640, 480, 16);
	SetWindowText("GF TETRIS");

	// DxLib 初期化処理
	if (DxLib_Init() == -1) {
		MessageBox(
			NULL,
			"初期化処理に失敗しました。DirectXがインストールされていない可能性があります。",
			"Init Error",
			MB_OK | MB_ICONERROR
			);
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 乱数初期化
	srand(time(0));

	// ゲームループ
	while (!ProcessMessage() && !ClearDrawScreen()) {

		// update
		Parent::getInstance()->update();

		// 裏画面から表画面に描画
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}