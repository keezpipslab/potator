#pragma once
#include "ofMain.h"

// grid is a custom 3D
//  object that we've
//  created in this
//  example.
//
// We inherit from ofNode

class spaceship : public ofNode {
	public:
	void customDraw();
	void zetup(string naam);
	void openProject(string naam);
	
	int currentLine;
	ofImage nuImage;
	int camWidth;
	int camHeight;
	unsigned char * 	bigCharTexture;
	ofTexture			bigVideoTexture;
	vector <ofPoint> pts;
	vector <ofPoint> pts2;
	//vector <ofPoint> pts3;
	
	vector <int> texturePts;
	int picHi;
	int growTeller;
	
	int texturePos;
	
};