#include"cocos2d.h"
#include"SceneManager.h"
#include"ui\CocosGUI.h"
#include"cocostudio\CocoStudio.h"
using namespace cocostudio;
using namespace ui;
USING_NS_CC;

class MenuLayer :public Layer {
public:
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	SceneManager * smr;
};
