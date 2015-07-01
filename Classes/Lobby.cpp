//
//  Lobby.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Lobby.h"
#include "SceneManager.h"

using namespace cocos2d;
// << Standard
bool Lobby::init() {
    if (! Node::init()) {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(background);
    
    return true;
}
// >>

void Lobby::onEnter()
{
    Node::onEnter();
    
    this->setupUI();
}

void Lobby::setupUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* logo = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    logo->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.75f));
    
    ui::Button* singlePlayerButton = ui::Button::create();
    singlePlayerButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    singlePlayerButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.4f));
    singlePlayerButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    singlePlayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::singlePlayerPressed, this));
    
    ui::Button* multiplayerButton = ui::Button::create();
    multiplayerButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    multiplayerButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.25f));
    multiplayerButton->loadTextures("multiplayerButton.png", "multiplayerButtonPressed.png");
    multiplayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::multiplayerPressed, this));
    
    this->addChild(logo);
    this->addChild(singlePlayerButton);
    this->addChild(multiplayerButton);
}

void Lobby::singlePlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        SceneManager::getInstance()->enterGameScene(false);
    }
}
void Lobby::multiplayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        CCLOG("2 Player");
    }
}
