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
#include "CocosGUI.h"
#include "Grid.h"
#include "TetrominoBag.h"

class Grid;

class GameScene : public cocos2d::Node {
public:
    CREATE_FUNC(GameScene);
    
protected:
    Grid* grid;
private:
    bool init() override; // virtual bool init(); in older version
    void onEnter() override;
    
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setupTouchHandling();
    
    void setGameActive(bool active);
    void step(float dt);
    bool active;
    
    std::unique_ptr<TetrominoBag> tetrominoBag;
    
    Tetromino* createRandomTetromino();
};

#endif /* defined(__Tetrominos__GameScene__) */
