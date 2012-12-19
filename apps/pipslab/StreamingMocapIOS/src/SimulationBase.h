#ifndef ROXLU_SIMULATION_BASE_H
#define ROXLU_SIMULATION_BASEH

#include <stdio.h>
  
class SimulationBase {
 public:
  SimulationBase();
  ~SimulationBase();
  virtual void setup();
  virtual void update();
  virtual void draw();
  virtual void onTouchDown(float x, float y);
  virtual void onTouchMoved(float x, float y);
  virtual void onTouchUp(float x, float y);
 public:
  int width;
  int height;
};

#endif
