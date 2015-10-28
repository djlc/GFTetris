#include "DxLib.h"
#include "Game.h"
#include "Stage.h"
#include "Fps.h"

Game::Game() {
	// �X�e�[�W
	list.push_back(new Stage(40, 40));

	// FPS����
	list.push_back(new Fps());
}

Game::~Game() {

}

Child* Game::update() {
	Child* next = this;

	// �^�X�N��update�����ԂɎ��s
	for (vector<GameChild*>::iterator it = list.begin(); it != list.end(); ++it) {
		(*it)->update();
	}

	return next;
}
