#include"gameLayer.h"
#include<vector>
USING_NS_CC;



bool GameLevelLayer::init() {
	map = TMXTiledMap::create("untiled.tmx");
	map->setAnchorPoint(Vec2::ZERO);
	map->setPosition(Vec2::ZERO);
	this->addChild(map, -1);
	//加载地图

	auto objects = map->getObjectGroup("objects");
	ValueMap _map = objects->getObject("others");
	int x = _map.at("x").asInt();
	int y = _map.at("y").asInt();//起点位置

	Size visibleSize = Director::getInstance()->getVisibleSize();
	screenWidth = visibleSize.width;
	screenHeight = visibleSize.height;

	_player = Player::create("HelloWorld.png");
	_player->setPosition(x,y);
	auto body = PhysicsBody::createBox(_player->getContentSize());
	PhysicsShape* ps = body->getShape(0);
	ps->setMass(0.2f);
	ps->setDensity(0.2f);
	ps ->setFriction(1.0f);
	ps->setRestitution(0);
	_player->setPhysicsBody(body);
	this->addChild(_player,1);//设置人物

	auto staticbody = PhysicsBody::createBox(map->getTileSize());
	staticbody->setDynamic(false);
	
	auto Land = map->getLayer("land");
	Land->setPhysicsBody(staticbody);
	int tileGid;
	Sprite* landsp;
	//for (int i = 0; i < Land->getLayerSize().height; i++) {
	//	for (int j = 0; j < Land->getLayerSize().width; j++) {
	//		tileGid = Land->getTileGIDAt(Vec2(i, j));
	//		if (tileGid) {
	//			landsp = Land->getTileAt(Vec2(i, j));
	//			auto hide = Hide::create();
	//			landsp->runAction(hide);
	//		}
	//	}
	//}
	

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameLevelLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLevelLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	scheduleUpdate();//键盘监听
	
	//定时器，游戏时间5分钟//////
	auto timerLayer = Layer::create();
	timerLabel = Label::create();
    	timerLabel->setTextColor(Color4B::WHITE);
   	timerLabel->setSystemFontSize(40);
    	timerLabel->setAnchorPoint(Vec2(0, 1));
    	timerLabel->setPosition(Vec2(20, visibleSize.height));
    	timerLater->addChild(timerLabel);
    	startTime = time(NULL);
    	schedule(schedule_selector(GameLayer::timer));
	this->addChild(timerLayer, 200);
	/////////////////
	
	
	
	return true;
}
void GameLevelLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
		keys[keycode] = true;
}
void GameLevelLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
		keys[keycode] = false;
		_player->velocityx = 0;
}
void GameLevelLayer::update(float delta) {
	auto rightarrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto leftarrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto uparrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto downarrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (isKeyPressed(rightarrow)) {
		if (_player->face == 'l') {
			Action* flipx = FlipX::create(true);
			log("%c", _player->face);
			_player->runAction(flipx);
			_player->runAction(flipx->reverse());
			_player->face = 'r';
			log("%c", _player->face);
		}
		keyPressedDuration(rightarrow,delta);
		
	}
	if (isKeyPressed(leftarrow)) {
		if (_player->face == 'r') {
			Action* flipx = FlipX::create(true);
			log("%c", _player->face);
			_player->runAction(flipx);
			_player->face = 'l';
		}
		
		keyPressedDuration(leftarrow,delta);
	}

}
bool GameLevelLayer::isKeyPressed(EventKeyboard::KeyCode keycode) {
	if (keys[keycode]) {
		return true;
	}
	else {
		return false;
	}
}

void GameLevelLayer::keyPressedDuration(EventKeyboard::KeyCode keycode,float delta) {
	if (_player->velocityx < 5) {
		_player->velocityx += _player->acc*delta;
	}
	int offsetX = 0, offsetY = 0;
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -5;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = 5;
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	
	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.3, Vec2(_player->getPositionX() + offsetX, _player->getPositionY() + offsetY));
	_player->runAction(moveTo);
	setViewpointCenter(_player->getPosition());

}
void GameLevelLayer::smallwalkright() {
	SpriteFrame *frame = NULL;

	auto animation = Animation::create();
	for (int i = 0; i < 11; i++)
	{
		frame = SpriteFrame::create("HelloWorld.png", Rect(i * 14, 0, 14, 16));
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(3.0f / 15.0f);
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);
	auto repeatanimate = RepeatForever::create(animate);
	_player->runAction(repeatanimate);
	log("success?");
}

void GameLevelLayer::setViewpointCenter(Vec2 position) {
	int x = MAX(position.x, screenWidth / 2);
	int y = MAX(position.y, screenHeight / 2);
	x = MIN(x, (map->getMapSize().width*map->getTileSize().width - screenWidth / 2));
	y = MIN(y, (map->getMapSize().height*map->getTileSize().height - screenHeight / 2));
	Point actualPosition = Vec2(x, y);
	Point center = Vec2(screenWidth / 2, screenHeight / 2);
	Point viewPoint = center - actualPosition;
	this->setPosition(viewPoint);

}

void GameLayer:: timer(float dt){
    double usedTime_s = 300-difftime(time(NULL), startTime);
    if (usedTime_s>=0) {
        double usedTime_min = usedTime_s/60;
        timerLabel->setString(StringUtils::format("%02d:%02d", (int)usedTime_min,(int)(usedTime_s)%60));
    } else {
        unschedule(schedule_selector(GameLayer::timer));
        //执行游戏结束的函数
    }
}






