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
#include "cinder/Rand.h"

#include <algorithm>

Map::Map()
{
    viewConway = false;
}

void Map::setup( int w, int h )
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
            
            tiles[x][y].height = 1.0;
            
            // set 5 percent of the initial tiles to alive:
            tiles[x][y].alive = ci::Rand::randFloat() < 0.05 ? 1 : 0;            
        }
    }
}

void Map::update()
{
    // iterate over everything except for the border:
    for ( int x = 1 ; x < mapSize - 1 ; x++ )
    {
        for (int y = 1 ; y < mapSize - 1 ; y++ )
        {
            int n = 0;
            
            if ( tiles[x - 1][y - 1].alive ) n++;
            if ( tiles[x + 0][y - 1].alive ) n++;
            if ( tiles[x + 1][y - 1].alive ) n++;
            
            if ( tiles[x - 1][y + 0].alive ) n++;
            if ( tiles[x + 1][y + 0].alive ) n++;
            
            if ( tiles[x - 1][y + 1].alive ) n++;
            if ( tiles[x + 0][y + 1].alive ) n++;
            if ( tiles[x + 1][y + 1].alive ) n++;
            
            if ( tiles[x][y].alive && ( n < 2 || n > 3 ) )
            {
                tiles[x][y].alive = false;
                tiles[x][y].height -= 0.05;
            }
            
            else if ( !tiles[x][y].alive && n == 3 )
            {
                tiles[x][y].alive = true;
                tiles[x][y].height -= 0.05;
            }
            
        }
    }
}

void Map::toggleView()
{
    viewConway = !viewConway;
}

void Map::draw()
{    
    for ( int x = 0 ; x < mapSize ; x++ )
    {
        for (int y = 0 ; y < mapSize ; y++ )
        {
            float c = tiles[x][y].height;

            if ( viewConway )
            {
                if ( !tiles[x][y].alive )
                    ci::gl::color( 1.0, 1.0, 1.0 );
                else
                    ci::gl::color( 0.0, 0.0, 0.0);
            }
            
            else
            {
                ci::gl::color( 0, 1.0 - c, c * 0.9 );
            }
            
            ci::gl::drawCube(   ci::Vec3f( tiles[x][y].x , tiles[x][y].y, 0 ), 
                                ci::Vec3f( spacing, spacing, spacing ) );
        }
    }
}