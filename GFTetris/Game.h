#pragma once

#include "Child.h"
#include "GameChild.h"
#include <vector>


using namespace std;

class Game : public Child {
	// �^�X�N���X�g
	vector<GameChild*> list;
public:
	Game();
	~Game();
	Child* update();
};
