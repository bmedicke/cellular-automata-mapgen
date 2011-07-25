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
    float heightChange;
    float initialLife;
};

void mapgenApp::setup()
{
    setWindowSize( 800, 800 );
    framerate = 60;
    setFullScreen( false );
    
    wireframe = false;
    pause = false;
    
    heightChange = map.getHeightChange();
    initialLife = map.getInitialLife();

    map.setup( getWindowWidth(), getWindowHeight() );
}

void mapgenApp::mouseDown( MouseEvent event )
{
}

void mapgenApp::keyDown( KeyEvent event )
{
    switch ( event.getCode() ) {
            
        // show/hide wireframes:
        case KeyEvent::KEY_i:
            wireframe = !wireframe;
            if ( wireframe )
                enableWireframe();
            else
                disableWireframe();
            break;
        
        // toggle fullscreen:
        case KeyEvent::KEY_f:
            if ( isFullScreen() )
                setFullScreen( false );
            else
                setFullScreen( true );
            break;
        
        // start a new map and unpause the game:
        case KeyEvent::KEY_r:
            map.reset();
            pause = false;
            break;
        
        // toggle pause:
        case KeyEvent::KEY_SPACE:
            pause = !pause;
            break;
        
        // toggle view mode:
        case KeyEvent::KEY_m:
            map.toggleView();
            break;
        
        // speed up simulation:
        case KeyEvent::KEY_p:
            framerate++;
            framerate = ci::math<int>::clamp ( framerate, 1, 60 );
            break;
        
        // slow down simulation:
        case KeyEvent::KEY_o:
            framerate--;
            framerate = ci::math<int>::clamp ( framerate, 1, 60 );
            break;
        
        // increase the height change:
        case KeyEvent::KEY_k:
            heightChange += 0.02;
            map.setHeightChange( ci::math<float>::clamp 
                                ( heightChange, 0.02, 1.0 ) );
            break;
            
        // decrease the height change:
        case KeyEvent::KEY_j:
            heightChange -= 0.02;
            map.setHeightChange( ci::math<float>::clamp 
                                ( heightChange, 0.02, 1.0 ) );
            break;
            
        // increase the initial life:
        case KeyEvent::KEY_h:
            initialLife += 0.02;
            map.setInitialLife( ci::math<float>::clamp 
                                ( initialLife, 0.02, 1.0 ) );
            break;
            
        // decrease the initial life:
        case KeyEvent::KEY_g:
            initialLife -= 0.02;
            map.setInitialLife( ci::math<float>::clamp 
                                ( initialLife, 0.02, 1.0 ) );
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
