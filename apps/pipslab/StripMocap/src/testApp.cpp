#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  vidBig = true;
	
  camWidth 		= 720;	// try to grab at this size. 
  camHeight 		= 576;
	
  singleField= true;
	
  if (singleField){
    picHi= 2048;
    bigCharTexture = new unsigned char[camWidth*picHi*3];
    bigVideoTexture.allocate(camWidth,picHi, GL_RGB);
    dir.allowExt("txt");
    dir.listDir("/Users/keezpips/Desktop/3d/");
		
    nuImage.allocate(camWidth, picHi, OF_IMAGE_COLOR);
	
  }else{
		
    picHi= 2048;
    bigCharTexture = new unsigned char[6*camWidth*picHi*3];
    bigVideoTexture.allocate(6*camWidth,picHi, GL_RGB);
    dir.allowExt("txt");
    dir.listDir("/Users/keezpips/Desktop/3dfat/");
		
    nuImage.allocate(camWidth * 6, picHi, OF_IMAGE_COLOR);
  }		
	
  sampleTexture = new unsigned char[camWidth*3];
  /*     ouwe videoGrabber
         vidGrabber.setVerbose(true);
         vidGrabber.initGrabber(camWidth,camHeight);
  */
	
  // nieuw
  vidGrabber.listVideoDevices();											// all list... methods also return a vector<string> of devices/codecs
  vidGrabber.listAudioDevices();
	
  //vidGrabber.setVideoDeviceID("Built-in iSight");							// can set deviceID's by string
  vidGrabber.setAudioDeviceID("Built-in Microphone");
	
  vidGrabber.listVideoCodecs();
  vidGrabber.listAudioCodecs();
	
  vidGrabber.setVideoCodec("QTCompressionOptions240SizeH264Video");		// default is JPEG
  vidGrabber.setAudioCodec("QTCompressionOptionsVoiceQualityAACAudio");	// default is High Quality AAC
	
  vidGrabber.setUseAudio(false);						// audio recording defaults to false so you need to set this
  // true if you want audio with your video. Need to do it BEFORE
  // initializing the grabber.
	
  vidGrabber.initGrabber(camWidth, camHeight);
	
  vidGrabber.setVerbose(true);
  //	
  vidGrabber.setDeviceID(1);
  //	
  //	vidGrabber.initGrabber(camWidth,camHeight);
  vidGrabber.initRecording();							// call this to init recording output 
	
  ////////////////// end nieuw video
	
	
	
	
	
	
  grabOn= false;
  currentLine = 0;
	
  //  stripgedeelte
  ofEnableArbTex(); //already on by default
  //img.loadImage("earth.jpg");
	
  drawOn= false;
  glEnable(GL_DEPTH_TEST);
  //cam.setPosition(0, 150, 0);
  cam.setDistance(1);
  cam.setParent(rigidB);
	
  cam.setPosition(0, 0, 0);
	
  //	cam.setDistance(0);
  //rigidBpoot1.setPosition(ofVec3f(-80, 0, -100));
  //rigidBpoot2.setPosition(ofVec3f(80, 0, -100));
  rigidBpoot1.setPosition(ofVec3f(-40, 0, -100));
  rigidBpoot2.setPosition(ofVec3f(40, 0, -100));
  rigidBpoot1.setParent(rigidC);
  rigidBpoot2.setParent(rigidC);
  //rigidBpoot1.setParent(rigidB);
  //rigidBpoot2.setParent(rigidB);

	
  ofSetVerticalSync(true);
  ofSetFrameRate(30);
	
	
  middelpunt.setPosition(ofVec3f(0, 1200,0));
	
  cout << "listening for osc messages on port " << PORT << "\n";
  receiver.setup( PORT );
	
  mocapOn= true;
	
  // gamepad stuff //
  ofxGamepadHandler::get()->enableHotplug();
	
  //CHECK IF THERE EVEN IS A GAMEPAD CONNECTED
  if(ofxGamepadHandler::get()->getNumPads()>0){
    ofxGamepad* pad = ofxGamepadHandler::get()->getGamepad(0);
    ofAddListener(pad->onAxisChanged, this, &testApp::axisChanged);
    ofAddListener(pad->onButtonPressed, this, &testApp::buttonPressed);
    ofAddListener(pad->onButtonReleased, this, &testApp::buttonReleased);
  }
	
  //CHECK IF THERE EVEN IS A GAMEPAD CONNECTED
  if(ofxGamepadHandler::get()->getNumPads()>1){
    ofxGamepad* pad2 = ofxGamepadHandler::get()->getGamepad(1);
    ofAddListener(pad2->onAxisChanged, this, &testApp::axisChanged);
    ofAddListener(pad2->onButtonPressed, this, &testApp::buttonPressed);
    ofAddListener(pad2->onButtonReleased, this, &testApp::buttonReleased);
  }
	
  delayV= 3;
  externalCam = true;
	
  flowTexture= false;
  showInterface= true;
  butterflyOn= false;
  sausageOn= false;
  bubbleOn= false;
  peelOn= false;
  zasdOn= false;
	
  circleDens= 50;
  for(int i=0;i<circleDens;i++){
    poot[i].setPosition(ofVec3f(sin(i* TWO_PI/ (float)circleDens)* 60,0, -cos(i* TWO_PI/(float)circleDens)* 60));
    poot[i].setParent(rigidB38);
    //sausjes[i].init();
  }
	
  normalVideo= true;
  radius360= 200;
  offsetX= 360;
  offsetY= 288;
  currentLine =1;
  rotateTeller= 0;
	
  //cam.setFov(90.0);
  myFov = 30;
  //myOffset = 0;
  myTilt= 0;
  myPan= 0;
  myPan= 0;
  showTexture= false;
	
  syn.loadSound("sounds/fadeo.aiff");
  syn.setLoop(true);
  syn3.loadSound("sounds/chant.aiff");
  syn3.setLoop(true);
  syn2.loadSound("sounds/rumblesample.aif");
  syn2.setLoop(true);
  syn4.loadSound("sounds/lichtstok.aiff");
  syn4.setLoop(true);
  mainMusic.loadSound("sounds/lichtstok.aiff");
  errorSound.loadSound("sounds/licht.aiff");
	
		
  //dir.allowExt("txt");
  //dir.listDir("/Users/keezpips/Desktop/3d/");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  dirTeller=0;
  camMode = 1;
  camTeller=0;
	
  scultpName = "Untitled";
	
	
  //nuImage.clear();
  sizeOfTexture= 0;
	
  cam.setFov(myFov);
	
	
	
  texLooping =false;
  texLoopStart =0;
  texLoopEnd = 1;
	
  errorSoundPlaying = false;
	
  beamCamPoint.setPosition(ofVec3f(0, 0, -4000));
  beamCamPoint.pan(180);
  beamCamPoint.setParent(rigidB40);

  // midi part //---------
  // print input ports to console
  midiIn.listPorts(); // via instance
  //ofxMidiIn::listPorts(); // via static as well
	
  // open port by number (you may need to change this)
  midiIn.openPort(1);
  //midiIn.openPort("IAC Pure Data In");	// by name
  //midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
  // don't ignore sysex, timing, & active sense messages,
  // these are ignored by default
  midiIn.ignoreTypes(true, true, true);
	
  // add testApp as a listener
  midiIn.addListener(this);
	
  // print received messages to the console
  midiIn.setVerbose(true);
	
  //midiChannelIn= XML.getValue("MIDI:MAINCHANNEL",8);
  midiChannelIn= 1;
  //
	
  augmented_cam.loadImage("icons/augmented_cam.png"); //augmented_cam.png
  bg_video_Off.loadImage("icons/bg_video_Off.png"); //augmented_cam.png
  bg_video_On.loadImage("icons/bg_video_On.png"); //augmented_cam.png
  camera_draw.loadImage("icons/camera_draw.png"); //augmented_cam.png
  interface_On.loadImage("icons/interface_On.png"); //augmented_cam.png
  rotate_cam.loadImage("icons/rotate_cam.png"); //augmented_cam.png
  stick_draw.loadImage("icons/stick_draw.png"); //augmented_cam.png
  trumpet_On.loadImage("icons/trumpet_On.png"); //augmented_cam.png
	
  fadeOn= false;
  camMode= 0;
  doVidGrab= true;
  texturePosFloat= 0;
	
	
  midiOut.listPorts(); // via static too
	
  // connect
  midiOut.openPort(0);	// by number
  //midiOut.openPort("IAC Driver Pure Data In");	// by name
  //midiOut.openVirtualPort("ofxMidiOut");		// open a virtual port
	
	
  //----
  sender.setup(HOST, PORT);
  sendOSCout = true;
	
	
	
  rigidZasd1.setPosition(ofVec3f(-100, 0, 110));
  rigidZasd2.setPosition(ofVec3f(100, 0, 110));
  rigidZasd1.setParent(rigidZasd);
  rigidZasd2.setParent(rigidZasd);
	
  realTimeGrab = true;
  scannedImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    
   
    
  sendableImage.allocate(85, 1, OF_IMAGE_COLOR);
  sendableTexture = new unsigned char[85*3];

  // @roxlu
  server.streaming_potator.setTextureSize(512, 2048);
  server.setup("3344");
}


