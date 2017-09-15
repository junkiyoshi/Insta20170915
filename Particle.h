#pragma once

#include "ofMain.h"

class Particle {
public:
	Particle();
	Particle(ofVec3f location, float radius, ofColor c);
	~Particle();

	void start_rotate();
	void update();
	void draw();

	ofVec3f getLocation();

private:
	float radius;
	float deg, tmp_deg;
	ofVec3f location;
	ofColor body_color;
};