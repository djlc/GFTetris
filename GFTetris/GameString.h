#pragma once
class GameString {

	// t=0�̎��̍��W
	double x, y;
	// ���x
	double vx, vy;
	
	// �J�E���^�ƈړ����Ԃƕ\������
	int cnt, showTimer, moveTimer;
	
	// ����
	char* str;
	
	// t=0�̎��̐F
	unsigned int r, g, b;
	// �F�̕ω����x
	unsigned int vr, vg, vb;

	// �`��
	void draw();

public:
	
	// �ʒu�E�F�Œ�
	GameString(char* str, double x, double y, unsigned int r, unsigned int g, unsigned int b, int showTimer);

	// �F�Œ�
	GameString(char* str, double x, double y, double dx, double dy, unsigned int r, unsigned int g, unsigned int b, int moveTimer, int showTimer);

	// default
	GameString(char* str, double x, double y, double dx, double dy, unsigned int r, unsigned int g, unsigned int b, int dr, int dg, int db, int moveTimer, int showTimer);

	// �f�X�g���N�^
	~GameString();
	
	bool isTimeElapsed();

	// �l�̍X�V
	void update();
};

