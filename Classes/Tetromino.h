//
//  Tetromino.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__Tetromino__
#define __Tetrominos__Tetromino__

#include <cocos2d.h>
#include "Constants.h"
#include "Coordinate.h"

class Tetromino : public cocos2d::Node {
    
public:
    static Tetromino* createWithType(TetrominoType type);
    
    void rotate(bool right);
    int getHighestYCoodinate();
    int getHighestXCoodinate();
    
    int getWidthInBlocks();
private:
    TetrominoType type;
    cocos2d::Color3B color;
    std::vector<std::vector<Coordinate>> rotations;
    std::vector<cocos2d::Sprite*> blocks;
    
    int rotationIndex;
    
    bool initWithType(TetrominoType type);
};

#endif /* defined(__Tetrominos__Tetromino__) */
