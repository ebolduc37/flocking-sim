#pragma once
#include "ofMain.h"

//========================================================================
// Spherical coordinates class
//========================================================================
//
// Spherical coordinates are described by a radius, an angle theta,
// and an angle phi.
//
class spheCoord {
    
public:
    
    //--------------------------------------------------------------
    // Public member variables
    //--------------------------------------------------------------
    
    double radius;
    double theta;
    double phi;
    
    
    //--------------------------------------------------------------
    // Public class constructors
    //--------------------------------------------------------------
    
    spheCoord() {}
    spheCoord(double radius, double theta, double phi);
    
    
    //--------------------------------------------------------------
    // Overloaded operator
    //--------------------------------------------------------------
    
    spheCoord& operator+=(const spheCoord& other);
    
    
    //--------------------------------------------------------------
    // Public member functions
    //--------------------------------------------------------------
    
    ofVec3f inCartesian();
    
};
