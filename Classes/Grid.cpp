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

#pragma lifecycle

bool Grid::init() {
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }
    
    /*
     Testing
    Tetromino* test = Tetromino::createWithType(TetrominoType::J);
    this->addChild(test);
    test->rotate(true);
     */
    this->activeTetromino = nullptr;
    
    return true;
}

void Grid::onEnter()
{
    Node::onEnter();
    
    this->activeTetromino = Tetromino::createWithType(TetrominoType::L);
    this->addChild(activeTetromino);
}

#pragma mark lifecycle

void Grid::rotateActiveTetromino() {
    
    if (this->activeTetromino) {
        this->activeTetromino->rotate(true);
    }
    
    // TODO: Check if collision, undo rotation
}