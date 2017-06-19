#include"cocos2d.h"
USING_NS_CC;

#pragma once
class Unit : public cocos2d::Sprite {
public:
	Unit() {};
	~Unit() {};
	static Unit* create(const char *pszFileName);
	void update(float delta) {};
	bool isOnGround;
	Vec2 speed;
};

