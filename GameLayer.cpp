#include"gameLayer.h"
#include"Player.h"
USING_NS_CC;

CCScene* GameLevelLayer::scene()
{
	CCScene *scene = CCScene::create();
	if (!scene)
		return NULL;

	GameLevelLayer *layer = GameLevelLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameLevelLayer::init() {
	//加载一个蓝色背景当装饰
	CCLayerColor *blueSky = CCLayerColor::create(ccc4(100, 100, 250, 255));
	this->addChild(blueSky,1);
	//加载地图
	map = CCTMXTiledMap::create("level1.tmx");
	this->addChild(map,2);
	Player* _player = Player::create("koalio_stand.png");
	_player->setPosition(ccp(100, 200));
	map->addChild(_player, 15);
	_player->scheduleUpdate();
	return true;
}



