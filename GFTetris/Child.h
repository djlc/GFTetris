#pragma once

class Child {
public:
	
	// デストラクタ
	virtual ~Child() {};

	// 実行メソッド
	virtual Child* update() = 0;
};

