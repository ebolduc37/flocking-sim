#include "ofApp.h"

//--------------------------------------------------------------
// Setup parameters
//--------------------------------------------------------------

namespace {

// Simulation variables
//
const int NUM_BOIDS = 512; // total number of boids
const double LENGTH = 10.0; // edge length of the periodic cube

// Visualization variables
//
const int FPS = 24; // frames per second
const spheCoord CAM_STEP( 20, 1.0/100*M_PI, 1.0/100*M_PI ); // camera movement
const spheCoord CAM_POS_INI( 1.5*1000, 0.15*M_PI, 0.45*M_PI ); // initial camera position
const bool SHOW_INFO = true; // show/hide information on screen
const bool SHOW_COMM = false; // show/hide commands on screen

// Data capture variables
//
const bool SAVE = false; // save frames or not
const int TIME = 45; // time limit for application to run and save
const std::string FILE_NAME = "flocking-sim"; // file name prefix
std::string DIR = "demo";

}


//--------------------------------------------------------------
// Parameters & more
//--------------------------------------------------------------

namespace {

const int N_C_DEFAULT = 8;
const int N_C_MAX = 32;
const double R_B = 0.2;
const double R_E = 0.5;
const double R_A = 0.8;
const double R_0 = 1.0;
const double ALPHA = 35.0;
const double BETA = 5.0;
const double GAMMA_DEFAULT = 1.0;
const double GAMMA_MAX = 2.0;

const int INF_NUMERICAL = 1 << 16;
const double LENGTH_RANDOMIZE = R_E * std::cbrt(NUM_BOIDS);

}


//--------------------------------------------------------------
// Static function
//--------------------------------------------------------------

// Find indices of the n smallest elements of a vector.
//
static vector<int> findSmallestIndices( vector<double> &vec, const int &n ){
    
    vector<int> ind(vec.size());
    iota( ind.begin(), ind.end(), 0 );
    partial_sort( ind.begin(), ind.begin() + n, ind.end(),
                 [&vec]( int i, int j ){ return vec[i] < vec[j]; } );
    return vector<int>( ind.begin(), ind.begin() + n );
    
}

//--------------------------------------------------------------
// Public member functions
//--------------------------------------------------------------

// Randomize position and velocity of all boids within a cube.
//
void ofApp::randomizeBoids( const double &edgeLength ){
    
    for ( unsigned int i = 0; i < b.size(); i++ ){ b[i].randomize(edgeLength); }
    
}

// Setup the application.
//
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(FPS);
    ofEnableAlphaBlending();
    
    n_c = N_C_DEFAULT;
    gamma = GAMMA_DEFAULT;
    playBoids = true;
    wireframeMode = true;
    
    boid::setEdgeLength(LENGTH);
    b.assign( NUM_BOIDS, boid() );
    randomizeBoids(LENGTH_RANDOMIZE);
    
    for ( unsigned int i = 0; i < b.size(); i++ ){
        std::string name = ofToString(i);
        if ( i < 100 ) { name = "0" + name; }
        if ( i < 10 ) { name = "0" + name; }
        b[i].setName(name);
    }
    
    r = new ofVec3f*[b.size()];
    d = new double*[b.size()];
    l = new line*[b.size()];
    
    for ( unsigned int i = 0; i < b.size(); ++i ){
        r[i] = new ofVec3f[b.size()];
        d[i] = new double[b.size()];
        l[i] = new line[b.size()];
    }
    
    cam_pos = CAM_POS_INI;
    cam.setGlobalPosition(cam_pos.inCartesian());
    cam.lookAt(ofVec3f( 0, 0, 0 ));
    cam_deltaPosition = spheCoord( 0, 0, 0 );
    
    currentFrame = 0;
    
    for ( unsigned int i = 1; i < 100; i++ ){
        std::string suffix = "_" + ofToString(i);
        if ( !ofDirectory::doesDirectoryExist( DIR + suffix ) ){
            DIR = DIR + suffix;
            ofDirectory::createDirectory( DIR );
            break;
        }
    }

}

