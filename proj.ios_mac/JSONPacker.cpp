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
        
        rapidjson::Value& colorDoc = tetrominoDoc["color"];
        
        int r = colorDoc["r"].GetInt();
        int g = colorDoc["g"].GetInt();
        int b = colorDoc["b"].GetInt();
        
        Color3B color = Color3B(r, g, b);
        
        std::vector<std::vector<Coordinate>> rotations;
        rapidjson::Value& rotationsDoc = tetrominoDoc["rotations"];
        for (rapidjson::SizeType rotationsIndex = 0; rotationsIndex < rotationsDoc.Size(); ++rotationsIndex) {
            
            std::vector<Coordinate> rotation;
            rapidjson::Value& rotationDoc = rotationsDoc[rotationsIndex];
            
            for (rapidjson::SizeType rotationIndex = 0; rotationIndex < rotationDoc.Size(); ++rotationIndex) {
                rapidjson::Value& coordinateDoc = rotationDoc[rotationIndex];
                int x = coordinateDoc["x"].GetInt();
                int y = coordinateDoc["y"].GetInt();
                rotation.push_back(Coordinate(x,y));
            }
            rotations.push_back(rotation);
        }
        
        TetrominoState state;
        state.color = color;
        state.rotations = rotations;
        
        return state;
    }
}