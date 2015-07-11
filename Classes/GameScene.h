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
#include "PreviewGrid.h"

class Grid;

class GameScene : public cocos2d::Node {
public:
    CREATE_FUNC(GameScene);
    void setNetworkdedSession(bool networkedSession);
    void receivedData(const void* data, unsigned long length);
    
protected:
    Grid* grid;
    cocos2d::ui::Text* scoreLabel;
    cocos2d::ui::Text* timeLeftLabel;
    int totalScore;
    bool active;
    float stepInterval;
    float timeLeft;
    bool networkedSession;
    bool gameIsOver;
    PreviewGrid* previewGrid;
    
    // Lifecycle
    bool init() override; // virtual bool init(); in older version
    void onEnter() override;
    void setupTouchHandling();
    
    // Game Logic
    Tetromino* createRandomTetromino();
    void setGameActive(bool active);
    void step(float dt);
    void update(float dt) override;
    void updateScoreStateFromScore();
    void updateGameSpeed(int score);
    void gameOver();
    
    // Networking
    void sendGameStateOverNetwork();
    
    // Utility
    Coordinate convertPositionToCoodinate(cocos2d::Vec2 position);
    Coordinate touchCoordinate;
    
    // UI
    void updateScoreLabel(int score);
    void updateTimeLeftLabel(float time);
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    std::unique_ptr<TetrominoBag> tetrominoBag;
    
};

#endif /* defined(__Tetrominos__GameScene__) */
