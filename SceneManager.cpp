#include"SceneManager.h"
#include"MenuLayer.h"
#include"gameLayer.h"
void SceneManager::creatScene() {
	startScene = Scene::create();
	auto menulayer = MenuLayer::create();
	menulayer->smr = this;
	startScene->addChild(menulayer);

}
void SceneManager::toGameScene() {
	gameScene = GameLevelLayer::scene();
	Director::getInstance()->replaceScene(gameScene);
}
