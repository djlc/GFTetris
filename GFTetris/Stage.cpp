#include "Stage.h"
#include "Block.h"
#include "Mino.h"
#include "MinoGenerator.h"
#include "DxLib.h"

Stage::Stage(const int _x, const int _y) : x(_x), y(_y), field(STAGE_WIDTH, STAGE_HEIGHT) {
	
	initStage();
	
	score = 0;
	line = 0;
	level = 1;
	
	mino = MinoGenerator::getRandomMino();
	nextMino = MinoGenerator::getRandomMino();

	keyEnable = true;
	gameState = STATE_MINO_MOVING;
	next = STATE_MINO_MOVING;

	elist[0] = 0;	// SINGLE
	elist[1] = 0;	// DOUBLE
	elist[2] = 0;	// TRIPLE
	elist[3] = 0;	// TETRIS
	elist[4] = 0;	// PENTRIS
}

Stage::~Stage() {
}

void Stage::initStage() {
	for (int i = 0; i < STAGE_WIDTH; i++) {
		for (int j = 0; j < STAGE_HEIGHT; j++) {
			field(i, j) = (1 <= i && i <= STAGE_WIDTH - 2 && j != STAGE_HEIGHT - 1) ? Block() : Block(Block::BLOCK_WALL, Block::COLOR_WALL);
		}
	}
}

void Stage::draw() {
	// ステージ
	for (int i = 0; i < STAGE_WIDTH; i++) {
		for (int j = 2; j < STAGE_HEIGHT; j++) {
			field(i, j).draw(x + i * Block::BLOCK_SIZE, y + j * Block::BLOCK_SIZE);
		}
	}

	// 影
	mino->drawShadow(x + mino->x * Block::BLOCK_SIZE, y + mino->sy * Block::BLOCK_SIZE);
	// ミノ
	mino->draw(x + mino->getPosX(), y + mino->getPosY() );

	DrawFormatString(0, 20, 0x00ffffff, "%d", mino->lastCnt);

	// NEXT
	DrawString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 2, "NEXT", 0x00ffffff);
	DrawBox(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 3, x + Block::BLOCK_SIZE * 20, y + Block::BLOCK_SIZE * 9, 0x00ffffff, false);
	nextMino->draw(x + Block::BLOCK_SIZE * 15, y + Block::BLOCK_SIZE * 4);

	// SCORE
	DrawFormatString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 15, 0x00ffffff, "LEVEL : %d", level);
	DrawFormatString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 17, 0x00ffffff, "SCORE : %d", score);
	DrawFormatString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 19, 0x00ffffff, "LINE  : %d", line);

	// 内訳
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 15, 0x00ffffff, "SINGLE  : %d", elist[0]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 17, 0x00ffffff, "DOUBLE  : %d", elist[1]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 19, 0x00ffffff, "TRIPLE  : %d", elist[2]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 21, 0x00ffffff, "TETRIS  : %d", elist[3]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 23, 0x00ffffff, "PENTRIS : %d", elist[4]);

	// GameOver
	if (isGameOver()) {
		DrawString(100, 0, "< GAME OVER >", Block::Color::COLOR_YELLOW);
	}
}

// -1 : 反時計,  +1 : 時計
void Stage::rotate(int direction) {
	// データのコピー
	Array<Block> temp(mino->field.getHeight(), mino->field.getWidth());
	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			temp(i, j).block = mino->field(i, j).block;
			temp(i, j).color = mino->field(i, j).color;
		}
	}

	if (direction == 1) {
		for (int i = 0; i < mino->field.getHeight(); i++) {
			for (int j = 0; j < mino->field.getHeight(); j++) {
				mino->field(i, j).block = temp(j, mino->field.getHeight() - i - 1).block;
				mino->field(i, j).color = temp(j, mino->field.getHeight() - i - 1).color;
			}
		}
	}

	if (direction == -1) {
		for (int i = 0; i < mino->field.getHeight(); i++) {
			for (int j = 0; j < mino->field.getHeight(); j++) {
				mino->field(i, j).block = temp(mino->field.getHeight() - j - 1, i).block;
				mino->field(i, j).color = temp(mino->field.getHeight() - j - 1, i).color;
			}
		}
	}
}

