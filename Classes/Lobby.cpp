//
//  Lobby.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Lobby.h"

using namespace cocos2d;
// << Standard
bool Lobby::init() {
    if (! Node::init()) {
        return false;
    }
    
    
    LayerColor* background = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(background);
    
    return true;
}
// >>