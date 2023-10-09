#include "boid.h"

//--------------------------------------------------------------
// Constants
//--------------------------------------------------------------

namespace {

    const double V_0 = 0.05;
    const double SIZE = 0.05;
    const int RESOLUTION = 4;

}


//--------------------------------------------------------------
// Private static member variables
//--------------------------------------------------------------

double boid::edgeLength = 10.0;
bool boid::drawNames = false;


//--------------------------------------------------------------
// Public static member functions
//--------------------------------------------------------------

// Set edge length of periodic cube.
//
void boid::setEdgeLength( const double &edgeLength_ ){
    
    if ( edgeLength_ != 0 ){ edgeLength = abs(edgeLength_); }
    
}

// Enable names to be shown.
//
void boid::enableNames(){
    
    drawNames = true;
    
}

// Disable names to be shown.
//
void boid::disableNames(){
    
    drawNames = false;
    
}


//--------------------------------------------------------------
// Static function
//--------------------------------------------------------------

// Generate a random vector within a cube.
//
static ofVec3f randomInCube( const double &edgeLength ){
    
    double x = 0.5*edgeLength*ofRandomf();
    double y = 0.5*edgeLength*ofRandomf();
    double z = 0.5*edgeLength*ofRandomf();
    
    return ofVec3f( x, y, z );
    
}

// Generate a random vector within a sphere.
//
static ofVec3f randomInSphere( const double &radius ){
    
    double x, y, z, d2;
    
    do {
        x = radius*ofRandomf();
        y = radius*ofRandomf();
        z = radius*ofRandomf();
        d2 = x*x + y*y + z*z;
    } while ( d2 > radius*radius );
    
    return ofVec3f( x, y, z );
    
}


//--------------------------------------------------------------
// Public class constructor
//--------------------------------------------------------------

// Default boid class constructor.
// New boids are given a random position and a random velocity.
//
boid::boid(){
    
    size = SIZE;
    randomize();
    
}


//--------------------------------------------------------------
// Public member functions
//--------------------------------------------------------------

// Set name.
//
void boid::setName( const std::string &name_ ){
    
    name = name_;
    
}

// Set velocity in a direction with fixed speed.
//
void boid::setVelocity( const ofVec3f &velocity_ ){
    
    velocity.set(velocity_);
    velocity.scale(V_0);
    
}

// Set position within the periodic cube.
//
void boid::setPosition( const ofVec3f &position_ ){
    
    position.set(position_);
    if ( abs(position.x) > 0.5*edgeLength ){ position.x -= ofSign(position.x) * edgeLength; }
    if ( abs(position.y) > 0.5*edgeLength ){ position.y -= ofSign(position.y) * edgeLength; }
    if ( abs(position.z) > 0.5*edgeLength ){ position.z -= ofSign(position.z) * edgeLength; }
    
}

// Randomize the position and velocity.
//
void boid::randomize( const double &edgeLength_ ){
    
    if ( abs(edgeLength_) < edgeLength ) { setPosition(randomInCube(edgeLength_)); }
    else { setPosition(randomInCube(edgeLength)); }
    setVelocity(randomInSphere(1.0));
    
}

// Update the position with one step of the velocity.
//
void boid::update(){
    
    setPosition( position + velocity );
    
}

// Draw the boid at its position.
//
void boid::draw(){
    
    if (drawNames) { ofDrawBitmapString( getName(), getPosition() ); }
    ofSetSphereResolution(RESOLUTION);
    ofDrawSphere( getPosition(), size );
    
}