// Update of the application at every frame.
//
void ofApp::update(){
    
    cam_pos += cam_deltaPosition;
    if ( cam_pos.radius < CAM_STEP.radius ){ cam_pos.radius = CAM_STEP.radius; }
    if ( cam_pos.phi < CAM_STEP.phi ){ cam_pos.phi = CAM_STEP.phi; }
    if ( cam_pos.phi > M_PI-CAM_STEP.phi ){ cam_pos.phi = M_PI - CAM_STEP.phi; }
    cam.setGlobalPosition(cam_pos.inCartesian());
    cam.lookAt(ofVec3f( 0, 0, 0 ));
    
    if ( playBoids ){ for ( unsigned int i = 0; i < b.size(); i++ ){ b[i].update(); } }
    
    for ( unsigned int i = 0; i < b.size(); i++ ){
        if ( n_c == 0 ){ break; }
        d[i][i] = INF_NUMERICAL;
        
        for ( unsigned int j = i+1; j < b.size(); j++ ){
            
            ofVec3f r_period = r[i][j] = b[j].getPosition() - b[i].getPosition();
            const double SAFE_DIST = 0.5 * LENGTH - R_0;
            
            for ( int sx = -1; sx <= 1; sx++ ){
                bool nearBoundary = sx * b[i].getPosition().x > SAFE_DIST;
                if ( sx != 0 && !nearBoundary ) continue;
                bool nearBoundaryOpp = sx * b[j].getPosition().x < -SAFE_DIST;
                if ( sx != 0 && !nearBoundaryOpp ) continue;
                
                for ( int sy = -1; sy <= 1; sy++ ){
                    bool nearBoundary = sy * b[i].getPosition().y > SAFE_DIST;
                    if ( sy != 0 && !nearBoundary ) continue;
                    bool nearBoundaryOpp = sy * b[j].getPosition().y < -SAFE_DIST;
                    if ( sy != 0 && !nearBoundaryOpp ) continue;
                    
                    for ( int sz = -1; sz <= 1; sz++ ){
                        bool nearBoundary = sz * b[i].getPosition().z > SAFE_DIST;
                        if ( sz != 0 && !nearBoundary ) continue;
                        bool nearBoundaryOpp = sz * b[j].getPosition().z < -SAFE_DIST;
                        if ( sz != 0 && !nearBoundaryOpp ) continue;
                        
                        ofVec3f r_shift = r[i][j] + LENGTH * ofVec3f( sx, sy, sz );
                        if ( r_shift.length() < r_period.length() ){ r_period = r_shift; }
                    }
                }
            }
            r[i][j] = r_period;
            r[j][i] = -r[i][j];
            d[i][j] = r[i][j].length();
            d[j][i] = d[i][j];
        }
    }
    
    for ( unsigned int i = 0; i < b.size(); i++ ){
        if ( n_c == 0 ){ break; }
        
        vector<double> distances( d[i], d[i] + b.size() );
        vector<int> smallestIndices = findSmallestIndices( distances, n_c );
        
        ofVec3f v1 = ofVec3f( 0, 0, 0 );
        ofVec3f v2 = ofVec3f( 0, 0, 0 );
        
        for ( unsigned int j = 0; j < n_c; j++ ){
            int smallIndex = smallestIndices.at(j);
            l[i][j].start = b[i].getPosition();
            l[i][j].end = b[i].getPosition() + r[i][smallIndex];
            l[i][j].color = ofVec3f( 0, 0, 0 );
            
            if ( d[i][smallIndex] < R_B ){
                v1 += b[smallIndex].getVelocity();
                v2 += r[i][smallIndex].scale(-INF_NUMERICAL);
                l[i][j].color.x = 255;
            }
            else if ( d[i][smallIndex] < R_A ){
                double scaleFactor = 0.25 * ( d[i][smallIndex] - R_E )/( R_A - R_E );
                v1 += b[smallIndex].getVelocity();
                v2 += r[i][smallIndex].scale(scaleFactor);
                l[i][j].color.z = 255;
            }
            else if (d[i][smallIndex] < R_0){
                v1 += b[smallIndex].getVelocity();
                v2 += r[i][smallIndex].normalize();
                l[i][j].color.y = 255;
            }
            else {
                l[i][j].end = l[i][j].start;
            }
        }

        double r_theta = 2.0 * M_PI * ofRandomuf();
        double r_z = ofRandomf();
        double r_rho = sqrt( 1.0 - r_z * r_z );
        ofVec3f v3 = ofVec3f( r_rho * cos( r_theta ), r_rho * sin( r_theta ), r_z );
        
        b[i].setVelocity( ALPHA * v1 + BETA * v2 + gamma * n_c * v3 );
    }

    ++currentFrame;
    
}

