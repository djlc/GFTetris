#include "Parent.h"
#include "Game.h"

Parent* Parent::instance = 0;

Parent::Parent() {
	mChild = new Game;
}

Parent::~Parent() {
	delete mChild;
	mChild = 0;
	delete instance;
	instance = 0;
}

void Parent::update() {
	Child* next = mChild->update();
}

Parent* Parent::getInstance() {
	if (instance == 0) instance = new Parent;
	return instance;
}
