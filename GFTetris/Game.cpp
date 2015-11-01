#include "DxLib.h"
#include "Game.h"
#include "Stage.h"
#include "Fps.h"
#include "GameResource.h"

Game::Game() {
	// 効果音
	GameResource::init();
	// ステージ
	list.push_back(new Stage(40, 40, 1));
	// FPS制御
	list.push_back(new Fps());
}

Game::~Game() {

}

Child* Game::update() {
	Child* next = this;

	// タスクのupdateを順番に実行
	for (vector<GameChild*>::iterator it = list.begin(); it != list.end(); ++it) {
		(*it)->update();
	}

	return next;
}
