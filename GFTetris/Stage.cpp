#include "Stage.h"
#include "Block.h"
#include "Mino.h"
#include "MinoGenerator.h"
#include "GameResource.h"
#include "DxLib.h"

Stage::Stage(const int _x, const int _y, const int _startLevel)
	: x(_x), y(_y), startLevel(_startLevel), field(STAGE_WIDTH, STAGE_HEIGHT) {
	
	initStage();
}

Stage::~Stage() {
}

void Stage::initStage() {
	for (int i = 0; i < STAGE_WIDTH; i++) {
		for (int j = 0; j < STAGE_HEIGHT; j++) {
			field(i, j) = (1 <= i && i <= STAGE_WIDTH - 2 && j != STAGE_HEIGHT - 1) ? Block() : Block(Block::BLOCK_WALL, Block::COLOR_WALL);
		}
	}
	score = 0;
	line = 0;
	this->startLevel = startLevel;
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

void Stage::draw() {
	// �X�e�[�W
	for (int i = 0; i < STAGE_WIDTH; i++) {
		for (int j = 2; j < STAGE_HEIGHT; j++) {
			field(i, j).draw(x + i * Block::BLOCK_SIZE, y + j * Block::BLOCK_SIZE);
		}
	}

	// �e
	mino->drawShadow(x + mino->x * Block::BLOCK_SIZE, y + mino->sy * Block::BLOCK_SIZE);
	// �~�m
	mino->draw(x + mino->getPosX(), y + mino->getPosY() );

	// NEXT
	DrawString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 2, "NEXT", 0x00ffffff);
	DrawBox(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 3, x + Block::BLOCK_SIZE * 21, y + Block::BLOCK_SIZE * 10, 0x00ffffff, false);
	nextMino->draw(x + Block::BLOCK_SIZE * 15, y + Block::BLOCK_SIZE * 4);

	// SCORE
	DrawFormatString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 15, 0x00ffffff, "LEVEL : %d", level);
	DrawFormatString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 17, 0x00ffffff, "SCORE : %d", score);
	DrawFormatString(x + Block::BLOCK_SIZE * 14, y + Block::BLOCK_SIZE * 19, 0x00ffffff, "LINE  : %d", line);

	// ����
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 15, 0x00ffffff, "SINGLE  : %d", elist[0]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 17, 0x00ffffff, "DOUBLE  : %d", elist[1]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 19, 0x00ffffff, "TRIPLE  : %d", elist[2]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 21, 0x00ffffff, "TETRIS  : %d", elist[3]);
	DrawFormatString(x + Block::BLOCK_SIZE * 24, y + Block::BLOCK_SIZE * 23, 0x00ffffff, "PENTRIS : %d", elist[4]);

	// ������
	for (list<GameString*>::iterator it = string.begin(); it != string.end();) {
		(*it)->update();
		if ((*it)->isTimeElapsed()) {
			it = string.erase(it);
			continue;
		}
		it++;
	}

	// Debug
	//DrawFormatString(200, 0, 0x00ffffff, "Mino : (%.1f, %.1f), V : %.2f", mino->x, mino->y, (1.0 + (double)level) * 0.02);

	// GameOver
	if (isGameOver()) {
		DrawString(100, 0, "< GAME OVER >", Block::Color::COLOR_YELLOW);
	}
}

// -1 : �����v,  +1 : ���v
void Stage::rotate(int direction) {
	// �f�[�^�̃R�s�[
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
		if (downJudge()) {
			mino->down(0.3);
		}
		if (!downJudge()) mino->lastCnt -= 5;
		return true;
	} else {
		return false;
	}
}

bool Stage::checkDropKey() {
	if (CheckHitKey(KEY_INPUT_UP)) {
		return true;
	} else {
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

// ���݈ʒu�ɏd�Ȃ����~�m��1�ł������false��Ԃ�
bool Stage::Judge() {

	int intMinoY = floor(mino->y);

	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO &&
				(field(mino->x + i, intMinoY + j).block == Block::BLOCK_WALL ||
					field(mino->x + i, intMinoY + j).block == Block::BLOCK_MINO)) return false;
		}
	}
	return true;
}

// 1�u���b�N���̕����ɏd�Ȃ�~�m��1�ł������false��Ԃ�
bool Stage::downJudge() {

	int intMinoY = floor(mino->y);

	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO &&
				(field(mino->x + i, intMinoY + j + 1).block == Block::BLOCK_WALL ||
					field(mino->x + i, intMinoY + j + 1).block == Block::BLOCK_MINO)) {
				mino->y = intMinoY;
				return false;
			}
		}
	}
	return true;
}

// �ړ�����ꏊ�ɏd�Ȃ�~�m��1�ł������false��Ԃ�
bool Stage::moveJudge(int direction) {

	int intMinoY = ceil(mino->y);

	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO &&
				(field(mino->x + i + direction, intMinoY + j).block == Block::BLOCK_WALL ||
					field(mino->x + i + direction, intMinoY + j).block == Block::BLOCK_MINO)) return false;
		}
	}
	return true;
}