//--------------------------------------------------------------
void testApp::update(){
  //  server.update();
	
  // check for waiting messages
  while( receiver.hasWaitingMessages() )
    {
      // get the next message
      ofxOscMessage m;
      receiver.getNextMessage( &m );
      if (sendOSCout){sender.sendMessage(m);}
		
		
		
		
      // check for mouse moved message
      if ( m.getAddress() == "/rigidbody/65537" )
        {
          if (m.getArgAsFloat( 0 ) ==0 && m.getArgAsFloat( 1 ) ==0){
            //	if (!errorSoundPlaying){
            //errorSound.play();
            errorSoundPlaying= true;
          }else{
            if (errorSoundPlaying) {
              //errorSound.stop();
              errorSoundPlaying= false;
            }
			

            // both the arguments are int32's
            //rigid37x, rigid37y, rigid37qx, rigid37qy, rigid37qz, rigid37qw
            rigid37x = m.getArgAsFloat( 0 );
            rigid37y = m.getArgAsFloat( 1 );
            rigid37z = m.getArgAsFloat( 2 );
            rigid37qx = m.getArgAsFloat( 3 );
            rigid37qy = m.getArgAsFloat( 4 );
            rigid37qz = m.getArgAsFloat( 5 );
            rigid37qw = m.getArgAsFloat( 6 );
            //delayV= 0;
            delayV= 3;	
			
            if (delayV ==0){
              if (!externalCam){
				
                rigidB.setOrientation(ofQuaternion(rigid37qx,-rigid37qy,rigid37qz,rigid37qw));
                rigidB.setPosition(ofPoint(-rigid37x, rigid37y, -rigid37z));
					
                rigidC.setOrientation(ofQuaternion(rigid37qx,-rigid37qy,rigid37qz,rigid37qw));
                rigidC.setPosition(ofPoint(-rigid37x, rigid37y, -rigid37z));	
              }
            }else{
				
              posquad nu;
              nu.x=rigid37x; nu.y=rigid37y; nu.z=rigid37z; nu.qx=rigid37qx; nu.qy=rigid37qy; nu.qz=rigid37qz; nu.qw=rigid37qw;
              delayer.push_back(nu); 
              if ( delayer.size() > delayV){
                posquad plee= delayer[delayer.size()-(1 + delayV)];
                if (!externalCam){
                  rigidB.setOrientation(ofQuaternion(plee.qx,-plee.qy,plee.qz,plee.qw));
                  rigidB.setPosition(ofPoint(-plee.x,plee.y,-plee.z));
                }
					
                rigidC.setOrientation(ofQuaternion(rigid37qx,-rigid37qy,rigid37qz,rigid37qw));
                rigidC.setPosition(ofPoint(-rigid37x, rigid37y, -rigid37z));	
					
              }
            }
			
          } // haakjes van error test	
			
        }
		
		
		
      // check for mouse moved message
      if ( m.getAddress() == "/rigidbody/65538" ){
			
        if (m.getArgAsFloat( 0 ) ==0 && m.getArgAsFloat( 1 ) ==0){
          //	if (!errorSoundPlaying){
          //errorSound.play();
          //errorSoundPlaying= true;
        }else{
          //if (errorSoundPlaying) {
          //					errorSound.stop();
          //					errorSoundPlaying= false;
          //				}
			
			
          // both the arguments are int32's
          //rigid37x, rigid37y, rigid37qx, rigid37qy, rigid37qz, rigid37qw
          rigid38x = m.getArgAsFloat( 0 );
          rigid38y = m.getArgAsFloat( 1 );
          rigid38z = m.getArgAsFloat( 2 );
          rigid38qx = m.getArgAsFloat( 3 );
          rigid38qy = m.getArgAsFloat( 4 );
          rigid38qz = m.getArgAsFloat( 5 );
          rigid38qw = m.getArgAsFloat( 6 );
          //delayV= 0;
          delayV= 3;	
			
          if (delayV ==0){
            rigidB38.setOrientation(ofQuaternion(rigid38qx,-rigid38qy,rigid38qz,rigid38qw));
            rigidB38.setPosition(ofPoint(-rigid38x, rigid38y, -rigid38z));
          }else{
				
            posquad nu;
            nu.x=rigid38x; nu.y=rigid38y; nu.z=rigid38z; nu.qx=rigid38qx; nu.qy=rigid38qy; nu.qz=rigid38qz; nu.qw=rigid38qw;
            delayer38.push_back(nu); 
            if ( delayer38.size() > delayV){
              posquad plee= delayer38[delayer38.size()-(1 + delayV)];
              rigidB38.setOrientation(ofQuaternion(plee.qx,-plee.qy,plee.qz,plee.qw));
              rigidB38.setPosition(ofPoint(-plee.x,plee.y,-plee.z));
            }
          }
			
        }
			
      }
      // check for mouse moved message
      if ( m.getAddress() == "/rigidbody/65539" ){
			
			
			
        if (m.getArgAsFloat( 0 ) ==0 && m.getArgAsFloat( 1 ) ==0){
          //	if (!errorSoundPlaying){
          //errorSound.play();
          //	errorSoundPlaying= true;
        }else{
          //if (errorSoundPlaying) {
          //					errorSound.stop();
          //					errorSoundPlaying= false;
          //				}
				
				
          // both the arguments are int32's
          //rigid37x, rigid37y, rigid37qx, rigid37qy, rigid37qz, rigid37qw
          rigid39x = m.getArgAsFloat( 0 );
          rigid39y = m.getArgAsFloat( 1 );
          rigid39z = m.getArgAsFloat( 2 );
          rigid39qx = m.getArgAsFloat( 3 );
          rigid39qy = m.getArgAsFloat( 4 );
          rigid39qz = m.getArgAsFloat( 5 );
          rigid39qw = m.getArgAsFloat( 6 );
          //delayV= 0;
          delayV= 3;	
			
          if (delayV ==0){
            rigidB39.setOrientation(ofQuaternion(rigid39qx,-rigid39qy,rigid39qz,rigid39qw));
            rigidB39.setPosition(ofPoint(-rigid39x, rigid39y, -rigid39z));
          }else{
				
            posquad nu;
            nu.x=rigid39x; nu.y=rigid39y; nu.z=rigid39z; nu.qx=rigid39qx; nu.qy=rigid39qy; nu.qz=rigid39qz; nu.qw=rigid39qw;
            delayer39.push_back(nu); 
            if ( delayer39.size() > delayV){
              posquad plee= delayer39[delayer39.size()-(1 + delayV)];
              rigidB39.setOrientation(ofQuaternion(plee.qx,-plee.qy,plee.qz,plee.qw));
              rigidB39.setPosition(ofPoint(-plee.x,plee.y,-plee.z));
            }
          }
			
			
			
        }

      }
		
      if ( m.getAddress() == "/rigidbody/65541" ){
        if (m.getArgAsFloat( 0 ) ==0 && m.getArgAsFloat( 1 ) ==0){
          //	if (!errorSoundPlaying){
          //errorSound.play();
          //	errorSoundPlaying= true;
        }else{
          float rigid41x, rigid41y, rigid41z, rigid41qx, rigid41qy, rigid41qz, rigid41qw;

          rigid41x = m.getArgAsFloat( 0 );
          rigid41y = m.getArgAsFloat( 1 );
          rigid41z = m.getArgAsFloat( 2 );
          rigid41qx = m.getArgAsFloat( 3 );
          rigid41qy = m.getArgAsFloat( 4 );
          rigid41qz = m.getArgAsFloat( 5 );
          rigid41qw = m.getArgAsFloat( 6 );
				
          rigidZasd.setOrientation(ofQuaternion(rigid41qx,-rigid41qy,rigid41qz,rigid41qw));
          rigidZasd.setPosition(ofPoint(-rigid41x, rigid41y, -rigid41z));
        }
      }
      /*
			
        if (m.getArgAsFloat( 0 ) ==0 && m.getArgAsFloat( 1 ) ==0){
        //	if (!errorSoundPlaying){
        //errorSound.play();
        //	errorSoundPlaying= true;
        }else{
        //if (errorSoundPlaying) {
        //					errorSound.stop();
        //					errorSoundPlaying= false;
        //				}
				
				
        // both the arguments are int32's
        //rigid37x, rigid37y, rigid37qx, rigid37qy, rigid37qz, rigid37qw
        rigid41x = m.getArgAsFloat( 0 );
        rigid41y = m.getArgAsFloat( 1 );
        rigid41z = m.getArgAsFloat( 2 );
        rigid41qx = m.getArgAsFloat( 3 );
        rigid41qy = m.getArgAsFloat( 4 );
        rigid41qz = m.getArgAsFloat( 5 );
        rigid41qw = m.getArgAsFloat( 6 );
        //delayV= 0;
        delayV= 3;	
				
        if (delayV ==0){
        rigidZasd.setOrientation(ofQuaternion(rigid41qx,-rigid41qy,rigid41qz,rigid41qw));
        rigidZasd.setPosition(ofPoint(-rigid41x, rigid41y, -rigid41z));
        }else{
					
        posquad nu;
        nu.x=rigid41x; nu.y=rigid41y; nu.z=rigid41z; nu.qx=rigid41qx; nu.qy=rigid41qy; nu.qz=rigid41qz; nu.qw=rigid41qw;
        delayer41.push_back(nu); 
        if ( delayer41.size() > delayV){
        posquad plee= delayer41[delayer41.size()-(1 + delayV)];
        rigidZasd.setOrientation(ofQuaternion(plee.qx,-plee.qy,plee.qz,plee.qw));
        rigidZasd.setPosition(ofPoint(-plee.x,plee.y,-plee.z));
        }
        }
				
				
				
        }
			
        }
      */
		
      // check for mouse moved message
      if ( m.getAddress() == "/rigidbody/65542" ){
			
			
			
        if (m.getArgAsFloat( 0 ) ==0 && m.getArgAsFloat( 1 ) ==0){
          //	if (!errorSoundPlaying){
          //errorSound.play();
          //	errorSoundPlaying= true;
        }else{
          //if (errorSoundPlaying) {
          //					errorSound.stop();
          //					errorSoundPlaying= false;
          //				}
				
				
          // both the arguments are int32's
          //rigid37x, rigid37y, rigid37qx, rigid37qy, rigid37qz, rigid37qw
          rigid40x = m.getArgAsFloat( 0 );
          rigid40y = m.getArgAsFloat( 1 );
          rigid40z = m.getArgAsFloat( 2 );
          rigid40qx = m.getArgAsFloat( 3 );
          rigid40qy = m.getArgAsFloat( 4 );
          rigid40qz = m.getArgAsFloat( 5 );
          rigid40qw = m.getArgAsFloat( 6 );
          //delayV= 0;
          delayV= 0;	
				
          if (delayV ==0){
            rigidB40.setOrientation(ofQuaternion(rigid40qx,-rigid40qy,rigid40qz,rigid40qw));
            rigidB40.setPosition(ofPoint(-rigid40x, rigid40y, -rigid40z));
          }else{
					
            posquad nu;
            nu.x=rigid40x; nu.y=rigid40y; nu.z=rigid40z; nu.qx=rigid40qx; nu.qy=rigid40qy; nu.qz=rigid40qz; nu.qw=rigid40qw;
            delayer40.push_back(nu); 
            if ( delayer40.size() > delayV){
              posquad plee= delayer40[delayer40.size()-(1 + delayV)];
              rigidB40.setOrientation(ofQuaternion(plee.qx,-plee.qy,plee.qz,plee.qw));
              rigidB40.setPosition(ofPoint(-plee.x,plee.y,-plee.z));
            }
          }
				
				
				
        }
			
      }
		
		
    }
	
  if (externalCam){
    switch (camMode) {
      case 1: // rotating
        rotateTeller += 0.011;
        if (rotateTeller>TWO_PI) {rotateTeller= 0;}
        rigidB.setGlobalPosition(ofVec3f(sin(rotateTeller)* 3000, 1200.0, -cos(rotateTeller)* 3000));
        rigidB.setOrientation(ofVec3f(0, -rotateTeller * ( 360.0/ TWO_PI) + 180, 0));
        //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
        //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
				
        break;
      case 2:
        // moving with path
        if( pts.size() > 0 ){
          camTeller++;
          if (camTeller > pts.size()-2) camTeller= 0;
					
					
          rotateTeller += 0.01;
          if (rotateTeller>TWO_PI) {rotateTeller= 0;}
          rigidB.setGlobalPosition(ofVec3f(pts[camTeller].x,pts[camTeller].y, pts[camTeller].z));
        }
        rigidB.setOrientation(ofVec3f(0, -rotateTeller * ( 360.0/ TWO_PI) + 180, 0));
        //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
        //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
				
        break;
      case 3:
        rigidB.setGlobalPosition(beamCamPoint.getGlobalPosition());
        rigidB.setOrientation(beamCamPoint.getGlobalOrientation());
        //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
        //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
				
        break;
      case 4:
        rigidB.setGlobalPosition(rigidB40.getGlobalPosition());
        rigidB.setOrientation(rigidB40.getGlobalOrientation());
        //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
        //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
				
        break;
      case 5:
        rigidB.setGlobalPosition(beamCamPoint.getGlobalPosition());
        rigidB.setOrientation(beamCamPoint.getGlobalOrientation());
        rigidB.roll(180);
        //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
        //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
				
        break;
      default:
        //rotateTeller += 0.01;
        if (rotateTeller>TWO_PI) {rotateTeller= 0;}
        rigidB.setGlobalPosition(ofVec3f(sin(rotateTeller)* 3000, 1200.0, -cos(rotateTeller)* 3000));
        rigidB.setOrientation(ofVec3f(0, -rotateTeller * ( 360.0/ TWO_PI) + 180, 0));
        //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
        //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
				
        break;
    } 
    //rotateTeller += 0.01;
    //		if (rotateTeller>TWO_PI) {rotateTeller= 0;}
    //		rigidB.setGlobalPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
    //		rigidB.setOrientation(ofVec3f(0, -rotateTeller * ( 360.0/ TWO_PI) + 180, 0));
    //rigidB.setPosition(ofVec3f(sin(rotateTeller)* 3000, 1500.0, -cos(rotateTeller)* 3000));
    //cam.lookAt(middelpunt, ofVec3f(0, -1, 0));
		
  }
	
  //rigidB.setPosition(ofPoint(rigid38x, rigid38y,rigid38z));
	
  ofBackground(0,0,0);
  //ofBackground(50,50,50);
	
  ///vidGrabber.grabFrame();   oud
  vidGrabber.update();
	 
	
	
	
  if (vidGrabber.isFrameNew()){
		
    int currentLineV;
    int currentLineH;
    int totalPixels = camWidth*camHeight*3;
    unsigned char * pixels = vidGrabber.getPixels();
    if (realTimeGrab){
			
    }else{
			
    }
    if (grabOn){
			
			
      //cout << currentLine << " " << currentLineV << " " << currentLineH << "\n";
      if (doVidGrab){
        currentLine++;
        if (singleField){
          if (currentLine >= picHi) {
            currentLine = 1;
            sizeOfTexture= picHi;
            saveAll();
          }else {
            sizeOfTexture= currentLine;
          }
					
        }else {
          currentLineV= currentLine % (picHi); //0-2048
          currentLineH= int(currentLine / (picHi));  // 0- 4
					
					
					
          if (currentLine >= picHi*6) {
            currentLine = 1;
            sizeOfTexture= picHi;
            saveAllfat();
          }else {
            sizeOfTexture= currentLine;
          }
        }

					
					
					
					
					
        if (normalVideo){
				
          for (int i = 0; i < (camWidth * 3); i++){
            int nuSmall = ((camHeight/ 2) * camWidth) * 3 + i;
            //int nuBig= (currentLineV * (camWidth * 10) + currentLineH * camWidth) * 3 +i;
            int nuBig;
            if (singleField){
              nuBig= currentLine * camWidth * 3 +i;
            }else {
              nuBig= (currentLineV * camWidth * 6 + currentLineH * camWidth) * 3 +i;
						
            }
            //
				
            bigCharTexture[nuBig] = pixels[nuSmall];
					
            if (realTimeGrab == false) {
              bigCharTexture[nuBig] = sampleTexture[i];

            }else {
              sampleTexture[i] =pixels[nuSmall];
            }

					
          }
        }else {
          for (int i = 0; i < (camWidth); i++){
            float nux=offsetX+ sin(TWO_PI*(float(i)/camWidth))* radius360;
            float nuy=offsetY -cos(TWO_PI*(float(i)/camWidth))* radius360;
            int nuSmall = ((int)nux+ (int)nuy * camWidth) * 3;
            //int nuBig= (currentLineV * (camWidth * 10) + currentLineH * camWidth) * 3 +i;
            for (int j = 0; j < 3; j++){

              int nuBig= (currentLine * camWidth +i)* 3 +j ;
              bigCharTexture[nuBig] = pixels[nuSmall+j];
            }
          }
        }
			
			
        if (singleField){
          bigVideoTexture.loadData(bigCharTexture, camWidth,picHi, GL_RGB);
        }else {
          bigVideoTexture.loadData(bigCharTexture, camWidth*6,picHi, GL_RGB);
					
        }
                
                
        ///////// nieuw //
        int deler = (camWidth/ 85);
        // cout << deler << " ";
        for (int i=0; i<85; i++) {
          //     cout << i << " ";
          int tot1 = 0;
          int tot2 = 0;
          int tot3 = 0;
          for (int j=0; j< deler; j++) {
            //  for (int k=0; k<3; k++) {
            tot1 += pixels[((camHeight/ 2) * camWidth  +    i*(int)(camWidth/ 85)+j) *3];
            tot2 += pixels[((camHeight/ 2) * camWidth  +    i*(int)(camWidth/ 85)+j) *3 +1];
            tot3 += pixels[((camHeight/ 2) * camWidth  +    i*(int)(camWidth/ 85)+j) *3 +2];
            //  }
          }
          // cout << "tot1:" << tot1 << " " << tot2 << " " << tot3 << " ";
                    
          char nuTot1= tot1/ deler;
          char nuTot2= tot2/ deler;
          char nuTot3= tot3/ deler;
                    
          // cout << "tot1:" << nuTot1 << " " << nuTot2 << " " << nuTot3 << " ";
          sendableTexture[i*3]= nuTot1;
          sendableTexture[i*3+1]= nuTot2;
          sendableTexture[i*3+2]= nuTot3;
          
        }
        sendableImage.setFromPixels(sendableTexture, 85, 1, OF_IMAGE_COLOR);

        
                
				
				
      }
    }
  }
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetHexColor(0xffffff);
  if (showInterface){
		
    sendableImage.draw(0,0,85*10 ,10);
        
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
		
		
    ofDrawBitmapString("PIPS:lab Potator tool v0.5", 200, 740);
    ofDrawBitmapString("fov:" + ofToString(myFov) + " tilt:" + ofToString(myTilt) + " pan:" + ofToString(myPan) + " roll:" + ofToString(myRoll), 200, 760);
    ofDrawBitmapString("cr:" + ofToString(currentLine) + " tP:" + ofToString(texturePos ) + " teller:" + ofToString(dirTeller ) , 200, 780);
    ofDrawBitmapString("camMode:" + ofToString(camMode) + " realTimeGrab:" + ofToString(realTimeGrab) , 200, 720);
  }

  if (showInterface) vidGrabber.draw(20,20,160,120);
  ofEnableAlphaBlending();
  ofSetColor(255,255,255,200);

	
  if (showTexture){bigVideoTexture.draw(20,20+ camHeight,camWidth,picHi);}
	
  //  stripgedeelte
  float cx = img.width/2; //center of image
  float cy = img.height/2;    
	
	
	
  cam.begin();
	 
  ofPushMatrix();         // push the current coordinate position
	
  // ofRotateX(rigidB39.getGlobalOrientation().getEuler().y);          // change the coordinate system
  //  ofTranslate(rigidB39.getPosition());
   	
	
  if( pts3.size() > 0 ){
    glLineWidth(5.0);
    ofSetColor(200,200,200,200);
    int numPts = pts3.size();
    int oldPointX;
    int oldPointY;
    int oldPointZ;
		
    glBegin(GL_LINES);
    for(int i = 0; i < numPts-1; i++){
      if (pts3[i].x > 9999 || pts3[i+1].x > 9999){
      }else {
        glVertex3f(pts3[i].x,pts3[i].y, pts3[i].z);
        glVertex3f(pts3[i+1].x,pts3[i+1].y, pts3[i+1].z);
      }

      //ofSphere(pts3[i].x, pts3[i].y, pts3[i].z, 40);
    }
    glEnd();

		
  }
	
  ofPopMatrix();           // recall the pushed coordinate position

	
  ofSetColor(255,255,255,200);
	
  if( pts.size() > 0){
		
    //bigVideoTexture.getTextureReference().bind();
    bigVideoTexture.bind();
		
		
    //glBegin(GL_QUAD_STRIP);
    glBegin(GL_QUADS);
    int numPts = pts.size();
    int oldPointX;
    int oldPointY;
    int oldPointZ;
    if (flowTexture){
      texturePosFloat += 1.0;
			
    }
    texturePos= (int)texturePosFloat ;
    growTeller++;
    int offset =0;
    for(int i = 0; i < numPts-1; i++){
			
      if (pts[i].x > 9999 || pts[i+1].x > 9999){
        //	growTeller=0;
        offset= i;
      }else{
			
        if (i <offset+ growTeller){

          if (singleField){
            glTexCoord2f(0,(texturePts[i] + texturePos) % currentLine);
            glVertex3f(pts[i].x,pts[i].y, pts[i].z);
            glTexCoord2f(camWidth,(texturePts[i]+ texturePos) % currentLine);
            glVertex3f(pts2[i].x,pts2[i].y, pts2[i].z);
            glTexCoord2f(camWidth,(texturePts[i+1]+ texturePos) % currentLine);
            glVertex3f(pts2[i+1].x,pts2[i+1].y, pts2[i+1].z);
            glTexCoord2f(0,(texturePts[i+1]+ texturePos) % currentLine);
            glVertex3f(pts[i+1].x,pts[i+1].y, pts[i+1].z);
          }else {
            //int currentLineV= texturePts[i] % (picHi); //0-2048
            //int currentLineH= int(texturePts[i] / (picHi));  // 0- 4
            int currentLineV= (texturePts[i]+texturePos) % (picHi); //0-2048
            int currentLineH= int((texturePts[i]+texturePos) / (picHi));  // 0- 4
						
            glTexCoord2f(currentLineH * (camWidth),currentLineV);
            glVertex3f(pts[i].x,pts[i].y, pts[i].z);
            glTexCoord2f((currentLineH+1) * (camWidth),currentLineV);
            glVertex3f(pts2[i].x,pts2[i].y, pts2[i].z);
            glTexCoord2f((currentLineH+1) * (camWidth),currentLineV);
            glVertex3f(pts2[i+1].x,pts2[i+1].y, pts2[i+1].z);
            glTexCoord2f((currentLineH) * (camWidth),currentLineV);
            glVertex3f(pts[i+1].x,pts[i+1].y, pts[i+1].z);
          }

        }
      }
			
    }
    glEnd();
		
    bigVideoTexture.unbind();
		
  }
  if( sausjes[0].pootwaarde.size() > 0 ){
		
    //bigVideoTexture.getTextureReference().bind();
    bigVideoTexture.bind();
    glBegin(GL_QUADS);
    //	float deeltex= camWidth/ 10.0;
    float deeltex= 512/ (float)circleDens;
    int numPts = sausjes[0].pootwaarde.size();
		
    if (flowTexture){ texturePos++;}
		
    for(int i = 0; i < numPts-1; i++){
      for(int j = 0; j < circleDens; j++){
        ofPoint now0= sausjes[j].pootwaarde[i];
        ofPoint now1= sausjes[(j+1) % circleDens].pootwaarde[i];
        ofPoint now2= sausjes[(j+1) % circleDens].pootwaarde[i+1];
        ofPoint now3= sausjes[j].pootwaarde[i+1];
			
        glTexCoord2f(deeltex*j ,(texturePtsBubbel[i]+ texturePos) % currentLine);
        glVertex3f(now0.x,now0.y, now0.z);
        glTexCoord2f(deeltex*(j+1),(texturePtsBubbel[i]+ texturePos) % currentLine);
        glVertex3f(now1.x,now1.y, now1.z);
        glTexCoord2f(deeltex*(j+1),(texturePtsBubbel[i+1]+ texturePos) % currentLine);
        glVertex3f(now2.x,now2.y, now2.z);
        glTexCoord2f(deeltex*j,(texturePtsBubbel[i+1]+ texturePos) % currentLine);
        glVertex3f(now3.x,now3.y, now3.z);
			
        //glTexCoord2f(deeltex*j ,texturePts[i]);
        //					glVertex3f(now0.x,now0.y, now0.z);
        //					glTexCoord2f(deeltex*(j+1),texturePts[i]);
        //					glVertex3f(now1.x,now1.y, now1.z);
        //					glTexCoord2f(deeltex*(j+1),texturePts[i+1]);
        //					glVertex3f(now2.x,now2.y, now2.z);
        //					glTexCoord2f(deeltex*j,texturePts[i+1]);
        //					glVertex3f(now3.x,now3.y, now3.z);
      }
    }
    glEnd();
	
    bigVideoTexture.unbind();
  }
	
  if (plakplaatjes.size() > 0){
    for(int i = 0; i < plakplaatjes.size()-1; i++){
      ofPushMatrix();         // push the current coordinate position
			
      // ofRotateX(rigidB39.getGlobalOrientation().getEuler().y);          // change the coordinate system
			
      ofTranslate(ofVec3f( plaklocs[i].x,  plaklocs[i].y,  plaklocs[i].z));
      plakplaatjes[i].draw(0,0, 320,240);		 
      //plakplaatjes[i].bind();
      //plaklocs[i]
      //plakplaatjes[i].unbind();	
      ofPopMatrix(); 
			
    }
		
  }
	
	
	
	
  if (showInterface){
    nullPoint.draw();
    //rigidB.draw();
    rigidBpoot1.draw();
    rigidBpoot2.draw();
		
    rigidZasd1.draw();
    rigidZasd2.draw();
		
		
    middelpunt.draw();
    rigidB39.draw();
		
    for(int i=0;i<circleDens;i++){
      poot[i].draw();
    }
		
		
  }
  cam.end();
  if (peelOn){
		
    pts.push_back(rigidBpoot1.getGlobalPosition());
    pts2.push_back(rigidBpoot2.getGlobalPosition());


    int last = pts.size()-1;

    texturePts.push_back(0);
    texturePts[last] = currentLine;
		
    sendViaRoxlu();
    ofDrawBitmapString("x:" + ofToString(pts[last].x) + " y:"+ ofToString(pts[last].y)+ " z:" + ofToString(pts[last].z)  , 200, 20 );
		
  }
	
  if (zasdOn){
		
    pts.push_back(rigidZasd1.getGlobalPosition());
    pts2.push_back(rigidZasd2.getGlobalPosition());
		
    texturePts.push_back(currentLine);
    
    
    sendViaRoxlu();
   		
  }
	
  // butterflyOn sausageOn bubbleOn
  if (sausageOn){
    pts3.push_back(rigidB38.getGlobalPosition());
  }
	
  if (bubbleOn){
    texturePtsBubbel.push_back(currentLine);
    for(int i=0;i<circleDens;i++){
			
      sausjes[i].addTo(poot[i].getGlobalPosition());
    }
		
  }
  if (butterflyOn){
    pts.push_back(rigidB38.getGlobalPosition());
    pts2.push_back(rigidB39.getGlobalPosition());
				
    texturePts.push_back(currentLine);
    
     sendViaRoxlu();
    
		
  }
  if (showInterface) {
    ofDrawBitmapString("x:" + ofToString(rigidB.getGlobalPosition().x) + " y:"+ ofToString(rigidB.getGlobalPosition().y)+ " z:" + ofToString(rigidB.getGlobalPosition().z)  , 200, 40 );
  }
	
  nullPoint.draw();
  rigidB.draw();
  rigidBpoot1.draw();
  rigidBpoot2.draw();

  ofSetColor(255,255,255,100);
  if (vidBig == true) { vidGrabber.draw(0,0, ofGetWidth(), ofGetHeight());}
  //ofSetHexColor(0xffffff);
	
  if (showInterface) {
		
		
    if (vidBig == true){
      bg_video_On.draw(1*60,700);
    }else {
      bg_video_Off.draw(1*60,700);

    }
    if (externalCam == true){
      rotate_cam.draw(5*60,700);
    }else {
      augmented_cam.draw(5*60,700);
			
    }
	
    camera_draw.draw(3*60,700);
    interface_On.draw(4*60,700);
	
    stick_draw.draw(6*60,700);
    trumpet_On.draw(7*60,700);
  }

  if (fadeOn){
    if( pts.size() > 0 ){
      pts.erase(pts.begin());
      pts2.erase(pts2.begin());

    }
  }
  syphOut.publishScreen();

	
}


