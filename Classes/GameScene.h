//
//  GameScene.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__GameScene__
#define __Tetrominos__GameScene__

#include <cocos2d.h>


class GameScene : public cocos2d::Node {
public:
    CREATE_FUNC(GameScene);
    
private:
    bool init() override; // virtual bool init(); in older version
    
};

#endif /* defined(__Tetrominos__GameScene__) */
