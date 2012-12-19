#ifndef ROXLU_STREAMING_POTATOR_H
#define ROXLU_STREAMING_POTATOR_H

#include <stdio.h>
#include <vector>
#include <roxlu/Roxlu.h>
#include <sstream>
#include "PotatorTypes.h"
#include "StreamingGeometryServer.h"

struct PotatorTask {
  PotatorTask();
  PotatorDataType date_type;
  void* data;
  size_t len;
};

void sps_on_new_connection(StreamingGeometryServer* serv, StreamingConnection* con, void* user); /* gets called when a new connection is created */

class StreamingPotatorServer : public Runnable {
 public:
  StreamingPotatorServer(StreamingGeometryServer& server);
  void run();
  void sendVertexPosition(const float x, const float y, const float z); // send one point
  void sendVertexPositions( // send two points that are used to create a triangle strip
                           const float x1,
                           const float y1,
                           const float z1,
                           const float x2,
                           const float y2,
                           const float z2,
                           const int texLine
                           );
  void sendVertexPositions(PotatorVertexPositions& p);
  void sendVertexPositionsEndMarker(); // tell the client we reached the end of a strip
  void sendTextureInfo(int w, int h); 
  void sendTextureLine(int line, unsigned char* data, int nbytes);
  void sendReset(); // resets the whole application.
  void setTextureSize(const int w, const int h);
 private:
  void addTask(PotatorTask* task);
 private:
  std::vector<PotatorTask*> tasks;
  StreamingGeometryServer& server;
  Mutex mutex;
 public:
  int tex_w;
  int tex_h; 
};


#endif