void testApp::sendViaRoxlu(){
  // @roxlu

  ofVec3f p1 = pts.back(); //rigidZasd1.getGlobalPosition();
  ofVec3f p2 = pts2.back(); //rigidZasd2.getGlobalPosition();
  server.streaming_potator.sendVertexPositions(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, currentLine);
  server.streaming_potator.sendTextureLine(
                                         currentLine,
                                         sendableTexture,
                                         85 * 3
                                         );
}

void testApp::doPlaatje(){
  posquad nu;
  nu.x=rigid38x; nu.y=rigid38y; nu.z=rigid38z; nu.qx=rigid38qx; nu.qy=rigid38qy; nu.qz=rigid38qz; nu.qw=rigid38qw;
	
  plaklocs.push_back(nu);
  ofTexture tNu;
  tNu.allocate(camWidth,camHeight, GL_RGB);
  tNu.loadData(vidGrabber.getPixels(), camWidth,camHeight, GL_RGB);
  plakplaatjes.push_back(tNu);
  cout << "plak:" << plakplaatjes.size();
}

// 
void testApp::butterFly(bool onNotOff){
  if (onNotOff == false){
    midiOut.sendNoteOn(1, 37,  0);
    butterflyOn= false;
    grabOn= false;
		
    pts.push_back(ofPoint(10000,0,0));
    pts2.push_back(ofPoint(10000,0,0));
    texturePts.push_back(0);
    syn2.stop();
    sendOSCommand("/vlinderTool", 0);
  }else{
    midiOut.sendNoteOn(1, 37,  0);
    butterflyOn= true;
    grabOn= true;
    syn2.play();
    sendOSCommand("/vlinderTool", 1);
  }
}

