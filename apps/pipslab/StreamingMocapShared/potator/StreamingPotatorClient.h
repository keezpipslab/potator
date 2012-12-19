#ifndef ROXLU_STREAMING_POTATOR_CLIENT_H
#define ROXLU_STREAMING_POTATOR_CLIENT_H

#include <potator/StreamingGeometryClient.h>
#include <potator/PotatorTypes.h>
#include <roxlu/Roxlu.h>

#include <string>
#include <algorithm>
#include <vector>

void on_geometry_read(char* data, size_t len, void* user);
void on_geometry_close(void* user);

class StreamingPotatorClient : public Runnable { 
 public:
  StreamingPotatorClient(StreamingGeometryClient& client);
  ~StreamingPotatorClient();
  void run();
  bool hasData();
  void addData(PotatorStreamData* d);
  void copyAndFlushData(std::vector<PotatorStreamData*>& result);
  void reset();
 public:
  StreamingGeometryClient& client;
  std::string in_buffer;
  std::vector<PotatorStreamData*> data;
  Mutex mutex;
};

#endif
