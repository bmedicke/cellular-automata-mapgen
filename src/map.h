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
    void positionTiles( int w, int h );
    void draw();
private: 
    static const int mapSize = 60;
    Tile tiles[mapSize][mapSize];
    int spacing;
};

#endif
