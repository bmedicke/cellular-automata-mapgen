// include local files first, to make sure they include everything they need:
#include "map.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
    Map map;
};

void mapgenApp::setup()
{
    setWindowSize( 800, 800 );
    setFrameRate( 60.0f );
    setFullScreen( false );
    
    wireframe = false;

    map.positionTiles( getWindowWidth(), getWindowHeight() );
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
    map.positionTiles( getWindowWidth(), getWindowHeight() );
}

void mapgenApp::update()
{
}

void mapgenApp::draw()
{
	clear();
    map.draw();

}


CINDER_APP_BASIC( mapgenApp, RendererGl )
