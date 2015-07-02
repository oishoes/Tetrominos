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
    
    this->activeTetromino = nullptr;
    this->activeTetrominoCoordinate = Coordinate();
    
    return true;
}

void Grid::onEnter()
{
    Node::onEnter();
    //Test
    //this->activeTetromino = Tetromino::createWithType(TetrominoType::L);
    //this->addChild(activeTetromino);
}

void Grid::rotateActiveTetromino() {
    
    if (this->activeTetromino) {
        this->activeTetromino->rotate(true);
    }
    
    // TODO: Check if collision, undo rotation
}

void Grid::spawnTetromino(Tetromino* tetromino) {
    
    this->activeTetromino = tetromino;
    
    // TODO: Place tetromino in correct position in grid
    this->activeTetromino->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    int highestY = activeTetromino->getHighestYCoodinate();
    int width = activeTetromino->getWidthInBlocks();
    
    Coordinate spawnCoordinate = Coordinate((GRID_WIDTH / 2) - (width / 2) - 1, GRID_HEIGHT - highestY - 1);
    Vec2 spawnPosition = this->convertCoordinateToPosition(spawnCoordinate);
    
    this->setActiveTetrominoCoodinate(spawnCoordinate);
    
    this->activeTetromino->setPosition(spawnPosition);
    this->addChild(this->activeTetromino);
}

void Grid::step () {
    Coordinate activeCoodinate = this->getActiveTetrominoCoodinate();
    Coordinate nextCoodinate = Coordinate(activeCoodinate.x, activeCoodinate.y - 1);
    
    this->setActiveTetrominoCoodinate(nextCoodinate);
}

#pragma mark PrivateMethods

Vec2 Grid::convertCoordinateToPosition(Coordinate coordinate) {
    Size contentSize = this->getContentSize();
    
    float blockWidth = contentSize.width / float(GRID_WIDTH);
    float blockHeight = contentSize.height / float(GRID_HEIGHT);
    
    return Vec2(coordinate.x * blockWidth, coordinate.y * blockHeight);
}

Coordinate Grid::getActiveTetrominoCoodinate() {
    return this->activeTetrominoCoordinate;
}

void Grid::setActiveTetrominoCoodinate(Coordinate coordinate) {
    if (activeTetromino) {
        activeTetrominoCoordinate = coordinate;
        
        activeTetromino->setPosition(this->convertCoordinateToPosition(activeTetrominoCoordinate));
        
    }
}