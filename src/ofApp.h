#pragma once

#include "ofMain.h"
#include "ofxZmq.h"
#include "ofxKinectV2.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		ofxZmqPublisher videopublisher;

		ofxKinectV2 kinect;

		ofTexture texDepth;


		string serial = "502577241942";
		string port = "13000";
		vector<string> keys;
		int cloudDensity = 3;
	

};
