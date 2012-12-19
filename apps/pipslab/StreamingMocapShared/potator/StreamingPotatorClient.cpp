#include <potator/StreamingPotatorClient.h>

// -------------------------------
// CALLBACKS
// -------------------------------
#define USE_LOOP

void on_geometry_read(char* data, size_t len, void* user) {
  //  return;
  StreamingPotatorClient* c = static_cast<StreamingPotatorClient*>(user);
  V((">> Adding %zu bytes, curr-size: %zu\n", len, c->in_buffer.size()));
  std::copy(data, data+len, std::back_inserter(c->in_buffer));

  // parse when we have enough bytes for the smalles packet.
  size_t buf_size = c->in_buffer.size();
  size_t texture_line_min_size = sizeof(int) * 2 + sizeof(char*); // @todo we should make this a bit more secure
#ifdef USE_LOOP
  while(c->in_buffer.size() > 0) {
#endif
    if(c->in_buffer[0] == PDT_VERTEX_POSITION && buf_size >= sizeof(PotatorVertexPosition)) {
      V(("> PDT_VERTEX_POSITION\n"));
      PotatorVertexPosition* p = new PotatorVertexPosition();
      char* ptr = (char*)c->in_buffer.c_str();
      memcpy((char*)p, ptr, sizeof(*p));
      c->in_buffer.erase(0, sizeof(*p));

      c->addData(p);
      //printf("%f, %f, %f\n", p->x, p->y, p->z);
    }
    else if(c->in_buffer[0] == PDT_VERTEX_POSITIONS && buf_size >= sizeof(PotatorVertexPositions)) {
      V(("> PDT_VERTEX_POSITIONS\n"));
      PotatorVertexPositions* p = new PotatorVertexPositions();
      char* ptr = (char*)c->in_buffer.c_str();
      memcpy((char*)p, ptr, sizeof(*p));
      c->in_buffer.erase(0, sizeof(*p));
      c->addData(p);
      //printf("%f, %f, %f - %f, %f, %f\n", p->x1, p->y1, p->z1, p->x2, p->y2, p->z2);
    }
    else if(c->in_buffer[0] == PDT_VERTEX_POSITIONS_END_MARKER) {
      V(("> PDT_VERTEX_POSITIONS_END_MARKER\n"));
      PotatorStreamData* p = new PotatorStreamData(PDT_VERTEX_POSITIONS_END_MARKER);
      c->addData(p);
      c->in_buffer.erase(0, 1);
    }
    else if(c->in_buffer[0] == PDT_TEXTURE_INFO && buf_size >= sizeof(PotatorTextureInfo)) {
      V(("> PDT_TEXTURE_INFO\n"));
      PotatorTextureInfo* p = new PotatorTextureInfo();
      char* ptr = (char*)c->in_buffer.c_str();
      memcpy((char*)p, ptr, sizeof(*p));
      c->in_buffer.erase(0, sizeof(*p));
      c->addData(p);
    }
    else if(c->in_buffer[0] == PDT_TEXTURE_LINE && buf_size >= texture_line_min_size) {

      int line;
      int nbytes;
      char* ptr = (char*)c->in_buffer.c_str();
      memcpy((char*)&line, (ptr+1), sizeof(line));
      memcpy((char*)&nbytes, (ptr+1+sizeof(line)), sizeof(line));
      V(("> PDT_TEXTURE_LINE, line: %d, bytes: %d, still in buffer: %zu, buf_size: %zu\n", line, nbytes, c->in_buffer.size(), buf_size));
      if(buf_size >= nbytes) {
        V("> PDT_TEXTURE_LINE, AND ERASE SOME DATA!\n");
        unsigned char* line_data = new unsigned char[nbytes];
        memcpy(line_data, (ptr+1+sizeof(line)+sizeof(nbytes)), nbytes);
        PotatorTextureLine* p = new PotatorTextureLine();
        p->line = line;
        p->nbytes = nbytes;
        p->data = line_data;
        c->in_buffer.erase(0, (1+sizeof(line)+sizeof(nbytes)+nbytes)); // erase a PotatorTextureLine 
        c->addData(p);
      }
      else {
        V(("<< PDT_TEXTURE_LINE, we didn't receive all image bytes. buffer size: %zu, we need: %d\n", c->in_buffer.size(), nbytes));
        return;
      }
    }
    else if(c->in_buffer[0] == PDT_RESET) {
      V(("> PDT_RESET\n"));
      PotatorStreamData* p = new PotatorStreamData(PDT_RESET);
      c->in_buffer.erase(0, 1);
      c->addData(p);
    }
    else {
      V(("> NONE: We still have: %zu in buffer", c->in_buffer.size()));
      return;
    }
    buf_size = c->in_buffer.size();
#ifdef USE_LOOP
  }
#endif
}

// called when connected is closed.. reconnect
void on_geometry_close(void* user) {
  printf("Disconnected.. try to reconnect..\n");
  StreamingPotatorClient* c = static_cast<StreamingPotatorClient*>(user);
  c->client.reconnect(5000);
}

// -------------------------------
// POTATOR CLIENT
// -------------------------------
StreamingPotatorClient::StreamingPotatorClient(StreamingGeometryClient& client)
  :client(client)
{
}

StreamingPotatorClient::~StreamingPotatorClient() {
}

void StreamingPotatorClient::run() {
  client.setReadCallback(on_geometry_read, this);
  client.setCloseCallback(on_geometry_close, this);
  while(true) {
    client.update();
  }
}

void StreamingPotatorClient::addData(PotatorStreamData* d) {
  mutex.lock();
  data.push_back(d);
  mutex.unlock();
}


bool StreamingPotatorClient::hasData() {
  bool f = false;
  mutex.lock();
  f = data.size();
  mutex.unlock();
  return f;
}

// Copy points to data over to the given vector. 
// CALLER IS RESPONSIBLE TO FREE MEMORY
void StreamingPotatorClient::copyAndFlushData(std::vector<PotatorStreamData*>& result) {
  mutex.lock();
  std::copy(data.begin(), data.end(), std::back_inserter(result));
  data.clear();
  mutex.unlock();
}

void StreamingPotatorClient::reset() {
  return;
  mutex.lock();
  in_buffer.clear();
  mutex.unlock();
  /*
  mutex.lock();
  for(std::vector<PotatorStreamData*>::iterator it = data.begin(); it != data.end(); ++it) {
    delete *it;
  }

  data.clear();
  in_buffer.clear();
   mutex.unlock();
  printf("SteamingPotatorClient::reset().\n");
  */
}
