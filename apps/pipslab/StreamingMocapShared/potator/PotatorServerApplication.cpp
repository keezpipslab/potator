#include <potator/PotatorServerApplication.h>

PotatorServerApplication::PotatorServerApplication()
  :streaming_potator(geom)
{
}

PotatorServerApplication::~PotatorServerApplication() {
}

void PotatorServerApplication::setup(const std::string port) {
  if(!geom.setup(port)) {
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