// Draw.
//
void ofApp::draw(){
    
    if ( wireframeMode ){ ofBackground(ofColor( 0, 0, 0 )); }
    else { ofBackground(ofColor( 96, 168, 196 )); }
    
    cam.begin();
    ofEnableDepthTest();
    ofPushMatrix();
        ofScale(100);
        ofSetColor( 255, 255, 255, 50 );
        ofNoFill();
        ofDrawBox( ofVec3f( 0, 0, 0 ), LENGTH );
        ofFill();
        for ( unsigned int i = 0; i < b.size(); i++ ){
            ofSetColor(0);
            if ( wireframeMode ){
                for ( unsigned int j = 0; j < n_c; j++ ){
                    ofSetColor( l[i][j].color.x, l[i][j].color.y, l[i][j].color.z, 100 );
                    ofDrawLine( l[i][j].start, l[i][j].end );
                }
                ofSetColor(255);
            }
            b[i].draw();
        }
    ofPopMatrix();
    ofDisableDepthTest();
    cam.end();
    
    std::string title = "Statistical Mechanics for Natural Flocks of Birds\n";
    title += "(Bialek et al., 2012)";
    
    std::string desc = "There are " + std::to_string(b.size()) + " birds.\n";
    desc += "The noise factor is ";
    desc += std::to_string(gamma).substr( 0, std::to_string(gamma).find(".") + 2 );
    desc += ".\n";
    desc += "They interact with at most their ";
    desc += std::to_string(n_c) + " nearest neighbours.";
    
    std::string comm = "";
    comm += "R: randomize\n";
    comm += "W/A/S/D: rotate\n";
    comm += "Q/E: zoom out/in\n";
    comm += "SPACEBAR: play/pause\n";
    comm += "UP/DOWN: change the noise factor\n";
    comm += "LEFT/RIGHT: change the number of neighbours";
    
    const int LINE_HEIGHT = 10;
    const int N_LINES_DESC = 3;
    const int N_LINES_COMM = 6;
    
    ofSetColor(255);
    if ( SHOW_COMM ){
        if ( SHOW_INFO ){ ofDrawBitmapString( title + "\n\n" + desc, 20, 20 ); }
        ofDrawBitmapString( comm, 20, ofGetHeight() - ( 20 + N_LINES_COMM*LINE_HEIGHT ));
    }
    else if ( SHOW_INFO ){
            ofDrawBitmapString( title, 20, 10 + LINE_HEIGHT );
            ofDrawBitmapString( desc, 20, ofGetHeight() - ( 10 + N_LINES_DESC*LINE_HEIGHT ));
    }
    
    if ( SAVE ){
        ofSaveScreen( DIR + "/raw/" + FILE_NAME + "_" + DIR + "_" + ofToString(currentFrame) + ".jpg" );
        if ( currentFrame >= FPS*TIME ){ ofExit(0); }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed( int key ){
    
    if( key == 'r' ){ randomizeBoids(LENGTH_RANDOMIZE); }
    if( key == ' ' ){ playBoids = !playBoids; }
    if( key == 'p' ){ wireframeMode = !wireframeMode; }
    if( key == OF_KEY_RIGHT && n_c < b.size()-2 ){ ++n_c; }
    if( key == OF_KEY_RIGHT && n_c > N_C_MAX ){ n_c = N_C_MAX; }
    if( key == OF_KEY_LEFT && n_c > 0 ){ --n_c; }
    if( key == OF_KEY_UP && gamma < GAMMA_MAX - 0.05 ){ gamma += 0.1; }
    if( key == OF_KEY_DOWN && gamma >= 0.05 ){ gamma -= 0.1; }
    if( key == OF_KEY_DOWN && gamma < 0.05 ){ gamma = 0; }
    if( key == 'e' ){ cam_deltaPosition.radius = -CAM_STEP.radius; }
    if( key == 'q' ){ cam_deltaPosition.radius = CAM_STEP.radius; }
    if( key == 'd' ){ cam_deltaPosition.theta = CAM_STEP.theta; }
    if( key == 'a' ){ cam_deltaPosition.theta = -CAM_STEP.theta; }
    if( key == 'w' ){ cam_deltaPosition.phi = -CAM_STEP.phi; }
    if( key == 's' ){ cam_deltaPosition.phi = CAM_STEP.phi; }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased( int key ){

    if( key == 'e' || key == 'q' ){ cam_deltaPosition.radius = 0.0; }
    if( key == 'd' || key == 'a' ){ cam_deltaPosition.theta = 0.0; }
    if( key == 'w' || key == 's' ){ cam_deltaPosition.phi = 0.0; }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved( int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged( int x, int y, int button ){

}

//--------------------------------------------------------------
void ofApp::mousePressed( int x, int y, int button ){

}

//--------------------------------------------------------------
void ofApp::mouseReleased( int x, int y, int button ){

}

//--------------------------------------------------------------
void ofApp::mouseEntered( int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseExited( int x, int y ){

}

//--------------------------------------------------------------
void ofApp::windowResized( int w, int h ){

}

//--------------------------------------------------------------
void ofApp::gotMessage( ofMessage msg ){

}

//--------------------------------------------------------------
void ofApp::dragEvent( ofDragInfo dragInfo ){

}
