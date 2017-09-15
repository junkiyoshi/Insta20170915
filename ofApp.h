#pragma once

#include "ofMain.h"
#include "Particle.h"

#include "Leap.h"
#pragma comment(lib, "Leap.lib")

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		
		ofEasyCam cam;
		vector<Particle*> particles;

		float size;

		vector<ofVec3f> points;
		vector<float> radiuses;

		Leap::Controller leap;
		void drawHand(Leap::Hand hand);
		void drawFinger(Leap::Finger finger);
};
