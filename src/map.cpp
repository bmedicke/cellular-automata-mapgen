//
//  map.cpp
//  mapgen
//
//  Created by Benjamin Medicke on 24.07.11.
//  Copyright 2011 Benjamin Medicke. All rights reserved.
//

#include "map.h"

#include "Tile.h"

#include "cinder/gl/gl.h"

#include <algorithm>

void Map::positionTiles( int w, int h )
{
    // space the tiles along the smaller dimension to make sure
    // that they are all visible:
    spacing = std::min( w, h ) / mapSize;
    
    for ( int x = 0 ; x < mapSize ; x++ )
    {
        for (int y = 0 ; y < mapSize ; y++ )
        {
            // space the tiles evenly with an offset of
            // 0.5 spacing to center the grid:
            tiles[x][y].x = x * spacing + 0.5 * spacing;
            tiles[x][y].y = y * spacing + 0.5 * spacing;
        }
    }
}

void Map::draw()
{
    // make the size slightly smaller than the spacing 
    // to better distinguish them from each other:
    int size = spacing * 0.9;
    
    for ( int x = 0 ; x < mapSize ; x++ )
    {
        for (int y = 0 ; y < mapSize ; y++ )
        {
            ci::gl::drawCube(   ci::Vec3f( tiles[x][y].x , tiles[x][y].y, 0 ), 
                                ci::Vec3f( size, size, size ) );
        }
    }
}