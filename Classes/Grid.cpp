//
//  Grid.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Grid.h"
#include "Tetromino.h"
#include "UIConstants.h"

using namespace cocos2d;

#pragma lifecycle

bool Grid::init() {
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }
    
    this->activeTetromino = nullptr;
    this->activeTetrominoCoordinate = Coordinate();
    
    this->score = 0;
    this->totalLinesCleared = 0;
    
    for (int index = 0; index < GRID_HEIGHT; ++index) {
        std::vector<Sprite*> row(GRID_WIDTH, nullptr);
        blocksLanded.push_back(row);
    }
    
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
        
        if (this->checkIfTetrominoCollides(activeTetromino, activeTetrominoCoordinate)) {
            this->activeTetromino->rotate(false);
        } else {
            ghostTetromino->rotate(true);
            this->updateGhostTetrominoPosition();
        }
    
    }
}

void Grid::spawnTetromino(Tetromino* tetromino) {
    
    this->activeTetromino = tetromino;
    
    this->activeTetromino->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    int highestY = activeTetromino->getHighestYCoodinate();
    int width = activeTetromino->getWidthInBlocks();
    
    Coordinate spawnCoordinate = Coordinate((GRID_WIDTH / 2) - (width / 2) - 1, GRID_HEIGHT - highestY - 1);
    Vec2 spawnPosition = this->convertCoordinateToPosition(spawnCoordinate);
    
    this->setActiveTetrominoCoodinate(spawnCoordinate);
    
    this->activeTetromino->setPosition(spawnPosition);
    this->addChild(this->activeTetromino);
    
    // add ghos
    TetrominoType type = tetromino->getTetrominoType();
    this->ghostTetromino = Tetromino::createWithType(type);
    
    this->ghostTetromino->setCascadeOpacityEnabled(true);
    this->ghostTetromino->setOpacity(GHOST_TETROMINO_OPACITY);
    this->updateGhostTetrominoPosition();
    
    this->addChild(this->ghostTetromino);
}

void Grid::step () {
    if (activeTetromino) {
        Coordinate activeCoodinate = this->getActiveTetrominoCoodinate();
        Coordinate nextCoordinate = Coordinate(activeCoodinate.x, activeCoodinate.y - 1);
        
        if (this->checkIfTetrominoCollides(activeTetromino, nextCoordinate)) {
            this->deactivateTetromino(activeTetromino, activeCoodinate);
        } else {
            this->setActiveTetrominoCoodinate(nextCoordinate);
        }
    }
}

#pragma mark public 

std::vector<std::vector<Sprite*>> Grid::getBlocksLanded() {
    return this->blocksLanded;
}

Size Grid::getBlockSize() {
    Size contentSize = this->getContentSize();
    Size blockSize(contentSize.width / float(GRID_WIDTH), contentSize.height /float(GRID_HEIGHT));
    return blockSize;
}

void Grid::dropActiveTetromino() {
    if (this->getActiveTetromino()) {
        Coordinate landingCoordinate = this->getTetrominoLandingCoodinate();
        
        this->setActiveTetrominoCoodinate(landingCoordinate);
        this->deactivateTetromino(activeTetromino, activeTetrominoCoordinate);
    }
}

int Grid::getScore() {
    return this->score;
}

int Grid::getTotalLinesCleared() {
    return this->totalLinesCleared;
}

bool Grid::checkIfTopReached() {
    
    for (Sprite* block : blocksLanded.back()) {
        if (block) {
            return true;
        }
    }
    
    return false;
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
        if (! this->checkIfTetrominoCollides(activeTetromino, coordinate)) {
            activeTetrominoCoordinate = coordinate;
            activeTetromino->setPosition(this->convertCoordinateToPosition(activeTetrominoCoordinate));
        }
    
        this->updateGhostTetrominoPosition();
    }
}

Tetromino* Grid::getActiveTetromino() {
    return activeTetromino;
}

