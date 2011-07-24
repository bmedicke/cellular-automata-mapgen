// include local files first, to make sure they include everything they need:
#include "Tile.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include <algorithm>

using namespace ci;
using namespace ci::app;
using namespace ci::gl;

class mapgenApp : public AppBasic 
{
public:
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
    void keyUp( KeyEvent event );
    void resize( ResizeEvent event );
	void update();
	void draw();

private:    
    bool wireframe;
    
    static const int mapSize = 30;
    Tile tiles[mapSize][mapSize];
};

void mapgenApp::setup()
{
    setWindowSize( 800, 800 );
    setFrameRate( 60.0f );
    setFullScreen( false );
    
    wireframe = false;

    // GRIDCODE:
    
    // space the tiles along the smaller dimension to make sure
    // that they are all visible:
    int spacing = std::min( getWindowWidth(), getWindowHeight() ) / mapSize;
    
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

void mapgenApp::mouseDown( MouseEvent event )
{
}

void mapgenApp::keyDown( KeyEvent event )
{
    switch ( event.getCode() ) {
            
        case KeyEvent::KEY_w:
            wireframe = !wireframe;
            if ( wireframe )
                enableWireframe();
            else
                disableWireframe();
            break;
            
        case KeyEvent::KEY_f:
            if ( isFullScreen() )
                setFullScreen( false );
            else
                setFullScreen( true );
            break;
            
        default:
            break;
    }
}

void mapgenApp::keyUp( KeyEvent event )
{
}

void mapgenApp::resize( ResizeEvent event )
{
    // realign the tiles.
}

void mapgenApp::update()
{
}

void mapgenApp::draw()
{
	clear();
    
    
    // GRIDCODE:
    // make the size slightly smaller than the spacing 
    // to distinguish them from each other:
    int size = std::min( getWindowWidth(), getWindowHeight() ) / mapSize * 0.9;
    
    for ( int x = 0 ; x < mapSize ; x++ )
    {
        for (int y = 0 ; y < mapSize ; y++ )
        {
            drawCube(   Vec3f( tiles[x][y].x , tiles[x][y].y, 0 ), 
                        Vec3f( size, size, size ) );
        }
    }
}


CINDER_APP_BASIC( mapgenApp, RendererGl )
