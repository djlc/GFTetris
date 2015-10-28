#pragma once

class Block {

public:
	// BlockID
	enum BlockID : unsigned char {
		BLOCK_NONE,
		BLOCK_MINO,
		BLOCK_WALL = 0xFF
	};

	// Color
	enum Color : unsigned int {
		COLOR_NONE = 0x00000000,
		COLOR_WALL = 0x00C0C0C0,
		COLOR_RED = 0x00FF0000,
		COLOR_GREEN = 0x0000FF00,
		COLOR_BLUE = 0x000000FF,
		COLOR_YELLOW = 0x00FFFF00,
		COLOR_ORANGE = 0x00FF6600,
		COLOR_PURPLE = 0x00800080,
		COLOR_LIGHTBLUE = 0x0000FFFF,
	};
	// Shadow Color
	enum Shadow : unsigned int {
		SHADOW_RED = 0x00330000,
		SHADOW_GREEN = 0x00003300,
		SHADOW_BLUE = 0x00000033,
		SHADOW_YELLOW = 0x00333300,
		SHADOW_ORANGE = 0x00331400,
		SHADOW_PURPLE = 0x00190019,
		SHADOW_LIGHTBLUE = 0x00003333,
	};

	// Size
	static const unsigned int BLOCK_SIZE = 16;

	// Block
	BlockID block;

	// Color
	Color color;
	Block();
	Block(BlockID block, Color color);
	~Block();
	void draw(int x, int y);
	void draw(int x, int y, Shadow s);

};

