#ifndef ROXLU_POTATOR_SERVER_APPLICATION_H
#define ROXLU_POTATOR_SERVER_APPLICATION_H

#include <string>
#include <potator/StreamingGeometryServer.h>
#include <potator/StreamingPotatorServer.h>
#include <potator/PotatorDrawer.h>
#include <potator/PotatorTypes.h>
#include <potator/PotatorLoader.h>
#include <potator/PotatorPlayer.h>
#include <potator/PotatorData.h>
#include <roxlu/io/File.h>
#include <roxlu/experimental/Image.h>

class PotatorServerApplication {
 public:
  PotatorServerApplication();
  ~PotatorServerApplication();
  void setup(const std::string port);
  void update();
  void reset();
 public:
  StreamingGeometryServer geom;
  StreamingPotatorServer streaming_potator;
  Thread server_thread;
  PotatorPlayer player;
};

#endif
