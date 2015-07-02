//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"

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
    
    return true;
}