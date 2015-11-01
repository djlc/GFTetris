#include "MinoGenerator.h"
#include "Array.h"
#include "Block.h"
#include "Mino.h"

Array<char> MinoGenerator::TETRA_MINO[7] = {
	Array<char>(2,2),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(4,4),
};

Array<char> MinoGenerator::PENT_MINO[12] = {
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(3,3),
	Array<char>(4,4),
	Array<char>(4,4),
	Array<char>(4,4),
	Array<char>(5,5),
};

Block::Color MinoGenerator::setColor(int num) {

	Block::Color color;

	switch (num % 7) {
	case 0:
		color = Block::COLOR_YELLOW;
		break;
	case 1:
		color = Block::COLOR_BLUE;
		break;
	case 2:
		color = Block::COLOR_PURPLE;
		break;
	case 3:
		color = Block::COLOR_ORANGE;
		break;
	case 4:
		color = Block::COLOR_RED;
		break;
	case 5:
		color = Block::COLOR_GREEN;
		break;
	case 6:
		color = Block::COLOR_LIGHTBLUE;
		break;
	default:
		color = Block::COLOR_NONE;
		break;
	}
	return color;
}

MinoGenerator::MinoGenerator() {
	// テトラミノ(ブロックを表す記号として0x01でなく0x31を使っていることに注意)
	TETRA_MINO[0].load("1111");
	TETRA_MINO[1].load("100111000");
	TETRA_MINO[2].load("010111000");
	TETRA_MINO[3].load("001111000");
	TETRA_MINO[4].load("000110011");
	TETRA_MINO[5].load("000011110");
	TETRA_MINO[6].load("0010001000100010");

	// ペントミノ
	PENT_MINO[0].load("011110010");
	PENT_MINO[1].load("110110100");
	PENT_MINO[2].load("100100111");
	PENT_MINO[3].load("100110011");
	PENT_MINO[4].load("111010010");
	PENT_MINO[5].load("101111000");
	PENT_MINO[6].load("010111010");
	PENT_MINO[7].load("110010011");
	PENT_MINO[8].load("0100010001000110");
	PENT_MINO[9].load("0010011001000100");
	PENT_MINO[10].load("0010011000100010");
	PENT_MINO[11].load("0010000100001000010000100");
}

MinoGenerator::~MinoGenerator() {
}

Mino* MinoGenerator::getRandomMino() {
	MinoGenerator();

	// 色判定
	Mino* mino;
	int num = rand() % 7;
	int pent = rand() % 12;

	if (rand() % 6 != 0) {
		mino = new Mino(TETRA_MINO[num], setColor(num));
	} else {
		mino = new Mino(PENT_MINO[pent], setColor(pent));
	}

	return mino;
}
