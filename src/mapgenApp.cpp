//
//  mapgenApp.cpp
//  mapgenApp
//
//  Created by Benjamin Medicke on 24.07.11.
//  Copyright 2011 Benjamin Medicke. All rights reserved.
//

// Additionally to the on screen menu this shortcuts are available:
// space: pause/unpause simulation.
// f: toggle fullscreen.
// r: start a new map and unpause the game.

// local files first, to make sure they include all dependencies they need:
#include "map.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

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
    
    bool pause;
    bool mapView;
    int framerate;
    float heightChange;
    float initialLife;
    Map map;
    
    // params:
    params::InterfaceGl params;
    
    // camera:
    CameraPersp camera;
    Vec3f eye, center, up;
    float cameraDistance;
    Quatf sceneRotation;
    
};

void mapgenApp::setup()
{
    // setup camera:
    cameraDistance = 500.0f;
    eye = Vec3f( 0.0f, 0.0f, cameraDistance );
    center = Vec3f::zero();
    up = Vec3f::yAxis();
    camera.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    // setup params:
    params = params::InterfaceGl( "Game of Life", Vec2i( 240, 220 ) );
    params.addParam( "Scene Rotation", &sceneRotation, "opened=1" );
    params.addSeparator();
    params.addParam( "Eye Distance", &cameraDistance, 
                     "min=50.0 max=1500 step=10 keyIncr=s keyDecr=w" );
    params.addParam( "Simulation Speed", &framerate,
                     "min=1 max=100 step=1 keyIncr=p keyDecr=o" );
    params.addParam( "Height Change", &heightChange,
                     "min=0.02f max=1.0f step=0.02f keyIncr=h keyDecr=b" );
    params.addParam( "Initial Life", &initialLife,
                    "min=0.02f max=1.0f step=0.02f keyIncr=j keyDecr=n" );
    params.addParam( "Pause", &pause,"keyincr=space" );
    params.addParam( "Map View", &mapView,"keyincr=m" );
    
    // setup window:
    setWindowSize( 800, 800 );
    framerate = 60;
    setFullScreen( false );
    
    pause = false;
    mapView = true;
    
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
        
        case KeyEvent::KEY_f:
            if ( isFullScreen() )
                setFullScreen( false );
            else
                setFullScreen( true );
            break;
        
        case KeyEvent::KEY_r:
            map.reset();
            pause = false;
            break;
        
        case KeyEvent::KEY_SPACE:
            pause = !pause;
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
}

void mapgenApp::update()
{
    setFrameRate( framerate );
    
    map.setInitialLife( initialLife );
    map.setHeightChange( heightChange );
    
    
    map.setMapView( mapView );
    
    if ( !pause )
        map.update();
    
    // update camera:
    eye = Vec3f( 0.0f, 0.0f, cameraDistance );
    camera.lookAt( eye, center, up );
    gl::setMatrices( camera );
    gl::rotate( sceneRotation );
    
}

void mapgenApp::draw()
{
    clear( Color( 0.0f, 0.0f, 0.7f ) );
    gl::enableDepthRead();
	gl::enableDepthWrite();
    
    map.draw();
    
    // draw params window:
    params::InterfaceGl::draw();
}

CINDER_APP_BASIC( mapgenApp, RendererGl )
