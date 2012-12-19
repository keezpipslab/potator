#include "Spaceship.h"

// grid is a custom 3D
//  object that we've
//  created in this
//  example.

void spaceship::zetup(string naam){
	cout << "\n" <<  "setp";
	camWidth = 720;
	camHeight = 576;
	picHi= 2048;
	nuImage.allocate(camWidth, picHi, OF_IMAGE_COLOR);
	bigCharTexture = new unsigned char[camWidth*picHi*3];
	bigVideoTexture.allocate(camWidth,picHi, GL_RGB);
	growTeller= 0;
	openProject(naam);
	texturePos= 0;
	
}

void spaceship::customDraw(){
	texturePos--;
	if (texturePos<0) texturePos= currentLine;
	/*
	ofPushStyle();

	//give a saturation and lightness
	ofSetColor(255, 100, 100);

	ofDrawGrid(100.0f);

	ofPopStyle();
	 */
	
	//ofBox(100,100,200,100);
	ofSetColor(255,255,255,200);
	if( pts.size() > 0 ){
		
		//bigVideoTexture.getTextureReference().bind();
		bigVideoTexture.bind();
		
		
		//glBegin(GL_QUAD_STRIP);
		glBegin(GL_QUADS);
		int numPts = pts.size();
		int oldPointX;
		int oldPointY;
		int oldPointZ;
		growTeller++;
		int offset =0;
		//int texturePos= 0;
		for(int i = 0; i < numPts-1; i++){
			
			if (pts[i].x > 9999 || pts[i+1].x > 9999){
				//	growTeller=0;
				offset= i;
			}else{
				
				if (i <offset+ growTeller){
					
					
					glTexCoord2f(0,(texturePts[i] + texturePos) % currentLine);
					glVertex3f(pts[i].x,pts[i].y, pts[i].z);
					glTexCoord2f(camWidth,(texturePts[i]+ texturePos) % currentLine);
					glVertex3f(pts2[i].x,pts2[i].y, pts2[i].z);
					glTexCoord2f(camWidth,(texturePts[i+1]+ texturePos) % currentLine);
					glVertex3f(pts2[i+1].x,pts2[i+1].y, pts2[i+1].z);
					glTexCoord2f(0,(texturePts[i+1]+ texturePos) % currentLine);
					glVertex3f(pts[i+1].x,pts[i+1].y, pts[i+1].z);
				}
			}
			
		}
		glEnd();
		
		bigVideoTexture.unbind();
		
	}
	
	
}



void spaceship::openProject(string naam){
	
	//string naam = dir[dirTeller].getBaseName();
	//string strNm= ofToString(naam);
	cout << "nu naam: " << naam << " " << naam.substr(11, naam.length()) << "\n";
	
	
	string filePart = naam.substr(11, naam.length());
	ofBuffer buffer = ofBufferFromFile("/Users/keezpipslab/Desktop/3d/vectordata_" + filePart + ".txt"); // reading into the buffer
	//ofBuffer buffer = ofBufferFromFile("/Users/keezpipslab/Desktop/3d/vectordata_20120606231847.txt"); // reading into the buffer
	string data= buffer.getText(); // let's see what it says
	vector<string> lines = ofSplitString(data, "\n", true, true);
	
	//scultpName = filePart;
	pts.clear();
	pts2.clear();
	texturePts.clear();
	
	int index = 0;
	while (index < lines.size()-2)
	{
		ofPoint temp;
		ofPoint temp2;
		int textemp;
		
		string line = lines[index];
		vector<string> channels = ofSplitString(line, " ");
		
		temp.x = ofToFloat(channels[0]);
		temp.y = ofToFloat(channels[1]);
		temp.z= ofToFloat(channels[2]);
		temp2.x= ofToFloat(channels[3]);
		temp2.y= ofToFloat(channels[4]);
		temp2.z= ofToFloat(channels[5]);
		textemp = ofToInt(channels[6]);
		
		if (temp.x == 0.0 || temp2.x == 0.0) {
			cout << "detected";
		}else {
			pts.push_back(temp);
			pts2.push_back(temp2);
			texturePts.push_back(textemp);
			currentLine= textemp;
			
			
		}
		index++;
		
	}
	
	cout << "loading /Users/keezpipslab/Desktop/3d/img" + filePart + ".png" + "\n";
	
	
	
	nuImage.loadImage("/Users/keezpipslab/Desktop/3d/img" + filePart + ".png");
	unsigned char * pixels2 = nuImage.getPixels();
	
	for (int w= 0; w<camWidth; w++) {
		for (int h= 0; h<picHi; h++) {
			for (int i= 0; i<3; i++) {
				
				bigCharTexture[(camWidth*h+ w)*3 +i]=  pixels2[(camWidth*h+ w)*3 +i];
				
			}
			
			
		}
	}
	
	bigVideoTexture.loadData(bigCharTexture, camWidth,picHi, GL_RGB);
	
	
	
	
	
	
}
