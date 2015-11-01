#pragma once

#include "Array.h"
#include "Block.h"
#include "GameChild.h"

class Mino {
public:
	Mino(Array<char> data, Block::Color color);
	~Mino();
	Array<Block> field;
	int cnt;	// �J�E���^
	int lastCnt; // �P�\�J�E���^
	double x, y;	// field(0,0)�̑��΍��W
	int sx, sy;	// �e�~�m�̑��΍��W
	bool isFixed;	// �Œ�ς݂��ǂ���
	bool visible;
	int getPosX(), getPosY();
	void draw(int x, int y);
	void drawShadow(int x, int y);
	void down(double v);
	void update(int level);
};

