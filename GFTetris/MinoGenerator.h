#pragma once
#include "Array.h"

class Mino;
class Block;

class MinoGenerator {
	static Array<char> TETRA_MINO[7];
	static Array<char> PENT_MINO[12];
public:
	MinoGenerator();
	~MinoGenerator();
	static Mino * getRandomMino();
};

