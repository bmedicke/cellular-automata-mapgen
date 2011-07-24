// include local files first, to make sure they include everything they need:
#include "map.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

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
    bool pause;
    int framerate;
    Map map;
};

void mapgenApp::setup()
{
    setWindowSize( 800, 800 );
    framerate = 60;
    setFullScreen( false );
    
    wireframe = false;
    pause = false;

    map.setup( getWindowWidth(), getWindowHeight() );
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
        
        case KeyEvent::KEY_r:
            map.setup( getWindowWidth(), getWindowHeight() );
            pause = false;
            break;
            
        case KeyEvent::KEY_SPACE:
            pause = !pause;
            break;
        
        case KeyEvent::KEY_m:
            map.toggleView();
            break;
            
        case KeyEvent::KEY_p:
            framerate++;
            framerate = ci::math<int>::clamp ( framerate, 1, 60 );
            break;
        
        case KeyEvent::KEY_o:
            framerate--;
            framerate = ci::math<int>::clamp ( framerate, 1, 60 );
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
    // reposition camera to show all tiles.
}

void mapgenApp::update()
{
    setFrameRate( framerate );
    
    if ( !pause )
        map.update();
}

void mapgenApp::draw()
{
	clear();
    map.draw();

}


CINDER_APP_BASIC( mapgenApp, RendererGl )
