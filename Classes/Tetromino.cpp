//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"

#define GRID_SIZE 4

using namespace cocos2d;

Tetromino* Tetromino::createWithType(TetrominoType type) {
    Tetromino* tetromino = new (std::nothrow) Tetromino();
    
    if (tetromino && tetromino->initWithType(type)) {
        tetromino->autorelease();
        return tetromino;
    }
    
    CC_SAFE_DELETE(tetromino);
    
    return nullptr;
}

bool Tetromino::initWithType(TetrominoType type) {
    if (! Node::init()) {
        return false;
    }
    
    this->type = type;
    
    rotations = std::vector<std::vector<Coordinate>>();
    
    // no need here now
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("tetrominos.json");
    
    std::string jsonString = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    JSONPacker::TetrominoState tetrominoState = JSONPacker::unpackTetrominoJSON(jsonString, type);
    
    this->color = tetrominoState.color;
    this->rotations = tetrominoState.rotations;
    this->blocks = std::vector<Sprite*>(4);
    
    float gridSize = float(GRID_SIZE);
    
    Sprite* dummyBlock = Sprite::create("block.png");
    Size dummySize = dummyBlock->getContentSize();
    
    this->setContentSize(Size(dummySize.width * gridSize, dummySize.height * gridSize));
    
    auto coordinates = rotations[0];
    
    for (Coordinate coordinates : coordinates) {
        Sprite* block = Sprite::create("block.png");
        block->setColor(this->color);
        block->setAnchorPoint(Vec2(0.0f, 0.0f));
        block->setPosition(Vec2(coordinates.x * dummySize.width, coordinates.y * dummySize.height));
        
        this->addChild(block);
        this->blocks.push_back(block);
    }
    
    
    return true;
}