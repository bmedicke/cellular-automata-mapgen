// include local files first, to make sure they include everything they need:
#include "map.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

#include <sstream>

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
    void updateMenu();
    void drawMenu();
    bool wireframe;
    bool pause;
    int framerate;
    float heightChange;
    float initialLife;
    Map map;
    
    bool info;
    float infoFontSize;
    std::string infoString[8];
    Font infoFont;
};

void mapgenApp::setup()
{
    setWindowSize( 800, 800 );
    framerate = 60;
    setFullScreen( false );
    
    wireframe = false;
    pause = false;
    
    info = true;
    infoFontSize = 20.0;    
    infoFont = Font( loadResource( "Andale Mono.ttf"), infoFontSize );
    
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
            
        // toggle info overlay:
        case KeyEvent::KEY_i:
            info = !info;
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
            heightChange = ci::math<float>::clamp ( heightChange, 0.02, 1.0 );
            map.setHeightChange( heightChange );
            break;
            
        // decrease the height change:
        case KeyEvent::KEY_j:
            heightChange -= 0.02;
            heightChange = ci::math<float>::clamp ( heightChange, 0.02, 1.0 );
            map.setHeightChange( heightChange );
            break;
            
        // increase the initial life:
        case KeyEvent::KEY_h:
            initialLife += 0.02;
            initialLife = ci::math<float>::clamp ( initialLife, 0.02, 1.0 );
            map.setInitialLife( initialLife );
            break;
            
        // decrease the initial life:
        case KeyEvent::KEY_g:
            initialLife -= 0.02;
            initialLife = ci::math<float>::clamp ( initialLife, 0.02, 1.0 );
            map.setInitialLife( initialLife );
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
    // TODO: reposition camera to show all tiles.
}

void mapgenApp::update()
{
    setFrameRate( framerate );
    
    if ( !pause )
        map.update();
    
    updateMenu();
    
}

void mapgenApp::draw()
{
	clear();
    map.draw();
    
    if ( info )
        drawMenu();
}

void mapgenApp::updateMenu()
{
    std::stringstream ss;
    
    ss << "toggle info (i)";
    infoString[0] = ss.str();
    ss.str("");
    ss << "toggle fullscreen (f)";
    infoString[1] = ss.str();
    ss.str("");
    ss << "toggle view mode (m)";
    infoString[2] = ss.str();
    ss.str("");
    ss << "new game (r)";
    infoString[3] = ss.str();
    ss.str("");
    ss << "pause (space): " << pause;
    infoString[4] = ss.str();
    ss.str("");
    ss << "control speed (o/p): " << getFrameRate();
    infoString[5] = ss.str();
    ss.str("");
    ss << "height change (j/k): " << heightChange;
    infoString[6] = ss.str();
    ss.str("");
    ss << "initial life (g/h): " << initialLife;
    infoString[7] = ss.str();
    ss.str("");
}

void mapgenApp::drawMenu()
{
    Color color( 1.0, 1.0, 1.0 );
    float padding = 1.3;
    
    for ( int i = 0 ; i < 8 ; i++ )
    {
        Vec2f position = Vec2f( getWindowWidth() / 2, 
                               getWindowHeight() - 
                               infoFontSize * padding * ( i + 1 ) );
        drawStringCentered( infoString[i], position, color, infoFont );
        
    }
}

CINDER_APP_BASIC( mapgenApp, RendererGl )
