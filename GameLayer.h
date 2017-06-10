#pragma once
#include"cocos2d.h"
#include"Player.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
class GameLevelLayer : public cocos2d::CCLayer
{
public:
	GameLevelLayer(void) {};
	~GameLevelLayer(void) {};
	CREATE_FUNC(GameLevelLayer);
	std::map<EventKeyboard::KeyCode, bool> keys;
	bool init();
	int screenWidth, screenHeight;
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float delta);
	Player* _player;
	bool isKeyPressed(EventKeyboard::KeyCode keycode);
	void keyPressedDuration(EventKeyboard::KeyCode keycode,float delta);
	void smallWalkRight();
	void smallWalkLeft();
	void setViewpointCenter(Vec2 positon);
	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact,PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact,const PhysicsContactPostSolve& solve);
	void onContactSeparate(PhysicsContact& contact);
	Vec2 tileCoordForPosition(const Vec2& position);
	void updatewhenjump();
	void playerdie();
	void timer(float dt);
protected:
	cocos2d::CCTMXTiledMap *map;
	cocos2d::TMXLayer *Land;
	cocos2d::TMXLayer *Pipe;
	cocos2d::TMXLayer *Coin;
	cocos2d::TMXLayer *Block;
private:
    time_t startTime;
	Label* timerLabel;
	
};

