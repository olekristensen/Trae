#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxGui.h"
//#include "ofxOscParameterSync.h"
#include "ofxXmlSettings.h"
#include "ofxOscReceiver.h"
//#include "ofxStereoCamera.h"
#include "StereoPlane.h"
#include "ofxBullet.h"
#include "VoronoiWall.h"
#include "CeilingPlane.h"
#include "Ribbon.h"
#include "BoxFloor.h"
#include "WireMesh.h"
#include "Lines.h"
#include "CommonPerspectiveTest.h"
#include "Voro3D.h"
#include "ContentScene.h"
#include "TestScene.h"
#include "ofxUI.h"

class testApp : public ofBaseApp
{
public:
	
	void setup();
	void update();
	void draw();
	
	void drawScene1();
    void drawScene2();
    
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    void exit();

    ofxSyphonServer sbsOutputServer;
    
    bool showGrid;

    ofxOscReceiver oscReceiver;
//    ofxOscSender oscSender;
    
    //ofParameter<float> boxOneZ; // a fraction of clock
    //ofParameter<float> boxTwoZ;
    
    ofVec3f camPosWall;
    ofVec3f camPosFloor;
    float eyeSeperation;
    
    float dancerEllipseSize;
    ofVec2f dancerPos;
    
    //    ofxOscParameterSync sync;
    //ofParameterGroup parameters;
    //ofxPanel gui;
    
    bool hideGUI;
    
    ofxUIScrollableCanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    
    void drawRibbon();
    
    //this holds all of our points
    vector<ofVec3f> points;
    //this keeps track of the center of all the points
    ofVec3f center;
    
    ofFbo fbo;
    StereoPlane * floor;
    StereoPlane * wall;
    StereoPlane * activePlane;
    int activePlaneIndex;
    
    void drawFloor();
    vector<StereoPlane *> planes;
    ofxXmlSettings settings;
    
    float dancerHeight;
    
    bool addSphere = false;

    void drawBulletFloor();
    
    void commonWorldDraw();
    
    /*VoronoiWall * voronoiWall;
    VoronoiWall * voronoiPlaza;
    CeilingPlane * ceilingPlane;
    Ribbon * ribbon;
    BoxFloor * boxFloor;
    CommonPerspectiveTest * cmpTest;
    */
    
    
    void drawScenes(int _surfaceId=0);
    
    // Scenes
    TestScene * testScene;
    VoronoiWall * voronoiWall;
    BoxFloor * boxFloor;
    
    vector<ContentScene*> contentScenes;
    
    //WireMesh * wireMesh;
    //ofParameter<ofVec3f> meshOffsetWall;
    //ofParameter<ofVec3f> meshOffsetFloor;
    //Lines * lines;
    //Voro3D * voro3d;
    
};