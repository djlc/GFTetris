#pragma once
#include "Child.h"

class Parent {
	
	// サブクラス
	Child* mChild;

	enum MODE {
		MODE_TITLE,
		MODE_GAME,
		MODE_SETTING
	};

	// モード
	MODE mode;
	
	// Singleton
	static Parent* instance;

	Parent();
	~Parent();

public:

	// 実行メソッド(中身)
	void update();

	// インスタンス取得
	static Parent* getInstance();
};