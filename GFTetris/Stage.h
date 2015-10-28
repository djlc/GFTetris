#pragma once
#include "Array.h"
#include "GameChild.h"

class Block;
class Mino;

class Stage : public GameChild {

	// 定数
	enum {
		STAGE_HEIGHT = 24,
		STAGE_WIDTH = 12
	};

	// ステート
	enum state {
		STATE_MINO_MOVING,
		STATE_MINO_FIX,
		STATE_ERASE_FLASH,
		STATE_ERASE_LINE,
		STATE_GAMEOVER,
		STATE_WAITING
	};
	state gameState, next;

	// ステージ
	Array<Block> field;

	// ミノ
	Mino* mino;

	// NEXT
	Mino* nextMino;

	// Level
	int level;

	// Score
	int score;

	// ライン数
	int line;

	// 消去の内訳
	int elist[5];

	// 原点
	const int x, y;

	// ステージ初期化
	void initStage();

	// 描画
	void draw();

	// row行目のライン消去
	void eraseLine(int row);

	// row行目が埋まっているかチェック
	bool isFilledLine(int row);

	// 1からrow行目を1段下にシフトする
	void shiftField(int row);

	void down(); // 自動落下
	void rotate(int direction);
	void move(int direction);
	void checkRotateKey();
	bool checkDownKey();
	void checkMoveKey();
	bool Judge();
	bool downJudge();
	bool moveJudge(int direction);
	bool rotateJudge(int direction);
	void fix();

	// 影を作る
	void createShadow();

	// 最初からミノが重なったらゲームオーバー
	bool isGameOver();

	// キー入力を有効にする
	bool keyEnable;

public:

	Stage(const int x, const int y);
	~Stage();

	// 実行メソッド
	GameChild* update();
};

