#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
  ofBackground(33);
  
	app.setup("home.roxlu.com", "3344");
  cam.setup(ofGetWidth(), ofGetHeight());
  cam.translate(0.0f, 0.0f, 8.0f);
  ax.setup(10);
}

//--------------------------------------------------------------
void testApp::update(){
	app.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	const float* pm = cam.pm().getPtr();
  const float* vm = cam.vm().getPtr();
  ax.draw(pm, vm);
  app.draw(pm, vm);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	cam.onMouseDragged(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	cam.onMouseDown(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}