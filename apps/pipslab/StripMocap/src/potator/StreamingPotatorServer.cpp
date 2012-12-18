#include <potator/StreamingPotatorServer.h>

// ------------------------------------------------
// CALLBACKS
// ------------------------------------------------
void sps_on_new_connection(StreamingGeometryServer* serv, StreamingConnection* con, void* user) {
  StreamingPotatorServer* s = static_cast<StreamingPotatorServer*>(user);
  s->sendTextureInfo(s->tex_w,s->tex_h);
  printf("new connection callback, sending texture w: %d, and h: %d\n", s->tex_w, s->tex_h);
}

// ------------------------------------------------
// POTATOR SERVER 
// ------------------------------------------------

StreamingPotatorServer::StreamingPotatorServer(StreamingGeometryServer& server) 
  :server(server)
{
}

void StreamingPotatorServer::run() {

  server.setOnConnectionCallback(sps_on_new_connection, this);

  while(true) {
    server.update();
  }
}

void StreamingPotatorServer::sendVertexPosition(const float x, const float y, const float z) {
  printf("SEND: %f, %f, %f\n", x,y,z);
  PotatorVertexPosition p;
  p.x = x;
  p.y = y;
  p.z = z;
  p.type = PDT_VERTEX_POSITION;
  server.sendToAllClients((char*)&p, sizeof(p));
}

void StreamingPotatorServer::sendVertexPositions(
                                                 const float x1,
                                                 const float y1,
                                                 const float z1,
                                                 const float x2,
                                                 const float y2,
                                                 const float z2,
                                                 const int texLine
                                                 )
{
  PotatorVertexPositions p;
  p.x1 = x1;
  p.y1 = y1;
  p.z1 = z1;
  p.x2 = x2;
  p.y2 = y2;
  p.z2 = z2;
  p.texture_line = texLine;
  sendVertexPositions(p);
}

void StreamingPotatorServer::sendVertexPositions(PotatorVertexPositions& p) {
  server.sendToAllClients((char*)&p, sizeof(p));
}

void StreamingPotatorServer::sendVertexPositionsEndMarker() {
  char c = PDT_VERTEX_POSITIONS_END_MARKER;
  server.sendToAllClients((char*)&c, sizeof(c));
}

void StreamingPotatorServer::sendTextureInfo(int w, int h) {
  PotatorTextureInfo ti(w,h);
  server.sendToAllClients((char*)&ti, sizeof(ti));
}

void StreamingPotatorServer::sendTextureLine(int line, unsigned char* data, int nbytes) {
  std::vector<char> to_send;
  to_send.push_back(PDT_TEXTURE_LINE);

  char* ptr = (char*)&line;
  std::copy(ptr, ptr + sizeof(line), std::back_inserter(to_send));

  ptr = (char*)&nbytes;
  std::copy(ptr, ptr + sizeof(nbytes), std::back_inserter(to_send));

  ptr = (char*)data;
  std::copy(ptr, ptr + nbytes, std::back_inserter(to_send));

  server.sendToAllClients((char*)&to_send[0], to_send.size());
}

void StreamingPotatorServer::sendReset() {
  char c = PDT_RESET;
  server.sendToAllClients((char*)&c, sizeof(c));
}

void StreamingPotatorServer::addTask(PotatorTask* task) {
  mutex.lock();
  tasks.push_back(task);
  mutex.unlock();
}

void StreamingPotatorServer::setTextureSize(const int w, const int h) {
  tex_w = w;
  tex_h = h;
}