void testApp::sausageTool(bool onNotOff){
  if (onNotOff == false){
    normalVideo= true;
    sausageOn = false;
    grabOn= false;
    pts3.push_back(ofPoint(10000,0,0));

    //pts.push_back(ofPoint(10000,0,0));
    //pts2.push_back(ofPoint(10000,0,0));
    //texturePts.push_back(0);
    syn4.stop();
  }else{
    normalVideo= false;
    sausageOn= true;
    grabOn= true;
		
    //sausageOn= true;
    //grabOn= true;
    syn4.play();
  }
}

void testApp::bobbelTool(bool onNotOff){
  if (onNotOff == false){
    normalVideo= true;
    bubbleOn= false;
    grabOn= false;
    //pts.push_back(ofPoint(10000,0,0));
    //pts2.push_back(ofPoint(10000,0,0));
    //texturePts.push_back(0);
    syn3.stop();
  }else{
    normalVideo= false;
    bubbleOn= true;
    grabOn= true;
		
    //sausageOn= true;
    //grabOn= true;
    syn3.play();
  }
}

void testApp::peelTool(bool onNotOff){
  if (onNotOff == false){
    midiOut.sendNoteOn(1, 36,  0);
    pts.push_back(ofPoint(10000,0,0));
    pts2.push_back(ofPoint(10000,0,0));
    texturePts.push_back(0);
		
    peelOn = false;
    grabOn= false;
    syn.stop();
    sendOSCommand("/peelTool", 0);
			
  }else{
    midiOut.sendNoteOn(1, 36,  127);
    peelOn = true;
    grabOn= true;
    syn.play();
    sendOSCommand("/peelTool", 1);
		
		
	
  }
}

