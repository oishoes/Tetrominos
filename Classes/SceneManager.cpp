//
//  SceneManager.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "SceneManager.h"
#include "GameScene.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

static SceneManager* sharedSceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (! sharedSceneManager)
    {
        sharedSceneManager = new (std::nothrow) SceneManager();
    }
    
    return sharedSceneManager;
}

SceneManager::SceneManager() {
    gameScene = nullptr;
    this->netWorkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->netWorkingWrapper->setDelegate(this);
}

SceneManager::~SceneManager() {
}

void SceneManager::enterGameScene(bool networked) {
    Scene* scene = Scene::create();
    this->gameScene = GameScene::create();
    this->gameScene->setNetworkdedSession(networked);
    
    scene->addChild(this->gameScene);
    
    Director::getInstance()->pushScene(scene);
}

void SceneManager::returnToLobby() {
    Director::getInstance()->popScene();
    if (gameScene) {
        Director::getInstance()->popScene();
        gameScene = nullptr;
        netWorkingWrapper->disconnect();
    }
}

void SceneManager::showPeerList() {
    netWorkingWrapper->showPeerList();
}

void SceneManager::receiveMultiplayerInvitations() {
    netWorkingWrapper->startAdvertisingAvailability();
}
void SceneManager::sendData(const void *data, unsigned long length) {
    netWorkingWrapper->sendData(data, length);
}

#pragma mark -
#pragma mark networkWrapperDelegateMethods

void SceneManager::receivedData(const void *data, unsigned long length) {
    if (gameScene) {
        gameScene->receivedData(data, length);
    }
}

void SceneManager::stateChanged(ConnectionState state) {
    switch (state) {
        case ConnectionState::CONNECTING:
            CCLOG("Connection...");
            break;
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
        case ConnectionState::CONNECTED:
            CCLOG("Connected");
            if (!gameScene) {
                this->netWorkingWrapper->stopAdvertisingAvailability();
                this->enterGameScene(true);
            }
            break;
    }
}