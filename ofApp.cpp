#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofNoFill();
	ofSetLineWidth(1.5);

	// Fbo Initialize (+ Shadow Gap)
	this->fbo.allocate(ofGetWidth() + 25, ofGetHeight() + 25);

	// Link pixels And pixels_mat
	this->fbo.readToPixels(this->pixels);
	this->pixels_mat = cv::Mat(this->pixels.getHeight(), this->pixels.getWidth(), CV_8UC4, this->pixels.getData());
}

//--------------------------------------------------------------
void ofApp::update() {

	// Make New Ripple
	if (ofGetFrameNum() % 3 == 0) {

		ofPoint point(ofRandom(this->fbo.getWidth()), ofRandom(this->fbo.getHeight()), ofRandom(500, 1000));
		unique_ptr<Ripple> ripple(new Ripple(point));
		this->ripples.push_back(move(ripple));
	}

	// Draw Ripples
	this->fbo.begin();
	ofClear(0);

	for (int i = this->ripples.size() - 1; i >= 0; i--) {

		if (this->ripples[i]->isLife()) {

			this->ripples[i]->update();
			this->ripples[i]->draw();
		}
		else {

			this->ripples.erase(this->ripples.begin() + i);
		}
	}

	this->fbo.end();

	// Copy Fbo To pixels
	this->fbo.readToPixels(this->pixels);

	// Gray
	cv::Mat gray_mat;
	cv::cvtColor(this->pixels_mat, gray_mat, cv::COLOR_RGBA2GRAY);
	for (int y = 0; y < this->pixels_mat.cols; y++) {

		for (int x = 0; x < this->pixels_mat.rows; x++) {

			if (gray_mat.at<unsigned char>(y, x) > 0) {

				this->pixels_mat.at<cv::Vec4b>(y, x) = cv::Vec4b(gray_mat.at<unsigned char>(y, x), gray_mat.at<unsigned char>(y, x), gray_mat.at<unsigned char>(y, x), this->pixels_mat.at<cv::Vec4b>(y, x)[3]);
			}
		}
	}

	// Blur Process
	cv::GaussianBlur(this->pixels_mat, this->pixels_mat, cv::Size(19, 19), 10, 10);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);

	// Draw Shadow
	ofImage draw_image;
	draw_image.setFromPixels(this->pixels);
	draw_image.draw(-5, -5);

	// Draw Fbo Image 
	this->fbo.draw(-25, -25);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}