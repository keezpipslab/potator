#include <potator/PotatorServerApplication.h>

PotatorServerApplication::PotatorServerApplication()
  :streaming_potator(geom)
{
}

PotatorServerApplication::~PotatorServerApplication() {
}

void PotatorServerApplication::setup() {
  if(!geom.setup()) {
    ::exit(0);
  }
  server_thread.create(streaming_potator);
}

void PotatorServerApplication::reset() {
  player.reset();
  streaming_potator.sendReset();
}

void PotatorServerApplication::update() {
}

