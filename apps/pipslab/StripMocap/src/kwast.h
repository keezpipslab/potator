/*
 *  kwast.h
 *  thePotatorFade
 *
 *  Created by keezpips on 9/16/12.
 *  Copyright 2012 PIPS:lab. All rights reserved.
 *
 */


#ifndef _kwast
#define _kwast

#include "ofMain.h"

class Kwast
{
public:
	int id;
	//ofNode pootje;	
	vector <ofPoint> pts;
	vector <ofPoint> pts2;
	//----
	//----------------------------------------------------------------	
	
	void init(int id) {
		
		
	}
	
	
	void draw() {
		
		
		
	}
	
	/*
		if (onNotOff == false){
			butterflyOn= false;
			grabOn= false;
		
			pts.push_back(ofPoint(10000,0,0));
			pts2.push_back(ofPoint(10000,0,0));
		texturePts.push_back(0);
		syn2.stop();
	}else{
		butterflyOn= true;
		grabOn= true;
		syn2.play();
	}
	}
	*/
	void addTo(ofPoint p) {
		pootwaarde.push_back(p);
		
	}
	
	void clear(){
		pootwaarde.clear();
	}
	
};


#endif