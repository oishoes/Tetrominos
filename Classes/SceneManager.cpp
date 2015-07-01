//
//  SceneManager.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "SceneManager.h"

using namespace cocos2d;

static SceneManager* sharedSceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (! sharedSceneManager)
    {
        sharedSceneManager = new (std::nothrow) SceneManager();
    }
    
    return sharedSceneManager;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}