// ��]�ړ�����ꏊ�ɏd�Ȃ�~�m��1�ł������false��Ԃ�
bool Stage::rotateJudge(int direction) {

	int intMinoY = ceil(mino->y);

	for (int i = 0; i < mino->field.getHeight(); i++) {
		for (int j = 0; j < mino->field.getHeight(); j++) {
			if (mino->field(i, j).block == Block::BLOCK_MINO) {
				if (direction == -1) {
					if (field(mino->x + j, intMinoY + mino->field.getHeight() - i - 1).block == Block::BLOCK_WALL ||
						field(mino->x + j, intMinoY + mino->field.getHeight() - i - 1).block == Block::BLOCK_MINO) {
						return false;
					}
				} else {
					if (field(mino->x + mino->field.getHeight() - j - 1, intMinoY + i).block == Block::BLOCK_WALL ||
						field(mino->x + mino->field.getHeight() - j - 1, intMinoY + i).block == Block::BLOCK_MINO) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

// �~�m���X�e�[�W�ɌŒ�(�o�^)
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
	mino->sy = mino->y;
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
	// �������x�v�Z��
	double v = (1.0 + (double)level) * 0.01;
	mino->down(v);
}

void Stage::drop() {
	mino->y = mino->sy;
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
	level = startLevel + line / 10;
	// �X�R�A�v�Z
	score = elist[0] * 40 + elist[1] * 100 + elist[2] * 300 + elist[3] * 1200 + elist[4] * 6000;

	// �`��
	draw();

	static int timer = 0;

	// ���������C����T��
	static int list[5] = { 0,0,0,0,0 };
	static int localCnt = 0;
	
	switch (gameState) {

	case STATE_MINO_MOVING :
		// �L�[���͂̊Ď�
		if (keyEnable) {
			checkRotateKey();
			checkMoveKey();
			checkDownKey();
			createShadow();
			mino->cnt++;
			if (downJudge()) down();
			if (checkDropKey()) {
				PlaySoundMem(GameResource::SHandle[0], DX_PLAYTYPE_BACK);
				drop();
				mino->lastCnt = 0;
			}
		}
		
		// �u���b�N�Ɖ��Őڂ��Ă���Ȃ�J�E���^�J�n
		if (!downJudge()) {
			mino->lastCnt--;
		}
		else {
			mino->lastCnt = 30;
		}
		// �P�\�J�E���^��0�ɂȂ�����Œ�
		if (mino->lastCnt < 0) {
			gameState = STATE_WAITING;	timer = 1;
			next = STATE_MINO_FIX;
		}
		if (isGameOver()) {
			gameState = STATE_WAITING;	timer = 30;
			next = STATE_GAMEOVER;
		}
		break;

	case STATE_MINO_FIX:
		fix();
		// �����郉�C����T��
		for (int i = 0; i <= STAGE_HEIGHT - 2; i++) {
			if (isFilledLine(i)) {
				list[localCnt++] = i;
			}
		}
		gameState = STATE_ERASE_FLASH;	timer = 10;
		break;

	case STATE_ERASE_FLASH:
		if (timer == 0) {
			// ���ԂɂȂ����玟�֐i��
			gameState = STATE_ERASE_LINE;
		} else {
			for (int i = 0; i < localCnt; i++) {
				DrawBox(x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE * list[i], x + Block::BLOCK_SIZE * 11, y + Block::BLOCK_SIZE * (list[i] + 1), 0x00ffffff, true);
			}
			timer--;
		}
		break;

	case STATE_ERASE_LINE:
		// ���C���������ċl�߂�
		for (int i = 0; i < localCnt; i++) {
			eraseLine(list[i]);
			shiftField(list[i]);
			PlaySoundMem(GameResource::SHandle[1], DX_PLAYTYPE_BACK);
		}
		if (localCnt >= 1) {
			elist[localCnt - 1]++;	// �X�R�A�ǉ�
		}
		
		timer = 3;

		switch (localCnt) {
		case 0:

			break;
		case 1:
			string.push_back(new GameString("SINGLE", 0, 450, 500, 0, 255, 255, 255, -254, -254, -254, 120, 120));
			break;
		case 2:
			string.push_back(new GameString("DOUBLE", 0, 450, 500, 0, 255, 255, 255, -254, -254, -254, 120, 120));
			break;
		case 3:
			string.push_back(new GameString("TRIPLE", 0, 450, 500, 0, 255, 255, 255, -254, -254, -254, 120, 120));
			break;
		case 4:
			string.push_back(new GameString("TETRIS", 0, 450, 500, 0, 255, 255, 255, -254, -254, -254, 120, 120));
			break;
		case 5:
			string.push_back(new GameString("PENTRIS", 0, 450, 500, 0, 255, 255, 255, -254, -254, -254, 120, 120));
			break;
		}

		// ���̃~�m�̏���
		for (int i = 0; i < 5; i++) list[i] = 0;
		localCnt = 0;
		mino = nextMino;
		nextMino = MinoGenerator::getRandomMino();
		gameState = STATE_WAITING;
		next = STATE_MINO_MOVING;
		break;

	case STATE_GAMEOVER:
		// �X�e�[�W
		for (int j = 2; j < STAGE_HEIGHT; j++) {
			for (int i = 0; i < STAGE_WIDTH; i++) {
				if (field(i, j).block == Block::BLOCK_MINO) {
					field(i, j).block = Block::BLOCK_WALL;
					field(i, j).color = Block::COLOR_WALL;
				}
			}
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			initStage();
		}
		break;
	
	case STATE_WAITING:
		if (timer == 0) {
			// ���ԂɂȂ����玟�֐i��
			gameState = next;
		} else {
			// ���Ԃ�����܂ő҂�
			timer--;
		}
		break;
	}
	
	return this;
}