#ifndef ROXLU_STREAMING_GEOMETRY_CLIENTH
#define ROXLU_STREAMING_GEOMETRY_CLIENTH

#include <stdio.h>
#include <string>
#include <algorithm>

extern "C" {
  #include <uv.h>
}

uv_buf_t sgc_alloc(uv_handle_t* buffer, size_t size);
void sgc_on_read(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf);
void sgc_on_connect(uv_connect_t* con, int status);
void sgc_on_resolved(uv_getaddrinfo_t* resolver, int status, struct addrinfo* res);
void sgc_on_timer(uv_timer_t* timer, int status);

typedef void(*cb_geometry_client_read)(char* data, size_t len, void* user);
typedef void(*cb_geometry_client_close)(void* user);

class StreamingGeometryClient {
 public:
  StreamingGeometryClient();
  ~StreamingGeometryClient();
  bool setup(const std::string host, const std::string port);
  void setReadCallback(cb_geometry_client_read readCB, void* readUser);
  void setCloseCallback(cb_geometry_client_close closeCB, void* closeUser);
  void update();
  bool reconnect(int waitMillis = 0);
 public:
  bool doConnect();
 public:
  cb_geometry_client_read read_cb;
  cb_geometry_client_close close_cb;
  void* read_user;
  void* close_user;
  uv_connect_t connect;
  uv_getaddrinfo_t resolver;
  uv_tcp_t socket;
  uv_write_t write_req;
  uv_loop_t* loop;
  uv_timer_t timer;
  int wait_reconnect_millis;
  std::string server_host;
  std::string server_port;
};

#endif
