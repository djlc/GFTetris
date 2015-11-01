#pragma once
#include "Array.h"
#include "GameChild.h"
#include "GameString.h"
#include <list>

using namespace std;

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
	int startLevel;
	int level;

	// Score
	int score;

	// ���C����
	int line;

	// �����̓���
	int elist[5];

	// ���_
	const int x, y;

	// �����\���n
	list<GameString*> string;

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

	// �~�m�̈ړ�
	void down();
	void drop();
	void rotate(int direction);
	void move(int direction);

	// �L�[���͔���
	void checkRotateKey();
	bool checkDownKey();
	bool checkDropKey();
	void checkMoveKey();

	// �~�m�̈ړ��Ɋւ��锻��
	bool Judge();
	bool downJudge();
	bool moveJudge(int direction);
	bool rotateJudge(int direction);

	// �~�m�̌Œ�
	void fix();

	// �e�����
	void createShadow();

	// �ŏ�����~�m���d�Ȃ�����Q�[���I�[�o�[
	bool isGameOver();

	// �L�[���͂�L���ɂ���
	bool keyEnable;

public:

	Stage(const int x, const int y, const int startLevel);
	~Stage();

	// ���s���\�b�h
	GameChild* update();
};

