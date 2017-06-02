#include"gameLayer.h"
#include<vector>
USING_NS_CC;



bool GameLevelLayer::init() {
	map = TMXTiledMap::create("MarioMap1.tmx");
	map->setScale(2);
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

	_player = Player::create("MarioStand.png");
	_player->setPosition(20,100);
	_player->setScale(2);
	_player->setTag(1);
	auto body = PhysicsBody::createBox(_player->getContentSize());
	body->setRotationEnable(false);
	body->setEnabled(true);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setGroup(0);
	PhysicsShape* ps = body->getShape(0);
	ps->setMass(0.2f);
	ps->setFriction(0);
	ps->setDensity(0.2f);
	ps->setRestitution(0);
	_player->setPhysicsBody(body);
	this->addChild(_player, 1);//设置人物
	
	

	Land = map->getLayer("land");
	int gid;
	for (int i = 0; i < Land->getLayerSize().width; i++) {
		gid = Land->getTileGIDAt(Vec2(i, 12));
		if (gid) {
			(Land->getTileAt(Vec2(i, 12)))->setPhysicsBody(PhysicsBody::createEdgeBox(Size(map->getTileSize().width / 2,
				map->getTileSize().height / 2)));
			(Land->getTileAt(Vec2(i, 12)))->getPhysicsBody()->setCategoryBitmask(0x01);
			(Land->getTileAt(Vec2(i, 12)))->getPhysicsBody()->setContactTestBitmask(0x01);
			(Land->getTileAt(Vec2(i, 12)))->getPhysicsBody()->setCategoryBitmask(0x01);
			(Land->getTileAt(Vec2(i, 12)))->getPhysicsBody()->setGroup(0);
		}
	}
	log("%d", _player->getTag());
	Pipe = map->getLayer("pipe");
	for (int i = 0; i < Pipe->getLayerSize().width; i++) {
		for (int j = 0; j < Pipe->getLayerSize().height; j++) {
			gid = Pipe->getTileGIDAt(Vec2(i, j));
			if (gid) {
				Pipe->getTileAt(Vec2(i, j))->setPhysicsBody(PhysicsBody::createEdgeBox(Size(map->getTileSize().width / 2,
					map->getTileSize().height / 2)));
			}
		}
	}
	Block = map->getLayer("block");
	for (int i = 0; i < Block->getLayerSize().width; i++) {
		for (int j = 0; j < Block->getLayerSize().height; j++){
			gid = Block->getTileGIDAt(Vec2(i, j));
			if (gid) {
				Block->getTileAt(Vec2(i, j))->setPhysicsBody(PhysicsBody::createEdgeBox(Size(map->getTileSize().width / 2,
					map->getTileSize().height / 2)));
			}
		}
	}
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin =CC_CALLBACK_1(GameLevelLayer::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(GameLevelLayer::onContactPreSolve, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(GameLevelLayer::onContactPostSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameLevelLayer::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameLevelLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLevelLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	scheduleUpdate();//键盘监听
	return true;
}
void GameLevelLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
		keys[keycode] = true;
		auto rightarrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		auto leftarrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		auto uparrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
		auto downarrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
		if (keycode == rightarrow) {
			smallWalkRight();
		}
		if (keycode == leftarrow) {
			smallWalkLeft();
		}
}
void GameLevelLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
		keys[keycode] = false;
		auto rightarrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		auto leftarrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		auto uparrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
		auto downarrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
		if (keycode == rightarrow) {
			_player->stopActionByTag(11);
		}
		if (keycode == leftarrow) {
			_player->stopActionByTag(12);
		}
}
void GameLevelLayer::update(float delta) {
	auto rightarrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto leftarrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto uparrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto downarrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (isKeyPressed(rightarrow)) {
		keyPressedDuration(rightarrow,delta);
	}
	if (isKeyPressed(leftarrow)) {
		keyPressedDuration(leftarrow,delta);
	}
	if (!isKeyPressed(rightarrow)&&_player->getPhysicsBody()->getVelocity().x>0) {
		_player->getPhysicsBody()->setVelocity(Vect(0,_player->getPhysicsBody()->getVelocity().y));
	}
	if (!isKeyPressed(leftarrow) && _player->getPhysicsBody()->getVelocity().x<0) {
		_player->getPhysicsBody()->setVelocity(Vect(0, _player->getPhysicsBody()->getVelocity().y));
	}
	if (isKeyPressed(uparrow)) {
		keyPressedDuration(uparrow, delta);
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
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_player->getPhysicsBody()->getVelocity().x > -80) {
			_player->getPhysicsBody()->applyImpulse(Vect(-100, 0));
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_player->getPhysicsBody()->getVelocity().x < 80) {
			_player->getPhysicsBody()->applyImpulse(Vect(100, 0));
		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_player->isOnGround) {
			if (_player->getPhysicsBody()->getVelocity().y < 150) {
				log("jump");
				_player->getPhysicsBody()->applyImpulse(Vect(0, 6000));

				_player->isOnGround = false;
			}
		}
		break;
	}
	setViewpointCenter(_player->getPosition());

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
bool GameLevelLayer::onContactBegin(PhysicsContact& contact) {
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (spriteA&&spriteB) {
		if (spriteA->getTag() == 1 && spriteB->getPhysicsBody()->getGroup()==0 || spriteA->getPhysicsBody()->getGroup() == 0 && spriteB->getTag() == 1) {
			_player->isOnGround = true;
			log("on ground");
		}
	}
	return true;
}

bool GameLevelLayer::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	
	return true;
}
void GameLevelLayer::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
	
}
void GameLevelLayer::onContactSeparate(PhysicsContact& contact) {

}
void GameLevelLayer::smallWalkRight() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("smallWalkRight.plist");
	auto animation = Animation::create();
	for (int i = 1; i <11; i++) {
		std::string szName = StringUtils::format("smallWalkRight%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
	}
	animation->setDelayPerUnit(1.0f / 15.0f);
	animation->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(animation, "smallWalkRight");
	auto smallWalkRight = AnimationCache::getInstance()->getAnimation("smallWalkRight");
	auto animate = Animate::create(smallWalkRight);
	auto repeat = RepeatForever::create(animate);
	repeat->setTag(11);
	_player->runAction(repeat);
}
void GameLevelLayer::smallWalkLeft() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("smallWalkLeft.plist");
	auto animation = Animation::create();
	for (int i = 1; i <11; i++) {
		std::string szName = StringUtils::format("smallWalkLeft%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
	}
	animation->setDelayPerUnit(1.0f / 15.0f);
	animation->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(animation, "smallWalkLeft");
	auto smallWalkLeft = AnimationCache::getInstance()->getAnimation("smallWalkLeft");
	auto animate = Animate::create(smallWalkLeft);
	auto repeat = RepeatForever::create(animate);
	repeat->setTag(12);
	_player->runAction(repeat);
}
