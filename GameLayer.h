#pragma once
#include"cocos2d.h"
#include"SceneManager.h"
#include"Player.h"
class GameLevelLayer : public cocos2d::CCLayer
{
private:
    time_t startTime;
    Label* timerLabel;
public:
	GameLevelLayer(void) {};
	~GameLevelLayer(void) {};
	CREATE_FUNC(GameLevelLayer);
	std::map<EventKeyboard::KeyCode, bool> keys;
	bool init();
	SceneManager* smr;
	int screenWidth, screenHeight;
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float delta);
	Player* _player;
	bool isKeyPressed(EventKeyboard::KeyCode keycode);
	void keyPressedDuration(EventKeyboard::KeyCode keycode,float delta);
	void smallwalkright();
	void setViewpointCenter(Vec2 positon);
	void timer(float dt);
protected:
	cocos2d::CCTMXTiledMap *map;
	cocos2d::TMXLayer *Land;
};

