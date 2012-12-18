#include <potator/StreamingGeometryServer.h>

// -------------------------------------------------------------
// SERVER CALLBACKS
// -------------------------------------------------------------
uv_buf_t sg_alloc(uv_handle_t* hande, size_t size) {
  return uv_buf_init((char*)malloc(size), size);
}

void sg_after_write(uv_write_t* req, int status) {
  printf("StreamingGeometryServer, sg_after_write()\n");
}

void sg_on_close(uv_handle_t* handle) {
  printf("StreamingGeometryServer, sg_on_close()\n");
  /*
  StreamingConnection* con = static_cast<StreamingConnection*>(handle->data);
  std::vector<StreamingConnection*>::iterator it = std::find(con->geom->clients.begin(), con->geom->clients.end(), con);
  if(it != con->geom->clients.end()) {
    con->geom->clients.erase(it);
    delete con;
  }
  */
}

void sg_on_shutdown(uv_shutdown_t* handle, int status) {
  //  uv_close((uv_handle_t*)handle, sg_on_close);
}

void sg_on_read(uv_stream_t* handle, ssize_t nread, uv_buf_t buf) {
  StreamingConnection* con = static_cast<StreamingConnection*>(handle->data);
  //  free(buf.base);
  if(nread == -1) {
    if(uv_last_error(con->geom->loop).code == UV_EOF) {
      //      uv_close((uv_handle_t*)handle, sg_on_close);
      StreamingConnection* con = static_cast<StreamingConnection*>(handle->data);
      std::vector<StreamingConnection*>::iterator it = std::find(con->geom->clients.begin(), con->geom->clients.end(), con);
      if(it != con->geom->clients.end()) {
        con->geom->clients.erase(it);
        printf("removed!\n");
        delete con;
      }   
    }
  }
}

void sg_on_connection(uv_stream_t* server, int status) {
  int r = 0;
  StreamingGeometryServer* g = static_cast<StreamingGeometryServer*>(server->data);
  if(status != 0) {
    printf("ERROR: Cannot connect: %s\n", uv_strerror(uv_last_error(g->loop)));
    return;
  }

  StreamingConnection* con = new StreamingConnection();
  con->geom = g;
  con->shutdown_req.data = con;
  r = uv_tcp_init(g->loop, &con->sock);
  if(r != 0) {
    printf("ERROR: cannot call uv_tcp_init(): %s\n", uv_strerror(uv_last_error(g->loop)));
    delete con;
    return ;
  }

  con->sock.data = con;
  r = uv_accept(server, (uv_stream_t*)&con->sock);
  if(r != 0) {
    printf("ERROR: cannot call uv_accept(): %s\n", uv_strerror(uv_last_error(g->loop)));
    delete con;
    return;
  }

  r = uv_read_start((uv_stream_t*)&con->sock, sg_alloc, sg_on_read);
  if(r != 0) {
    printf("ERROR: cannot call uv_read_start(): %s\n", uv_strerror(uv_last_error(g->loop)));
    delete con;
    return;
  }
  printf("VERBOSE: new connection\n");
  g->clients.push_back(con);

  if(g->con_cb) {
    g->con_cb(g, con, g->con_user);
  }
}

// -------------------------------------------------------------
// STREAMING GEOMETRY 
// -------------------------------------------------------------

StreamingGeometryServer::StreamingGeometryServer() 
  :loop(NULL)
  ,con_cb(NULL)
  ,con_user(NULL)
{
}

StreamingGeometryServer::~StreamingGeometryServer() {
}

bool StreamingGeometryServer::setup() {
  server.data = this;
  write_req.data = this;
  loop = uv_default_loop();
  struct sockaddr_in addr = uv_ip4_addr("0.0.0.0", 3344);
  int r = 0;

  r = uv_tcp_init(loop, &server);
  if(r) {
    printf("ERROR: Cannot create streaming geometry server: %s\n", uv_strerror(uv_last_error(loop)));
    return false;
  }

  r = uv_tcp_bind(&server, addr);
  if(r) {
    printf("ERROR: Cannot bind streaming geometry server: %s\n", uv_strerror(uv_last_error(loop)));
    return false;
  }

  r = uv_listen((uv_stream_t*)&server, 128, sg_on_connection);
  if(r) {
    printf("ERROR: Cannot listen streaming geometry server: %s\n", uv_strerror(uv_last_error(loop)));
    return false;
  }

  return true;
}

void StreamingGeometryServer::sendToAllClients(const char* data, size_t len) {
  uv_buf_t buf;
  buf.base = (char*)data;
  buf.len = len;
  for(std::vector<StreamingConnection*>::iterator it = clients.begin(); it != clients.end(); ++it) {
    printf("sendingToAllClients, num: %zu\n", clients.size());
    StreamingConnection* con = *it;
    if(uv_write(&con->write_req, (uv_stream_t*)&con->sock, &buf, 1,sg_after_write)) {
      printf("ERROR: cannot uv_write()\n");
    }
  }
}

void StreamingGeometryServer::update() {
  uv_run(loop);
}

void StreamingGeometryServer::setOnConnectionCallback(cb_on_connection conCB, void* conUser) {
  con_cb = conCB;
  con_user = conUser;
}
