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
}

SceneManager::~SceneManager() {
}

void SceneManager::enterGameScene(bool networked) {
    Scene* scene = Scene::create();
    GameScene* gameScene = GameScene::create();
    
    scene->addChild(gameScene);
    
    Director::getInstance()->pushScene(scene);
}