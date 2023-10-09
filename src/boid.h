#pragma once
#include "ofMain.h"

//========================================================================
// Boid class
//========================================================================
//
// Each boid has a name, size, position, and velocity.
// All boids are constrained to a periodic cube.
//
class boid {
    
private:
    
    //--------------------------------------------------------------
    // Private static member variables
    //--------------------------------------------------------------
    
    static double edgeLength;
    static bool drawNames;
    
    
    //--------------------------------------------------------------
    // Private member variables
    //--------------------------------------------------------------
    
    std::string name;
    double size;
    ofVec3f position;
    ofVec3f velocity;
    
    
    //--------------------------------------------------------------
    // Private member functions
    //--------------------------------------------------------------
    
    void setPosition( const ofVec3f &position );
    
    
public:
    
    //--------------------------------------------------------------
    // Public static member functions
    //--------------------------------------------------------------
    
    static void setEdgeLength( const double &edgeLength_ );
    
    static double getEdgeLength(){ return edgeLength; }
    
    static void enableNames();
    static void disableNames();
    
    
    //--------------------------------------------------------------
    // Public class constructor
    //--------------------------------------------------------------
    
    boid();
    
    
    //--------------------------------------------------------------
    // Public member functions
    //--------------------------------------------------------------
    
    void setName( const std::string &name );
    void setVelocity( const ofVec3f &velocity );
    
    std::string getName() { return name; }
    ofVec3f getVelocity() { return velocity; }
    ofVec3f getPosition() { return position; }
    
    void randomize( const double &edgeLength );
    void randomize() { randomize(edgeLength); }
    void update();
    void draw();
    
};
