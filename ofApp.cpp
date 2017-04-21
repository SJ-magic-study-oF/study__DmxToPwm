/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/
char targetIP[] = "10.7.206.7";

enum LED_TYPE{
	LEDTYPE_STAGELIGHT,
	LEDTYPE_TAPE,
};
struct Led{
	LED_TYPE LedType;
	int OdeOffset;
};

/* */
Led Led[] = {
	// DMX/PWM converter 1									
	{	LEDTYPE_TAPE	,	0	},	//	0		HardOffset =	1
	{	LEDTYPE_TAPE	,	3	},	//	1			
	{	LEDTYPE_TAPE	,	6	},	//	2			
	{	LEDTYPE_TAPE	,	9	},	//	3			
	{	LEDTYPE_TAPE	,	12	},	//	4			
	{	LEDTYPE_TAPE	,	15	},	//	5			
	{	LEDTYPE_TAPE	,	18	},	//	6			
	{	LEDTYPE_TAPE	,	21	},	//	7			
										
	// DMX/PWM converter 2									
	{	LEDTYPE_TAPE	,	24	},	//	8		HardOffset =	25
	{	LEDTYPE_TAPE	,	27	},	//	9			
	{	LEDTYPE_TAPE	,	30	},	//	10			
	{	LEDTYPE_TAPE	,	33	},	//	11			
	{	LEDTYPE_TAPE	,	36	},	//	12			
	{	LEDTYPE_TAPE	,	39	},	//	13			
	{	LEDTYPE_TAPE	,	42	},	//	14			
	{	LEDTYPE_TAPE	,	45	},	//	15			
										
	// Stage Light									
	{	LEDTYPE_STAGELIGHT	,	48	},	//	16		HardOffset =	49
};

const int NUM_LEDS = sizeof(Led)/sizeof(Led[0]);

/************************************************************
************************************************************/

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowShape(600, 400);
    
	ofSetVerticalSync(false);
    ofSetFrameRate(60);
	
    //at first you must specify the Ip address of this machine
    artnet.setup("10.0.0.2"); //make sure the firewall is deactivated at this point
	
	/********************
	********************/
	for(int i = 0; i < DMX_SIZE; i++){
		data[i] = 0;
	}
	
	/********************
	********************/
	ofColor initColor = ofColor(0, 0, 0, 255);
	ofColor minColor = ofColor(0, 0, 0, 0);
	ofColor maxColor = ofColor(255, 255, 255, 255);
	
	/********************
	********************/
	gui.setup();
	gui.add(LedId.setup("LedId", 0, 0, NUM_LEDS - 1));
	gui.add(color.setup("color", initColor, minColor, maxColor));
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	// All Led on
	ofColor CurrentColor = color;
	for(int i = 0; i < NUM_LEDS; i++){
		set_dataArray(i, CurrentColor);
	}
	
	/*/
	
	// single Led on
	for(int i = 0; i < DMX_SIZE; i++){
		data[i] = 0;
	}
	
	ofColor CurrentColor = color;
	set_dataArray(LedId, CurrentColor);
	//*/
}

//--------------------------------------------------------------
void ofApp::set_dataArray(int id, ofColor CurrentColor){
	switch(Led[id].LedType){
		case LEDTYPE_STAGELIGHT:
			data[Led[id].OdeOffset + 0] = CurrentColor.a;
			data[Led[id].OdeOffset + 1] = CurrentColor.r;
			data[Led[id].OdeOffset + 2] = CurrentColor.g;
			data[Led[id].OdeOffset + 3] = CurrentColor.b;
			
			data[Led[id].OdeOffset + 4] = 0; // w;
			data[Led[id].OdeOffset + 5] = 1; // Strobe. 1-9:open
			
			break;
			
		case LEDTYPE_TAPE:
			data[Led[id].OdeOffset + 0] = CurrentColor.r;
			data[Led[id].OdeOffset + 1] = CurrentColor.g;
			data[Led[id].OdeOffset + 2] = CurrentColor.b;
			
			break;
	}
}

//--------------------------------------------------------------
void ofApp::exit(){
	for(int i = 0; i < DMX_SIZE; i++){
		data[i] = 0;
	}
    artnet.sendDmx(targetIP, data, DMX_SIZE);
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(30);
	
	/********************
	********************/
    // list nodes for sending
    // with subnet / universe
	// artnet.sendDmx("10.0.0.149", 0xf, 0xf, testImage.getPixels(), 512);
    artnet.sendDmx(targetIP, data, DMX_SIZE);
	
	/********************
	********************/
	gui.draw();
	
	/********************
	********************/
	printf("%5.1f\r", ofGetFrameRate());
	fflush(stdout);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
