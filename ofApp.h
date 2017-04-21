/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxGui.h"


/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		DMX_SIZE = 512,
	};
	unsigned char data[DMX_SIZE];
	ofxArtnet artnet;
	
	ofxPanel gui;
	ofxIntSlider LedId;
	ofxColorSlider color;
	
	/****************************************
	****************************************/
	void set_dataArray(int id, ofColor color);

public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();
	void exit();

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
