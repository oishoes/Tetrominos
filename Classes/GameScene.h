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
    cocos2d::ui::Text* scoreLabel;
    int totalScore;
    bool active;
    
    // Lifecycle
    bool init() override; // virtual bool init(); in older version
    void onEnter() override;
    void setupTouchHandling();
    
    // Game Logic
    Tetromino* createRandomTetromino();
    void setGameActive(bool active);
    void step(float dt);
    void updateScoreStateFromScore();
    void updateScoreLabel(int score);
    
    // Utility
    Coordinate convertPositionToCoodinate(cocos2d::Vec2 position);
    Coordinate touchCoordinate;
    
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    std::unique_ptr<TetrominoBag> tetrominoBag;
    
};

#endif /* defined(__Tetrominos__GameScene__) */
