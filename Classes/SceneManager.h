//
//  SceneManager.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__SceneManager__
#define __Tetrominos__SceneManager__

#include <cocos2d.h>

class SceneManager {
public:
    static SceneManager* getInstance();
    
private:
    SceneManager();
    ~SceneManager();
};
#endif /* defined(__Tetrominos__SceneManager__) */
