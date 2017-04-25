#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("20170425");
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofBackground(255);

	this->grabed = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();

	//ofTranslate(ofGetWidth() / 2, ofGetHeight(), 0);

	Leap::Frame frame = leap.frame();
	Leap::HandList hands = frame.hands();
	for (int i = 0; i < hands.count(); i++) {
		if (hands[i].isRight()) {

			float r = 0;
			float g = 0;
			float b = ofMap(hands[i].pinchStrength(), 0, 1, 0.0f, 255.0f);

			ofSetColor(r, g, b, 255);

			this->drawHand(hands[i]);
		}
	}

	if (this->tmp_line.size() > 0) {
		ofPath path = ofPath();
		path.setStrokeColor(ofColor(255, 0, 0));
		path.setFilled(false);
		path.setStrokeWidth(3);
		path.moveTo(this->tmp_line[0]);
		for (int i = 1; i < this->tmp_line.size(); i++) {
			path.lineTo(this->tmp_line[i]);
		}
		path.draw();
		path.close();
	}

	for (int i = 0; i < this->lines.size(); i++){
		vector<ofVec3f> history = this->lines[i];

		if (history.size() > 0) {

			ofPath path = ofPath();
			path.setStrokeColor(0);
			path.setFilled(false);
			path.setStrokeWidth(5);
			path.moveTo(history[0]);
			for (int j = 1; j < history.size(); j++) {
				path.lineTo(history[j]);
			}
			path.draw();
			path.close();
		}
	}

	cam.end();
	
}

void ofApp::drawHand(Leap::Hand hand) {

	//Leap::FingerList fingers = hand.fingers();
	//for (int j = 0; j < fingers.count(); j++) {
	//	this->drawFinger(fingers[j]);
	//}

	ofPushMatrix();
	ofVec3f palm_point = ofVec3f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 3, hand.palmPosition().z);
	ofTranslate(palm_point);
	ofSphere(10);
	ofPopMatrix();

	if (hand.isRight() && hand.pinchStrength() > 0.35) {
		this->grabed = true;

		this->tmp_line.push_back(palm_point);
	}
	else if (this->grabed) {
		this->grabed = false;

		this->lines.push_back(this->tmp_line);
		this->tmp_line.clear();
		this->tmp_line.shrink_to_fit();
	}

	cout << "Palm x = " << palm_point.x << " y = " << palm_point.y << " z = " << palm_point.z << endl;
}

void ofApp::drawFinger(Leap::Finger finger) {

	ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 3, finger.tipPosition().z);
	ofPushMatrix();
	ofTranslate(tip_point);
	ofSphere(5);
	ofPopMatrix();

	ofVec3f base_point = ofVec3f(tip_point.x + finger.direction().x * finger.length(),// * -1,
		tip_point.y + finger.direction().y * finger.length() - 1,
		tip_point.z + finger.direction().z * finger.length() - 1);
	ofPushMatrix();
	ofTranslate(base_point);
	ofSphere(5);
	ofPopMatrix();

	ofLine(tip_point, base_point);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	this->tmp_line.clear();
	this->tmp_line.shrink_to_fit();
	this->lines.clear();
	this->lines.shrink_to_fit();
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
