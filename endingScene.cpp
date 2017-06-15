#include "endingScene.h"
USING_NS_CC;


bool endingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //background
    auto background = Sprite::create("bg_ending.jpg");
    
    background->setScale(0.5);
    
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    this->addChild(background, 0);
    
    /////////score
    /*
    auto score = Label::create("", "Arial", 40);
    
    score->setString(StringUtils::format("Score: %d",i_score));
    
    score->setPosition(Vec2(visibleSize.width*0.5+origin.x, visibleSize.height*0.5+origin.y));
    
    score->setColor(Color3B::WHITE);
    
    this->addChild(score);
    
    */////////////////////////////
    
    //重新开始按钮
    auto restartButton = MenuItemLabel::create(Label::createWithSystemFont("Play Again", "Arial", 25), CC_CALLBACK_1(endingScene::endingCallBack, this));
    
    restartButton->setPosition(Vec2(visibleSize.width*0.35+origin.x, visibleSize.height*0.3+origin.y));
    
    restartButton->setColor(Color3B::WHITE);
    
    restartButton->setTag(1);
    
    //结束游戏按钮
    auto exitButton = MenuItemLabel::create(Label::createWithSystemFont("Exit", "Arial", 25), CC_CALLBACK_1(endingScene::endingCallBack, this));
    
    exitButton->setPosition(Vec2(visibleSize.width*0.65+origin.x, visibleSize.height*0.3+origin.y));
    
    exitButton->setColor(Color3B::WHITE);
    
    exitButton->setTag(2);
    
    //menu
    auto endingMenu = Menu::create(restartButton, exitButton, NULL);
    
    endingMenu->setPosition(Vec2::ZERO);
    
    this->addChild(endingMenu, 1);
    
    return true;
    
}

void endingScene::endingCallBack(Ref* pSender){

    //记录分数，录入排行榜，未完成
    //
    
    switch (((MenuItemLabel *)pSender)->getTag()) {
    
        case 1:
            toGameScene();
            break;
            
        case 2:
            toMainScene();
            break;
            
        default:
            break;
            
    }
}

void endingScene:: toMainScene(){

    auto scene = MenuLayer::createScene();
    
    Director::getInstance()->replaceScene(scene);
    
}

void endingScene:: toGameScene(){

    auto scene = GameLevelLayer::createScene();
    
    Director::getInstance()->replaceScene(scene);
    
}

void endingScene:: addTitle(){

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto title = Label::create("GAME  OVER", "Arial", 50);
    
    if (passTheGame == true) {
        title->setString("WELL  DONE!");
    }
    
    title->setPosition(Vec2(visibleSize.width*0.5+origin.x, visibleSize.height*0.7+origin.y));
    
    title->setColor(Color3B::WHITE);
    
    this->addChild(title);
    
}
