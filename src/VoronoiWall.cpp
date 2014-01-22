//
//  VoronoiWall.cpp
//  StereoPlanes
//
//  Created by Johan Bichel Lindegaard on 15/01/14.
//
//

#include "VoronoiWall.h"

void VoronoiWall::setup() {
    
    name = "Voronoi Wall";
    oscAddress = "/voronoiwall";
    // Voronoi wall
    
    vbounds.set(-1, 0, 1, 1);
    depth = 0.2;
    
    nCells = 400;
    
    
    light.setPosition(2, 2, -2);
    light.setSpotlight();
    light.lookAt(ofVec3f(0,0,0));
    light.setDiffuseColor(ofColor(245,245,170));
    light.setAmbientColor(ofColor(64,84,89));
    light.setSpecularColor(ofColor::white);
    
    dirLight.setSpotlight();
    dirLight.setPosition(-1, -1, 1);
    dirLight.lookAt(ofVec3f(0,0,0));
    dirLight.setDiffuseColor(ofColor(191,191,170));
    
    //voronoi.setBounds(vbounds);
    
    genTheVoronoi();
    
   // params->add(shivering.set("Shiver", 0, 0, 6));
    /*params->add(wallSpeed.set("wallSpeed", 0, 0, 2));
    params->add(subdivisions.set("Subdivisions", 4, 0, 400));
    
    params->add(wallBreakPos.set("wallBreakPos", ofVec3f(0.1,0.5,0), ofVec3f(-1,-1,-1), ofVec3f(1,1,1)));
    params->add(wallBreakReach.set("wallBreakReach", ofVec3f(0.2,2,1), ofVec3f(0,0,0), ofVec3f(2,2,2)));
    params->add(wallBreakStrength.set("wallBreakStrength", 0, 0, 1.8));
    
    params->add(breakPointRadius.set("breakPointRadius", 0.2, 0, 1.4));
     
    
    for(int i=0; i<5; i++) {
        BreakPoint br;
        br.pos = ofVec3f(0,0,0);
        br.radius = 0.25;
        br.pressure = 0;
        
        breakPoints.push_back(br);
    }
    
    params->add(autoOn);*/

}


void VoronoiWall::draw(int _surfaceId) {
    
    if(_surfaceId == 0) {
    /*for(int i = 0; i < cellMeshes.size(); i++){
        ofSetColor(255,255,255,255);
        cellMeshes[i].drawFaces();
        
        ofPushStyle();
        ofSetLineWidth(3);
        ofSetColor(0,0,0);
        //cellMeshes[i].drawWireframe();
        ofPopStyle();
    }*/
        
        
        light.enable();
        dirLight.enable();
        
        ofRectangle bounds = ofRectangle(wallBreakPos.x-wallBreakReach.x/2, wallBreakPos.y-wallBreakReach.y/2, wallBreakReach.x, wallBreakReach.y);
        
        
        for(int i=0; i < cells.size(); i++) {
            
            if(!bounds.inside(cells[i].mesh.getCentroid())) {
                
                if(autoOn) {
                    cells[i].offset.z = ofSignedNoise(wallTime + i) * wallBreakStrength;
                }
                
                bool inBreakpoint = false;
                for(int b=0; b<breakPoints.size(); b++) {
                    
                    //todo: break more with distance
                    
                    if(breakPoints[b].pos.distance(cells[i].mesh.getCentroid()) < breakPoints[b].radius) {
                        cells[i].offset.z = ofMap(breakPoints[b].pos.distance(cells[i].mesh.getCentroid()), 0, breakPoints[b].radius, breakPoints[b].pressure, 0);
                        inBreakpoint = true;
                    }
                }
                
                if(!inBreakpoint) {
                    cells[i].offset.z * 0.6978;
                }
                
            } else {
                
                cells[i].offset.z = 0;
                
            }
            
            
            for(int c=0; c<cells[i].mesh.getColors().size(); c++) {
                cells[i].mesh.setColor(c, ofColor(ofMap(cells[i].offset.z, -0.2, 0.2, 255,100)));
                cells[i].mesh.setColor(c,cells[i].color);
                
            }
            
            ofPushMatrix();
            ofTranslate(cells[i].offset);
            cells[i].mesh.draw();
            
            ofPopMatrix();
        }
        
        light.disable();
        dirLight.disable();

        
        
        
        
    }
    
    /*updateCells();
    
    ofRectangle bounds = ofRectangle(wallBreakPos.get().x-wallBreakReach.get().x/2, wallBreakPos.get().y-wallBreakReach.get().y/2, wallBreakReach.get().x, wallBreakReach.get().y);
    
    glPushMatrix();
    ofNoFill();
    */
    
    //light.enable();
    //dirLight.enable();
    
    // draw a frame for the breaking wall
    //ofFill();
    //ofSetColor(200,230,200);
    // left
    /*ofRect(-1, -1, 0.1, 2);
     ofRect(0.9, -1, 0.1, 2);
     ofRect(-1, -1, 2, 0.1);
     ofRect(-1, 0.9, 2, 2);
     */
    
    /*ofPushMatrix();
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor(0);
    ofTranslate(wallBreakPos.get().x, wallBreakPos.get().y);
    // ofEllipse(0, 0, wallBreakReach.get().x, wallBreakReach.get().y);
    ofPopMatrix();
    //ofDrawRect(bounds.getPosition(), );
    
    for(int i=0; i < cells.size(); i++) {
        
        
        // ofRect(bounds.getPosition().x, bounds.getPosition().y, 0, bounds.getWidth(), bounds.getHeight());
        
        if(!bounds.inside(cells[i].mesh.getCentroid())) {
            
            if(autoOn.get()) {
                cells[i].offset.z = ofSignedNoise(wallTime + i) * wallBreakStrength.get();
            }
            
            
            bool inBreakpoint = false;
            for(int b=0; b<breakPoints.size(); b++) {
                
                //todo: break more with distance
                
               if(breakPoints[b].pos.distance(cells[i].mesh.getCentroid()) < breakPoints[b].radius) {
                   cells[i].offset.z = ofMap(breakPoints[b].pos.distance(cells[i].mesh.getCentroid()), 0, breakPoints[b].radius, breakPoints[b].pressure, 0);
                    inBreakpoint = true;
                }
            }
            
            if(!inBreakpoint) {
                cells[i].offset.z * 0.6978;
            }
            
        } else {
            
            cells[i].offset.z = 0;
            
        }
        
        
        for(int c=0; c<cells[i].mesh.getColors().size(); c++) {
            cells[i].mesh.setColor(c, ofColor(ofMap(cells[i].offset.z, -0.2, 0.2, 255,100)));
            //cells[i].mesh.setColor(c,cells[i].color);

        }
        
        ofPushMatrix();
        ofTranslate(cells[i].offset);
        cells[i].mesh.draw();
        
        ofPopMatrix();*/
        
    //}
    
    /*for(int b=0; b<breakPoints.size(); b++) {
        ofPushMatrix();
        ofTranslate(0, 0, -0.1);
        ofSetColor(0,0,0,20);
        //ofCircle(breakPoints[b].pos, breakPoints[b].radius);
        ofPopMatrix();
    }*/
    
    //light.disable();
    //dirLight.disable();
    
    //ofDisableLighting();
    /*glPopMatrix();
        
    }*/
    
}

