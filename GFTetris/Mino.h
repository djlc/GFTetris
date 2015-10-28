#pragma once

#include "Array.h"
#include "Block.h"
#include "GameChild.h"

class Mino {
public:
	Mino(Array<char> data, Block::Color color);
	~Mino();
	Array<Block> field;
	int cnt;	// カウンタ
	int lastCnt; // 猶予カウンタ
	int x, y;	// field(0,0)の相対座標
	int sx, sy;	// 影ミノの相対座標
	bool isFixed;	// 固定済みかどうか
	bool visible;
	int getPosX(), getPosY();
	void draw(int x, int y);
	void drawShadow(int x, int y);
	void update(int level);
};

