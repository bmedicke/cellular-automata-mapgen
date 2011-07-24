//
//  map.h
//  mapgen
//
//  Created by Benjamin Medicke on 24.07.11.
//  Copyright 2011 Benjamin Medicke. All rights reserved.
//

#ifndef mapgen_map_h
#define mapgen_map_h

#include "Tile.h"

class Map
{
public:
    Map();
    void setup( int w, int h );
    void draw();
    void update();
private: 
    static const int mapSize = 100;
    Tile tiles[mapSize][mapSize];
    int spacing;
};

#endif