void VoronoiWall::updateCells() {
    /*
    bool changed = false;
    while(subdivisions.get() > voronoi.getPoints().size()) {
        voronoi.addPoint(ofRandomPointInRect(vbounds));
        changed = true;
    }
    
    while(subdivisions.get() < voronoi.getPoints().size()) {
        voronoi.getPoints().erase(voronoi.getPoints().begin());
        changed = true;
    }
    
    if(changed) {
        cells.clear();
        
        voronoi.generateVoronoi();
        
        for(int i=0; i<voronoi.cells.size(); i++) {
     
            Cell cell;
            cell.mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
            
            for(int v=0; v<voronoi.cells[i].pts.size(); v++) {
                cell.mesh.addVertex(voronoi.cells[i].pts[v]);
                ofColor col; // move to draw
                col.set(ofMap(0.0, -0.2, 0.2, 255,100));
                cell.mesh.addColor(col);
            }
            
            cell.offset = ofVec3f(0,0,0);
            int r = ofRandom(0,255);
            cell.color = ofColor(ofRandom(r/2,r), ofRandom(r/2,r), r);
            
            cells.push_back(cell);
        }
    }*/
    
}

void VoronoiWall::genTheVoronoi() {
    
    voro::container con(-vbounds.width,vbounds.width,
                        -vbounds.height,vbounds.height,
                        -depth,depth,
                        1,1,1,
                        false,false,false, // set true to flow beyond box
                        8);
    
    for(int i = 0; i < nCells;i++){
        ofPoint newCell = ofPoint(ofRandom(-vbounds.width,vbounds.width),
                                  ofRandom(-vbounds.height,vbounds.height),
                                  ofRandom(-depth,depth));
        
        addCellSeed(con, newCell, i, true);
    }
    
    
    cellMeshes = getCellsFromContainer(con);
    
    for (int i=0; i < cellMeshes.size(); i++) {
        
        Cell cell;
        cell.mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        cell.offset = ofVec3f(0,0,0);
        int r = ofRandom(0,255);
        cell.color = ofColor(ofRandom(r/2,r), ofRandom(r/2,r), r);
        cell.mesh = cellMeshes[i];
        
        cells.push_back(cell);
    }
    
    
    //cellRadius = getCellsRadius(con);
    //cellCentroids = getCellsCentroids(con);
    
    /*
    int n = subdivisions.get();
    for(int i=0; i<n; i++) {
        vpts.push_back(ofRandomPointInRect(vbounds));
    }
    
    //vpts.push_back(ofVec3f(0,0,0));
    voronoi.clear();
    for(int i=0; i<vpts.size(); i++) {
        voronoi.addPoint(vpts[i]);
    }
    
    
    voro::wall
    
    voronoi.generateVoronoi();*/
}

void VoronoiWall::update() {
    /*
    if(active) {
    
        wallTime += 0.01 * wallSpeed;
    
        for(int b=0; b<breakPoints.size(); b++) {

        if(breakPoints[b].pressure > 6) {
            breakPoints[b].pressure = 6;
        }
           
        breakPoints[b].pressure *= 0.98;
        // radius ? ofMap(breakPoints[b].pressure, 0, 1, 0.2, 0.8);
        
        }
    }
    */
}


void VoronoiWall::drawVoronoiWall3d() {
}