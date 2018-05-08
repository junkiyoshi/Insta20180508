#pragma once
#include "ofMain.h"

class Ripple
{
public:

	Ripple();
	Ripple(ofPoint point);
	void update();
	void draw();
	bool isLife();
private:

	ofPoint point;
	float radius;
	float radius_max;
	float radius_span;
	ofColor body_color;
	bool life;
};