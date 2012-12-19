#ifndef ROXLU_STREAMING_GEOMETRY_SERVERH
#define ROXLU_STREAMING_GEOMETRY_SERVERH

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

extern "C" {
#include <uv.h>
}

// @todo - handle on_close

class StreamingGeometryServer;

struct StreamingConnection {
  uv_tcp_t sock;
  uv_shutdown_t shutdown_req;
  uv_write_t write_req;
  StreamingGeometryServer* geom;
};


void sg_on_read(uv_stream_t* handle, ssize_t nread, uv_buf_t buf);
void sg_after_write(uv_write_t* req, int status);
uv_buf_t sg_alloc(uv_handle_t* hande, size_t size);
void sg_on_connection(uv_stream_t* server, int status);
void sg_on_close(uv_handle_t* handle);
void sg_on_shutdown(uv_handle_t* handle, int status);

typedef void(*cb_on_connection)(StreamingGeometryServer* server, StreamingConnection* con, void* user); /* gets called upon new connection */

class StreamingGeometryServer {
 public:
  StreamingGeometryServer();
  ~StreamingGeometryServer();
  bool setup(const std::string port);
  void update();
  void sendToAllClients(const char* data, size_t len);
  void setOnConnectionCallback(cb_on_connection conCB, void* conUser);
 public:
  std::vector<StreamingConnection*> clients;
  uv_loop_t* loop;
  cb_on_connection con_cb; /* called when we get a new connection */
  void* con_user; /* passed into the new connection callback */
  uv_tcp_t server;
  uv_write_t write_req;

};
#endif
