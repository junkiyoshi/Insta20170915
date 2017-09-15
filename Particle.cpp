#include "Particle.h"

Particle::Particle() : Particle(ofVec3f(0, 0, 0), 10, ofColor(255)) {

}

Particle::Particle(ofVec3f location, float radius, ofColor body_color) {
	this->location = location;
	this->radius = radius;
	this->body_color = body_color;

	this->deg = 0;
	this->tmp_deg = 0;
}

Particle::~Particle() {

}

void Particle::start_rotate()
{
	if (tmp_deg > 0) { return; }
	this->tmp_deg = tmp_deg + 180;
}

void Particle::update() {
	if (this->deg < this->tmp_deg)
	{
		this->deg += 5;
	} else {
		this->tmp_deg = 0;
		this->deg = 0;
	}
}

void Particle::draw() {
	ofPushMatrix();
	ofTranslate(this->location);
	ofRotateY(this->deg);
	//ofNoFill();

	ofSetColor(this->body_color);
	ofBeginShape();
	float x, y;
	for (int i = 0; i < 360; i += 60) {
		x = this->radius * cos(DEG_TO_RAD * (i + 90));
		y = this->radius * sin(DEG_TO_RAD * (i + 90));
		ofVertex(x, y, 0);
	}
	ofEndShape(true);

	ofPopMatrix();
}

ofVec3f Particle::getLocation()
{
	return this->location;
}