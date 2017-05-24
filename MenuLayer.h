#ifndef _MenuLayer_h_
#define _MenuLayer_h_

#include <cocos2d.h>
//#include "SceneManager.h"
USING_NS_CC;

class MenuLayer :public Layer {
public:
    
    void menuCallback(Ref* pSender);
    virtual bool init();
	CREATE_FUNC(MenuLayer);
	//SceneManager * smr;
};

#endif // _MenuLayer_h_
