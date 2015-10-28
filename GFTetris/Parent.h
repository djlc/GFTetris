#pragma once
#include "Child.h"

class Parent {
	
	// �T�u�N���X
	Child* mChild;

	enum MODE {
		MODE_TITLE,
		MODE_GAME,
		MODE_SETTING
	};

	// ���[�h
	MODE mode;
	
	// Singleton
	static Parent* instance;

	Parent();
	~Parent();

public:

	// ���s���\�b�h(���g)
	void update();

	// �C���X�^���X�擾
	static Parent* getInstance();
};