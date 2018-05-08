#include "Ripple.h"

Ripple::Ripple() : Ripple(ofPoint()) {

}

Ripple::Ripple(ofPoint point) {

	this->point = point;
	this->radius = 1;
	this->radius_max = point.z / 10;
	this->body_color.setHsb(ofRandom(255), 255, 255);
	this->life = true;
}

void Ripple::update() {

	if (this->life == false) {

		return;
	}

	if (this->point.z > 0) {

		this->point -= ofPoint(0, 0, 30);
		return;
	}

	if (this->radius > this->radius_max) {

		this->life = false;
		return;
	}
	else {

		this->radius += 1;
	}
}

void Ripple::draw() {

	ofPushMatrix();
	ofTranslate(this->point);

	if (this->point.z > 0) {

		ofSetColor(this->body_color);
		ofDrawLine(ofPoint(), ofPoint(0, 0, 30));
	}
	else {

		ofSetColor(this->body_color, ofMap(this->radius, 1, this->radius_max, 255, 10));
		ofBeginShape();
		for (int deg = 0; deg < 360; deg++) {

			ofVertex(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD));
		}
		ofEndShape(true);
	}

	ofPopMatrix();
}

bool Ripple::isLife() {

	return this->life;
}
