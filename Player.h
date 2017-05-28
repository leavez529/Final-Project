#include"cocos2d.h"
USING_NS_CC;

#pragma once
class Player : public cocos2d::Sprite {
public:
	Player() {
		face = 'r';
	};
	~Player() {};
	static Player* create(const char *pszFileName);
	void update(float delta) {};
	float acc=0.005;
	float velocityx;
	int velocityy;
	int accx;
	char face;
	
	
};
