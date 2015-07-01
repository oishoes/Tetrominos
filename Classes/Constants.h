//
//  Constants.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef Tetrominos_Constants_h
#define Tetrominos_Constants_h

// global constant int variable
static const int GRID_WIDTH     = 10;
static const int GRID_HEIGHT    = 20;

// struct, enum or class?
// specify the exact number of each type
enum class TetrominoType {
    I = 0,
    O = 1,
    T = 2,
    S = 3,
    Z = 4,
    J = 5,
    L = 6
};

#endif
