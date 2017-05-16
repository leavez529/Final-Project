#include"cocos2d.h"
#include"SceneManager.h"
class GameLevelLayer : public cocos2d::CCLayer
{
public:
	GameLevelLayer(void) {};
	~GameLevelLayer(void) {};
	CREATE_FUNC(GameLevelLayer);

	bool init();
	static cocos2d::CCScene* scene();
	SceneManager* smr;
protected:
	cocos2d::CCTMXTiledMap *map;
};
