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
#include "time.h"
#include "UIConstants.h"

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
    this->stepInterval = INITIAL_STEP_INTERVAL;
    this->active = false;
    this->totalScore = 0;
    this->timeLeft = TIME_PER_GAME;
    
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
    
    ui::Button* backButton =  ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    backButton->setPosition(Vec2(0.0f, visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(GameScene::backButtonPressed, this));
    this->addChild(backButton);
    
    // setup labels
    this->scoreLabel = ui::Text::create("0", FONT_NAME, FONT_SIZE);
    this->scoreLabel->setAnchorPoint(Vec2(0.5f,1.0f));
    this->scoreLabel->setColor(LABEL_COLOR);
    this->scoreLabel->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.95f));
    this->addChild(this->scoreLabel);
    
    // setup time labels
    this->timeLeftLabel = ui::Text::create("0", FONT_NAME, FONT_SIZE);
    this->timeLeftLabel->setAnchorPoint(Vec2(0.5f,1.0f));
    this->timeLeftLabel->setColor(LABEL_COLOR);
    this->timeLeftLabel->setPosition(this->scoreLabel->getPosition() - Vec2(0.0f, FONT_SIZE * 1.5f));
    this->addChild(this->timeLeftLabel);

    this->setupTouchHandling();
    
    this->setGameActive(true);
}

void GameScene::setupTouchHandling() {
    auto touchListener = EventListenerTouchOneByOne::create();
    
    static Vec2 firstTouchPos;
    static Vec2 lastTouchPos;
    static bool allowRotate = true;
    static std::clock_t touchStartedTime;
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        firstTouchPos = this->convertTouchToNodeSpace(touch);
        lastTouchPos = firstTouchPos;
        touchStartedTime = clock();
        allowRotate = true;
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);
        Vec2 difference = touchPos - lastTouchPos;
        
        Tetromino* activeTetromino = grid->getActiveTetromino();
        
        if (activeTetromino) {
            //Coordinate touchCoordinate = this->convertPositionToCoodinate(touchPos);
            Coordinate differenceCoordinate = this->convertPositionToCoodinate(difference);
            Coordinate activeTetrominoCoodinate = grid->getActiveTetrominoCoodinate();
            
            if (differenceCoordinate.y <= -1000) {
                Coordinate newTetrominoCoodinate = Coordinate(activeTetrominoCoodinate.x, activeTetrominoCoodinate.y -1);
                grid->setActiveTetrominoCoodinate(newTetrominoCoodinate);
                
                allowRotate = false;
                lastTouchPos = touchPos;
            } else if (abs(differenceCoordinate.x) >= 1) {
                Coordinate newTetrominoCoodinate;
                bool movingRight = (differenceCoordinate.x > 0);
                
                newTetrominoCoodinate =
                Coordinate(activeTetrominoCoodinate.x + (movingRight ? 1 : -1), activeTetrominoCoodinate.y);
                
                grid->setActiveTetrominoCoodinate(newTetrominoCoodinate);
                lastTouchPos = touchPos;
                allowRotate = false;

            }
        }
    };
    
    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        Vec2 touchEndPos = this->convertTouchToNodeSpace(touch);
        Size blockSize = this->grid->getBlockSize();
        float distance = touchEndPos.distance(firstTouchPos);
        
        if (distance < blockSize.width && allowRotate) {
            grid->rotateActiveTetromino();
        } else {
            
            Vec2 difference = touchEndPos - firstTouchPos;
            std::clock_t clockDifference = clock() - touchStartedTime;
            
            if (clockDifference <= 0) {
                return;
            }
            
            float touchDuration = (float) (clock() - touchStartedTime) / CLOCKS_PER_SEC;
            float velocity = fabsf(difference.y / touchDuration);
            
            if (velocity > DROP_VELOCITY) {
                grid->dropActiveTetromino();
                this->updateScoreStateFromScore();
            }
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

void GameScene::updateScoreLabel(int score) {
    std::string scoreString = StringUtils::toString(score);
    this->scoreLabel->setString(scoreString);
}

void GameScene::updateTimeLeftLabel(float time) {
    this->timeLeft = time;
    std::string timeLeftString = StringUtils::format("%2.1f", this->timeLeft);
    this->timeLeftLabel->setString(timeLeftString);
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
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::step), this->stepInterval);
        this->scheduleUpdate();
    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::step));
        this->unscheduleUpdate();
    }
}

void GameScene::step(float dt) {
    
    // crunch time code
    if (grid->checkIfTopReached()) {
        // TODO: Game over
        this->gameOver();
    }
    
    Tetromino* activeTetromino = grid->getActiveTetromino();
    if(!activeTetromino) {
        Tetromino* newTetroino = this->createRandomTetromino();
        this->grid->spawnTetromino(newTetroino);
    } else {
        this->grid->step();
        this->updateScoreStateFromScore();
    }
}

void GameScene::gameOver() {
    this->setGameActive(false);
    
    
    std::string scoreString = StringUtils::toString(totalScore);
    std::string messageContent = "Your score is " + scoreString + " !";
    
    MessageBox(messageContent.c_str(), "Game Over");
    
    SceneManager::getInstance()->returnToLobby();
}

void GameScene::update(float dt) {
    Node::update(dt);
    
    this->updateTimeLeftLabel(this->timeLeft - dt);
    
    if (this->timeLeft <= 0.0f) {
        this->gameOver();
    }
}

void GameScene::updateScoreStateFromScore() {
    int newScore = this->grid->getScore();
    if (newScore > this->totalScore) {
        this->totalScore = newScore;
        this->updateScoreLabel(newScore);
        this->updateGameSpeed(this->totalScore);
    }
}

void GameScene::updateGameSpeed(int score) {
    int stepAcceleration = score / SCORE_TO_ACCELERATE;
    
    //float intervalDeduction = INITIAL_STEP_INTERVAL * float(stepAcceleration) * ACCELERATION_FACTOR;
    float intervalDeduction = powf(ACCELERATION_FACTOR, stepAcceleration);
    
    float newInterval = MAX((INITIAL_STEP_INTERVAL * intervalDeduction), SPEED_MAX);
    
    this->stepInterval = newInterval;
    
    this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::step));
    
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::step), this->stepInterval);
}

#pragma mark Utility Methods

Coordinate GameScene::convertPositionToCoodinate(Vec2 position) {
    Size blockSize = this->grid->getBlockSize();
    
    return Coordinate(position.x / blockSize.width, position.y * blockSize.height);
}