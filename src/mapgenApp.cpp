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
	void update();
	void draw();
private:
    Vec2f center;
    bool wireframe;
};

void mapgenApp::setup()
{
    setWindowSize( 500, 500 );
    setFrameRate( 60.0f );
    setFullScreen( false );
    wireframe = false;
}

void mapgenApp::mouseDown( MouseEvent event )
{
}

void mapgenApp::keyDown( KeyEvent event )
{
    switch ( event.getCode() ) {
            
        case KeyEvent::KEY_w:
            wireframe = !wireframe;
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


void mapgenApp::update()
{
    if ( wireframe )
        enableWireframe();
    else
        disableWireframe();
    
    center.set( getWindowWidth() * 0.5, getWindowHeight() * 0.5 );
}

void mapgenApp::draw()
{
	clear();
    drawCube( Vec3f( center, 10.0 ), Vec3f( 100.0, 100.0, 100.0 ) );
}


CINDER_APP_BASIC( mapgenApp, RendererGl )
