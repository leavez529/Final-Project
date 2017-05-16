#include<MenuLayer.h>

bool MenuLayer::init() {
	Node* node = CSLoader::createNode("menu/menuScene.csb");
	this->addChild(node);
	return true;
}
