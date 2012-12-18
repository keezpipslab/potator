#ifndef ROXLU_POTATOR_CLIENT_APPLICATION_H
#define ROXLU_POTATOR_CLIENT_APPLICATION_H

#include <roxlu/Roxlu.h>
#include <potator/StreamingGeometryClient.h>
#include <potator/StreamingPotatorClient.h>
#include <potator/PotatorDrawer.h>

class PotatorClientApplication {
 public:
  PotatorClientApplication();
  ~PotatorClientApplication();
  void setup();
  void update();
  void draw(const float* pm, const float* vm);
  void reset(); // resets everything to "start" state.
 public:
  StreamingGeometryClient geometry_client;
  StreamingPotatorClient potator_client;
  Thread potator_thread;
  PotatorDrawer drawer;
};

#endif
