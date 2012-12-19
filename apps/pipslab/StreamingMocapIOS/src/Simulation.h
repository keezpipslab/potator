#ifndef ROXLU_SIMULATION_H
#define ROXLU_SIMULATION_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <roxlu/Roxlu.h>
#include "SimulationBase.h"
#include <potator/PotatorClientApplication.h>
  
class Simulation : public SimulationBase {
 public:
  Simulation();
  ~Simulation();
  void setup();
  void update();
  void draw();
  void onTouchDown(float x, float y);
  void onTouchUp(float x, float y);
  void onTouchMoved(float x, float y);
 private:
  EasyCam cam;
  Axis ax;
  PotatorClientApplication app;
};

#endif
