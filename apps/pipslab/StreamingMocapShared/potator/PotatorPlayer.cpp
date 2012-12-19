#include <potator/PotatorPlayer.h>

PotatorPlayer::PotatorPlayer() 
  :fps(25.0f)
  ,dx(0)
  ,timeout(0)
  ,state(0)
  ,data(NULL)
{
  millis_per_frame = (1.0f/fps) * 1000;
}

PotatorPlayer::~PotatorPlayer() {
}

void PotatorPlayer::play() {
  state = 1;
  timeout = Timer::now() + millis_per_frame;
}

void PotatorPlayer::setFPS(const float f) {
  fps = f;
  millis_per_frame = (1.0f/fps) * 1000;
}

void PotatorPlayer::reset() {
  state = 0;
  dx = 0;
  timeout = 0;
}

// returns bool if there is new data
bool PotatorPlayer::update() {
  if(state != 1 || data == NULL) {
    return false;
  }
  rx_uint64 now = Timer::now();
  
  if(now > timeout) {
    timeout = now + millis_per_frame;
    ++dx; //  %= data->size();

    // ready
    if(dx > data->size()-1) {
      dx = data->size() -1;
      state = 0;
    }

    return true;
  }
  return false;
}

void PotatorPlayer::setData(PotatorData* d) {
  data = d;
}
