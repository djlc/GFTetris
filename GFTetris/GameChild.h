#pragma once
class GameChild {
public:
	virtual ~GameChild() {};
	virtual GameChild* update() = 0;
};

