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

#pragma -
#pragma LifeCycle

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
    this->blocks = std::vector<Sprite*>();
    this->blocks.reserve(4);
    this->rotationIndex = 0;
    
    float gridSize = float(GRID_SIZE);
    
    Sprite* dummyBlock = Sprite::create("block.png");
    Size dummysize = dummyBlock->getContentSize();
    
    this->setContentSize(Size(dummysize.width * gridSize, dummysize.height * gridSize));
    
    auto coordinates = this->getCurrentRotation();
    
    for (Coordinate coordinates : coordinates) {
        Sprite* block = Sprite::create("block.png");
        block->setColor(this->color);
        block->setAnchorPoint(Vec2(0.0f, 0.0f));
        block->setPosition(Vec2(coordinates.x * dummysize.width, coordinates.y * dummysize.height));
        
        this->addChild(block);
        this->blocks.push_back(block);
    }
    
    return true;
}

#pragma -
#pragma Public Methods

void Tetromino::rotate(bool right) {
    
    if (right) {
        rotationIndex++;
    } else {
        rotationIndex--;
    }
    
    if (rotationIndex >= (int) rotations.size()) {
        rotationIndex = 0;
    } else if (rotationIndex < 0) {
        rotationIndex = (int) rotations.size() - 1;
    }
    
    //this->getHighestYCoodinate();
    //this->getWidthInBlocks();
    
    auto coordinates = this->getCurrentRotation();
    
    for (int i = 0; i < GRID_SIZE; ++i) {
        Sprite* block = blocks[i];
        Coordinate coordinate = coordinates[i];
        
        Size blockSize = block->getContentSize();
        block->setPosition(Vec2(coordinate.x * blockSize.width, coordinate.y * blockSize.height));
    }
}

int Tetromino::getHighestYCoodinate() {
    
    auto coordinates = this->getCurrentRotation();
    
    int highest = 0;
    for (Coordinate coordinate : coordinates) {
        if (coordinate.y > highest) {
            highest = coordinate.y;
        }
    }
    return highest;
}

int Tetromino::getWidthInBlocks() {
    auto coordinates = this->getCurrentRotation();
    
    int rightMost = 0;
    int leftMost = GRID_SIZE;
    
    for (Coordinate coordinate : coordinates)
    {
        if (coordinate.x < leftMost)
        {
            leftMost = coordinate.x;
        }
        
        if (coordinate.x > rightMost)
        {
            rightMost = coordinate.x;
        }
    }
    
    return rightMost - leftMost + 1;
}

//int Tetromino::getHighestXCoodinate() {
//}

int Tetromino::getMinimumXCoodinate() {
    auto coordinates = this->getCurrentRotation();
    
    int leftMost = GRID_SIZE;
    for (Coordinate coordinate : coordinates) {
        if (coordinate.x < leftMost) {
            leftMost = coordinate.x;
        }
    }
    
    return leftMost;
}

std::vector<int> Tetromino::getSkirt() {
    int width = getWidthInBlocks();
    int skirtStart = getMinimumXCoodinate();
    
    std::vector<int> skirt = std::vector<int> (width, GRID_SIZE - 1);
    
    auto coordinates = this->getCurrentRotation();
    
    for (Coordinate coordinate : coordinates) {
        int x = coordinate.x - skirtStart;
        int skirtY = skirt[x];
        
        if (coordinate.y < skirtY) {
            skirt[x] = coordinate.y;
        }
    }
    return skirt;
}

std::vector<Sprite*> Tetromino::getBlocks() {
    return this->blocks;
}

std::vector<Coordinate> Tetromino::getCurrentRotation() {
    return rotations[rotationIndex];
}