// -1 : x--,  +1 : x++
void Stage::move(int direction) {
	if (direction == -1) {
		mino->x--;
	}
	if (direction == 1) {
		mino->x++;
	}
}

void Stage::checkRotateKey() {
	static bool oldstat = false, newstat = false;
	if (!oldstat) {

		if (CheckHitKey(KEY_INPUT_Z) && rotateJudge(-1)) {
			rotate(-1);
			newstat = true;
		}

		if (CheckHitKey(KEY_INPUT_X) && rotateJudge(1)) {
			rotate(1);
			newstat = true;
		}

	}
	else {

		if (CheckHitKey(KEY_INPUT_Z) == 0 && CheckHitKey(KEY_INPUT_X) == 0) {
			newstat = false;
		}

	}
	oldstat = newstat;
}

bool Stage::checkDownKey() {
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		if (downJudge() && mino->cnt % 2) down();
		if (!downJudge()) mino->lastCnt -= 5;
		return true;
	}
	else {
		return false;
	}
}

void Stage::checkMoveKey() {
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (mino->cnt % 4 == 0 && moveJudge(-1)) move(-1);
	}

	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (mino->cnt % 4 == 0 && moveJudge(1)) move(1);
	}
}

// 現在位置に重なったミノが1つでもあればfalseを返す
bool Stage::Judge() {
	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO &&
				(field(mino->x + i, mino->y + j).block == Block::BLOCK_WALL ||
					field(mino->x + i, mino->y + j).block == Block::BLOCK_MINO)) return false;
		}
	}
	return true;
}

// 1ブロック下の部分に重なるミノが1つでもあればfalseを返す
bool Stage::downJudge() {
	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO &&
				(field(mino->x + i, mino->y + j + 1).block == Block::BLOCK_WALL ||
					field(mino->x + i, mino->y + j + 1).block == Block::BLOCK_MINO)) return false;
		}
	}
	return true;
}

// 移動する場所に重なるミノが1つでもあればfalseを返す
bool Stage::moveJudge(int direction) {
	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO &&
				(field(mino->x + i + direction, mino->y + j).block == Block::BLOCK_WALL ||
					field(mino->x + i + direction, mino->y + j).block == Block::BLOCK_MINO)) return false;
		}
	}
	return true;
}

// 回転移動する場所に重なるミノが1つでもあればfalseを返す
bool Stage::rotateJudge(int direction) {
	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO) {
				if (direction == -1) {
					if (field(mino->x + j, mino->y + mino->field.getHeight() - i - 1).block == Block::BLOCK_WALL ||
						field(mino->x + j, mino->y + mino->field.getHeight() - i - 1).block == Block::BLOCK_MINO) {
						return false;
					}
				} else {
					if (field(mino->x + mino->field.getHeight() - j - 1, mino->y + i).block == Block::BLOCK_WALL ||
						field(mino->x + mino->field.getHeight() - j - 1, mino->y + i).block == Block::BLOCK_MINO) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

// ミノをステージに固定(登録)
void Stage::fix() {
	mino->lastCnt = 0;
	mino->isFixed = true;
	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block != Block::BLOCK_NONE && mino->field(i, j).color != Block::COLOR_NONE) {
				field(mino->x + i, mino->y + j).block = mino->field(i, j).block;
				field(mino->x + i, mino->y + j).color = mino->field(i, j).color;
			}
		}
	}
}

void Stage::createShadow() {
	mino->sy = 0;
	while (true) {
		for (int i = 0; i < mino->field.getHeight(); i++) {
			for (int j = 0; j < mino->field.getHeight(); j++) {
				if (mino->field(i, j).block == Block::BLOCK_MINO &&
					(field(mino->x + i, mino->sy + j + 1).block == Block::BLOCK_WALL ||
						field(mino->x + i, mino->sy + j + 1).block == Block::BLOCK_MINO)) {
					goto exit;
				}
			}
		}
		mino->sy++;
	}
exit:
	return;
}

bool Stage::isGameOver() {
	if (!Judge() && mino->x == 3 && mino->y == 0) return true;
	return false;
}

