//
//  map.h
//  mapgen
//
//  Created by Benjamin Medicke on 24.07.11.
//  Copyright 2011 Benjamin Medicke. All rights reserved.
//

// Uses cellular automata to create 2D tilebased terrain.
// Different automata create a wide variety of maps.
// For a big list of cellular automata rules visit:
// http://www.mirekw.com/ca/rullex_life.html

// To add rules edit the survival/birth requirements in the update() function.

// Set the percantage of initially alive cells in the setup() function.

// For a better result use rules that create few or no oscillators,
// because they create visible fragments in the terrain.
// Moving oscillators on the other hand can create interesting rifts.

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
    void toggleView();
private: 
    static const int mapSize = 100;
    Tile tiles[mapSize][mapSize];
    int spacing;
    bool viewLife;
};

#endif
