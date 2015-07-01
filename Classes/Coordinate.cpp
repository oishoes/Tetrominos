//
//  Coordinate.cpp
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#include "Coordinate.h"

Coordinate:: Coordinate() : x(0), y(0) {
}

Coordinate:: Coordinate(int x, int y) : x(x), y(y) {
}

Coordinate Coordinate::add(Coordinate a, Coordinate b) {
    return Coordinate(a.x + b.x, a.y + b.y);
}