void testApp::zasdTool(bool onNotOff){
  if (onNotOff == false){
    midiOut.sendNoteOn(1, 36,  0);
    pts.push_back(ofPoint(10000,0,0));
    pts2.push_back(ofPoint(10000,0,0));
    texturePts.push_back(0);
		
    zasdOn = false;
    grabOn= false;
    syn.stop();
    sendOSCommand("/zasdTool", 0);
		
  }else{
    midiOut.sendNoteOn(1, 36,  127);
    zasdOn = true;
    grabOn= true;
    syn.play();
    sendOSCommand("/zasdTool", 1);
		
		
		
  }
}

void testApp::capturecamTool(){
  doPlaatje();
}

void testApp::doExternalCam(){
  externalCam= true;
  cam.reset();
	
  posTemp= cam.getGlobalPosition();
  rotTemp= cam.getGlobalOrientation();
  camMode= 0;	
  //cam.clearParent();
  //cam.setGlobalPosition( ofVec3f(1000,1000,1000));
  //cam.lookAt(rigidB,  ofVec3f(0,1,0));
}

void testApp::doInternalCam(){
  externalCam= false;
  cam.resetTransform();
  //cam.reset();
  //rigidB.setGlobalPosition(ofVec3f(0,0,0));
  //rigidB.setOrientation(ofVec3f(0,0,0));
  rigidB.setGlobalPosition(posTemp);
  rigidB.setOrientation(rotTemp);
	
  //cam.setGlobalPosition( rigidB.getGlobalPosition());
  //cam.setOrientation(rigidB.getOrientation());
  //cam.setDistance(1);
  cam.setParent(rigidB);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
  // in fullscreen mode, on a pc at least, the 
  // first time video settings the come up
  // they come up *under* the fullscreen window
  // use alt-tab to navigate to the settings
  // window. we are working on a fix for this...
  if (key=='e'){
		
    doExternalCam();
  }
  if (key=='r'){
    doInternalCam();
		
  }
  if (key == 's' || key == 'S'){
    vidGrabber.videoSettings();
  }
  if (key == 'g' || key == 'G'){
    doVidGrab = !doVidGrab;
		
  }
	
  switch(key) {
    case ' ':
      mainMusic.play();

    case 'M':
    case 'm':
      if(cam.getMouseInputEnabled()) cam.disableMouseInput();
      else cam.enableMouseInput();
      break;
			
    case 'F':
    case 'f':
      ofToggleFullscreen();
      break;
    case 'd':
      peelTool(true);
      break;
    case 'z':
      zasdTool(true);
      break;
			
    case 'n':
      newField();
			server.reset();
      break;
    case 'p':
      if (singleField){
        saveAll();
      }else{
        saveAllfat();
      }
      break;
    case 't':
      showTexture= !showTexture;
      break;
			
    case 'o':
      if (singleField){
        openProject2();
      }else{
        openProject2fat();
      }
      //	openProject2();
      break;
    case 'c':
      doPlaatje();
      break;
    case 'x':
			
			
      butterFly(true);
			
      break;
    case 'v':
      vidBig = !vidBig;
      break;
    case '-':
      myFov--;
      cam.setFov(myFov);
      break;
    case '=':
      myFov++;
      cam.setFov(myFov);
      break;
    case '[':
     myTilt--;
      cam.tilt(-1);
     // texturePosFloat -= 1.0;
      break;
    case ']':
     /// texturePosFloat += 1.0;
     myTilt++;
     cam.tilt(1);
      break;
    case '9':
      myPan--;
      cam.pan(-1);
      break;
    case '0':
      myPan++;
      cam.pan(1);
      break;
    case '7':
      myRoll--;
      cam.roll(-1);
      break;
    case '8':
      myRoll++;
      cam.roll(1);
      break;
    case '5':
      //dirTeller--;
      //if (dirTeller < 0) dirTeller= dir.size()-1;
      //openProject2();
      break;
    case '6':
      dirTeller++;
      if (dirTeller > dir.size() -1) dirTeller= 0;
      newField();
      if (singleField){
        openProject2();
      }else{
        openProject2fat();
      }
      break;
    case 'q':
      flowTexture= !flowTexture;
      if (!flowTexture) texturePos =0;
      break;
    case 'a':
			
      camMode++;
      if (camMode >5) camMode=0;
      break;
			
    case 'i':
      growTeller=0;
      break;

    case 'b':	
      bobbelTool(true);
      break;
    case 'l':	
      sausageTool(true);
      break;
    case '4':
      saveAllXML();
      break;
    case '3':
      export2Json();
      break;
    case '2':
      showInterface = !showInterface;
      break;
			
    case 'w':
      fadeOn= !fadeOn;
      break;
			
  }
	
	
}



