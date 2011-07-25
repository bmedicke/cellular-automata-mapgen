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
    heightChange = 0.05;
    initialLife = 0.8;
    viewLife = false;
    spacing = 10.0;
}

void Map::setup( int w, int h )
{
    // space the tiles along the smaller dimension to make sure
    // that they are all visible:
    spacing = std::min( w, h ) / mapSize;
    
    reset();
}

void Map::reset()
{
    for ( int x = 0 ; x < mapSize ; x++ )
    {
        for (int y = 0 ; y < mapSize ; y++ )
        {
            // space the tiles evenly with an offset of
            // 0.5 spacing to center the grid:
            tiles[x][y].x = x * spacing + 0.5 * spacing;
            tiles[x][y].y = y * spacing + 0.5 * spacing;
            
            // start out with water everywhere:
            tiles[x][y].height = 0.0;
            
            // set a percentage of the initial tiles to alive:
            tiles[x][y].alive = ci::Rand::randFloat() < initialLife ? 1 : 0;
            tiles[x][y].newState = tiles[x][y].alive;
        }
    }
}

void Map::update()
{
    // iterate over everything except for the border and mark
    // which cells should live, die and be born:
    for ( int x = 1 ; x < mapSize - 1 ; x++ )
    {
        for (int y = 1 ; y < mapSize - 1 ; y++ )
        {
            
            int n = countAliveNeighbours( x, y );
            
            applyRules( x, y, n );
            
        }
    }
    
    // now that we have counted all neighbours and determined the new states,
    // we can actually change the alive-status of the cells:
    for ( int x = 1 ; x < mapSize - 1 ; x++ )
    {
        for (int y = 1 ; y < mapSize - 1 ; y++ )
        {
            tiles[x][y].alive = tiles[x][y].newState;
        }
    }
}

void Map::draw()
{    
    for ( int x = 0 ; x < mapSize ; x++ )
    {
        for (int y = 0 ; y < mapSize ; y++ )
        {
            float h = tiles[x][y].height;
            
            // game of life view mode:
            if ( viewLife )
            {
                if ( tiles[x][y].alive )
                    ci::gl::color( 0.0, 0.0, 0.0 );
                else
                    ci::gl::color( 1.0, 1.0, 1.0);
            }
            
            // map view mode:
            else
            {
                // fade from blue to green the heigher a tile is:
                ci::gl::color( 0.0, h, ( 1.0 - h ) * 0.9 );
            }
            
            ci::gl::drawCube(   ci::Vec3f( tiles[x][y].x , tiles[x][y].y, 0 ), 
                                ci::Vec3f( spacing, spacing, spacing ) );
        }
    }
}

int Map::countAliveNeighbours( int x, int y )
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
    
    return n;
}

void Map::applyRules( int x, int y, int n )
{
    // This is where the cellular automata rules are defined.
    
    // Rules are defined as:
    // S: neighbours necessary to survive.
    // B: neighbours necessary to be born.
    
    // For a big list of different rules visit:
    // http://www.mirekw.com/ca/rullex_life.html
    
    // great examples are (S/B):
    // 2x2: 125/36
    // conway's: 23/3
    // mine: 1258/357, 23/356
    
    
    if ( tiles[x][y].alive &&
        !( 
          // survival: 
          n == 2 ||
          n == 3 ) )
    {
        tiles[x][y].newState = false;
        tiles[x][y].height += heightChange;
    }
    
    else if ( !tiles[x][y].alive && 
             ( 
              // birth:
              n == 3 ||
              n == 5 ||
              n == 6) )
    {
        tiles[x][y].newState = true;
        tiles[x][y].height += heightChange;
    }
}

void Map::toggleView()
{
    viewLife = !viewLife;
}

bool Map::setHeightChange( float h )
{
    if ( isZeroToOne( h ) )
    {
        heightChange = h;
        return true;
    }

    else
        return false;
}

bool Map::setInitialLife( float i )
{
    if ( isZeroToOne( i ) )
        {
            initialLife = i;
            return true;
        }

    else
        return false;
}

float Map::getHeightChange()
{
    return heightChange;
}

float Map::getInitialLife()
{
    return initialLife;
}

bool Map::isZeroToOne( float f )
{
    if ( f <= 1.0 && f >= 0.0 )
        return true;
    else
        return false;
}