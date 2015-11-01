#pragma once
#include "Array.h"
#include "Mino.h"
#include "Block.h"

class MinoGenerator {
	static Array<char> TETRA_MINO[7];
	static Array<char> PENT_MINO[12];
	static Block::Color setColor(int num);
public:
	MinoGenerator();
	~MinoGenerator();
	static Mino * getRandomMino();
};

