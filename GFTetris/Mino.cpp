#include "Mino.h"
#include "Block.h"
#include "DxLib.h"

Mino::Mino(Array<char> data, Block::Color color)
	: field(data.getHeight(), data.getHeight()) {

	for (int i = 0; i < data.getHeight(); i++) {
		for (int j = 0; j < data.getHeight(); j++) {
			field(i, j) = Block( data(i, j) == '1' ? Block::BLOCK_MINO : Block::BLOCK_NONE, data(i, j) == '1' ? color : Block::COLOR_NONE);
		}
	}

	// ‰Šú‘Š‘ÎÀ•W
	x = 3; y = 0;
	sx = x; sy = y;

	// —P—\ƒJƒEƒ“ƒ^
	isFixed = false;

	visible = true;
}

Mino::~Mino() {
}

// x‚ÉBLOCK_SIZE‚ðŠ|‚¯‚½’l
int Mino::getPosX() {
	return x * Block::BLOCK_SIZE;
}

// y‚ÉBLOCK_SIZE‚ðŠ|‚¯‚½’l
int Mino::getPosY() {
	return y * Block::BLOCK_SIZE;
}

void Mino::draw(int x, int y) {
	if (visible) {
		for (int i = 0; i < field.getHeight(); i++) {
			for (int j = 0; j < field.getHeight(); j++) {
				if (field(i, j).color != Block::COLOR_NONE) field(i, j).draw(x + i * Block::BLOCK_SIZE, y + j * Block::BLOCK_SIZE);
			}
		}
	}
}

void Mino::drawShadow(int x, int y) {
	if (visible) {
		for (int i = 0; i < field.getHeight(); i++) {
			for (int j = 0; j < field.getHeight(); j++) {
				if (field(i, j).color != Block::COLOR_NONE) {
					Block::Shadow s;
					switch (field(i, j).color) {
					case Block::COLOR_BLUE:
						s = Block::SHADOW_BLUE;
						break;
					case Block::COLOR_GREEN:
						s = Block::SHADOW_GREEN;
						break;
					case Block::COLOR_LIGHTBLUE:
						s = Block::SHADOW_LIGHTBLUE;
						break;
					case Block::COLOR_ORANGE:
						s = Block::SHADOW_ORANGE;
						break;
					case Block::COLOR_PURPLE:
						s = Block::SHADOW_PURPLE;
						break;
					case Block::COLOR_RED:
						s = Block::SHADOW_RED;
						break;
					case Block::COLOR_YELLOW:
						s = Block::SHADOW_YELLOW;
						break;
					}
					field(i, j).draw(x + i * Block::BLOCK_SIZE, y + j * Block::BLOCK_SIZE, s);
				}
			}
		}
	}
}

void Mino::update(int level) {
}
