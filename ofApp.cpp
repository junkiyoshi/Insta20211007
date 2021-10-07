#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 20;
	for(int x = radius * 3; x <= ofGetWidth() - radius * 3; x += radius * 2){

		for (int y = radius * 3; y <= ofGetHeight() - radius * 3; y += radius * 2) {

			int deg = ofMap(ofNoise(x * 0.002, y * 0.002, ofGetFrameNum() * 0.01), 0, 1, 0, 360);

			if (deg < 80) { deg = 0; }
			else if (deg < 90) { deg = ofMap(deg, 80, 90, 0, 90); }
			else if (deg < 170) { deg = 90; }
			else if (deg < 180) { deg = ofMap(deg, 170, 180, 90, 180); }
			else if (deg < 260) { deg = 180; }
			else if (deg < 270) { deg = ofMap(deg, 260, 270, 180, 270); }
			else if (deg < 350) { deg = 270; }
			else if (deg < 360) { deg = ofMap(deg, 350, 360, 270, 360); }


			this->draw_MAGATAMA(glm::vec2(x, y), radius * 0.9, 0 + deg, ofColor(239), ofColor(39));
			this->draw_MAGATAMA(glm::vec2(x, y), radius * 0.9, 180 + deg, ofColor(39), ofColor(239));
		}
	}
		
}

//--------------------------------------------------------------
void ofApp::draw_MAGATAMA(glm::vec2 location, float radius, float rotate_deg, ofColor color_1, ofColor color_2) {

	float len = radius * 0.5522;
	float deg = 0;

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(rotate_deg);

	vector<glm::vec2> vertices;
	vector<pair<glm::vec2, glm::vec2>> handle_list;

	vertices.push_back(glm::vec2(0, 0));
	deg = 180;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * 0.5, radius * -0.5));
	deg = 90;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius * -1));
	deg = 0;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len  * sin(deg * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius, 0));
	deg = 270;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos((deg + 180) * DEG_TO_RAD), len * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius));
	deg = 0;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * -0.5, radius * 0.5));
	deg = 90;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	ofSetColor(color_1);
	ofFill();
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}
	ofEndShape();

	ofSetColor(color_2);
	ofBeginShape();
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.2 * cos(deg * DEG_TO_RAD), radius * 0.2 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);

	ofSetColor(ofColor(39));
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}

	ofNextContour(true);
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.2 * cos(deg * DEG_TO_RAD), radius * 0.2 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}