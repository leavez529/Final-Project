#ifndef __ENDING_SCENE_H__
#define __ENDING_SCENE_H__

#include "cocos2d.h"
#include "MenuLayer.h"
#include "GameLevelLayer.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;

class endingScene : public cocos2d::Layer{

public:
    bool passTheGame;
    
    virtual bool init();
    
    CREATE_FUNC(endingScene);
    
    void endingCallBack(Ref* pSender);
    
    void toGameScene();
    
    void toMainScene();
    
    void addTitle();
    
};

#endif // __ENDING_SCENE_H__
