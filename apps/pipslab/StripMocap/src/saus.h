/*
 *  saus.h
 *  firsttexturedraw
 *
 *  Created by keezpips on 5/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _saus
#define _saus

#include "ofMain.h"

class Saus
{
public:
	int id;
	//ofNode pootje;	
	vector <ofPoint> pootwaarde;
	//----
	//----------------------------------------------------------------	
	
	void init(int id) {
		
		
	}
	
	
	void draw() {
		
		
		
	}
	
	
	void addTo(ofPoint p) {
		pootwaarde.push_back(p);
		
	}
	
	void clear(){
		pootwaarde.clear();
	}
	
};


#endif