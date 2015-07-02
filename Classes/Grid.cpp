//
//  Grid.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Grid.h"
#include "Tetromino.h"

using namespace cocos2d;

bool Grid::init() {
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }
    
    Tetromino* test = Tetromino::createWithType(TetrominoType::J);
    this->addChild(test);
    
    return true;
}

void Grid::onEnter()
{
    Node::onEnter();
}