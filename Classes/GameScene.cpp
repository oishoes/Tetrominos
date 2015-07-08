//
//  GameScene.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Lobby.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Tetromino.h"

using namespace cocos2d;

#pragma mark LifeCycle

// << Standard
bool GameScene::init() {
    if (! Node::init()) {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(background);
    this->tetrominoBag = std::unique_ptr<TetrominoBag>(new TetrominoBag());
    this->active = false;
    
    return true;
}
// >>

void GameScene::onEnter() {
    Node::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // setup grid
    grid = Grid::create();
    grid->setAnchorPoint(Vec2(0.5f,0.0f));
    grid->setPosition(Vec2(visibleSize.width * 0.5f, 0.1f));
    this->addChild(grid);
    
    Tetromino* randomTest = this->createRandomTetromino();
    grid->spawnTetromino(randomTest);
    
    ui::Button* backButton =  ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    backButton->setPosition(Vec2(0.0f, visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(GameScene::backButtonPressed, this));
    this->addChild(backButton);
    this->setupTouchHandling();
    
    this->setGameActive(true);
}

void GameScene::setupTouchHandling() {
    auto touchListener = EventListenerTouchOneByOne::create();
    
    static Vec2 firstTouchPos;
    static Vec2 lastTouchPos;
    //static bool allowRotate = true;
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        firstTouchPos = this-> convertTouchToNodeSpace(touch);
        lastTouchPos = firstTouchPos;
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);
        Vec2 difference = touchPos - lastTouchPos;
        
        Tetromino* activeTetromino = grid->getActiveTetromino();
        
        if (activeTetromino) {
            Coordinate touchCoordinate = this->convertPositionToCoodinate(touchPos);
            Coordinate differenceCoordinate = this->convertPositionToCoodinate(difference);
            Coordinate activeTetrominoCoodinate = grid->getActiveTetrominoCoodinate();
            
            if (abs(differenceCoordinate.x) >= 1) {
                Coordinate newTetrominoCoodinate;
                bool movingRight = (differenceCoordinate.x > 0);
                
                newTetrominoCoodinate =
                Coordinate(activeTetrominoCoodinate.x + (movingRight ? 1 : -1), activeTetrominoCoodinate.y);
                /*
                if (differenceCoordinate.x > 0) {
                    // move right
                    newTetrominoCoodinate = Coordinate(activeTetrominoCoodinate.x - 1, activeTetrominoCoodinate.y);
                } else {
                    // move left
                    newTetrominoCoodinate = Coordinate(activeTetrominoCoodinate.x + 1, activeTetrominoCoodinate.y);
                }
                 */
                
                grid->setActiveTetrominoCoodinate(newTetrominoCoodinate);
                //allowRotate = false;
                lastTouchPos = touchPos;
            }
        }
    };
    
    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        Vec2 touchEndPos = this->convertTouchToNodeSpace(touch);
        
        float distance = touchEndPos.distance(firstTouchPos);
        
        Size blockSize = this->grid->getBlockSize();
        
        if (distance < blockSize.width) { // && allowRotate
            grid->rotateActiveTetromino();
        }
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

#pragma mark UIMethods

void GameScene::backButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->returnToLobby();
    }
}

#pragma mark Public Methods

Tetromino* GameScene::createRandomTetromino() {
    
    TetrominoType tetrominoType = tetrominoBag->getTetromino();
    
    Tetromino* newTetromino = Tetromino::createWithType(tetrominoType);
    
    return newTetromino;
}


#pragma mark Private Methods
void GameScene::setGameActive(bool active) {
    this->active = active;
    
    if (this->active) {
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::step), INITIAL_STEP_INTERVAL);
        
    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::step));
        
    }
}

void GameScene::step(float dt) {
    this->grid->step();
}

#pragma mark Utility Methods

Coordinate GameScene::convertPositionToCoodinate(Vec2 position) {
    Size blockSize = this->grid->getBlockSize();
    
    return Coordinate(position.x / blockSize.width, position.y * blockSize.height);
}