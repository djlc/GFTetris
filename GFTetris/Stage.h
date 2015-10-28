#pragma once
#include "Array.h"
#include "GameChild.h"

class Block;
class Mino;

class Stage : public GameChild {

	// �萔
	enum {
		STAGE_HEIGHT = 24,
		STAGE_WIDTH = 12
	};

	// �X�e�[�g
	enum state {
		STATE_MINO_MOVING,
		STATE_MINO_FIX,
		STATE_ERASE_FLASH,
		STATE_ERASE_LINE,
		STATE_GAMEOVER,
		STATE_WAITING
	};
	state gameState, next;

	// �X�e�[�W
	Array<Block> field;

	// �~�m
	Mino* mino;

	// NEXT
	Mino* nextMino;

	// Level
	int level;

	// Score
	int score;

	// ���C����
	int line;

	// �����̓���
	int elist[5];

	// ���_
	const int x, y;

	// �X�e�[�W������
	void initStage();

	// �`��
	void draw();

	// row�s�ڂ̃��C������
	void eraseLine(int row);

	// row�s�ڂ����܂��Ă��邩�`�F�b�N
	bool isFilledLine(int row);

	// 1����row�s�ڂ�1�i���ɃV�t�g����
	void shiftField(int row);

	void down(); // ��������
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

	// �e�����
	void createShadow();

	// �ŏ�����~�m���d�Ȃ�����Q�[���I�[�o�[
	bool isGameOver();

	// �L�[���͂�L���ɂ���
	bool keyEnable;

public:

	Stage(const int x, const int y);
	~Stage();

	// ���s���\�b�h
	GameChild* update();
};

