//
//  Coordinate.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__Coordinate__
#define __Tetrominos__Coordinate__

class Coordinate {
public:
    int x;
    int y;
    
    Coordinate();
    Coordinate(int x, int y);
    
    static Coordinate add(Coordinate a, Coordinate b);
};

#endif /* defined(__Tetrominos__Coordinate__) */