//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
  switch(key) {
    case 'x':
      butterFly(false);
      break;	
    case 'b':	
      bobbelTool(false);
      break;
    case 'l':	
      sausageTool(false);
      break;
    case 'd':
      peelTool(false);
      break;
    case 'z':
      zasdTool(false);
      break;
				
				
  }		
}


void testApp::newField(){
  pts.clear();
  pts2.clear();
  pts3.clear();

  texturePts.clear();
	
  for(int i=0;i<circleDens;i++){
    sausjes[i].clear();
  }
  currentLine=0;
	
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
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






//--------------------------------------------------------------

void testApp::axisChanged(ofxGamepadAxisEvent& e)
{
  cout << "AXIS " << ofToString(e.axis) << " VALUE " << ofToString(e.value) << endl;
}

void testApp::buttonPressed(ofxGamepadButtonEvent& e)   // switched somehow !!!!!!!!!!
{
  cout << "BUTTON " << ofToString(e.button) << " PRESSED" << endl;
	
  if(e.button ==1){
    peelTool(false);
		
  }
	
  if(e.button ==3){
    butterFly(false);
		
  }
	
  if(e.button ==2){
    //bobbelTool(false);
    ofImage temp;
    scannedImage.setFromPixels(vidGrabber.getPixels(),camWidth, camHeight, OF_IMAGE_COLOR);
    //scannedImage= temp.clone();
    //scannedImage
    //bubbleOn= false;
    //grabOn= false;
  }
	
  if(e.button ==0){
    zasdTool(false);
    //sausageTool(false);
		
    //bubbleOn= false;
    //grabOn= false;
  }
	
  if(e.button ==9){
    newField();
		
  }
	
  if(e.button ==8){
    flowTexture= !flowTexture;
    if (!flowTexture) texturePos =3;
		
		
  }
	
  if(e.button ==500){
    ofToggleFullscreen();
  }
	
  if(e.button ==4){
    doInternalCam();
    vidBig= true;
		
		
		
  }
  if(e.button ==6){
    doExternalCam();
    vidBig= false;
    camMode= 1;
		
		
		
  }
  if(e.button ==200){
    myFov= 60;
    cam.setFov(myFov);
		
		
		
  }
	
  if(e.button ==300){
    myFov= 30;
    cam.setFov(myFov);		
		
		
  }
	
	
	
  if(e.button ==5){
    realTimeGrab = !realTimeGrab;
  }
  if(e.button ==130){
		
    sausageTool(false);
		
		
    //sausageOn= false;
    //pts3.push_back(ofPoint(10000,0,0));
		
  }
  if(e.button ==120){
    bobbelTool(false);

    //bubbleOn= false;
    //grabOn= false;
  }
	
  if(e.button ==400){
    newField();
		
  }
}

//   pRSSED !!!!
void testApp::buttonReleased(ofxGamepadButtonEvent& e)
{
  cout << "BUTTON " << ofToString(e.button) << " RELEASED" << endl;
  if(e.button ==1){
    peelTool(true);

  }
	
  if(e.button ==3){
    butterFly(true);
		
  }
	
  if(e.button ==2){
    //bobbelTool(true);
		
    //bubbleOn= false;
    //grabOn= false;
  }
	
  if(e.button ==0){
    zasdTool(true);
    //sausageTool(true);
		
    //bubbleOn= false;
    //grabOn= false;
  }
	
	
  if(e.button ==130){
    sausageTool(true);
    //sausageOn= true;
		
  }
  if(e.button ==120){
    bobbelTool(true);
    //bubbleOn= true;
    //grabOn= true;
		
  }
	
  if(e.button ==400){
    showInterface= !showInterface;
		
  }
	
	
	
}

string testApp::getDateName(){
  string maand, dag, uur, minuut, seconde;
  if (ofGetMonth() < 10){
    maand= "0" + ofToString(ofGetMonth());
  }else {
    maand= ofToString(ofGetMonth());
  }
  if (ofGetDay() < 10){
    dag= "0" + ofToString(ofGetDay());
  }else {
    dag= ofToString(ofGetDay());
  }
  if (ofGetHours() < 10){
    uur= "0" + ofToString(ofGetHours());
  }else {
    uur= ofToString(ofGetHours());
  }
  if (ofGetMinutes() < 10){
    minuut= "0" + ofToString(ofGetMinutes());
  }else {
    minuut= ofToString(ofGetMinutes());
  }
  if (ofGetSeconds() < 10){
    seconde= "0" + ofToString(ofGetSeconds());
  }else {
    seconde= ofToString(ofGetSeconds());
  }
  return ofToString(ofGetYear())+ maand +dag + uur + minuut + seconde ;
	
}


void testApp::skipToProject(){
  string naam = dir[dirTeller].getBaseName();
  //string strNm= ofToString(naam);
  cout << naam << " " << naam.substr(11, naam.length());
  openProject(naam.substr(11, naam.length()));
	
}

string testApp::openProject(string filePart){
	
  //ofBuffer buffer = ofBufferFromFile("/Users/keezpips/Desktop/3d/vectordata_" + filePart + ".txt"); // reading into the buffer
  ofBuffer buffer = ofBufferFromFile("/Users/keezpips/Desktop/3d/vectordata_20120606231847.txt"); // reading into the buffer
  string data= buffer.getText(); // let's see what it says
	
  cout << data << "\n";
  vector<string> lines = ofSplitString(data, "\n", true, true);
	
  pts.clear();
  pts2.clear();
  texturePts.clear();
	
  int index = 0;
  while (index < lines.size()-1)
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
		
      pts.push_back(temp);
      pts2.push_back(temp2);
      texturePts.push_back(textemp);
		
      currentLine= textemp;
		
      index++;
    }
		
	
  //nuImage.loadImage("/Users/keezpips/Desktop/3d/img20120606231847.png");
	
  cout << "/Users/keezpips/Desktop/3d/img" + filePart + ".png" + "\n";
  /*
	 
    ofImage nuImage;
    nuImage.loadImage("/Users/keezpips/Desktop/3d/img" + filePart + ".png");
    unsigned char * pixels2 = nuImage.getPixels();

    for (int w= 0; w<camWidth; w++) {
    for (int h= 0; h<picHi; h++) {
    for (int i= 0; i<3; i++) {
				
    bigCharTexture[(camWidth*h+ w)*3 +i]=  pixels2[(camWidth*h+ w)*3 +i];
				
    }
			
			
    }
    }
	
    bigVideoTexture.loadData(bigCharTexture, camWidth,picHi, GL_RGB);
  */
	
	

}


