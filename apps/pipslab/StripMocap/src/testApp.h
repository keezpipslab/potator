//fixen 
// delayers
// scanvlak
// eentool wissel ?
// brush
#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGamepadHandler.h"
#include "saus.h"
#include "ofxMidi.h"
#include "ofxQTKitVideoGrabber.h"
#include "ofxSyphon.h"
#include <potator/PotatorServerApplication.h>
#include "Spaceship.h"

// listen on port 12345
#define PORT 6000
#define NUM_MSG_STRINGS 20
#define HOST "192.168.0.19"
#define HOSTRGB "192.168.0.19"


struct posquad {
  float x;
  float y;
  float z;
  float qx;
  float qy;
  float qz;
  float qw;
} ;

class testApp : public ofBaseApp , public ofxMidiListener {
 public:

  void setup();
  void update();
  void draw();
		
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);		
  void saveAll();
  void saveAllfat();
  void saveAllXML();
  string getDateName();
  string openProject(string filePart);
  string openProject2();
  string openProject2fat();
  void export2Json();
  void export3Json();

  ofVec3f calculateNormal(ofVec3f p1, ofVec3f p2, ofVec3f p3);
	
  // gamepad
  void axisChanged(ofxGamepadAxisEvent &e);
  void buttonPressed(ofxGamepadButtonEvent &e);
  void buttonReleased(ofxGamepadButtonEvent &e);
  void butterFly(bool onNotOff);
  void bobbelTool(bool onNotOff);
  void sausageTool(bool onNotOff);
  void peelTool(bool onNotOff);
  void zasdTool(bool onNotOff);

  void capturecamTool();
  //analTool
  void doPlaatje();
  void skipToProject();
  void newField();
	
  ofxGamepad gbuttons;
	
  //-----
	
  ofTrueTypeFont font;
  ofxOscReceiver receiver;

  int current_msg_string;
  string msg_strings[NUM_MSG_STRINGS];
  float timers[NUM_MSG_STRINGS];

  int mouseX, mouseY;
  string mouseButtonState;
		
  ofxQTKitVideoGrabber	vidGrabber;
  //ofVideoGrabber 		vidGrabber;

  unsigned char* videoInverted;
  ofTexture videoTexture;
  int 				camWidth;
  int 				camHeight;
	
  unsigned char * 	bigCharTexture;
  ofTexture			bigVideoTexture;
	
  int currentLine;
  bool grabOn;
  int picHi;
	
  ofImage img;
  vector <ofPoint> pts;
  vector <ofPoint> pts2;
  vector <ofPoint> pts3;
	
  vector <int> texturePts;
  vector <int> texturePtsBubbel;
	
  vector <posquad> delayer;
  vector <posquad> delayer38;
  vector <posquad> delayer39;
  vector <posquad> delayer40;
  //vector <posquad> delayer41;


  int delayV;
	
  ofEasyCam cam; // add mouse controls for camera movement
  bool drawOn;
	
  float rigid37x, rigid37y,rigid37z, rigid37qx, rigid37qy, rigid37qz, rigid37qw;
  float rigid38x, rigid38y, rigid38z, rigid38qx, rigid38qy, rigid38qz, rigid38qw;
  float rigid39x, rigid39y, rigid39z, rigid39qx, rigid39qy, rigid39qz, rigid39qw;
  float rigid40x, rigid40y, rigid40z, rigid40qx, rigid40qy, rigid40qz, rigid40qw;
  //float rigid41x, rigid41y, rigid41z, rigid41qx, rigid41qy, rigid41qz, rigid41qw;
	
  bool mocapOn;
	
  ofNode		nullPoint;
  ofNode		rigidB;
	
  ofNode		rigidC;
	
  ofNode		rigidBpoot1;
  ofNode		rigidBpoot2;
  ofNode		middelpunt;
  ofNode		rigidB38;
  ofNode		rigidB39;
  ofNode		rigidB40;
	
  ofNode		kwastL, kwastR;
	
  ofNode		beamCamPoint;
	
  ofQuaternion quadd;
  bool vidBig;
  bool showTexture;
  bool externalCam;
	
  int texturePos;
  bool sausageOn;
  bool flowTexture;
  bool showInterface;
	
	
  ofNode poot[50];
  Saus sausjes[50];
	
  int textTeller;
  int circleDens;
  bool bubbleOn;
  bool butterflyOn;
  bool peelOn;
	
  ofQuaternion rotTemp;
  ofPoint posTemp;
	
  bool normalVideo;
  int offsetX;
  int offsetY;
  int radius360;
	
  float rotateTeller;
  float myFov;
  float myTilt;
  float myPan;
  float myRoll;
	
  ofSoundPlayer		syn;
  ofSoundPlayer		syn2;
  ofSoundPlayer		syn3;
  ofSoundPlayer		syn4;
  ofSoundPlayer mainMusic;
  ofSoundPlayer errorSound;
	
  vector <ofTexture> plakplaatjes;
  vector <posquad> plaklocs;

  ofDirectory dir;
  int dirTeller;
	
  int camMode;
  int camTeller;
	
  string scultpName;
  int growTeller;
  ofImage nuImage;
	
  int sizeOfTexture;
	
  bool texLooping;
  int texLoopStart;
  int texLoopEnd;
	
  bool errorSoundPlaying;
	
  void newMidiMessage(ofxMidiMessage& eventArgs);
	
	
  ofxMidiIn midiIn;
  ofxMidiMessage midiMessage;
	
  int midiChannelIn;
	
  ofImage augmented_cam;
  ofImage bg_video_Off;
  ofImage bg_video_On;
  ofImage camera_draw;
  ofImage interface_On;
  ofImage rotate_cam;
  ofImage stick_draw;
  ofImage trumpet_On;
	
  void doExternalCam();
  void doInternalCam();
	
  bool fadeOn;
	
  bool doVidGrab;
  ofImage grabbedFrame;
	
  float texturePosFloat;
	
  ofxMidiOut midiOut;
  void exit();
	
  //-----osc
  bool sendOSCout;
  ofxOscSender sender;
  ofxOscSender senderRGB;
  void sendOSCommand(string naam, bool onN);
	
  bool singleField;
  ofNode rigidZasd;
  ofNode rigidZasd1;
  ofNode rigidZasd2;
	
  bool zasdOn;
	
  bool realTimeGrab;
  ofImage scannedImage;
  unsigned char * 	sampleTexture;
	
  ofxSyphonServer syphOut;
    
  ofImage sendableImage;
  unsigned char *  sendableTexture;

  PotatorServerApplication server;
  void sendViaRoxlu();
  
  spaceship hal;

	void copyToSpaceShip();
};
