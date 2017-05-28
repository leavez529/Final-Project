#include"SceneManager.h"
#include"gameLayer.h"
void SceneManager::creatScene() {
	startScene = Scene::create();

}
void SceneManager::toGameScene() {
	gameScene = Scene::createWithPhysics();
	gameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	gameScene->getPhysicsWorld()->setGravity(Vect(0.0f, -200.0f));
	auto game = GameLevelLayer::create();
	gameScene->addChild(game);
	Director::getInstance()->runWithScene(gameScene);
}
