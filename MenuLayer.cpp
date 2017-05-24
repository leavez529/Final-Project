#include "MenuLayer.h"

void MenuLayer::menuCallback(Ref* pSender){
    switch (((MenuItemImage *)pSender)->getTag()) {
        case 1:
            //tsm->goGameScene();
            break;
        case 2:
            //tsm->goRankScene();
            break;
        case 3:
            //tsm->goSettingScene();
            break;
        case 4:
            Director::getInstance()->end();
            exit(0);
            break;
        default:
            break;
    }
    
}

bool MenuLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //create background
    auto background = Sprite::create("bg_opening.jpg");
    background->setScale(0.5);
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);
    
    //create buttons
    auto startButton = MenuItemImage::create("button_start.png", "button_start_selected.png", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    startButton->setPosition(Vec2(visibleSize.width*0.2,visibleSize.height*0.77));
    startButton->setScale(0.55);
    startButton->setTag(1);
    
    auto rankButton = MenuItemImage::create("button_rank.png", "button_rank_selected.png", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    rankButton->setPosition(Vec2(visibleSize.width*0.2,visibleSize.height*0.65));
    rankButton->setScale(0.55);
    rankButton->setTag(2);
    
    auto settingButton = MenuItemImage::create("button_setting.png", "button_setting_selected.png", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    settingButton->setPosition(Vec2(visibleSize.width*0.2,visibleSize.height*0.53));
    settingButton->setScale(0.55);
    settingButton->setTag(3);
    
    auto exitButton = MenuItemImage::create("button_exit.png", "button_exit_selected.png", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    exitButton->setPosition(Vec2(visibleSize.width*0.2,visibleSize.height*0.41));
    exitButton->setScale(0.55);
    exitButton->setTag(4);
    
    //create menu
    auto menu = Menu::create(startButton, rankButton, settingButton, exitButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);
    
	return true;
}
