/*
 Project Title: MeanderTest
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

vector< cell > grid;
int w ;
int cols, rows;

//--------------------------------------------------------------
void ofApp::setup(){
    figure.set(252, 72, 30);
    ground.set(252, 138, 106);
    ofBackground(ground);
    w = 40;
    cols = floor(ofGetWidth()/w);
    rows = floor(ofGetHeight()/w);
    
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            cell cell;
            cell.setLoc(i, j);
            grid.push_back(cell);
        }
    }
    currentCell =0;
    // ofSetFrameRate(10);
    direction = "start";
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ofBackground(51);
    for (int i = 0; i < grid.size(); i++) {
        grid[i].show();
    }
    grid [currentCell ].visited = true;
    grid [currentCell ].highlight();
    // STEP 1
    int next = grid[ currentCell ].checkNeighbors();

    if (next) {
        grid[next].visited = true;
        // STEP 2
        stack.push_back( grid [ currentCell ]);
        // STEP 3
        removeWalls( currentCell, next);
        // STEP 4
        currentCell =  next;
    } else if (stack.size() > 0) { // walk back down the stack
        grid[ currentCell ] = stack[stack.size()-1];
        stack.pop_back();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::removeWalls(int a, int  b) {
    int x =  grid[a].col - grid[b].col;
    if (x == 1) {
        grid[a].walls[3] = false;
        grid[b].walls[1] = false;
        direction = "left";
    } else if (x == -1) {
        grid[a].walls[1] = false;
        grid[b].walls[3] = false;
        direction = "right";
    }
    
    int y = grid[a].row - grid[b].row;
    if (y == 1) {
        grid[a].walls[0] = false;
        grid[b].walls[2] = false;
        direction = "up";
    } else if (y == -1) {
        grid[a].walls[2] = false;
        grid[b].walls[0] = false;
        direction = "down";
    }
}

//--------------------------------------------------------------
cell::cell(){
    // constructor
    walls = {true, true, true, true};
    visited = false;
}

//--------------------------------------------------------------
void cell::draw(){
    
}

//--------------------------------------------------------------
int cell::checkNeighbors(){
    vector<int> neighbors;
    int top    =  index(col, row-1) ;
    int right  =  index(col+1, row) ;
    int bottom =  index(col, row+1) ;
    int left   =  index(col-1, row) ;
    
    if ( top && !grid[top].visited) {
        neighbors.push_back(top);
    }
    
    if ( right  && !grid[right].visited) {
        neighbors.push_back(right);
    }
    
    if ( bottom  && !grid[bottom].visited) {
        neighbors.push_back(bottom);
    }
    
    if (left  && !grid[left].visited) {
        neighbors.push_back(left);
    }
    
    if (neighbors.size() > 0) {
        int r = floor(ofRandom(0, neighbors.size()));
        return neighbors[r];
    } else {
        return NULL;
    }
}

//--------------------------------------------------------------
void cell::highlight() {
    int x = col * w;
    int y = row * w;
    ofSetColor(255, 255, 255);
    ofDrawRectangle(x, y, w, w);
}

//--------------------------------------------------------------
void cell::show() {
    int x = col * w ;
    int y = row * w ;
    ofSetColor(252, 138, 106);
    ofSetLineWidth(1);
    if (walls[0]) { // top
        ofDrawLine(x , y , x + w, y);
    }
    
    if (walls[1]) { // right
        ofDrawLine(x + w, y , x + w, y + w);
    }
    
    if (walls[2]) { // bottom
        ofDrawLine(x + w, y + w, x , y + w);
    }
    
    if (walls[3]) { // left
        ofDrawLine(x , y + w, x , y);
    }
    
    if (visited) {
        ofSetColor(252, 72, 30);
        ofDrawRectangle(x, y, w, w);
    }
}

//--------------------------------------------------------------
int cell::index(int col, int row) {
    if (col < 0 || row < 0 || col > cols-1 || row > rows-1) {
        return 0;
    }
    return col + row * cols;
}

//--------------------------------------------------------------
void cell::setLoc(int col2, int row2){
    col = col2;
    row = row2;
}
