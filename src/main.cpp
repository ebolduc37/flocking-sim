#include "ofMain.h"
#include "ofApp.h"

//========================================================================
// Flocking Simulation
//========================================================================
//
// This application generates a visualization of emergent collective behavior by simulating a flock of birds on openFrameworks in C++. Flocking is simulated with a self-propelled particles model modified from "Statistical mechanics for natural flocks of birds" by Bialek et al. (2012). Such particles are also known as boids.
//
// The particles evolve in a system that has periodic boundary conditions such that the unit cell is a cube, which we call the simulation box. Each particle moves according to the model equations. They interact with at most a fixed number of their closest neighbors and are subject to an alignment force, a cohesion force, and noise. All model parameters are initialized according to Bialek et al.
//
// The cohesion force is formulated from a distance-dependent force between interacting neighbors. Interacting neighbors are connected by a line: a red line indicates that there is hard-core repulsion; a blue line indicates that their distance is near an "equilibrium" preferred distance and that the attraction-repulsion force is close to zero; and a green line indicates that the force is constant.
//
// Additionally, the user can change the interaction range and noise strength while the simulation is running.
//
// For more information, visit https://github.com/ebolduc37/flocking-sim .



//========================================================================
int main( )
{

    int windowSize[2] = { 1920/2, 1080/2 };
    //int windowSize[2] = { 1080/2, 1920/2 };
    
    ofSetupOpenGL(windowSize[0], windowSize[1], OF_WINDOW);
    ofRunApp(new ofApp());

}
