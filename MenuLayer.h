#pragma once
#ifndef _MenuLayer_h_

#define _MenuLayer_h_

#include <cocos2d.h>

USING_NS_CC;



class MenuLayer :public Layer {

public:

	void menuCallback(Ref* pSender);

	virtual bool init();

	CREATE_FUNC(MenuLayer);

	void toGameScene();
	static Scene* createScene();
};

#endif // _MenuLayer_h_
