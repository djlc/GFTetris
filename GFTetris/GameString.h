#pragma once
class GameString {

	// t=0の時の座標
	double x, y;
	// 速度
	double vx, vy;
	
	// カウンタと移動時間と表示時間
	int cnt, showTimer, moveTimer;
	
	// 文字
	char* str;
	
	// t=0の時の色
	unsigned int r, g, b;
	// 色の変化速度
	unsigned int vr, vg, vb;

	// 描画
	void draw();

public:
	
	// 位置・色固定
	GameString(char* str, double x, double y, unsigned int r, unsigned int g, unsigned int b, int showTimer);

	// 色固定
	GameString(char* str, double x, double y, double dx, double dy, unsigned int r, unsigned int g, unsigned int b, int moveTimer, int showTimer);

	// default
	GameString(char* str, double x, double y, double dx, double dy, unsigned int r, unsigned int g, unsigned int b, int dr, int dg, int db, int moveTimer, int showTimer);

	// デストラクタ
	~GameString();
	
	bool isTimeElapsed();

	// 値の更新
	void update();
};

