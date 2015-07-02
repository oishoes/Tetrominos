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
//class Coordinate;

class Grid : public cocos2d::Sprite {
public:
    CREATE_FUNC(Grid);
    
    void spawnTetromino(Tetromino* tetromino);
    void rotateActiveTetromino();
    void step();
    
    Coordinate getActiveTetrominoCoodinate();
private:
    Tetromino* activeTetromino;
    // Grid shouldn't be worring about grid stuff
    Coordinate activeTetrominoCoordinate;
    
    bool init() override;
    void onEnter() override;
    void setActiveTetrominoCoodinate(Coordinate coordinate);
    
    cocos2d::Vec2 convertCoordinateToPosition(Coordinate coordinate);
    
};

#endif /* defined(__Tetrominos__Grid__) */
