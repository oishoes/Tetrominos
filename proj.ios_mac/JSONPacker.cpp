//
//  JSONPacker.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "JSONPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace cocos2d;

namespace JSONPacker {
    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type) {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());
        
        const char* typeStr;
        
        switch (type) {
            case TetrominoType::I: typeStr = "I"; break;
            case TetrominoType::O: typeStr = "O"; break;
            case TetrominoType::T: typeStr = "T"; break;
            case TetrominoType::S: typeStr = "S"; break;
            case TetrominoType::Z: typeStr = "Z"; break;
            case TetrominoType::J: typeStr = "J"; break;
            case TetrominoType::L: typeStr = "L"; break;
                break;
                
            default:
                break;
        }
        
        rapidjson::Value& tetrominoDoc = document[typeStr];
    };
}