string testApp::openProject2(){
	
  string naam = dir[dirTeller].getBaseName();
  //string strNm= ofToString(naam);
  cout << naam << " " << naam.substr(11, naam.length());
	
	
  string filePart = naam.substr(11, naam.length());
  ofBuffer buffer = ofBufferFromFile("/Users/keezpips/Desktop/3d/vectordata_" + filePart + ".txt"); // reading into the buffer
  //ofBuffer buffer = ofBufferFromFile("/Users/keezpips/Desktop/3d/vectordata_20120606231847.txt"); // reading into the buffer
  string data= buffer.getText(); // let's see what it says
  vector<string> lines = ofSplitString(data, "\n", true, true);
	
  scultpName = filePart;
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
	
  cout << "/Users/keezpips/Desktop/3d/img" + filePart + ".png" + "\n";
	
	 
	
  nuImage.loadImage("/Users/keezpips/Desktop/3d/img" + filePart + ".png");
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

string testApp::openProject2fat(){
	
  string naam = dir[dirTeller].getBaseName();
  //string strNm= ofToString(naam);
  cout << naam << " " << naam.substr(11, naam.length());
  string filePart = naam.substr(11, naam.length());
	
	
  cout << "filetoopen " << "/Users/keezpips/Desktop/3dfat/vectordata_" + filePart + ".txt" << "\n";
  ofBuffer buffer = ofBufferFromFile("/Users/keezpips/Desktop/3dfat/vectordata_" + filePart + ".txt"); // reading into the buffer
  //ofBuffer buffer = ofBufferFromFile("/Users/keezpips/Desktop/3d/vectordata_20120606231847.txt"); // reading into the buffer
  string data= buffer.getText(); // let's see what it says
  vector<string> lines = ofSplitString(data, "\n", true, true);
	
  scultpName = filePart;
  pts.clear();
  pts2.clear();
  texturePts.clear();
	
  int index = 0;
  ofPoint old_Temp, old_Temp2;
	
  while (index < lines.size()-1)
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
		
      //if (temp.x == 0.0 || temp2.x == 0.0) {
      if (temp == old_Temp && temp2 == old_Temp2) {
        cout << "dubbel detected: " << temp << " " << old_Temp2 << textemp << "\n";
      }else {
        pts.push_back(temp);
        pts2.push_back(temp2);
        texturePts.push_back(textemp);
        currentLine= textemp;
			
        old_Temp= temp;
        old_Temp2= temp2;
			
      }
      index++;
		
    }
  cout << "loaded\n";
  cout << "/Users/keezpips/Desktop/3dfat/img" + filePart + ".png" + "\n";
	
	
	
  nuImage.loadImage("/Users/keezpips/Desktop/3dfat/img" + filePart + ".png");
  unsigned char * pixels2 = nuImage.getPixels();
	
  for (int w= 0; w<(camWidth*6); w++) {
    for (int h= 0; h<picHi; h++) {
      for (int i= 0; i<3; i++) {
				
        bigCharTexture[(camWidth*6*h+ w)*3 +i]=  pixels2[(camWidth*6*h+ w)*3 +i];
				
      }
			
			
    }
  }
	
  bigVideoTexture.loadData(bigCharTexture, camWidth*6,picHi, GL_RGB);
	
	
	
	
	
	
  cout << "done " << pts.size() << "\n";
	
	
}


void testApp::saveAll(){
	
  ofstream myfile;
  string daat = getDateName().c_str(); 
  string vecnaam;
  vecnaam= "/Users/keezpips/Desktop/3d/vectordata_" + daat + ".txt"; 
  cout << vecnaam;
  string imgnaam= "img" + daat;
  myfile.open(vecnaam.c_str());
	
	
	
	
  if( pts.size() > 0 ){
		
    for(int i = 0; i < pts.size(); i++){
      myfile << pts[i].x << " " << pts[i].y << " " << pts[i].z << " "<<  pts2[i].x << " " << pts2[i].y << " " << pts2[i].z << " " << texturePts[i] << "\n" ;
    }
  }
  myfile.close();
	
  //bigCharTexture = new unsigned char[camWidth*picHi*3];
	
  //bigVideoTexture.allocate(camWidth,picHi, GL_RGB);
	
  ofImage temp;
  temp.setFromPixels(bigCharTexture,camWidth, picHi, OF_IMAGE_COLOR);
	
	
  temp.saveImage("/Users/keezpips/Desktop/3d/" + imgnaam + ".png");
  //ofPixels saver;
  //ofSaveImage(ofPixels &pix, ", ofImageQualityType qualityLevel=OF_IMAGE_QUALITY_BEST)
  //saver.setFromPixels(bigCharTexture,)
  //bigVideoTexture
}

void testApp::saveAllfat(){
	
  ofstream myfile;
  string daat = getDateName().c_str(); 
  string vecnaam;
  vecnaam= "/Users/keezpips/Desktop/3dfat/vectordata_" + daat + ".txt"; 
  cout << vecnaam;
  string imgnaam= "img" + daat;
  myfile.open(vecnaam.c_str());
	
	
	
	
  if( pts.size() > 0 ){
		
    for(int i = 0; i < pts.size(); i++){
      myfile << pts[i].x << " " << pts[i].y << " " << pts[i].z << " "<<  pts2[i].x << " " << pts2[i].y << " " << pts2[i].z << " " << texturePts[i] << "\n" ;
    }
  }
  myfile.close();
	
  //bigCharTexture = new unsigned char[camWidth*picHi*3];
	
  //bigVideoTexture.allocate(camWidth,picHi, GL_RGB);
	
  ofImage temp;
  //temp.setFromPixels(bigCharTexture,camWidth, picHi, OF_IMAGE_COLOR);
  temp.setFromPixels(bigCharTexture,camWidth*6, picHi, OF_IMAGE_COLOR);
	
  temp.saveImage("/Users/keezpips/Desktop/3dfat/" + imgnaam + ".png");
  //ofPixels saver;
  //ofSaveImage(ofPixels &pix, ", ofImageQualityType qualityLevel=OF_IMAGE_QUALITY_BEST)
  //saver.setFromPixels(bigCharTexture,)
  //bigVideoTexture
}


