#include "ofApp.h"
#include "ofxArgParser.h"

//--------------------------------------------------------------
void ofApp::setup() {
	keys = ofxArgParser::allKeys();
	for (int i = 0; i < keys.size(); i++) {
		cout << "key: " << keys[i] << ", value: " << ofxArgParser::getValue(keys[i]) << endl;
		if (keys[i] == "serial") {
			serial = ofxArgParser::getValue(keys[i]);
		}
		else if (keys[i] == "port") {
			port = ofxArgParser::getValue(keys[i]);

		}
		else if (keys[i] == "density") {
			cloudDensity = ofToInt(ofxArgParser::getValue(keys[i]));
		}
		else if (keys[i] == "position") {
			string pos = ofxArgParser::getValue(keys[i]);
			std::vector<string> xy = ofSplitString(pos, ",");
			ofSetWindowPosition(ofToInt(xy[0]), ofToInt(xy[1]));
		}
	}


	ofSetFrameRate(60);
	videopublisher.bind("tcp://*:" + port);
	videopublisher.setHighWaterMark(1);
	videopublisher.setSendHighWaterMark(1);

	//see how many devices we have.
	ofxKinectV2 tmp;
	std::vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();


	ofxKinectV2::Settings ksettings;
	ksettings.enableRGB = false;
	ksettings.enableRGBRegistration = false;
	ksettings.enableIR = false;
	// use enableDepthRegistration if you would like to use getWorldCoordinateAt
	ksettings.enableDepthRegistration = true;
	ksettings.config.MinDepth = 0.5;
	ksettings.config.MaxDepth = 8.0;

	// Note you don't have to use ofxKinectV2 as a shared pointer, but if you
	// want to have it in a vector ( ie: for multuple ) it needs to be.
	for (int d = 0; d < deviceList.size(); d++) {
		if (deviceList[d].serial == serial) {
			kinect.open(deviceList[d].serial, ksettings);
		}
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	
		kinect.update();

		if (kinect.isFrameNew())
		{
			
			if (kinect.isDepthEnabled()) texDepth.loadData(kinect.getDepthPixels());
			
			
			ofBuffer depthData;

	
			for (std::size_t x = 0; x < texDepth.getWidth(); x++)
			{
				for (std::size_t y = 0; y < texDepth.getHeight(); y++)
				{
					if( x%cloudDensity ==0 && y%cloudDensity ==0){
						ofVec3f worldPos = kinect.getWorldCoordinateAt(x, y);
						char buffer[3 * sizeof(float)];
						float *f_buf = (float*)buffer;
						f_buf[0] = worldPos.x;
						f_buf[1] = worldPos.y;
						f_buf[2] = worldPos.z;
						depthData.append(buffer, 3 * sizeof(float));
						//int i = y * texDepth[d].getHeight() + x;
						//mesh.setVertex(i, ofVec3f(worldPos.x, worldPos.y, worldPos.z));
					}
				}
			}
			videopublisher.send(depthData, (512/2) * (424/2) * 3 * sizeof(float));
		}
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(255);
		if (texDepth.isAllocated()) {
			texDepth.draw(0, 0);
		}
		ofSetColor(0, 255, 0);
		for (int i = 0; i < keys.size(); i++){
			ofDrawBitmapStringHighlight(keys[i] + ": " + ofxArgParser::getValue(keys[i]), 10, ofGetHeight() - 20 - 20 * i);
		}
		ofDrawBitmapStringHighlight(ofToString((int)ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
