//this is ranklistScene.h

#ifndef ranklistScene_h

#define ranklistScene_h

#include "MenuLayer.h"

#include <cocos2d.h>

USING_NS_CC;

class ranklistScene : public Layer{
    
public:
    
    ranklistScene();
    
    ~ranklistScene();
    
    CREATE_FUNC(ranklistScene);
    
    virtual bool init();
    
    static Scene* createScene();
    
    void toMainScene();
    
    void backCallback(Ref* pSender);
    
    void sortScores();
    
};


#endif /* ranklistScene_h */