void testApp::saveAllXML(){
	
  ofstream myfile;
  string daat = getDateName().c_str(); 
  string vecnaam;
  vecnaam= "/Users/keezpips/Desktop/3dxml/xmldata_" + daat + ".xml"; 
  cout << vecnaam;
  string imgnaam= "img" + daat;
  myfile.open(vecnaam.c_str());
	
	
	
	
  if( pts.size() > 0 ){
    myfile << "<doublestroke>";
    for(int i = 0; i < pts.size(); i++){
      myfile << "<point1><x>" << pts[i].x << "</x><y>" << pts[i].y << "</y><z>" << pts[i].z << "</z></point1><point2><x>" << pts2[i].x << "</x><y>" << pts2[i].y << "</y><z>" << pts2[i].z << "</z></point2><texture>" << texturePts[i] << "</texture>" << "\n" ;
    }
    myfile << "</doublestroke>";
  }
  myfile.close();
	
  //bigCharTexture = new unsigned char[camWidth*picHi*3];
	
  //bigVideoTexture.allocate(camWidth,picHi, GL_RGB);
	
  ofImage temp;
  temp.setFromPixels(bigCharTexture,camWidth, picHi, OF_IMAGE_COLOR);
  //scannedImage
	
  temp.saveImage("/Users/keezpips/Desktop/3dxml/" + imgnaam + ".png");
  //ofPixels saver;
  //ofSaveImage(ofPixels &pix, ", ofImageQualityType qualityLevel=OF_IMAGE_QUALITY_BEST)
  //saver.setFromPixels(bigCharTexture,)
  //bigVideoTexture
}


void testApp::export2Json(){  // attempt 2 // dubbele input
	
  ofstream myfile;
  string daat = getDateName().c_str(); 
  string vecnaam;
  //vecnaam= "/Users/keezpips/Desktop/3dxml/json_" + daat + ".json"; 
  vecnaam= "/Users/keezpips/Sites/webgl_lessons/keez_vj/" + daat + "json.json";
	
  cout << vecnaam << "\n";
  //string imgnaam= "img" + daat;
  myfile.open(vecnaam.c_str());
	
	
	
	
  if( pts.size() > 0 ){
		
    vector <float> vertexPositions;
    vector <float> vertexNormals;
    vector <float> vertexTextureCoords;
    vector <int> indices;
		
    vertexPositions.clear();
    vertexNormals.clear();
    vertexTextureCoords.clear();
    indices.clear(); 
		
    //int oldPointX, oldPointY, oldPointZ;
    int pTeller= 0;
    float divideR= 50.0;
    float yLeveller= 1000.0;
		
    for(int i = 0; i < pts.size()-1; i++){
			
      //	cout << i << " " << pts[i]  << " " << pts2[i] << "\n";
			
		
      if (pts[i].x < 9999 && pts[i+1].x < 9999){
				
				
				
				
        //punt 0
        vertexPositions.push_back(pts[i].x /divideR);
        vertexPositions.push_back((pts[i].y- yLeveller) /divideR);
        vertexPositions.push_back(pts[i].z /divideR);
				
        vertexTextureCoords.push_back(0.0);
        vertexTextureCoords.push_back(1.0-texturePts[i]/ (float)picHi);
				
				
        //punt 1
        vertexPositions.push_back(pts2[i].x /divideR);
        vertexPositions.push_back((pts2[i].y- yLeveller) /divideR);
        vertexPositions.push_back(pts2[i].z /divideR);
				
        vertexTextureCoords.push_back(1.0);
        vertexTextureCoords.push_back(1.0-texturePts[i]/ (float)picHi);
				
				
        //punt 2
        vertexPositions.push_back(pts[i+1].x /divideR);
        vertexPositions.push_back((pts[i+1].y- yLeveller) /divideR);
        vertexPositions.push_back(pts[i+1].z /divideR);
				
        vertexTextureCoords.push_back(0.0);
        vertexTextureCoords.push_back(1.0-texturePts[i+1]/ (float)picHi);
							
        //punt 3
        vertexPositions.push_back(pts2[i+1].x /divideR);
        vertexPositions.push_back((pts2[i+1].y- yLeveller) /divideR);
        vertexPositions.push_back(pts2[i+1].z /divideR);
				
        vertexTextureCoords.push_back(1.0);
        vertexTextureCoords.push_back(1.0-texturePts[i+1]/ (float)picHi);

				
				
        indices.push_back(pTeller); //0
        indices.push_back(pTeller+1); // 1
        indices.push_back(pTeller+3); // laatste van driehoek //3
        //tweede driehoek
        indices.push_back(pTeller); // 0
        indices.push_back(pTeller+3); // 3
        indices.push_back(pTeller+2); //2
				
        pTeller +=4;
				
								
        ofVec3f n = calculateNormal(pts[i],pts2[i],pts2[i+1]);
        for(int ii = 0; ii < 2; ii++){
          vertexNormals.push_back(n.x);
          vertexNormals.push_back(n.y);
          vertexNormals.push_back(n.z);
        }
				
        n = calculateNormal(pts[i],pts2[i+1],pts[i+1]);
        for(int ii = 0; ii < 2; ii++){
          vertexNormals.push_back(n.x);
          vertexNormals.push_back(n.y);
          vertexNormals.push_back(n.z);
        }
				

				
				
				
      }
			
    }
				
    cout << "vertexPositions.size(): " << vertexPositions.size() << "\n";
    cout << "vertexNormals.size(): " << vertexNormals.size() << "\n";
    cout << "vertexTextureCoords.size(): " << vertexTextureCoords.size() << "\n";
    cout << "indices.size(): " << indices.size() << "\n";

		
    myfile << "{\n";
		
    myfile << "\"vertexPositions\" : [";
    for(int j = 0; j < vertexPositions.size(); j++){
      myfile << vertexPositions[j];
      if (j< vertexPositions.size()-1) {myfile << ",";}
    }
    myfile << "],\n";
		
    myfile << "\"vertexNormals\" : [";
    for(int i = 0; i < vertexNormals.size(); i++){
      myfile << vertexNormals[i];
      if (i< vertexNormals.size()-1) {myfile << ",";}
    }
    myfile << "],\n";
		
    myfile << "\"vertexTextureCoords\" : [";
    for(int i = 0; i < vertexTextureCoords.size(); i++){
      myfile << vertexTextureCoords[i];
      if (i< vertexTextureCoords.size()-1){ myfile << ",";}
    }
    myfile << "],\n";
		
    myfile << "\"indices\" : [";
    for(int i = 0; i < indices.size(); i++){
      myfile << indices[i];
      if (i< indices.size()-1){ myfile << ",";}
    }
    myfile << "]\n }";
  }
  myfile.close();
	
  string imgnaam= "img" + daat;
  ofImage temp;
  temp.setFromPixels(bigCharTexture,camWidth, picHi, OF_IMAGE_COLOR);
  temp.resize(128,2048);
	
  temp.saveImage("/Users/keezpips/Sites/webgl_lessons/keez_gl/" + imgnaam + ".jpg");
  temp.saveImage("/Users/keezpips/Sites/webgl_lessons/keez_vj/texture.jpg");
	
}

//

ofVec3f testApp::calculateNormal(ofVec3f p1, ofVec3f p2, ofVec3f p3){
  ofVec3f norMal;
  ofVec3f u = p2 - p1;
  ofVec3f v = p3 - p1;

  norMal.x= (u.y * v.z) - (u.z * v.y);
  norMal.y= (u.z * v.x) - (u.x * v.z);
  norMal.z= (u.x * v.y) - (u.y * v.x);
	
  return norMal.normalize();
}

void testApp::newMidiMessage(ofxMidiMessage& msg) {
	
  // make a copy of the latest message
  midiMessage = msg;
  cout << midiMessage.pitch;
  if (midiMessage.channel == midiChannelIn){
    cout << "pitch: " << midiMessage.pitch;
    if (midiMessage.velocity > 99){
      switch (midiMessage.pitch) {
        case 36: // 1
          doExternalCam();
          break;
        case 38: // 2
          //doVidGrab= !doVidGrab;
          camMode= 1;
          break;
        case 40: // 3
          vidBig = !vidBig;
          break;
        case 41: // 4
          //saveAll();
          newField();
          break;
        case 45: // 7
          camMode= 3;
          break;
        case 47: // 8
          flowTexture= !flowTexture;
          if (!flowTexture){
            texturePosFloat= 0.0;
            texturePos =0;
          }
          break;
        case 48: // 9
          //growTeller=0;
          camMode++;
          if (camMode >5) camMode=0;
				
          break;
				
        case 127: // 6
          doInternalCam();
          break;
				
				
      }
    }
  }
}



void testApp::exit() {
	
  // clean up
  midiOut.closePort();
}


void testApp::sendOSCommand(string naam, bool onN){
  if (sendOSCout){
    ofxOscMessage m;
    m.setAddress(naam);
    m.addIntArg(onN);
    sender.sendMessage(m);
  }
}
