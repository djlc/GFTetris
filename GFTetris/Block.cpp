#include "Block.h"
#include "DxLib.h"

Block::Block() {
	this->block = BLOCK_NONE;
	this->color = COLOR_NONE;
}

Block::Block(BlockID block, Color color) {
	this->block = block;
	this->color = color;
}

Block::~Block() {
}

void Block::draw(int x, int y) {
	// ’†
	DrawBox(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, this->color, true);
	// ˜g
	DrawBox(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, COLOR_NONE, false);
}

void Block::draw(int x, int y, Shadow s) {
	// ’†
	DrawBox(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, s, true);
	// ˜g
	DrawBox(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, COLOR_NONE, false);
}
