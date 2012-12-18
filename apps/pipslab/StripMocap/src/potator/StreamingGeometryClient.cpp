#include <potator/StreamingGeometryClient.h>

//----------------------------------------------
// CONNECTION CALLBACKS
//----------------------------------------------

uv_buf_t sgc_alloc(uv_handle_t* buffer, size_t size) {
  return uv_buf_init((char*)malloc(size), size);
}

void sgc_on_read(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf) {
  StreamingGeometryClient* c = static_cast<StreamingGeometryClient*>(tcp->data);
  if(nread < 0) {
    printf("@TODO: disconnected, remove!\n");
    free(buf.base);
    if(c->close_cb) {
      c->close_cb(c->close_user);
    }
    return;
  }

  // Parse incoming data
  if(c->read_cb) {
    c->read_cb(buf.base, nread, c->read_user);
  }
  free(buf.base);
}

// reconnect timer.
void sgc_on_timer(uv_timer_t* timer, int status) {
  uv_timer_stop(timer);
  StreamingGeometryClient* c = static_cast<StreamingGeometryClient*>(timer->data);
  c->doConnect();
}

void sgc_on_connect(uv_connect_t* con, int status) {
  StreamingGeometryClient* c = static_cast<StreamingGeometryClient*>(con->data);
  if(status == -1) {
    printf("ERROR: sgc_on_connect: %s\n", uv_err_name(uv_last_error(c->loop)));
    if(c->close_cb) {
      printf("reconnect!\n");
      c->close_cb(c->close_user);
    }

    return;
  }
  int r = uv_read_start((uv_stream_t*)&c->socket, sgc_alloc, sgc_on_read);
  if(r != 0) {
    printf("ERROR: uv_read_start(): %s\n", uv_err_name(uv_last_error(c->loop)));
    return;
  }
}

void sgc_on_resolved(uv_getaddrinfo_t* resolver, int status, struct addrinfo* res) {
  StreamingGeometryClient* c = static_cast<StreamingGeometryClient*>(resolver->data);
  if(status == -1) {
    printf("ERROR: sgc_on_resolved: %s\n", uv_err_name(uv_last_error(c->loop)));
    return;
  }

  int r = uv_tcp_init(c->loop, &c->socket);
  if(r != 0) {
    printf("ERROR: uv_tcp_init: %s\n", uv_err_name(uv_last_error(c->loop)));
    return;
  }

  r = uv_tcp_connect(&c->connect, &c->socket, *(struct sockaddr_in*)res->ai_addr, sgc_on_connect);
  if(r != 0) {
    printf("ERROR: uv_tcp_connect: %s\n", uv_err_name(uv_last_error(c->loop)));
    return;
  }
  uv_freeaddrinfo(res);
}

//----------------------------------------------
// STREAMING GEOMETRY CLIENT
//----------------------------------------------
StreamingGeometryClient::StreamingGeometryClient()
  :read_cb(NULL)
  ,read_user(NULL)
  ,close_cb(NULL)
  ,close_user(NULL)
{
}

StreamingGeometryClient::~StreamingGeometryClient() {
}

bool StreamingGeometryClient::setup(const std::string host, const std::string port) {
  server_host = host;
  server_port = port;

  loop = uv_default_loop();
  if(!loop) {
    printf("ERROR: cannot uv_default_loop()\n");
    return false;
  }
  write_req.data = this;
  connect.data = this;
  socket.data = this;
  resolver.data = this;

  timer.data = this;
  uv_timer_init(loop, &timer);
  return reconnect();
}

bool StreamingGeometryClient::reconnect(int waitMillis) {
  if(waitMillis == 0) {
    wait_reconnect_millis = 5000; // default
    return doConnect();
  }
  else {
    wait_reconnect_millis = waitMillis;
    uv_timer_start(&timer, sgc_on_timer, wait_reconnect_millis, 0);
  }
  return true; 
}

bool StreamingGeometryClient::doConnect() {
  struct addrinfo hints;
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = 0;

  int r = uv_getaddrinfo(loop, &resolver, sgc_on_resolved, server_host.c_str(), server_port.c_str(), &hints);
  if(r) {
    printf("ERROR: cannot resolve: %s\n", uv_err_name(uv_last_error(loop)));
    return false;
  }
  return true;
}

void StreamingGeometryClient::update() {
  uv_run(loop);
}

void StreamingGeometryClient::setReadCallback(cb_geometry_client_read readCB, void* readUser) {
  read_cb = readCB;
  read_user = readUser;
}

void StreamingGeometryClient::setCloseCallback(cb_geometry_client_close closeCB, void* closeUser) {
  close_cb = closeCB;
  close_user = closeUser;
}

  