bool Grid::checkIfTetrominoCollides(Tetromino *tetromino, Coordinate tetrominoCoordinate) {
    
    if (activeTetromino) {
        int skirtStart = tetromino->getMinimumXCoodinate();
        std::vector<int> skirt = tetromino->getSkirt();
        
        for (int index = 0; index < skirt.size(); ++index) {
            Coordinate localCoordinate = Coordinate(index + skirtStart, skirt[index]);
            Coordinate gridCoordinate = Coordinate::add(tetrominoCoordinate, localCoordinate);
            
            if (gridCoordinate.x < 0 || gridCoordinate.y < 0
                || gridCoordinate.x >= GRID_WIDTH || gridCoordinate.y >= GRID_HEIGHT) {
                
                return true;
            }
            if (blocksLanded[gridCoordinate.y][gridCoordinate.x]) {
                return true;
            }
        }
    }
    return false;
}

void Grid::deactivateTetromino(Tetromino* tetromino, Coordinate tetrominoCoordinate) {
    this->placeTetrominoOnBoard(tetromino, tetrominoCoordinate);
    
    this->activeTetromino->removeFromParent();
    this->activeTetromino = nullptr;
    
    this->ghostTetromino->removeFromParent();
    this->ghostTetromino  = nullptr;
    
    this->clearLines();
    
}

void Grid::placeTetrominoOnBoard(Tetromino* tetromino, Coordinate tetrominoCoordinate) {
    std::vector<Sprite*> blocks = tetromino->getBlocks();
    std::vector<Coordinate> coordinates = tetromino->getCurrentRotation();
    
    for (int index = 0; index < BLOCKS_PER_TETROMINO; ++index) {
        // get Tetromino Coodinate
        Coordinate localCoordinate = coordinates[index];
        // Convert to grid coodinate
        Coordinate globalCoordinate = Coordinate::add(tetrominoCoordinate, localCoordinate);
        
        // get the block sprite
        Sprite* block = blocks[index];
        
        // get the block's current postion in the grid space
        Vec2 gridPosition = block->getPosition() + tetromino->getPosition();
        
        // remove the block from the tetromino
        block->retain();
        block->removeFromParent();
        
        // add the block to grid (this)
        this->addChild(block);
        block->release();
        
        // set hte block sprite position
        block->setPosition(gridPosition);
        
        // add the block to blocksLanded
        blocksLanded[globalCoordinate.y][globalCoordinate.x] = block;
    }
}

Coordinate Grid::getTetrominoLandingCoodinate() {
    
    bool collided = false;
    Coordinate landingCoordinate = this->getActiveTetrominoCoodinate();
    
    while (!collided) {
        landingCoordinate.y--;
        if (this->checkIfTetrominoCollides(activeTetromino, landingCoordinate)) {
            landingCoordinate.y++;
            collided = true;
        }
    }
    return landingCoordinate;
}

void Grid::clearLines() {
    
    int linesCleared = 0;
    
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        // check the line if filled
        bool fullLine = true;
        std::vector<Sprite*> row = blocksLanded[y];
        
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (!row[x]) {
                fullLine = false;
                break;
            }
        }
        
        // clear the line if filled
        if (fullLine) {
            // remove the block sprites from grid and blocksLanded
            for (Sprite* block : row) {
                block->removeFromParent();
            }
            
            blocksLanded.erase(blocksLanded.begin() + y);
        
        
            // move blocks in all rows above down one y coordinate
            std::vector<std::vector<Sprite*>> rowsToMoveDown(blocksLanded.begin() + y, blocksLanded.end());
            for (std::vector<Sprite*> rowAbove : rowsToMoveDown) {
                for (Sprite* block : rowAbove) {
                    if (block) {
                        block->setPositionY(block->getPosition().y - block->getContentSize().height);
                    }
                }
            }
            
            linesCleared++;
            
            std::vector<Sprite*> newRow(GRID_WIDTH, nullptr);
            blocksLanded.push_back(newRow);
            
            // to check the new decremented line
            y--;
        }
    }

    totalLinesCleared += linesCleared;
    this->updateScore(linesCleared);
    
    CCLOG("%d", totalLinesCleared);
    CCLOG("%d", this->score);
}

void Grid::updateGhostTetrominoPosition() {
    if (ghostTetromino) {
        Coordinate landingCoordinate = this->getTetrominoLandingCoodinate();
        ghostTetromino->setPosition(this->convertCoordinateToPosition(landingCoordinate));
    }
}

void Grid::updateScore(int linesCleared) {
    int scoreToAdd = linesCleared;
    // if TETROMINO! override
    if (linesCleared == 4) {
        scoreToAdd = 5;
    }
    this->score += scoreToAdd;
}