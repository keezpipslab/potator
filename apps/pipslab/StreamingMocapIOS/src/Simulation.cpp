#include "Simulation.h"


Simulation::Simulation() {
}

Simulation::~Simulation() {
}

void Simulation::setup() {
  cam.setup(width, height);
  cam.translate(0.0f, 0.0f, 10.0f);
  ax.setup(10);
  app.setup("192.168.1.41", "3344"); // DIT ADRES MOET VERWIJZEN NAAR DE MOCAP-SERVER APPLICATIE
}

void Simulation::update() {
  app.update();
}

void Simulation::draw() {
  const float* pm = cam.pm().getPtr();
  const float* vm = cam.vm().getPtr();
 //	ax.draw(pm, vm);
  app.draw(pm, vm);
}


void Simulation::onTouchDown(float x, float y) {
  cam.onMouseDown(x,y);
}

void Simulation::onTouchUp(float x, float y) {
}

void Simulation::onTouchMoved(float x, float y) {
  cam.onMouseDragged(x,y);
 //	 printf("%f, %f\n", x, y);
}
