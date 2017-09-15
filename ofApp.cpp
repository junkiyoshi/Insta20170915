#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->size = 18;
	bool flg = true;
	for (float y = -ofGetHeight(); y < ofGetHeight(); y += this->size + this->size / 2) {
		for (float x = -ofGetWidth(); x < ofGetWidth(); x += this->size * sqrt(3)) {
			ofVec3f location;
			if (flg) {
				location = ofVec3f(x, y, 0);
			} else {
				location = ofVec3f(ofVec3f(x + (this->size * sqrt(3) / 2), y, 0));
			}

			this->particles.push_back(new Particle(location, this->size, ofColor(255)));
		}
		flg = !flg;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (Particle* p : this->particles) {
		p->update();	

		for(int i = 0; i < this->points.size(); i++){
			if (p->getLocation().distance(this->points[i]) > this->radiuses[i] - 3 && p->getLocation().distance(this->points[i]) < this->radiuses[i] + 3) {
				p->start_rotate();
			}
		}
	}

	for (int i = 0; i < this->radiuses.size(); i++) {
		this->radiuses[i] += 5;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();

	for (Particle* p : this->particles) {
		p->draw();
	}

	ofSetColor(0, 0, 255);
	Leap::Frame frame = leap.frame();
	for (Leap::Hand hand : frame.hands()) {
		this->drawHand(hand);

		if (hand.isRight()) {
			for (Leap::Finger finger : hand.fingers()) {
				if (finger.type() == Leap::Finger::Type::TYPE_INDEX) {
					float x = finger.tipPosition().x + finger.direction().x * finger.length();
					float y = (finger.tipPosition().y - ofGetHeight() / 2) + finger.direction().y * finger.length() - 1;
					float z = finger.tipPosition().z + finger.direction().z * finger.length() - 1;

					ofNoFill();
					ofEllipse(x, y, z, z < 10 ? z : 10, z < 10 ? z : 10);
					ofFill();

					if (z < -1) {
						this->points.push_back(ofVec3f(x, y, 0));
						this->radiuses.push_back(0);
					}

				}
			}
		}
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::drawHand(Leap::Hand hand) {
	Leap::FingerList fingers = hand.fingers();
	for (int j = 0; j < fingers.count(); j++) {
		this->drawFinger(fingers[j]);
	}

	ofPushMatrix();
	ofVec3f palm_point = ofVec3f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 2, hand.palmPosition().z);
	ofTranslate(palm_point);
	ofSphere(10);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFinger(Leap::Finger finger) {

	ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 2, finger.tipPosition().z);
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
	// this->points.push_back(ofVec3f(x - ofGetWidth() / 2, ofGetHeight() / 2 - y, 0));
	// this->radiuses.push_back(0);
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
