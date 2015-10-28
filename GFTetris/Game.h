#pragma once

#include "Child.h"
#include "GameChild.h"
#include <vector>


using namespace std;

class Game : public Child {
	// タスクリスト
	vector<GameChild*> list;
public:
	Game();
	~Game();
	Child* update();
};
