//
//  JSONPacker.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__JSONPacker__
#define __Tetrominos__JSONPacker__

#include "cocos2d.h"
#include "Constants.h"
#include "Coordinate.h"

namespace JSONPacker{
    struct TetrominoState {
        cocos2d::Color3B color;
        std::vector<std::vector<Coordinate>> rotations;
    };
    
    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type);
}

#endif /* defined(__Tetrominos__JSONPacker__) */
