#ifndef ROXLU_POTATOR_PLAYER_H
#define ROXLU_POTATOR_PLAYER_H

// Super basic player for potator data; 
// - no frame skipping
// - no special timeing code..

#include <roxlu/Roxlu.h>
#include <potator/PotatorData.h>

class PotatorPlayer {
 public:
  PotatorPlayer();
  ~PotatorPlayer();
  void setData(PotatorData* d);
  void play();
  void setFPS(const float f);
  bool update();
  void reset(); 
 public:
  PotatorData* data;
  float fps;
  int millis_per_frame;
  size_t dx;
  rx_uint64 timeout;
  int state; // 0 = disabled, 1 = playing 
};
#endif