void Stage::down() {
	mino->y++;
}

void Stage::eraseLine(int row) {
	for (int i = 1; i <= STAGE_WIDTH - 2; i++) {
		field(i, row).block = Block::BLOCK_NONE;
		field(i, row).color = Block::COLOR_NONE;
	}
	line++;
}

bool Stage::isFilledLine(int row) {
	for (int i = 1; i <= STAGE_WIDTH - 2; i++) {
		if (field(i, row).block != Block::BLOCK_MINO) {
			return false;
		}
	}
	return true;
}

void Stage::shiftField(int row) {
	for (int i = 1; i <= STAGE_WIDTH - 2; i++) {
		for (int j = row; j >= 1; j--) {
			field(i, j).block = field(i, j - 1).block;
			field(i, j).color = field(i, j - 1).color;
		}
	}
}

GameChild* Stage::update() {

	// Level
	level = line / 10 + 1;
	// スコア計算
	score = elist[0] * 40 + elist[1] * 100 + elist[2] * 300 + elist[3] * 1200 + elist[4] * 6000;

	// 描画
	draw();

	static int timer = 0;

	// 揃ったラインを探す
	static int list[5] = { 0,0,0,0,0 };
	static int localCnt = 0;
	
	switch (gameState) {

	case STATE_MINO_MOVING :
		// キー入力の監視
		if (keyEnable) {
			checkRotateKey();
			checkMoveKey();
			createShadow();
			mino->cnt++;
			if (checkDownKey() == false && downJudge() && (mino->cnt % (120 / level) == 0)) down();
		}
		
		// ブロックと下で接しているならカウンタ開始
		if (!downJudge()) {
			mino->lastCnt--;
		}
		else {
			mino->lastCnt = 50;
		}
		// 猶予カウンタが0になったら固定
		if (mino->lastCnt < 0) {
			gameState = STATE_WAITING;	timer = 1;
			next = STATE_MINO_FIX;
		}
		if (isGameOver()) gameState = STATE_GAMEOVER;
		break;

	case STATE_MINO_FIX:
		fix();
		// 消せるラインを探す
		for (int i = 0; i <= STAGE_HEIGHT - 2; i++) {
			if (isFilledLine(i)) {
				list[localCnt++] = i;
			}
		}
		gameState = STATE_ERASE_FLASH;	timer = 10;
		break;

	case STATE_ERASE_FLASH:
		if (timer == 0) {
			// 時間になったら次へ進む
			gameState = STATE_ERASE_LINE;
		}
		else {
			for (int i = 0; i < localCnt; i++) {
				DrawBox(x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE * list[i], x + Block::BLOCK_SIZE * 11, y + Block::BLOCK_SIZE * (list[i] + 1), 0x00ffffff, true);
			}
			timer--;
		}
		break;

	case STATE_ERASE_LINE:
		// ラインを消して詰める
		for (int i = 0; i < localCnt; i++) {
			eraseLine(list[i]);
			shiftField(list[i]);
		}
		if (localCnt >= 1) {
			elist[localCnt - 1]++;	// スコア追加
		}
		
		timer = 3;

		// 次のミノの準備
		for (int i = 0; i < 5; i++) list[i] = 0;
		localCnt = 0;
		mino = nextMino;
		nextMino = MinoGenerator::getRandomMino();
		gameState = STATE_WAITING;
		next = STATE_MINO_MOVING;
		break;

	case STATE_GAMEOVER:
		mino->visible = false;
		// ステージ
		for (int i = 0; i < STAGE_WIDTH; i++) {
			for (int j = 2; j < STAGE_HEIGHT; j++) {
				if (field(i, j).block == Block::BLOCK_MINO) {
					field(i, j).block = Block::BLOCK_WALL;
					field(i, j).color = Block::COLOR_WALL;
				}
			}
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			Stage(40, 40);
			gameState = STATE_MINO_MOVING;
			next = STATE_MINO_MOVING;
		}
		break;
	
	case STATE_WAITING:
		if (timer == 0) {
			// 時間になったら次へ進む
			gameState = next;
		} else {
			// 時間が来るまで待つ
			timer--;
		}
		break;
	}
	
	return this;
}