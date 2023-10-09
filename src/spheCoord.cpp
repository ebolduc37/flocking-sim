#include "spheCoord.h"

//--------------------------------------------------------------
// Public class constructor
//--------------------------------------------------------------

spheCoord::spheCoord(double radius, double theta, double phi):
    radius(radius),
    theta(theta),
    phi(phi)
{}


//--------------------------------------------------------------
// Overloaded operator
//--------------------------------------------------------------

spheCoord& spheCoord::operator+=(const spheCoord& other){
    
    radius += other.radius;
    theta += other.theta;
    phi += other.phi;
    return *this;
    
}


//--------------------------------------------------------------
// Public member functions
//--------------------------------------------------------------

// Return in cartesian coordinates.
//
ofVec3f spheCoord::inCartesian(){
    
    return radius*ofVec3f(sin(theta)*sin(phi), cos(phi), cos(theta)*sin(phi));
    
}
