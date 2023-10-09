#pragma once
#include "ofMain.h"
#include "boid.h"
#include "spheCoord.h"

//========================================================================
// Line class
//========================================================================
//
// A line in 3D space that has a start point, an end point, and a RGB color.
//
class line {
    
public:
    ofVec3f start;
    ofVec3f end;
    ofVec3f color;
    
};

//========================================================================
// ofApp class
//========================================================================
//
class ofApp : public ofBaseApp {
    
public:
    
    //--------------------------------------------------------------
    // Public member variables
    //--------------------------------------------------------------
    
    int n_c;
    double gamma;
    
    vector <boid> b;
    ofVec3f** r;
    double** d;
    line** l;
    
    bool playBoids;
    int currentFrame;
    bool wireframeMode;
    
    ofCamera cam;
    spheCoord cam_pos;
    spheCoord cam_deltaPosition;
    
    
    //--------------------------------------------------------------
    // Public member functions
    //--------------------------------------------------------------
    
    void randomizeBoids( const double &edgeLength );
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
};
