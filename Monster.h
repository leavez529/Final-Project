#include"cocos2d.h"
USING_NS_CC;

#pragma once
class Monster : public cocos2d::Sprite {
public:
	Monster() {};
	~Monster() {};
	static Monster* create(const char *pszFileName);
	void update(float delta) {};
	Vec2 speed;
};

