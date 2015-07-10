//
//  Grid.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__Grid__
#define __Tetrominos__Grid__

#include <cocos2d.h>
#include "Coordinate.h"
#include "Constants.h"

class Tetromino;

class Grid : public cocos2d::Sprite {
public:
    CREATE_FUNC(Grid);
    
    void spawnTetromino(Tetromino* tetromino);
    void rotateActiveTetromino();
    void step();
    void dropActiveTetromino();
    
    Coordinate getActiveTetrominoCoodinate();
    
    cocos2d::Size getBlockSize();
    
    Tetromino* getActiveTetromino();

    void setActiveTetrominoCoodinate(Coordinate coordinate);
    
    int getTotalLinesCleared();
    int getScore();
    
private:
    Tetromino* activeTetromino;
    Tetromino* ghostTetromino;
    // Grid shouldn't be worring about grid stuff
    Coordinate activeTetrominoCoordinate;
    
    std::vector<std::vector<cocos2d::Sprite*>> blocksLanded;
    
    bool init() override;
    void onEnter() override;
    
    int score;
    int totalLinesCleared;
    
    cocos2d::Vec2 convertCoordinateToPosition(Coordinate coordinate);
    
    bool checkIfTetrominoCollides(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void deactivateTetromino(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void placeTetrominoOnBoard (Tetromino* tetromino, Coordinate tetrominoCoordinate);
    Coordinate getTetrominoLandingCoodinate();
    void clearLines();
    
    void updateGhostTetrominoPosition();
    
    void updateScore(int linesCleared);
};

#endif /* defined(__Tetrominos__Grid__) */
